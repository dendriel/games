/*
 * GamePlay.cpp
 *
 *  Created on: 29/09/2013
 *      Author: marta
 */

#include <assert.h>
#include "GamePlay.h"
#include "timming.h"
#include "Jack.h"
#include "scenery.h"
#include "objects.h"
#include "sprites_data.h"

#include "util.h"


/*************************************************************************************************/

GamePlay::GamePlay(void):
m_Scenery(0),
m_Character(0)
{
	;;
}

GamePlay::~GamePlay(void)
{
	delete(m_Character);
}

/* Initialize static resources. */

st_sprite VisualElement::s_SpritePositions[SPRITE_POSITIONS];
st_offset *VisualElement::s_PivotOffset_8px;
long GameObject::s_Object_ids;
long Trigger::s_Trigger_ids;

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

void GamePlay::play_game_loop(void)
{
	en_action char_action;

	while(true) {

		/* Input. */
		char_action = m_Controller.get_user_action();

		// testing purpose.
		if (char_action == ACTION_CONSOLE_CLEAR) {
			//consoleClear();
			char_action = ACTION_NONE;
			m_Character->get_Inventory();
		}

		/* Update. */
		m_Character->update_actions_cooldown();
		 /* Could enqueue the character action too, but executing directly is more clearly. */
		this->execute_action(char_action);
		this->execute_queued_reactions();
		//TODO: background/m_Map.update(); // possible animated frames.

		/* Render. */
		swiWaitForVBlank();
		bgUpdate();
		oamUpdate(&oamMain);
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

void GamePlay::load_level(const en_scen_level level)
{
	m_Scenery = this->create_scenery(level);

	/* Load map. */
	m_MapProcessor << m_Scenery->get_Map();


	/* Load character. */
	m_Character = new Jack();

	this->set_character_relative_pos_32px(m_Scenery->get_CharStartPoint_x_32px(),
										m_Scenery->get_CharStartPoint_y_32px());

	/* Set pivot offset in order to get the sprite engine working. */
	VisualElement::set_PivotOffset(&m_Character->m_Pos_relative_8px);

	m_Scenery->fill_objects_list();
}

/*************************************************************************************************/

void GamePlay::set_character_relative_pos_32px(const int& x, const int& y)
{
	if ((x < SPRITE_SCREEN_CENTER_X_TILES) || (y < SPRITE_SCREEN_CENTER_Y_TILES)) {
		debug("Invalid character starting point.");
		assert(0);
		return;
	}

	const int move_x_32px = x - SPRITE_SCREEN_CENTER_X_TILES;
	const int move_y_32px = y - SPRITE_SCREEN_CENTER_Y_TILES;

	m_Character->add_relative_pos_x_8px(TILE_32PX_TO_8PX(move_x_32px));
	m_Character->add_relative_pos_y_8px(TILE_32PX_TO_8PX(move_y_32px));

	//debug("Moved to: %d,%d (%d,%d)",x,y, m_Pos_relative_8px.x, m_Pos_relative_8px.y);

	m_MapProcessor.move_map_32px(move_x_32px, move_y_32px);

}

/*************************************************************************************************/

void GamePlay::unload_level(void)
{
	delete(m_Scenery);
	delete(m_Character);
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

	dmaCopy(sprites_dataSharedPal, SPRITE_PALETTE, sprites_dataSharedPalLen);
}
