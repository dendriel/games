#include "includes.h"

PERSONAGEM heroi[3];
BITMAP *_menu[10];
ITEM item[100];
BITMAP *_menuItens[10];

/*	MENU[x]		Conteúdo
 * 
 * 	  0			Principal
 * 	  1			Itens
 *    2			Equipamentos
 *    3			Grupo
 *    4			Magias
 *    5			Status
 *    6			Volar
 *    7			Sair
 */

void menu(void) {
	
	int cont;				//	Variável para contagem.						//
	char caminho[50];		//	Endereco das imagens.						//
	int menu_pos = 1;		//	Indicador de pos do Menu.					//
	int px, py;				//	Posicao onde serao carregadas as imagens.	//
	
	menuDrawText(menu_pos);
		
	while (1) {
		
		if( (key[KEY_UP]) && (menu_pos != 1) ) 
		{
			menu_pos--;
			key[KEY_UP] = FALSE;
			menuDrawText(menu_pos);
		}
			
		if( (key[KEY_DOWN]) && (menu_pos != 7) )  
		{
			menu_pos++;
			key[KEY_DOWN] = FALSE;
			menuDrawText(menu_pos);		
		}
		
		if(key[KEY_ENTER]) 
		{		
			key[KEY_ENTER] = FALSE;
			
			
			if(menu_pos == 1) { menuItens(); return; }
			if(menu_pos == 7) exit(0);
			if(menu_pos == 6) return;
			
		}
			
		if(key[KEY_ESC]) {
			key[KEY_ESC] = FALSE;
			return;
		}		
	} 	
}

void menuDrawText(int menu_pos) {

	int px, py;
	if(menu_pos == 1){ px = 0; py = 0;}	  if(menu_pos == 2){ px = 0; py = 134;}
	if(menu_pos == 3){ px = 0; py = 203;} if(menu_pos == 4){ px = 0; py = 273;}
	if(menu_pos == 5){ px = 0; py = 340;} if(menu_pos == 6){ px = 0; py = 405;}
	if(menu_pos == 7){ px = 0; py = 467;}
	
	draw_sprite(SBUFFER, _menu[0], 0, 0);
	draw_sprite(SBUFFER, _menu[menu_pos], px, py);
	textprintf_ex(SBUFFER, sans_serif20, 547, 41,  makecol(0, 0, 0), -1, "%s", heroi[0].nome);
	textprintf_ex(SBUFFER, sans_serif20, 500, 77,  makecol(0, 0, 0), -1,"%d/%d", heroi[0].vita, heroi[0].vita_max);
	textprintf_ex(SBUFFER, sans_serif20, 500, 105, makecol(0, 0, 0), -1,"%d/%d", heroi[0].mana, heroi[0].mana_max);
	textprintf_ex(SBUFFER, sans_serif18, 495, 136, makecol(0, 0, 0), -1, "%d", heroi[0].ataque);	
	textprintf_ex(SBUFFER, sans_serif18, 573, 136, makecol(0, 0, 0), -1, "%d", heroi[0].defesa);	
	textprintf_ex(SBUFFER, sans_serif18, 666, 136, makecol(0, 0, 0), -1, "%d", heroi[0].magia);
	draw_sprite(screen, SBUFFER, 0, 0);
	
	return;
}

void menuItens(void) {
	
	int cont = 1, Lcont = 0, lado = 0, Niten = 0;
	
	atualizaMenuItens(_menuItens[0], 10, 100);
	//printf("%d\n\n", Niten);
	do{
		if( (key[KEY_UP]) && (cont > 1) )
		{
			key[KEY_UP] = 0;
			cont--;
			Niten--;
			atualizaMenuItens(_menuItens[0], (10 + lado), ((cont*30) + 70) );
			
		}
		
		if( (key[KEY_DOWN]) && (cont < 10) )
		{
			key[KEY_DOWN] = 0;
			cont++;
			Niten++;
			atualizaMenuItens(_menuItens[0], (10 + lado), ((cont*30) + 70) );
		}
		
		if( (key[KEY_RIGHT]) && Lcont < 2)
		{
			Lcont++;
			Niten += 10;
			lado = Lcont*300;
			atualizaMenuItens(_menuItens[0], (10 + lado), ((cont*30) + 70) );
			key[KEY_RIGHT] = 0;
		}
		
		if( (key[KEY_LEFT]) && Lcont > 0)
		{
			Lcont--;
			Niten -= 10;
			lado = Lcont*300;
			atualizaMenuItens(_menuItens[0], (10 + lado), ((cont*30) + 70) );
			key[KEY_LEFT] = 0;
			
		}
		
		if( (key[KEY_ENTER]) && (heroi[charID].item[Niten].ID != 0) )
		{
			key[KEY_ENTER] = 0;
			//printf("%d\n\n", Niten);
			//printf("%s = %d\n",  item[heroi[charID].item[Niten].ID].nome, heroi[charID].item[Niten].ID);
			
			if(item[heroi[charID].item[Niten].ID].classe == B)
			{
				printf("item de cura!\n");
			}
		}

	} while(!key[KEY_ESC]);
	
	key[KEY_ESC] = 0;
	menu();
}

void atualizaMenuItens(BITMAP *menuItens, int ponteiroPosx, int ponteiroPosy) {
	
	int i, Vcont = 0, Hcont = 0;
	draw_sprite(SBUFFER, menuItens, 0, 0);
	
	for( i = 0; i < 100; i++ ){
		printf("[%d] %d\n", i, heroi[charID].item[i].ID);
		if(heroi[charID].item[i].ID != 0)
		{
			textprintf_ex(SBUFFER, sans_serif18, 34 + Hcont, 90 + Vcont, makecol(255, 255, 255), -1, "%s x(%d)", item[heroi[0].item[i].ID].nome, heroi[0].item[i].quantidade);
			Vcont += 30;
		}
		
		if(Vcont == (10*30))	{
			Vcont = 0;
			Hcont += 300;
		}
		
		if(Hcont == (3*300)) {
			i = 100;
		}
	}
	draw_sprite(SBUFFER, _ponteiro, ponteiroPosx, ponteiroPosy);
	
	draw_sprite(screen, SBUFFER, 0, 0);
	
}