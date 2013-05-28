#include "includes.h"

struct PERSONAGEM heroi;
struct MAPA mapa[50];
ITEM item[100];

//-------------------Quest System
void ac_encontraItem(int posx, int posy) {
/*
	
	int acao;			// 0 = nada; 1 = pegar item;
	int ID;				// ID da acao.
	int itemID; 		// Item a ser recebido.
	int quant;			// Quantidade de itens.
	char menssagem[50];	// Mensagem que o personagem ira receber.
*/
	
	int i, flag = 0;

	for(i = 0; i <= heroi.itemCont; i++)
	{
		if(mapa[mapaID].matriz[43][31].itemID == heroi.item[i].ID)
		{
			if( (heroi.item[i].quantidade + mapa[mapaID].matriz[43][31].quant) > 99) //	Soma item.
			{
				if(heroi.itemCont < 99)	//	Adiciona item.
				{
					heroi.item[heroi.itemCont+1].ID = mapa[mapaID].matriz[posx][posy].itemID;
					heroi.item[heroi.itemCont+1].quantidade = mapa[mapaID].matriz[43][31].quant;
					mapa[mapaID].matriz[posx][posy].acao = 0;
					
					textprintf_ex(screen, sans_serif18, 300, 90 , makecol(255, 255, 255), -1, "Voce encontrou %d %s.", mapa[mapaID].matriz[43][31].quant, item[mapa[mapaID].matriz[43][31].itemID].nome);
					sleep(1);
				}
				else
				{
					textprintf_ex(screen, sans_serif18, 300, 90 , makecol(255, 255, 255), -1, "Voce encontrou %d %s.", mapa[mapaID].matriz[43][31].quant, item[mapa[mapaID].matriz[43][31].itemID].nome);
					sleep(1);
					pcl_atualizaMapa();
					textprintf_ex(screen, sans_serif18, 100, 90 , makecol(255, 255, 255), -1, "Voce nao tem espaço para carregar este item!", mapa[mapaID].matriz[43][31].quant, item[mapa[mapaID].matriz[43][31].itemID].nome);
					clear_keybuf();
				while(!keypressed());
				}
				return;
			}
			else
			{
				heroi.item[i].quantidade += (mapa[mapaID].matriz[43][31].quant);	//	Adiciona a quantidade ao item já existente.	//
				mapa[mapaID].matriz[posx][posy].acao = 0;
				
				textprintf_ex(screen, sans_serif18, 300, 90 , makecol(255, 255, 255), -1, "Voce encontrou %d %s.", mapa[mapaID].matriz[43][31].quant, item[mapa[mapaID].matriz[43][31].itemID].nome);
				sleep(1);

			}
		}
	}
	return;
}

//-------------------Transição entre mapas.
void ac_teletransporte(int hh, int hv) {
	
	int i;
	
	sleep(1);
	
    for (i = 0; i < 64; i++)
    {
          rectfill(screen, i * 12.5, 0, (i + 1) * 12.5, 599, i);
          usleep(10000);
    }
    //printf("carregaMapa(%d, %d, %d, %d, %d)\n", mapa[mapaID].matriz[hh][hv].mapaid, mapa[mapaID].matriz[hh][hv].posh, mapa[mapaID].matriz[hh][hv].posv, mapa[mapaID].matriz[hh][hv].hposh, mapa[mapaID].matriz[hh][hv].hposv);
    pcl_carregaMapa(mapa[mapaID].matriz[hh][hv].mapaid, mapa[mapaID].matriz[hh][hv].hposh, mapa[mapaID].matriz[hh][hv].hposv, mapa[mapaID].matriz[hh][hv].look);
	return;
}