#include "includes.h"

struct PERSONAGEM heroi;
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
		
		if(key[KEY_UP]) 
		{
			menu_pos--;
			if(menu_pos == 0) menu_pos = 7;
			key[KEY_UP] = FALSE;
			menuDrawText(menu_pos);
		}
			
		if(key[KEY_DOWN])  
		{
			menu_pos++;
			if(menu_pos == 8) menu_pos = 1;
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
	if(menu_pos == 1){ px = 0; py = 67;}  if(menu_pos == 2){ px = 0; py = 133;}
	if(menu_pos == 3){ px = 0; py = 200;} if(menu_pos == 4){ px = 0; py = 269;}
	if(menu_pos == 5){ px = 0; py = 341;} if(menu_pos == 6){ px = 0; py = 411;}
	if(menu_pos == 7){ px = 0; py = 468;}
	
	draw_sprite(SBUFFER, _menu[0], 0, 0);
	draw_sprite(SBUFFER, _menu[menu_pos], px, py);
	textprintf_ex(SBUFFER, sans_serif20, 542, 51,  makecol(0, 0, 0), -1, "%s", heroi.nome);
	textprintf_ex(SBUFFER, sans_serif20, 500, 87,  makecol(0, 0, 0), -1,"%d/%d", heroi.vita, heroi.vita_max);
	textprintf_ex(SBUFFER, sans_serif20, 500, 115, makecol(0, 0, 0), -1,"%d/%d", heroi.mana, heroi.mana_max);
	textprintf_ex(SBUFFER, sans_serif18, 495, 146, makecol(0, 0, 0), -1, "%d", heroi.ataque);	
	textprintf_ex(SBUFFER, sans_serif18, 573, 146, makecol(0, 0, 0), -1, "%d", heroi.defesa);	
	textprintf_ex(SBUFFER, sans_serif18, 666, 146, makecol(0, 0, 0), -1, "%d", heroi.magia);
	draw_sprite(screen, SBUFFER, 0, 0);
	
	return;
}

void menuItens(void) {
	
	int cont = 0, lado = 60, Niten = 0;
	int pagina = 1;
	int varteste = 70;
	
	atualizaMenuItens(_menuItens[0], 60, 115, pagina);

	do{
		printf("item = %d\n\n", Niten);
		if( (key[KEY_UP]) && (cont >= varteste) )
		{
			key[KEY_UP] = 0;
			cont -= varteste;
			Niten--;
			atualizaMenuItens(_menuItens[0], (lado), (cont + 115), pagina);
		}
		
		if( (key[KEY_DOWN]) && (cont < 4*varteste) )
		{
			key[KEY_DOWN] = 0;
			cont += varteste;
			Niten++;
			atualizaMenuItens(_menuItens[0], (lado), (cont + 115), pagina);
		}
		
		if(key[KEY_RIGHT])
		{
				if(lado < 2*230)
				{
					Niten += 5;
					lado += 230;
					atualizaMenuItens(_menuItens[0], lado, (cont + 115), pagina);
					key[KEY_RIGHT] = 0;
				}
			
				else if (pagina < 7) 
				{
					cont = 0;
					lado = 60;
					Niten = pagina*14+pagina;
					pagina++;
					atualizaMenuItens(_menuItens[0], 60, 115, pagina);
					key[KEY_RIGHT] = 0;
				}
		}
		
		if(key[KEY_LEFT])
		{
			if(lado > 230)
			{
			Niten -= 5;
			lado -= 230;
			atualizaMenuItens(_menuItens[0], lado, (cont + 115), pagina);
			key[KEY_LEFT] = 0;
			}
			else if (pagina > 1) {
				pagina--;
				cont = 0;
				lado = (2*230)+60;
				Niten = pagina*14-5+pagina;
				
				
				atualizaMenuItens(_menuItens[0], (2*230)+60, 115, pagina);
				key[KEY_LEFT] = 0;
			}
			
		}
		
		if( (key[KEY_ENTER]) && (heroi.item[Niten].ID != 0) )
		{
			key[KEY_ENTER] = 0;
			printf("%d\n\n", Niten);
			printf("%s = %d\n",  item[heroi.item[Niten].ID].nome, heroi.item[Niten].ID);
			
			if(item[heroi.item[Niten].ID].classe == B)
			{
				printf("item de cura!\n");
			}
		}

		if(heroi.item[Niten].ID != 0) {
			textprintf_ex(SBUFFER, sans_serif18, 70, 50, makecol(0, 0, 0), -1, "Quantidade: x%d", heroi.item[Niten].quantidade);
			textprintf_ex(SBUFFER, sans_serif18, 70, 480, makecol(0, 0, 0), -1, "Descricao:");
			textprintf_ex(SBUFFER, sans_serif18, 70, 520, makecol(0, 0, 0), -1, "%s", item[heroi.item[Niten].ID].descricao);
			draw_sprite(screen, SBUFFER, 0, 0);
		}
		
	} while(!key[KEY_ESC]);
	
	key[KEY_ESC] = 0;
	menu();
}

void atualizaMenuItens(BITMAP *menuItens, int ponteiroPosx, int ponteiroPosy, int pagina) {
	//printf("h = %d; v = %d\n", ponteiroPosx, ponteiroPosy);

	draw_sprite(SBUFFER, menuItens, 0, 0);
	
	switch (pagina) {
	
	case 1:
		atualizaMI2(0, 15);
		break;
		
	case 2:
		atualizaMI2(15, 30);
		break;
		
	case 3:
		atualizaMI2(30, 45);
		break;
		
	case 4:
		atualizaMI2(45, 60);
		break;
		
	case 5:
		atualizaMI2(60, 75);
		break;

	case 6:
		atualizaMI2(75, 90);
		break;
		
	case 7:
		atualizaMI2(90, 100);
		break;
		
	}
	draw_sprite(SBUFFER, _ponteiro, ponteiroPosx, ponteiroPosy);
	textprintf_ex(SBUFFER, sans_serif18, 640, 550, makecol(0, 0, 0), -1, "Pagina %d", pagina);
	draw_sprite(screen, SBUFFER, 0, 0);

	return;
}

void atualizaMI2(int k, int kmax) {
	
	int i, Vcont = 20, Hcont = 25;
	
	for( i = k; i < kmax; i++ ){
		//printf("[%d] %d\n", i, heroi.item[i].ID);
		if(heroi.item[i].ID != 0)
		{
			textprintf_ex(SBUFFER, sans_serif18, 60 + Hcont, 90 + Vcont, makecol(0, 0, 0), -1, "%s", item[heroi.item[i].ID].nome);
			//textprintf_ex(SBUFFER, sans_serif18, 60 + Hcont, 90 + Vcont, makecol(0, 0, 0), -1, "x(%d)", heroi[0].item[i].quantidade);
			Vcont += 70;
		}
				
		if(Vcont == (5*70)+20)	{
			Vcont = 20;
			Hcont += 231;
		}
				
		if(Hcont == (3*231)) {
			i = kmax;
		}
	}
	return;
}