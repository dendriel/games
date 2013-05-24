#include <allegro.h>
#include <pthread.h>
#include <stdbool.h>
#include <mqueue.h>

#include "linked_list.h"
#include "linked_listStructs.h"
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
static game_return_code gameVideo_visual_list_create(st_list *visual_list);

/**************************************************************************************************/
/**
 *	\d Insert the first item in the visual list.
 *	\p visual_list Reference to the visual list that will receive the element.
 *	\p visual_elem The element to be inserted.
 *	\r GAME_RET_SUCCESS for correctly operation; GAME_RET_ERROR otherwise.
 */
static game_return_code gameVideo_visual_list_add_first_elem(
st_list		*visual_list,
st_visual	*visual_elem);

/**************************************************************************************************/
/**
 *	\d Insert the first item in the visual list.
 *	\p visual_list Reference to the visual list that will receive the element.
 *	\p visual_elem The element to be inserted.
 *	\r GAME_RET_SUCCESS for correctly operation; GAME_RET_ERROR otherwise.
 */
static game_return_code gameVideo_visual_list_add_elem(
st_list *visual_list,
st_visual *visual_elem);

/*************************************************************************************************/

game_return_code gameVideo_init(void)
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

/**************************************************************************************************/

static void gameVideo_thread(void *data)
{
	int ret;
	mqd_t gvideo_mqueue;
	struct mq_attr attr;
//	char buffer[MAX_SIZE + 1];
//	int must_stop = 0;
	
	/* initialize the queue attributes */
	attr.mq_flags = 0;
	attr.mq_maxmsg = 1000;
	attr.mq_msgsize = 1024; //sizeof(st_visual);
	attr.mq_curmsgs = 0;
	
	/* Create the message queue. */
	gvideo_mqueue = mq_open(GAMEVIDEO_QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
	if (gvideo_mqueue == (mqd_t)-1) { //TODO: create a define for (mqd_t -1)
		debug("Failed to open mqueue. errno: %d; msg: %s", errno, strerror(errno));
		exit(-1);
	}

	/* Close the message queue. */
	ret = mq_close(gvideo_mqueue);
	if (ret != 0) {
		debug("Failed to close mqueue. errno: %d; msg: %s", errno, strerror(errno));
		exit(-1);
	}


	BITMAP *BUFFER; 	//	*Double Buffering.	//
	BITMAP *batalha_bmp = load_bitmap("./media/img/campo_batalha.bmp", NULL);

	BUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);

	int i = 0;
	char buffer[1024];
	while(true) {
		ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(gvideo_mqueue, buffer, 1024, NULL);
        //CHECK(bytes_read >= 0);

        buffer[bytes_read] = '\0';

		clear(BUFFER);
		draw_sprite(BUFFER, batalha_bmp, i, i);
		draw_sprite(screen, BUFFER, 0, 0);
		i+=1;
		sleep(0.05);
	}
}

/**************************************************************************************************/

static game_return_code gameVideo_visual_list_create(st_list *visual_list)
{
	visual_list = (st_list *)malloc(sizeof(st_list));
	if (!visual_list) {
		debug("Failed to allocate memory for st_list.");
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/**************************************************************************************************/

static game_return_code gameVideo_visual_list_add_first_elem(
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

static game_return_code gameVideo_visual_list_add_elem(
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

