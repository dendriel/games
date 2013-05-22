#include <allegro.h>

#include "gameVideo.h"
#include "game_defines.h"
#include "gameSystem_defines.h"


/*************************************************************************************************/

game_return_code gameVideo_init(void)
{
//	BITMAP *BUFFER; 	//	*Double Buffering.	//
//	BITMAP *SBUFFER;
	   
//	BUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);
//	SBUFFER = create_bitmap(GAMESYSTEM_MAX_X, GAMESYSTEM_MAX_Y);
	
	//	Carrega Imagens.	//
//	cfg_iniciaBitmaps();

	BITMAP *batalha_bmp = load_bitmap("./media/img/campo_batalha.bmp", NULL);

	draw_sprite(screen, batalha_bmp, 0, 0);

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

