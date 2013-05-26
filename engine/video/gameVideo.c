#include <allegro.h>
#include <pthread.h>
#include <stdbool.h>
#include <mqueue.h>
#include <errno.h>

#include "mixedAPI.h"
#include "mixedAPI_defines.h"
#include "alarm.h"
#include "alarm_defines.h"
#include "alarm_structs.h"
#include "debug.h"

#include "game_structs.h"
#include "game_defines.h"
#include "gameSystem_defines.h"
#include "gameVideo.h"
#include "gameVideo_defines.h"
#include "gameVideo_structs.h"
#include "gameVideo_screen.h"


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
static en_game_return_code gameVideo_set_update_screen_trigger(int *alarm_entry);

/**************************************************************************************************/
/**
 *	\b Remove the update screen alarm entry.
 *	\p Reference to the alarm (received at alarm creation).
 */
static void gameVideo_remove_update_screen_trigger(int alarm_entry);

/**************************************************************************************************/
/**
 *	\b Process game video requests.
 *	\p game_msg Data from the request.
 *	\r GAME_RET_SUCCESS for successfully message processing; GAME_RET_HALT_PROCESS if received a
 *	halting solicitation message.
 */
static en_game_return_code gameVideo_process_message(st_game_msg *game_msg);


/**************************************************************************************************/

static en_game_return_code gameVideo_set_update_screen_trigger(int *alarm_entry)
{
	en_alarm_ret_code ret;
	st_alarm alarm;
	st_game_msg *gvideo_msg;

	memset(&alarm, 0, sizeof(alarm));
	memset(&gvideo_msg, 0, sizeof(st_game_msg));

	/* Fill up alarm message. */
	alarm.wait_time = GAMEVIDEO_SCREEN_UPDATE_US;
	alarm.repeat = true;
	alarm.priority = GAME_MQUEUE_PRIO_0;
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

	/* Set the trigger alarm for drawing the buffer into screen. */
	ret = alarm_set_trigger(&alarm, alarm_entry);
	if (ret != ALARM_RET_SUCCESS) {
		debug("Failed to setup update screen trigger. ret: %d", ret);
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gameVideo_remove_update_screen_trigger(int alarm_entry)
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
	switch(id) {

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
				debug("Received halt module solicitation. Will exit...");
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
			debug("Unkown message type received. Type: %d", type);
		break;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gameVideo_thread(void *data)
{
	int alarm_entry;
	char recvd_data[sizeof(st_game_msg)];
	st_game_msg *game_msg = NULL;
	en_game_return_code ret;
	en_mixed_return_code mret;
	mqd_t gvideo_mqueue;

	memset(&recvd_data, 0, sizeof(recvd_data));

	/* Setup mqueue. */
	mret = mixed_open_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME, sizeof(st_game_msg));
	if (mret != MIXED_RET_SUCCESS) {
		exit(-1);
	}

	/* Setup update screen trigger. */
	ret = gameVideo_set_update_screen_trigger(&alarm_entry);
	if (ret != GAME_RET_SUCCESS) {
		exit(-1);
	}

	/* TODO: setup screen. */
	//BITMAP *BUFFER; 	//	*Double Buffering.	//
	//BITMAP *batalha_bmp = load_bitmap("./media/img/campo_batalha.bmp", NULL);
	//BUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);


	while(true) {
		ssize_t bytes_read;

        bytes_read = mq_receive(gvideo_mqueue, recvd_data, 1024, NULL);

		if (bytes_read == -1) {
			debug("Failed to receive message. errno: %d; msg: %s", errno, strerror(errno));
			continue;
		}
		game_msg = (st_game_msg *)recvd_data;

		//printf("bytes: %d - msg type: %d - msg id: %d\n", bytes_read, game_msg->type, game_msg->id);

		ret = gameVideo_process_message(game_msg);
		if (ret == GAME_RET_HALT) {
			/* Exiting message received. */
			break;
		}
//		clear(BUFFER);
//		draw_sprite(BUFFER, batalha_bmp, i, i);
//		draw_sprite(screen, BUFFER, 0, 0);
//		i+=1;
	}

	/* Free the resources. */
	mixed_close_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);
	gameVideo_remove_update_screen_trigger(alarm_entry);
}


/*************************************************************************************************/

en_game_return_code gameVideo_init(void)
{
	pthread_t video_th;

	pthread_create(&video_th, NULL, (void *)gameVideo_thread, NULL);

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

