#include "includes.h"

//**********************************//
//	Developer Vitor Rozsa			//
//	E-mail: vitor.rozsa@hotmail.com	//
//**********************************//

struct PERSONAGEM heroi;
struct MAPA mapa[50];

void iniciaChar(void) {

	int h, v, i, cont = 1;
	
	heroi.BMP[0] = carregaBitmap(heroi.BMP[0], "../bmp/heroi2.bmp");

	for( v = 0; v < 4; v++)	{
		for( h = 0; h < 3; h++)	{
			heroi.BMP[cont] = create_bitmap(32, 48);
			blit(heroi.BMP[0], heroi.BMP[cont], 32*h, 48*v, 0, 0, 32, 48);
			cont++;
		}
	}
	sprintf(heroi.nome, "Henry o Leao");
    
    //	Atributos.	//
    heroi.arma = 10;	//	*mudar.	//
    heroi.escudo = 0;
    heroi.armadura = 2;
    heroi.helmo = 0;
    heroi.botas = 0;
    
    heroi.forca = 		  10;
    heroi.habilidade = 	  10;
    heroi.resistencia =   10;
    heroi.agilidade = 	  10;
    heroi.inteligencia =  10;
    heroi.destreza =	  10;
    heroi.poder_de_fogo = 10;
    
    heroi.ataque = (heroi.forca + heroi.habilidade + heroi.arma);
    heroi.defesa = (heroi.resistencia + heroi.agilidade + heroi.escudo + heroi.armadura + heroi.helmo + heroi.botas);
    heroi.magia	= (heroi.inteligencia + heroi.destreza + heroi.poder_de_fogo);
    
    heroi.vita_max = (heroi.resistencia*5);
    heroi.mana_max = (heroi.inteligencia*5);
    
    heroi.vita = heroi.vita_max;
    heroi.mana = heroi.mana_max;
    
    //	Itens.	//
    heroi.moedas = 100;
    
    for(i = 0; i < 100; i++) heroi.item[i].ID = 0;
    
    heroi.item[0].ID = 1;
    heroi.item[0].quantidade = 2;
    
    heroi.item[1].ID = 2;
    heroi.item[1].quantidade = 1;
    
    heroi.item[2].ID = 3;
    heroi.item[2].quantidade = 12;
    
    heroi.item[3].ID = 4;
    heroi.item[3].quantidade = 99;
    
  for(i = 4; i < 99; i++)
  {
	    heroi.item[i].ID = 3;
	    heroi.item[i].quantidade = 99;
  }
    
//--------Conta quantos itens o personagem carrega.
    i = 0;
    while(heroi.item[i].ID != 0){
    	heroi.itemCont++;
    	i++;
    }
    
    heroi.itemCont--;
//------------------------------------------------//    
    return;
}

void moveChar(int move) {
	   
		/****NORTE****/
		if( (move == 1) && (heroi.POSV - 32 >= 0) )
		{
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[10],  heroi.POSH, heroi.POSV - 10);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[12],  heroi.POSH, heroi.POSV - 20);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);		
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[11],  heroi.POSH, heroi.POSV - 32);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);			
		    
		    heroi.POSV  = (heroi.POSV-32);

			heroi.LOOK = 0;
			heroi.MapaPos[1]--;
		}
		
		/****LESTE****/
		if( (move == 2) && (heroi.POSH + 32 <= 750) )
		{
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[lestee],  (heroi.POSH + 10), heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[lested],  (heroi.POSH + 20), heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[leste],  (heroi.POSH + 32), heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);	
		    
		    heroi.POSH = (heroi.POSH+32);
		    
			heroi.LOOK = 1;
			heroi.MapaPos[0]++;
		}		
		/****SUL****/
		if( (move == 3) && (heroi.POSV + 32 <= 572) )
		{
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[1],  heroi.POSH, heroi.POSV + 10);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[3],  heroi.POSH, heroi.POSV + 20);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[2],  heroi.POSH, heroi.POSV + 32);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
		    
		    heroi.POSV = (heroi.POSV+32);
//		    
			heroi.LOOK = 2;
			heroi.MapaPos[1]++;
		}
		/****OESTE****/
		if( (move == 4) && (heroi.POSH - 32 >= 0) )
		{
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[oested],  (heroi.POSH - 10), heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[oestee],  (heroi.POSH - 20), heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);
			
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[oeste],  (heroi.POSH - 32), heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(50000);		
			
		    heroi.POSH = (heroi.POSH-32);
		    
			heroi.LOOK = 3;
			heroi.MapaPos[0]--;
		}
		
		printf("heroi[%d|%d] || mapa[%d][%d]\n",heroi.MapaPos[charID], heroi.MapaPos[1], mapa[mapaID].posx, mapa[mapaID].posy);	
	return;
}

