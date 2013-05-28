#include "includes.h"

struct PERSONAGEM heroi;
struct MAPA mapa[50];
ITEM item[100];

				//ID do Mapa, 		-12 -> 0,	    -9 -> 0  	//
void pcl_carregaMapa (int mapa_id, int heroi_mapaPosH, int heroi_mapaPosV, int LOOK) {
	
	switch(mapa_id) {
	
	case 1:
		map_Mapa1(heroi_mapaPosH, heroi_mapaPosV, LOOK);
		break;
		
	case 2:
		map_Caverna1(heroi_mapaPosH, heroi_mapaPosV, LOOK);
		break;
		
	default:
		printf("Erro ao carregar mapa.\n");
		break;
	
	}
	return;
}

void pcl_atualizaMapa(void){
	
	int pos;
	
	if (heroi.LOOK == 0) pos = norte;
	if (heroi.LOOK == 1) pos = leste;
	if (heroi.LOOK == 2) pos = sul;
	if (heroi.LOOK == 3) pos = oeste;
	
	
	draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
	draw_sprite(BUFFER, heroi.BMP[pos],  (heroi.POSH), heroi.POSV);
	draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
	draw_sprite(screen, BUFFER, 0, 0);
	return;
}

//	Define todas as funções do personagem.	//

void pcl_principal(int id) {

	do {
	
		if( (key[KEY_UP]) || (key[KEY_W]) ) {
			andar(NORTE);
		}
	
		if( (key[KEY_RIGHT]) || (key[KEY_D]) ) {
			andar(LESTE);
		}

		if( (key[KEY_DOWN]) || (key[KEY_S]) ) {
			andar(SUL);
		}		
	
		if( (key[KEY_LEFT]) || (key[KEY_A]) ) {
			andar(OESTE);
		}		

		if(key[KEY_ESC]) {
			key[KEY_ESC] = 0;
			menu();
			draw_sprite(screen, BUFFER, 0, 0);
		}
	
		if(key[KEY_ENTER]) {
			key[KEY_ENTER] = 0;
			//batalha();
			draw_sprite(screen, BUFFER, 0, 0);
		}
		
		if(key[KEY_SPACE]) {
			key[KEY_SPACE] = 0;
			teclaAcao();
			draw_sprite(screen, BUFFER, 0, 0);
		}
		
	}while (!key[KEY_TAB]);
}

void teclaAcao(void) {
	
	int hh, hv;
	hh = heroi.MapaPos[0];
	hv = heroi.MapaPos[1] + 1;
	
	//LOOK
	
	switch(heroi.LOOK) {
	
	case 0: // norte
			
			//	Pegar Item.	//
			if(mapa[mapaID].matriz[hh][hv-1].acao == 2) {
				ac_encontraItem(hh, (hv - 1) );
			}
			
			if(mapa[mapaID].matriz[hh][hv].acao == 3) {
				printf("lol\n");
				ac_teletransporte(hh, hv);				
			}
		
		break;
		
	case 1: // leste
		
		if(mapa[mapaID].matriz[hh+1][hv].acao == 2) {
			ac_encontraItem( (hh + 1), hv);
		}
		
		if(mapa[mapaID].matriz[hh][hv].acao == 3) {
			ac_teletransporte(hh, hv);				
		}
		
		break;
		
	case 2: // sul
		
		if(mapa[mapaID].matriz[hh][hv+1].acao == 2) {
			ac_encontraItem(hh, (hv + 1) );
		}
		
		if(mapa[mapaID].matriz[hh][hv].acao == 3) {
			printf("lol2\n");
			ac_teletransporte(hh, hv);				
		}
		
		break;
		
	case 3: // oeste
		
		if(mapa[mapaID].matriz[hh-1][hv].acao == 2) {
			ac_encontraItem( (hh - 1), hv );
		}
		
		if(mapa[mapaID].matriz[hh][hv].acao == 3) {
			ac_teletransporte(hh, hv);				
		}
		
		break;
		
	}
	return;
}

