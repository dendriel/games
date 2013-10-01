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

/*************************************************************************************************/

GamePlay::GamePlay(void):
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
	this->init_basics();

	//TODO: put the game loop somewere around here.
	/* If need to start with a specific level. */
	if (level != SCEN_LEVEL_NONE) {
		this->load_level(level);
	}
	/* Starts by the first. */
	else {
		this->load_level(SCEN_LEVEL0);
	}
}

/*************************************************************************************************/

void GamePlay::load_level(const en_scen_level level)
{
	GameScenery *cur_scenery = this->create_scenery(level);

	/* Load map. */
	m_MapProcessor.load_Map(cur_scenery->get_Map(),
			cur_scenery->get_CharStartPoint_x(),
			cur_scenery->get_CharStartPoint_y());

	/* Load character. */
	m_Character = new Jhon(SCREEN_CENTER_X-16, SCREEN_CENTER_Y-16);

	/* Let the user play the game. =D */
	this->interact(cur_scenery);

	delete(m_Character);
}

void GamePlay::interact(GameScenery *cur_scenery)
{
	const size_t step_len = m_Character->get_StepLen_pixels();

	while(true) {
		//TODO: the user interaction must be inside a thread.
		en_facing action = m_Controller.get_held_direction();

		switch (action) {

		case W_UP:
			m_Character->move(W_UP);
			m_MapProcessor.scroll_Background(0, -1*step_len);
			break;

		case W_DOWN:
			m_Character->move(W_DOWN);
			m_MapProcessor.scroll_Background(0, step_len);
			break;

		case W_LEFT:
			m_Character->move(W_LEFT);
			m_MapProcessor.scroll_Background(-1*step_len, 0);
			break;

		case W_RIGHT:
			m_Character->move(W_RIGHT);
			m_MapProcessor.scroll_Background(step_len, 0);
			break;

		default:
			break;
		}

		oamUpdate(&oamMain);
		GSLEEP(1);
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
