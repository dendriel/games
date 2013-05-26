#include <allegro.h>
#include <pthread.h>
#include <stdbool.h>
#include <mqueue.h>
#include <errno.h>

#include "linked_list.h"
#include "linked_listStructs.h"
#include "alarm.h"
#include "alarm_defines.h"
#include "alarm_structs.h"
#include "debug.h"

#include "game_defines.h"
#include "gameSystem_defines.h"
#include "gameVideo.h"
#include "gameVideo_defines.h"
#include "gameVideo_structs.h"


/**************************************************************************************************/
/**
 *	\d Processing thread. Receive and process message commands.
 *	\p data Unused.
 */
static void gameVideo_thread(void *data);

/**************************************************************************************************/
/**
 *	\b Allocate memory for the visual list.
 *	\p visual_list Reference to the visual list.
 *	\r GAME_RET_SUCCESS for correctly list creation;
 *	GAME_RET_ERROR if could not create the list.
 */
static en_game_return_code gameVideo_visual_list_create(st_list *visual_list);

/**************************************************************************************************/
/**
 *	\d Insert the first item in the visual list.
 *	\p visual_list Reference to the visual list that will receive the element.
 *	\p visual_elem The element to be inserted.
 *	\r GAME_RET_SUCCESS for correctly operation; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameVideo_visual_list_add_first_elem(
st_list		*visual_list,
st_visual	*visual_elem);

/**************************************************************************************************/
/**
 *	\d Insert the first item in the visual list.
 *	\p visual_list Reference to the visual list that will receive the element.
 *	\p visual_elem The element to be inserted.
 *	\r GAME_RET_SUCCESS for correctly operation; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameVideo_visual_list_add_elem(
st_list *visual_list,
st_visual *visual_elem);

/**************************************************************************************************/
/**
 *	\b Create an periodical alarm to trigger the update of the screen.
 *	\p alarm_entry Filled with a reference to the created alarm.
 *	\r GAME_RET_SUCCESS if could create the alarm; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameVideo_set_update_screen_trigger(int *alarm_entry);

/**************************************************************************************************/
/**
 *	\b Open a mqueue to receive video related solicitations.
 *	\p gvideo_mqueue Used to hold the mqueue reference.
 *	\r GAME_RET_SUCCESS if could open the mqueue; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameVideo_open_mqueue(mqd_t *gvideo_mqueue);

/**************************************************************************************************/
/**
 *	\b Close the mqueue.
 *	\p gvideo_mqueue Reference to the mqueue that will be closed.
 *	\r GAME_RET_SUCCESS if could close the mqueue; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameVideo_close_mqueue(mqd_t *gvideo_mqueue);

/**************************************************************************************************/

static en_game_return_code gameVideo_open_mqueue(mqd_t *gvideo_mqueue)
{
	struct mq_attr attr;

	/* Initialize the queue attributes */
	attr.mq_flags = 0;
	attr.mq_maxmsg = 1000;
	attr.mq_msgsize = sizeof(st_visual);
	attr.mq_curmsgs = 0;
	
	/* Create the message queue. */
	*gvideo_mqueue = mq_open(GAMEVIDEO_QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
	if (*gvideo_mqueue == GAME_MQUEUE_FAILED) {
		debug("Failed to open mqueue. errno: %d; msg: %s", errno, strerror(errno));
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gameVideo_close_mqueue(mqd_t *gvideo_mqueue)
{
	int ret;

	/* Close the message queue. */
	ret = mq_close(*gvideo_mqueue);
	if (ret != 0) {
		debug("Failed to close mqueue. errno: %d; msg: %s", errno, strerror(errno));
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gameVideo_set_update_screen_trigger(int *alarm_entry)
{
	en_alarm_ret_code ret;
	st_alarm alarm;
	st_game_msg gvideo_msg;

	memset(&alarm, 0, sizeof(alarm));
	memset(&gvideo_msg, 0, sizeof(st_game_msg));

	/* Fill up game message (data for alarm message). */
	gvideo_msg.action = GAME_UPDATE_SCREEN;

	/* Fill up alarm message. */
	alarm.wait_time = GAMEVIDEO_SCREEN_UPDATE_US;
	alarm.repeat = true;
	alarm.priority = GAME_MQUEUE_PRIO_0;
	strncpy(alarm.dest_mqueue, GAMEVIDEO_QUEUE_NAME, sizeof(alarm.dest_mqueue));

	alarm.data = (void *)&gvideo_msg;

	/* Set the trigger alarm for drawing the buffer into screen. */
	ret = alarm_set_trigger(&alarm, alarm_entry);
	if (ret != ALARM_RET_SUCCESS) {
		debug("Failed to setup update screen trigger. ret: %d", ret);
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static void gameVideo_thread(void *data)
{
	int ret;
	int alarm_entry;
	en_game_return_code gret;
	mqd_t gvideo_mqueue;
	int alarm_entry;
	
	gret = gameVideo_open_mqueue(&gvideo_mqueue);
	if (rget != GAME_RET_SUCCESS) {
		exit(-1);
	}

	gret = gameVideo_set_update_screen_trigger(&alarm_entry);
	if (gret != GAME_RET_SUCCESS) {
		exit(-1);
	}

	BITMAP *BUFFER; 	//	*Double Buffering.	//
	BITMAP *batalha_bmp = load_bitmap("./media/img/campo_batalha.bmp", NULL);

	BUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);

	int i = 0;
	st_game_msg recvd_msg;
	memset(&recvd_msg, 0, sizeof(recvd_msg));

	while(true) {
		ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(gvideo_mqueue, recvd_msg, sizeof(recvd_msg), NULL);

		printf("received a message!! action: %d\n", recvd_msg.action);

//		clear(BUFFER);
//		draw_sprite(BUFFER, batalha_bmp, i, i);
//		draw_sprite(screen, BUFFER, 0, 0);
//		i+=1;
//		sleep(0.05);
	}
}

/**************************************************************************************************/

static en_game_return_code gameVideo_visual_list_create(st_list *visual_list)
{
	visual_list = (st_list *)malloc(sizeof(st_list));
	if (!visual_list) {
		debug("Failed to allocate memory for st_list.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gameVideo_visual_list_add_first_elem(
st_list		*visual_list,
st_visual	*visual_elem)
{
	int ret;
	st_list_item *list_item = NULL;

	if (!visual_list || !visual_elem) {
		debug("Null parameter received.");
		return GAME_RET_ERROR;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		debug("Failed to allocate memory for st_list_item.");
		return GAME_RET_ERROR;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = visual_elem;

	ret = list_add_first(visual_list, list_item);
	if (ret != 0) {
		debug("Failed to add first element to visual_list.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static en_game_return_code gameVideo_visual_list_add_elem(
st_list *visual_list,
st_visual *visual_elem)
{
	int ret;
	st_list_item *list_item = NULL;

	if (!visual_list || !visual_elem) {
		debug("Null parameter received.");
		return GAME_RET_ERROR;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		debug("Failed to allocate memory for st_list_item.");
		return GAME_RET_ERROR;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = visual_elem;

	ret = list_add_next(visual_list, list_item);
	if (ret != 0) {
		debug("Failed to add element to visual_list.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
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

