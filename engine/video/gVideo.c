#include <fcntl.h>
#include <allegro.h>
#include <pthread.h>
#include <stdbool.h>
#include <mqueue.h>
#include <errno.h>

#include "gVideo.h"
#include "gVideo_defines.h"
#include "gVideo_structs.h"
#include "gVideo_screen.h"
#include "game_structs.h"
#include "game_defines.h"
#include "gSystem_defines.h"

#include "mixedAPI.h"
#include "mixedAPI_defines.h"
#include "alarm.h"
#include "alarm_defines.h"
#include "alarm_structs.h"

#include "debug.h"


/**************************************************************************************************/
/**
 *	\d Processing thread. Receive and process message commands.
 *	\p data Unused.
 */
static void gameVideo_thread(void *data);

/**************************************************************************************************/
/**
 *	\b Create an periodical alarm to trigger the update of the screen.
 *	\p alarm_entry Filled with a reference to the created alarm.
 *	\r GAME_RET_SUCCESS if could create the alarm; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameVideo_set_screen_trigger(int *alarm_entry);

/**************************************************************************************************/
/**
 *	\b Remove the update screen alarm entry.
 *	\p Reference to the alarm (received at alarm creation).
 */
static void gameVideo_remove_screen_trigger(int alarm_entry);

/**************************************************************************************************/
/**
 *	\b Process game video requests.
 *	\p game_msg Data from the request.
 *	\r GAME_RET_SUCCESS for successfully message processing; GAME_RET_HALT_PROCESS if received a
 *	halting solicitation message.
 */
static en_game_return_code gameVideo_process_message(st_game_msg *game_msg);


/**************************************************************************************************/

