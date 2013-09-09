#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <nds.h>

/* References */
#include "nds/arm9/video.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/background.h"
#include "nds/arm9/sprite.h"
#include "nds/system.h"

/* Game related includes */
#include "util.h"
#include "GameVideo.h"
#include "GameCharacter.h"
#include "Maze1.h"
#include "Maze2.h"

/* Game resources */
#include "man.h"


int main(void)
{
	GameVideo screen;
	int x = 0;
	int y = 0;

	/* Initialize debugging console. */
	consoleDemoInit();
	lcdMainOnBottom();

	Maze1 *myMaze = new(Maze1);
	Maze2 *myMaze2 = new(Maze2);

	/* Initialize sprite manager*/
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	oamInit(&oamMain, SpriteMapping_1D_128, false);

	/* Initialize character. */
	GameCharacter persona((u8*)manTiles, SCREEN_CENTER_X-16, SCREEN_CENTER_Y-16);
	dmaCopy(manPal, SPRITE_PALETTE, 512);


	while(1) {
		scanKeys();
		int keys = keysHeld();

		if(keys & KEY_UP) {
			persona.move(W_UP);
			y--;
		}

		if(keys & KEY_DOWN) {
			persona.move(W_DOWN);
			y++;
		}

	    if(keys & KEY_LEFT) {
	    	persona.move(W_LEFT);
	    	x--;
	    }

		if(keys & KEY_RIGHT) {
			persona.move(W_RIGHT);
			x++;
		}

		if(keys & KEY_A) {
			screen.load_Map(myMaze2);
			x = y = 0;
		}


		if(keys & KEY_B) {
			screen.load_Map(myMaze);
			x = y = 0;
		}

		swiWaitForVBlank();
		consoleClear();

		screen.scroll_Background(x, y);
		oamUpdate(&oamMain);
		debug("x: %d; y: %d", x, y);
	}

	delete(myMaze);
	delete(myMaze2);
	return 0;
}

