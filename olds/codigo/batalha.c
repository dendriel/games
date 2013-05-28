#include "includes.h"

struct PERSONAGEM heroi;
ANIMATAQUE ataque[100];
//
//
//void batalha(void) {
//	
//	clear(SBUFFER);
//	clear(screen);
//	draw_sprite(SBUFFER, _menu_batalha, 0, 0);
//	draw_sprite(SBUFFER, _batalha, 0, 0);
//	draw_sprite(SBUFFER, heroi[0].bmp_o, 420, 210);
//	draw_sprite(SBUFFER, heroi[0].bmp_l, 180, 210);
//	
//	do {
//		draw_sprite(SBUFFER, _menu_batalha, 0, 0);
//		draw_sprite(SBUFFER, _batalha, 0, 0);
//		draw_sprite(SBUFFER, heroi[0].bmp_o, 420, 210);
//		draw_sprite(SBUFFER, heroi[0].bmp_l, 180, 210);
//		draw_sprite(screen, SBUFFER, 0, 0);	
//
//		
//		if (key[KEY_Z]) {
//			anima_ataque(1, 1);
//			key[KEY_Z] = 0;
//		}
//	} while (!key[KEY_TAB]);
//
//	
//	
//	while (!key[KEY_TAB]);
//	key[KEY_TAB] = 0;
//}
//
//
//void anima_ataque(int id, int pos) {
//	
//	draw_sprite(SBUFFER, _menu_batalha, 0, 0);
//	draw_sprite(SBUFFER, _batalha, 0, 0);
//	draw_sprite(SBUFFER, heroi[0].bmp_o, 420, 210);
//	draw_sprite(SBUFFER, heroi[0].bmp_l, 180, 210);;
//	draw_sprite(SBUFFER, ataque[id].BMP[0], 190, 245);
//	draw_sprite(screen, SBUFFER, 0, 0);
//	usleep(100000);
//	
//	draw_sprite(SBUFFER, _menu_batalha, 0, 0);
//	draw_sprite(SBUFFER, _batalha, 0, 0);
//	draw_sprite(SBUFFER, heroi[0].bmp_o, 420, 210);
//	draw_sprite(SBUFFER, heroi[0].bmp_l, 180, 210);;
//	draw_sprite(SBUFFER, ataque[id].BMP[1], 190, 245);
//	draw_sprite(screen, SBUFFER, 0, 0);
//	usleep(100000);
//	
//	draw_sprite(SBUFFER, _menu_batalha, 0, 0);
//	draw_sprite(SBUFFER, _batalha, 0, 0);
//	draw_sprite(SBUFFER, heroi[0].bmp_o, 420, 210);
//	draw_sprite(SBUFFER, heroi[0].bmp_l, 180, 210);;
//	draw_sprite(SBUFFER, ataque[id].BMP[2], 190, 245);
//	draw_sprite(screen, SBUFFER, 0, 0);
//	usleep(100000);
//}
//
//void anima_ataque2 (int heroi, int id, int alvo) {	//heroi = heroi atacante id = tipo de ataque; alvo = posição do ataque.	//
//}