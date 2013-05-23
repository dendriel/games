#include <allegro.h>
#include <pthread.h>
#include <stdbool.h>

#include "gameVideo.h"
#include "game_defines.h"
#include "gameSystem_defines.h"


/*************************************************************************************************/

/**
 * \d Processing thread. Receive and process message commands.
 * \p data Unused.
 */
static void gameVideo_thread(void *data);

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

static void gameVideo_thread(void *data)
{
	BITMAP *BUFFER; 	//	*Double Buffering.	//
	BITMAP *batalha_bmp = load_bitmap("./media/img/campo_batalha.bmp", NULL);

	BUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);

	int i = 0;
	while(true) {
		clear(BUFFER);
		draw_sprite(BUFFER, batalha_bmp, i, i);
		draw_sprite(screen, BUFFER, 0, 0);
		i+=5;
		sleep(1);
	}
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