static en_game_return_code gameVideo_set_screen_trigger(int *alarm_entry)
{
	en_alarm_ret_code ret;
	st_alarm alarm;
	st_game_msg *gvideo_msg;

	memset(&alarm, 0, sizeof(alarm));
	memset(&gvideo_msg, 0, sizeof(st_game_msg));

	/* Fill up alarm message. */
	alarm.wait_time = GAMEVIDEO_SCREEN_UPDATE_US;
	alarm.repeat = true;
	alarm.priority = GAME_MQUEUE_PRIO_1;
	strncpy(alarm.dest_mqueue, GAMEVIDEO_MQUEUE_NAME, sizeof(alarm.dest_mqueue));

	gvideo_msg = (st_game_msg *) malloc(sizeof(st_game_msg));
	if (!gvideo_msg) {
		debug("Failed to allocate memory for gvideo_msg.");
		return GAME_RET_ERROR;
	}

	memset(gvideo_msg, 0, sizeof(*gvideo_msg));
	gvideo_msg->type = GAME_ACTION_UPDATE_SCREEN;
	gvideo_msg->id = GAMEVIDEO_MOD_ID;
	alarm.data = (void *)gvideo_msg;
	alarm.data_size = sizeof(st_game_msg);

	/* Set the trigger alarm for drawing the buffer into screen. */
	ret = alarm_set_trigger(&alarm, alarm_entry);
	if (ret != ALARM_RET_SUCCESS) {
		debug("Failed to setup update screen trigger. ret: %d", ret);
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gameVideo_remove_screen_trigger(int alarm_entry)
{
	en_alarm_ret_code ret;

	ret = alarm_remove_trigger(alarm_entry);
	if (ret != ALARM_RET_SUCCESS) {
		debug("Failed to remove update screen alarm entry.");
	}
}

/**************************************************************************************************/

static void gameVideo_processe_brain_message(st_game_msg *game_msg)
{
	en_game_msg_type type;

	type = game_msg->type;
	switch (type) {

		case GAME_ACTION_ADD_SCREEN_ELEM:
			debug("Received solicitation to add an element to the visual list.");
			int index;
			index = gameVideo_screen_add_elem(&game_msg->v_elem);
			if (index == GAME_RET_ERROR) {
				critical("Failed to add element type %d into screen list.", game_msg->v_elem.type);
				game_msg->v_elem.key = GVIDEO_INVALID_KEY;
			}
			else {
				debug("Item type %d with index %d was added to visual list.", game_msg->v_elem.type, index);
				game_msg->v_elem.key = index;
			}
		break;

		default:
			debug("Invalid message type received from gameBrain module. type: %d", type);
		break;
	}

	// Re-send the packet to the request with the same packet.

	return;
}

/**************************************************************************************************/

static en_game_return_code gameVideo_process_message(st_game_msg *game_msg)
{
	en_game_msg_type type;
	en_game_mod_id id;

	type = game_msg->type;
	id = game_msg->id;

	/* Discovers the request of the message and processes acordingly. */
	switch (id) {

		case GAMEVIDEO_MOD_ID:
			if (type == GAME_ACTION_UPDATE_SCREEN) {
				gameVideo_screen_update();
			}
			else {
				debug("Unknown message received from gameVideo module. Type: %d.\n", type);
			}
		break;

		case GAMESYSTEM_MOD_ID:
			if (type == GAME_ACTION_HALT_MODULE) {
				debug("Received halt solicitation. Will exit...");
				return GAME_RET_HALT;
			}
			else {
				debug("Unknown message received from gameSystem module. Type: %d.\n", type);
			}
		break;

		case GAMEBRAIN_MOD_ID:
			gameVideo_processe_brain_message(game_msg);
		break;

		default:
			debug("Received message from invalid module. id: %d", id);
		break;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gameVideo_thread(void *data)
{
	int alarm_entry;
	char recvd_data[GAME_MQUEUE_RECV_BUF_SIZE];
	ssize_t bytes_read;
	st_game_msg *game_msg = NULL;
	en_game_return_code ret;
	en_mixed_return_code mret;
	mqd_t gvideo_mqueue;

	/* Setup gameVideo sub-module "screen". */
	debug("Initialize gameVideo screen sub-module.");
	ret = gameVideo_screen_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize gameVideo screen sub-module.");
		exit(-1);
	}

	/* Setup update screen trigger. */
	debug("Setup update screen alarm.");
	ret = gameVideo_set_screen_trigger(&alarm_entry);
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to setup screen alarm.");
		gameVideo_screen_finish();
		exit(-1);
	}

	/* Setup mqueue. */
	debug("Setup mqueue for receiving requests.");
	mret = mixed_create_mqueue(&gvideo_mqueue,
							GAMEVIDEO_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_RECV_MODE);
	if (mret != MIXED_RET_SUCCESS) {
		debug("Failed to setup mqueue.");
		gameVideo_remove_screen_trigger(alarm_entry);
		gameVideo_screen_finish();
		exit(-1);
	}

	while(true) {

		memset(&recvd_data, 0, sizeof(recvd_data));
        bytes_read = mq_receive(gvideo_mqueue, recvd_data, GAME_MQUEUE_RECV_BUF_SIZE, NULL);

		if (bytes_read == -1) {
			debug("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gameVideo_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			gameVideo_remove_screen_trigger(alarm_entry);
			/* Exiting message received. */
			break;
		}
	}

	/* Free the resources. */
	mixed_close_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);
	gameVideo_screen_finish();
	pthread_exit(0);
}


/*************************************************************************************************/

en_game_return_code gameVideo_init(pthread_t *thread_id)
{
	int ret;

	ret = pthread_create(thread_id, NULL, (void *)gameVideo_thread, NULL);
	if (ret != 0) {
		debug("Failed to create video module thread.");
		return GAME_RET_ERROR;
	}

//	BITMAP *BUFFER; 	//	*Double Buffering.	//
//	BITMAP *SBUFFER;
	   
//	BUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);
//	SBUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);
	
	//	Carrega Imagens.	//
//	cfg_iniciaBitmaps();


    //	Carrega Fontes.		//
	//cfg_iniciaFontes();
	return GAME_RET_SUCCESS;
}

//	Iniciar Imagens.	//
//void cfg_iniciaBitmaps(void) {
//	
//	int cont;
//	char caminho[50];
//	
////-------------Imagens de etc
//	_ponteiro = carregaBitmap(_ponteiro, "../bmp/ponteiro.bmp");
//    _menu_batalha = carregaBitmap(_menu_batalha, "../bmp/batalha/0.bmp");
//    _batalha = carregaBitmap(_batalha, "../bmp/campo_batalha.bmp");
//    
////-------------Imagens de Menu
////	for( cont = 0; cont < 8; cont++) {
////		sprintf(caminho, "../bmp/menu/%d.bmp",cont);
////		_menu[cont] = carregaBitmap(_menu[cont], caminho);
////	}
////	_menuItens[0] = carregaBitmap(_menuItens[0], "../bmp/menu/itens.bmp");
////	
//    return;
//}
//	Carregar Imagens.	//

//BITMAP *carregaBitmap(BITMAP *bitmap, char endereco[50]) {
//	
//	if( bitmap = load_bitmap(endereco, NULL) ) {
//		return(bitmap);
//	}
//	else {
//		printf("Falha ao tentar acessar \"%s\"\n",endereco);
//		allegro_exit();
//		exit(-1);
//	}
//	return;
//}

//	Iniciar Fontes.	//
//void cfg_iniciaFontes(void) {
//	
//	sans_serif18 = carregaFonte(sans_serif18, "../bmp/fontes/sans_serif18.pcx");
//	sans_serif20 = carregaFonte(sans_serif20, "../bmp/fontes/sans_serif20.pcx");
//	return;
//}

//	Carregar Fontes.//
//FONT *carregaFonte(FONT *nome, char endereco[50]) {
//	
//	if( nome = load_font(endereco, palette, NULL) ) {
//		return(nome);
//	}
//	else {
//		printf("Erro ao carregar fonte \"%s\".\n", endereco);
//		nome = font;
//		return(nome);
//	}
//}

