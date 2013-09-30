/*
 * GamePlay.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GamePlay.h"
#include "Jhon.h"

#include "scenery.h"

#include "Maze3.h"

#include "timming.h"

/*************************************************************************************************/

GamePlay::GamePlay(void):
m_Character(new Jhon)
{
	;;
}

/*************************************************************************************************/

GamePlay::~GamePlay(void)
{
	delete(m_Character);
}

/*************************************************************************************************/

void GamePlay::start(const int level)
{
	this->init_basics();

	/* If need to start with a specific level. */
	if (level > 0) {
		this->run_level(level);
	}
	/* Starts by the first. */
	else {
		this->run_level();
	}

	m_MapProcessor.load_Map(new Maze3);
	while(1) GSLEEP(1);
}

/*************************************************************************************************/

void GamePlay::run_level(en_scen_level level)
{

}



typedef enum {
	LEVEL_0 = 0,
	LEVEL_1
} en_scen_level;

/*************************************************************************************************/

GameScenery GamePlay::*create_scenery(en_scen_level level)
{
	switch(level) {
		case LEVEL_0:
			return S
			break;
	}
}



void GamePlay::init_basics(void)
{
	/* Initialize debugging console. */
	consoleDemoInit();
	lcdMainOnBottom();

	/* Initialize sprite manager*/
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	oamInit(&oamMain, SpriteMapping_1D_128, false);
}
