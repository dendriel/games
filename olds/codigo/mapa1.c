#include "includes.h"

	char end[50];
	struct MAPA mapa[50];
	struct PERSONAGEM heroi;
	
void map_Mapa1(int hposh, int hposv, int LOOK) {
	
	int h, v, i, j;
	int mh, mv;
	
	mapa_id = 1;			//	ID do mapa atual.				//
	mapaID = 1;				//	ID do mapa atual.				//
	
	//	Carrega primeiro Layer.	//
	mapa[mapaID].BMP[0] = carregaBitmap(mapa[mapaID].BMP[0], "../bmp/mapa1-1.bmp");
	//	Carrega segundo Layer.	//
	mapa[mapaID].BMP[1] = carregaBitmap(mapa[mapaID].BMP[0], "../bmp/mapa1-2.bmp");

	mapa[mapaID].largura = 2400;
	mapa[mapaID].altura  = 1760;
	
	mapa[mapaID].MH = (mapa[mapaID].largura / 32);
	mapa[mapaID].MV = (mapa[mapaID].altura / 32);
//_______________________________________________________________________________________________________________________
//-----------------------------------------------------------------------------------------------------------------------
	mh = ( (12 - hposh) * 32);			//	Calcula quanto o mapa tera que se mover na horizontal.						//
	mv = ( (9  - hposv) * 32);			//	Calcula quanto o mapa tera que se mover na vertical.						//
	
	if( mh >= 0) mh = 0; else if( mh < -1600) mh = - 1600;	//	Faz verificação se o mapa está no limite, então move o personagem.	//
	if( mv >= 0) mv = 0; else if( mv < -1152) mv = - 1152;	//	Faz verificação se o mapa está no limite, então move o personagem.	//
	
	mapa[mapaID].posx = mh;				//	Adicionar a posição horizontal ao mapa atual.								//
	mapa[mapaID].posy = mv;				//	Adicionar a posição vertical ao mapa atual.									//
 	
	heroi.MapaPos[0] = hposh;			//	Adicionar a coordenada horizontal ao heroi.									//
	heroi.MapaPos[1] = hposv;			//	Adicionar a coordenada vertical ao heroi.									//

	mh = ( (12 - hposh) * 32);			//	Calcula a coordenada horizontal na tela do heroi.							//
	mv = ( (9  - hposv) * 32);			//	Calcula a coordenada vertical na telal do heroi.							//
	
	if(mh >= 0) mh = mh*-1; else if(mh < -1600) mh = ( (mh*-1) - 1600 ); else mh = 0;	//	Verifica se a coordenada não está centrada na tela.	//
	if(mv >= 0) mv = mv*-1;	else if(mv < -1152) mv = ( (mv*-1) - 1152 ); else mv = 0;	//	Verifica se a coordenada não está centrada na tela.	//

	heroi.POSH = 384 + mh;				//	Salva a coordenada horizontal na tela do heroi.								//
    heroi.POSV = 288 + mv;				//	Salva a coordenada vertical na tela do heroi.								//
        
    heroi.LOOK = LOOK;					//	Seta o ponto cardeal para onde o heroi estará voltado. 0 = SUL				//
//_______________________________________________________________________________________________________________________     
	
	FILE *arq;
	arq = fopen("../bmp/mapa1.txt", "r");
	if(!arq)
	{
		printf("Falha ao carregar Layer 3.\n");
	}
	else{ 
		for(i = 0; i < 75; i++) { 
			for( j = 0; j < 55; j++) {
				mapa[mapaID].matriz[i][j].acao = fgetc(arq);
				if(mapa[mapaID].matriz[i][j].acao == 48) mapa[mapaID].matriz[i][j].acao = 0;
				else mapa[mapaID].matriz[i][j].acao = 1;
			}
		}
	}
	fclose(arq);
	
	mapa[mapaID].matriz[43][31].acao = 2;
	mapa[mapaID].matriz[43][31].ID = 1;
	mapa[mapaID].matriz[43][31].itemID = 4;
	mapa[mapaID].matriz[43][31].quant = 2;
	mapa[mapaID].matriz[43][31].substituir = carregaBitmap(mapa[mapaID].matriz[43][31].substituir, "../bmp/quests/ninho_vazio.bmp");
	mapa[mapaID].matriz[43][31].subs = 1;
	
	//	Teleporte.
	mapa[mapaID].matriz[64][5].acao = 3;		 //	Teletransporte.						//
	mapa[mapaID].matriz[64][5].ID = 0;		 	 //	Não bloqueia a passagem.			//
	mapa[mapaID].matriz[64][5].mapaid = 2;		 //	ID Mapa destino.					//
	mapa[mapaID].matriz[64][5].hposh = 14;		 // Posição horizontal.					//
	mapa[mapaID].matriz[64][5].hposv = 32;		 // Posição vertical.					//
	mapa[mapaID].matriz[64][5].look = SUL;		 // Posição que o heroi estará voltado.	//
	
    for (i = 64; i >= 0; i--)
    {
    	draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
    	draw_sprite(BUFFER, heroi.BMP[heroi.LOOK], heroi.POSH, heroi.POSV);
    	draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
    	rectfill(BUFFER, 0, 0, i * 12.5, 599, (63-i));   	
    	draw_sprite(screen, BUFFER, 0, 0);
    	usleep(10000);
    }
	
	return;
}
