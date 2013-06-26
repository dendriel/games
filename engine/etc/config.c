#include "includes.h"

//	Denveloper Vitor Rozsa			//
//	E-mail: vitor.rozsa@hotmail.com	//

	//ANIMATAQUE ataque[100];
	BITMAP *_menu[10];
	BITMAP *_menuItens[10];
	struct MAPA mapa[50];			//	Declarar estrutura de mapas.	//
	
void cfg_iniciaMidia(void) {

    allegro_init();					//	Inicia Suporte Allegro.						//

    install_keyboard();				//	Inicia Suporte para E/S de Teclado.			//

    install_mouse();				//	Inicia Suporte para E/S de Mouse.			//

    install_timer();				//	Inicia Suporte para Operações com tempo.	//
    
    set_color_depth(COLOR_BITS);	//	Seta quantidade configuração de cor.	//

//    if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, MAX_X, MAX_Y, VMAX_X, VMAX_Y)) //FULLSCREEN MODE
    if(set_gfx_mode(GFX_SAFE, MAX_X, MAX_Y, VMAX_X, VMAX_Y))	//	Inicia janela para modo gráfico.	//
    {
        allegro_message("Erro ao carregar GFX (modo seguro falhou...)\nErro: %s", allegro_error);
        allegro_exit();
        exit(-1);
    }
    return;
}

void cfg_iniciaConfig (void) {
	   
	BUFFER = create_bitmap(MAX_X, MAX_Y);
	SBUFFER = create_bitmap(MAX_X, MAX_Y);
	
	mapaID = 1;				//	ID do mapa atual.				//
	charID = 0;
	
	//	Carrega Imagens.	//
	cfg_iniciaBitmaps();
    //	Carrega Fontes.		//
	cfg_iniciaFontes();
	return;
}
 
//	Iniciar Imagens.	//
void cfg_iniciaBitmaps(void) {
	
	int cont;
	char caminho[50];
	
//-------------Imagens de etc
	_ponteiro = carregaBitmap(_ponteiro, "../bmp/ponteiro.bmp");
    _menu_batalha = carregaBitmap(_menu_batalha, "../bmp/batalha/0.bmp");
    _batalha = carregaBitmap(_batalha, "../bmp/campo_batalha.bmp");
    
//-------------Imagens de Menu
	for( cont = 0; cont < 8; cont++) {
		sprintf(caminho, "../bmp/menu/%d.bmp",cont);
		_menu[cont] = carregaBitmap(_menu[cont], caminho);
	}
	_menuItens[0] = carregaBitmap(_menuItens[0], "../bmp/menu/itens.bmp");
	
    return;
}
//	Carregar Imagens.	//
BITMAP *carregaBitmap(BITMAP *bitmap, char endereco[50]) {
	
	if( bitmap = load_bitmap(endereco, NULL) ) {
		return(bitmap);
	}
	else {
		printf("Falha ao tentar acessar \"%s\"\n",endereco);
		allegro_exit();
		exit(-1);
	}
	return;
}

//	Iniciar Fontes.	//
void cfg_iniciaFontes(void) {
	
	sans_serif18 = carregaFonte(sans_serif18, "../bmp/fontes/sans_serif18.pcx");
	sans_serif20 = carregaFonte(sans_serif20, "../bmp/fontes/sans_serif20.pcx");
	return;
}
//	Carregar Fontes.//
FONT *carregaFonte(FONT *nome, char endereco[50]) {
	
	if( nome = load_font(endereco, palette, NULL) ) {
		return(nome);
	}
	else {
		printf("Erro ao carregar fonte \"%s\".\n", endereco);
		nome = font;
		return(nome);
	}
}

//ataque[1].BMP[0] = create_bitmap(30, 30); 
//blit(LOAD, ataque[1].BMP[0], 0, 0, 0, 0, 30, 30);   
//
//ataque[1].BMP[1] = create_bitmap(30, 30); 
//blit(LOAD, ataque[1].BMP[1], 30, 0, 0, 0, 30, 30);   
//
//ataque[1].BMP[2] = create_bitmap(30, 30); 
//blit(LOAD, ataque[1].BMP[2], 60, 0, 0, 0, 30, 30);      