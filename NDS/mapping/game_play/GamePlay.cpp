/*
 * GamePlay.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include "GamePlay.h"
#include "timming.h"
#include "Jack.h"
#include "Jhon.h"
#include "scenery.h"
#include "objects.h"

#include "util.h"


/*************************************************************************************************/

st_sprite VisualElement::s_SpritePositions[SPRITE_POSITIONS];
st_offset *VisualElement::s_PivotOffset_8px;

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
	m_Scenery = this->create_scenery(level);

	/* Load map. */
	m_MapProcessor.load_Map(m_Scenery->get_Map());


	/* Load character. */
	m_Character = new Jack();
	m_Character->set_map_processor(m_MapProcessor);

	m_Character->set_relative_pos_32px( m_Scenery->get_CharStartPoint_x_32px(),
										m_Scenery->get_CharStartPoint_y_32px());

	/* Set pivot offset in order to get the sprite engine working. */
	VisualElement::set_PivotOffset(&m_Character->m_Pos_relative_8px);
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

	// Testing purpose!!!!!
	Torch torch(TILE_32PX_TO_8PX(22), TILE_32PX_TO_8PX(10));

	while(true) {

/*+++++++++++++++++++++++++++++++++++++ Get actions. +++++++++++++++++++++++++++++++++++++*/
		char_action = m_Controller.get_user_action();
		//ai_action = ai.get_ai_action();

		if (char_action == ACTION_CONSOLE_CLEAR) {
			consoleClear();
			char_action = ACTION_NONE;
		}

/*+++++++++++++++++++++++++++++++++++ Process actions. +++++++++++++++++++++++++++++++++++*/
		this->execute_action(char_action);
		//ai.execute_action(char_action);

		//TODO: background/m_Map.update(); // possible animated frames.

		swiWaitForVBlank();
		bgUpdate();
		oamUpdate(&oamMain);
	}
}

/*************************************************************************************************/

void GamePlay::execute_action(en_char_action& action)
{
	m_Character->update_actions_cooldown();

	switch(action) {

	/* Touch action. */
	case ACTION_TOUCH:
		this->touch_action();
	break;

	/* Walk actions. */
	case ACTION_WALK_NORTH:
	case ACTION_WALK_SOUTH:
	case ACTION_WALK_EAST:
	case ACTION_WALK_WEST:
	case ACTION_NONE:
		m_Character->move(action);
		break;
	default:
		debug("Untreated action received.");
		break;
	}
}

/*************************************************************************************************/

void GamePlay::touch_action(void)
{
	st_offset touching[2];

	memset(touching, 0 , sizeof(touching));

	m_Character->get_touch_position(touching);

	debug("pa: %d,%d; pb: %d,%d", touching[0].x, touching[0].y, touching[1].x, touching[1].y);
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

	VisualElement::init_SpritePositions();

	dmaCopy(jack_charsetPal, SPRITE_PALETTE, jack_charsetPalLen);
	//dmaCopy(torch_dataPal, SPRITE_PALETTE, torch_dataPalLen);
}
