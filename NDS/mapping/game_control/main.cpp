/*#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <nds.h>
#include <iostream>*/

/* References */
/*
#include "nds/arm9/video.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/background.h"
#include "nds/arm9/sprite.h"
#include "nds/system.h"*/

#include "GameEngine.h"


int main(void)
{
	GameEngine game_engine;

	game_engine.start_game();

	return 0;
#if 0
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
	Jhon persona(SCREEN_CENTER_X-16, SCREEN_CENTER_Y-16);
	dmaCopy(manPal, SPRITE_PALETTE, 512);

	screen.load_Map(myMaze3);

	int step_value = 3;

	// TODO: the caracter class give delays inside its methods. Must be a control
	// thread.
	while(true)
	{
		scanKeys();
		int keys = keysHeld();

		if(keys & KEY_UP) {
			persona.move(W_UP);
			screen.scroll_Background(0, -1*step_value);
		}

		if(keys & KEY_DOWN) {
			persona.move(W_DOWN);
			screen.scroll_Background(0, step_value);
		}

	    if(keys & KEY_LEFT) {
	    	persona.move(W_LEFT);
			screen.scroll_Background(-1*step_value, 0);
	    }

		if(keys & KEY_RIGHT) {
			persona.move(W_RIGHT);
			screen.scroll_Background(step_value, 0);
		}

		if(keys & KEY_B) {
			step_value++;
			debug("step_value: %d", step_value);
			//x = y = 0;
		}

		if(keys & KEY_A) {
			step_value--;
			debug("step_value: %d", step_value);
		}
		//consoleClear();

		oamUpdate(&oamMain);
		GSLEEP(1);
	}

	delete(myMaze);
	delete(myMaze2);
	delete(myMaze3);
#endif
}

