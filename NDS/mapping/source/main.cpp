#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <nds.h>
#include <iostream>

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
#include "Maze3.h"

/* Game resources */
#include "man.h"


int main(void)
{
	GameVideo screen;

	/* Initialize debugging console. */
	consoleDemoInit();
	lcdMainOnBottom();

	Maze1 *myMaze = new(Maze1);
	Maze2 *myMaze2 = new(Maze2);
	Maze3 *myMaze3 = new(Maze3);

	/* Initialize sprite manager*/
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	oamInit(&oamMain, SpriteMapping_1D_128, false);

	/* Initialize character. */
	GameCharacter persona((u8*)manTiles, SCREEN_CENTER_X-16, SCREEN_CENTER_Y-16);
	dmaCopy(manPal, SPRITE_PALETTE, 512);

	screen.load_Map(myMaze3);

	bool jump = 0;
	const int jump_value = 10;

	while(true)
	{
		scanKeys();
		int keys = keysHeld();

		if(keys & KEY_UP) {
			persona.move(W_UP);
			screen.scroll_Background(0, -1+(-1*jump_value*jump));
		}

		if(keys & KEY_DOWN) {
			persona.move(W_DOWN);
			screen.scroll_Background(0, 1+(jump_value*jump));
		}

	    if(keys & KEY_LEFT) {
	    	persona.move(W_LEFT);
			screen.scroll_Background(-1+(-1*jump_value*jump), 0);
	    }

		if(keys & KEY_RIGHT) {
			persona.move(W_RIGHT);
			screen.scroll_Background(1+(jump_value*jump), 0);
		}

		if(keys & KEY_B) {
			screen.load_Map(myMaze);
			//x = y = 0;
		}

		if(keys & KEY_A) {
			jump = !jump;
			for (int j = 0; j < Layer_1MapLen; j++) {
				std::cout << j;
			}
		}

		swiWaitForVBlank();
		//consoleClear();

		oamUpdate(&oamMain);
	}

	delete(myMaze);
	delete(myMaze2);
	delete(myMaze3);

	return 0;
}