void moveMapa(int move) {
	
	int cont, imag;
			   
	/****NORTE****/
	if(move == NORTE)
	{
		for( cont = 1, imag = 10; cont < 3; cont++, imag+=2)
		{
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, (mapa[mapaID].posy + (cont*12 -4) ));
			draw_sprite(BUFFER, heroi.BMP[imag],  heroi.POSH, heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, (mapa[mapaID].posy + (cont*12 -4) ));
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(MoveDelay);
		}
		clear(BUFFER);
		draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, (mapa[mapaID].posy + (cont*12 -4) ));
		draw_sprite(BUFFER, heroi.BMP[norte],  heroi.POSH, heroi.POSV);
		draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, (mapa[mapaID].posy + (cont*12 -4) ));
		draw_sprite(screen, BUFFER, 0, 0);
		usleep(MoveDelay);
					
		mapa[mapaID].posy += 32;
		heroi.LOOK = 0;
		heroi.MapaPos[1]--;
	}
				
	/****LESTE****/
	if(move == LESTE)
	{
		for( cont = 1, imag = 7; cont < 3; cont++, imag+=2)
		{
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], (mapa[mapaID].posx - (cont*12 -4) ), mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[imag],  heroi.POSH, heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], (mapa[mapaID].posx - (cont*12 -4) ), mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(MoveDelay);
		}
		clear(BUFFER);
		draw_sprite(BUFFER, mapa[mapaID].BMP[0], (mapa[mapaID].posx - (cont*12 -4) ), mapa[mapaID].posy);
		draw_sprite(BUFFER, heroi.BMP[leste],  heroi.POSH, heroi.POSV);
		draw_sprite(BUFFER, mapa[mapaID].BMP[1], (mapa[mapaID].posx - (cont*12 -4) ), mapa[mapaID].posy);
		draw_sprite(screen, BUFFER, 0, 0);	
		usleep(MoveDelay);
		
		mapa[mapaID].posx -= 32;
		heroi.LOOK = 1;
		heroi.MapaPos[0]++;
	}		
	/****SUL****/
	if(move == SUL)
	{
		for( cont = 1, imag = 1; cont < 3; cont++, imag+=2)
		{
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, (mapa[mapaID].posy - (cont*12 -4) ));
			draw_sprite(BUFFER, heroi.BMP[imag],  heroi.POSH, heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, (mapa[mapaID].posy - (cont*12 -4) ));
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(MoveDelay);
		}
		clear(BUFFER);
		draw_sprite(BUFFER, mapa[mapaID].BMP[0], mapa[mapaID].posx, (mapa[mapaID].posy - (cont*12 -4) ));
		draw_sprite(BUFFER, heroi.BMP[sul],  heroi.POSH, heroi.POSV);
		draw_sprite(BUFFER, mapa[mapaID].BMP[1], mapa[mapaID].posx, (mapa[mapaID].posy - (cont*12 -4) ));
		draw_sprite(screen, BUFFER, 0, 0);
		usleep(MoveDelay);
		
		mapa[mapaID].posy -= 32;
		heroi.LOOK = 2;
		heroi.MapaPos[1]++;
	}
	
	/****OESTE****/
	if(move == OESTE)
	{
		for( cont = 1, imag = 4; cont < 3; cont++, imag+=2)
		{
			clear(BUFFER);
			draw_sprite(BUFFER, mapa[mapaID].BMP[0], (mapa[mapaID].posx + (cont*12 -4) ), mapa[mapaID].posy);
			draw_sprite(BUFFER, heroi.BMP[imag],  heroi.POSH, heroi.POSV);
			draw_sprite(BUFFER, mapa[mapaID].BMP[1], (mapa[mapaID].posx + (cont*12 -4) ), mapa[mapaID].posy);
			draw_sprite(screen, BUFFER, 0, 0);			
			usleep(MoveDelay);
		}
		clear(BUFFER);
		draw_sprite(BUFFER, mapa[mapaID].BMP[0], (mapa[mapaID].posx + (cont*12 -4) ), mapa[mapaID].posy);
		draw_sprite(BUFFER, heroi.BMP[oeste],  heroi.POSH, heroi.POSV);
		draw_sprite(BUFFER, mapa[mapaID].BMP[1], (mapa[mapaID].posx + (cont*12 -4) ), mapa[mapaID].posy);
		draw_sprite(screen, BUFFER, 0, 0);
		usleep(MoveDelay);
		
		mapa[mapaID].posx += 32;
		heroi.LOOK = 3;
		heroi.MapaPos[0]--;
	}	
		printf("heroi[%d|%d] || mapa[%d][%d]\n",heroi.MapaPos[charID], heroi.MapaPos[1], mapa[mapaID].posx, mapa[mapaID].posy);
		printf("POSX: %d POSY: %d\n", heroi.POSH, heroi.POSV);
}