void andar(int direcao) {
	
	int hh, hv;
	hh = heroi.MapaPos[0];
	hv = heroi.MapaPos[1]+1;
	
	switch(direcao) {
/**********************************/
	case NORTE:
		
		hv--;
		switch (mapa[mapaID].matriz[hh][hv].acao) {

		case 0:
			if( (heroi.MapaPos[1] <= 9) || (heroi.MapaPos[1] > (mapa[mapaID].MV - 10)) )
			{
				moveChar(NORTE);
			}
			else{ moveMapa(NORTE);}
			break;
			
		case 1:
			heroi.LOOK = 0;
			mudaDirecao(norte);
			break;
			
		case 2:
			heroi.LOOK = 0;
			mudaDirecao(norte);
			break;
			
		case 3:
			if( (heroi.MapaPos[1] <= 9) || (heroi.MapaPos[1] > (mapa[mapaID].MV - 10)) )
			{
				moveChar(NORTE);
			}
			else{ moveMapa(NORTE);}
			break;
			
			
		default:
			break;
		}	
	break; // Norte Break //
/**********************************/
	case LESTE:
		
		hh++;
		switch (mapa[mapaID].matriz[hh][hv].acao) {
		case 0:
			
			if( (heroi.MapaPos[0] >= (mapa[mapaID].MH - 13))  || (heroi.MapaPos[0] < 12) )
			{
				moveChar(LESTE);
			}
			else{ moveMapa(LESTE); }
			break;
			
		case 1:
			heroi.LOOK = 1;
			mudaDirecao(leste);
			break;
			
		case 2:
			heroi.LOOK = 1;
			mudaDirecao(leste);
			break;
			
		case 3:
			if( (heroi.MapaPos[0] >= (mapa[mapaID].MH - 13))  || (heroi.MapaPos[0] < 12) )
			{
				moveChar(LESTE);
			}
			else{ moveMapa(LESTE);}
			break;
			
		default:
			break;
		}	
	break; // Leste Break //
/**********************************/
	case SUL:
		
		hv++;
		switch (mapa[mapaID].matriz[hh][hv].acao) {
		case 0:
			
			if( (heroi.MapaPos[1] >= (mapa[mapaID].MV - 10)) || (heroi.MapaPos[1] < 9) )
			{
				moveChar(SUL);
			}
			else{ moveMapa(SUL); }
			break;
			
		case 1:
			heroi.LOOK = 2;
			mudaDirecao(sul);
			break;
			
		case 2:
			heroi.LOOK = 2;
			mudaDirecao(sul);
			break;
			
		case 3:
			
			if( (heroi.MapaPos[1] >= (mapa[mapaID].MV - 10)) || (heroi.MapaPos[1] < 9) )
			{
				moveChar(SUL);
			}
			else{ moveMapa(SUL); }
			break;
			
		default:
			break;
		}	
		break; // Sul Break //
	
/**********************************/
	case OESTE:
		
		hh--;
		switch (mapa[mapaID].matriz[hh][hv].acao) {
		case 0:
			
			if( (heroi.MapaPos[0] <= 12) || (heroi.MapaPos[0] > (mapa[mapaID].MH - 13)) )
			{
				moveChar(OESTE);
			}
			else{ moveMapa(OESTE); }
			break;
			
		case 1:
			heroi.LOOK = 3;
			mudaDirecao(oeste);

			break;
			
		case 2:
			heroi.LOOK = 3;
			mudaDirecao(oeste);
			break;
			
		case 3:
			if( (heroi.MapaPos[0] <= 12) || (heroi.MapaPos[0] > (mapa[mapaID].MH - 13)) )
			{
				moveChar(OESTE);
			}
			else{ moveMapa(OESTE); }
			break;
			
		default:
			break;
		}	
		break; // Oeste Break //
	}
	
}

void mudaDirecao (int pos) {
	
	clear(BUFFER);
	draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
	draw_sprite(BUFFER, heroi.BMP[pos],  heroi.POSH, heroi.POSV);
	draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
	draw_sprite(screen, BUFFER, 0, 0);			
	return;
}