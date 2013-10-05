/*
 * GamePlay.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GamePlay.h"
#include "timming.h"
#include "Jhon.h"
//#include "Maze3.h"
#include "scenery.h"

//!< Max of 10 actions processing interactions before reading actions again. Total of 160ms
#define MAX_ACTIONS_INTERATIONS 10

/*************************************************************************************************/

GamePlay::GamePlay(void):
m_Scenery(0),
m_Character(0)
{
	;;
}

/*************************************************************************************************/

GamePlay::~GamePlay(void)
{
	delete(m_Character);
}

/*************************************************************************************************/

void GamePlay::start(const en_scen_level level)
{
	/* Keep track of the playing level. */
	en_scen_level curr_level;

	this->init_basics();

	/* If need to start with a specific level. */
	if (level != SCEN_LEVEL_NONE) {
		this->load_level(level);
		curr_level = level;
	}
	/* Starts by the first. */
	else {
		this->load_level(SCEN_LEVEL0);
		curr_level = SCEN_LEVEL0;
	}

	do {
		/* Let the user play the game. =D */
		this->play_game_loop();

		/* Increment the level (next level). */
		curr_level++;

	} while (curr_level != SCEN_LEVEL_END);

}

/*************************************************************************************************/

void GamePlay::load_level(const en_scen_level level)
{
	st_offset char_relative_pos_tiles;

	m_Scenery = this->create_scenery(level);

	char_relative_pos_tiles.x = m_Scenery->get_CharStartPoint_x_tiles();
	char_relative_pos_tiles.y = m_Scenery->get_CharStartPoint_y_tiles();

	/* Load map. */
	m_MapProcessor.load_Map(m_Scenery->get_Map(),
			char_relative_pos_tiles.x,
			char_relative_pos_tiles.y);

	/* Load character. */
	m_Character = new Jhon();
	m_Character->set_relative_pos_pixels(char_relative_pos_tiles.x*TILE_W_SIZE,
										char_relative_pos_tiles.y*TILE_H_SIZE);
	m_Character->set_map_processor(m_MapProcessor);
}

/*************************************************************************************************/

void GamePlay::unload_level(void)
{
	delete(m_Scenery);
	delete(m_Character);
}

/*************************************************************************************************/

void GamePlay::play_game_loop(void)
{
	en_char_action char_action;
	Timming timer;

	while(true) {

		unsigned int process_action_cnt = 0;

		/* Get actions. */
		char_action = m_Controller.get_user_action();
		//ai_action = ai.get_ai_action();

		/* Process actions. */
		while (process_action_cnt < MAX_ACTIONS_INTERATIONS) {

			//debug("%d", char_action);
			m_Character->execute_action(char_action, process_action_cnt);
			//ai.execute_action(char_action);
			//TODO: background/m_Map.update(); // possibility animated frames.


			//timer.start();
			swiWaitForVBlank();
			bgUpdate();
			oamUpdate(&oamMain);

			process_action_cnt++;
		}
	}
}

/*************************************************************************************************/

GameScenery *GamePlay::create_scenery(en_scen_level level)
{
	switch(level) {
		case SCEN_LEVEL0:
			return new(Scenery01);
			break;
		default:
			return NULL;
	}

	return NULL;
}

/*************************************************************************************************/

void GamePlay::init_basics(void)
{
	/* Map RAM to video memory. */
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

	/* Initialize debugging console. */
	consoleDemoInit();
	lcdMainOnBottom();

	/* Map RAM and initialize sprite manager*/
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	dmaCopy(manPal, SPRITE_PALETTE, 512);
}
