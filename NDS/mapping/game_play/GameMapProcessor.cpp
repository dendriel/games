/*
 * GameMapProcessor.cpp
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#include "GameMapProcessor.h"

#include <assert.h>
#include <string.h>
#include <assert.h>

/* References */
#include "nds/arm9/video.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/background.h"

/* Game related includes */
#include "util.h"


/* Definitions */
#define TILE_LEN_BYTES 2
#define TILES_TO_CP 32
#define TILE_SIZE 32
#define MAP_H_SIZE 184
#define VERTICAL_OFFSET 32
#define NO_VERTICAL_OFFSET 0

/*************************************************************************************************/
/* Public Functions Declaration																	 */
/*************************************************************************************************/

GameMapProcessor::GameMapProcessor(void):
m_LoadedMap(0)
{
	this->clean_resources();
}


/*************************************************************************************************/

void GameMapProcessor::clean_resources(void)
{
	memset(&m_LoadedMap_bounds_8px, 0, sizeof(m_LoadedMap_bounds_8px));
	memset(&m_LoadedMap_offset_8px, 0, sizeof(m_LoadedMap_offset_8px));
}

/*************************************************************************************************/

void GameMapProcessor::load_Map(GameMap *map)
{
	size_t i;

	/*if ((x_offset_32px < SPRITE_SCREEN_CENTER_X_TILES) || (y_offset_32px < SPRITE_SCREEN_CENTER_Y_TILES) ||
			(x_offset_32px > (map->m_SizeTile_32px.w - SPRITE_SCREEN_CENTER_X_TILES)) ||
			(y_offset_32px > (map->m_SizeTile_32px.h - SPRITE_SCREEN_CENTER_Y_TILES))) {
		debug("Invalid character starting point.");
		assert(0);
		return;
	}*/

	for (i = 0; i < map->m_LayersCount; ++i) {
		/* Initialize the layers of the background. */
		map->m_Background[i].id = bgInit(
			map->m_Background[i].layer,
			map->m_Background[i].type,
			map->m_Background[i].size,
			map->m_Background[i].dataBase,
			map->m_Background[i].tileBase);
		/* Set layers priority. */
		bgSetPriority(map->m_Background[i].id, map->m_Background[i].prio);
	}

	/* Set map palette. */
	dmaCopy(map->m_Tiles, bgGetGfxPtr(map->m_Background[0].id), map->m_TilesLen);
	dmaCopy(map->m_Palette, BG_PALETTE, map->m_PaletteLen);

	/* Draw map. TODO: maybe for smaller maps this will try to copy invalid data. */
	m_LoadedMap = map;

	/* Find map data loading bounds.
	 *
	 * Map origin = 0,0 8px;
	 * Map max is the size of the map in tiles of 8px minus a screen of 128x128px
	 *
	 */
	m_LoadedMap_bounds_8px.w = m_LoadedMap->m_SizeTile_8px.w - PIXEL_TO_TILE_8PX(SCREEN_WIDTH);
	m_LoadedMap_bounds_8px.h = m_LoadedMap->m_SizeTile_8px.h - PIXEL_TO_TILE_8PX(SCREEN_HEIGHT);

	/* Starting offset must be given with the move map function. */
	m_LoadedMap_offset_8px.x = 0;//TILE_32PX_TO_8PX(x_offset_32px);
	m_LoadedMap_offset_8px.x = 0;//TILE_32PX_TO_8PX(y_offset_32px);

	this->draw_LoadedMap();

	/* Draw the loaded map at the given position. */
	//this->move_map_32px((x_offset_32px - SPRITE_SCREEN_CENTER_X_TILES),
		//	(y_offset_32px - SPRITE_SCREEN_CENTER_Y_TILES));
}

/*************************************************************************************************/

int GameMapProcessor::move_map_8px(const int x, const int y)
{
	/* Right now, can move to only one direction per frame. */

	en_direction load_data = DIRECT_NONE;

	/* Find which direction. */
	if (x < 0) {
		load_data = DIRECT_LEFT;
	}
	else if (y < 0) {
		load_data = DIRECT_UP;
	}
	else if (x > 0) {
		load_data = DIRECT_RIGHT;
	}
	else if (y > 0) {
		load_data = DIRECT_DOWN;
	}
	/* x = 0; y = 0 */
	else {
		return 0;
	}

	//debug("Direction: %d", load_data);

	if (load_MapData_8px(load_data) != 0) {
		/* Map limits reached. */
		//debug("Invalid bounds");
		return -1;
	}

	draw_LoadedMap();

	return 0;
}

/*************************************************************************************************/

int GameMapProcessor::load_MapData_8px(en_direction direction)
{
	switch(direction) {
		case DIRECT_LEFT:
			if ((m_LoadedMap_offset_8px.x - 1) < 0) {
				/* There is no more tiles to the left. */
				//debug("data_offset.pos.x: %d", m_LoadedMap_data_offset.pos.x);
				return -1;
			}
			m_LoadedMap_offset_8px.x -= 1;
		break;
		case DIRECT_UP:
			if ((m_LoadedMap_offset_8px.y - 1) < 0) {
				/* There is no more tiles to the top. */
				//debug("data_offset.pos.y: %d", m_LoadedMap_data_offset.pos.y);
				debug("returned here up!!");
				return -1;
			}
			m_LoadedMap_offset_8px.y -= 1;
		break;
		case DIRECT_RIGHT:
			if ((m_LoadedMap_offset_8px.x + 1) > m_LoadedMap_bounds_8px.w) {
				/* There is no more tiles to the right. */
				//debug("data_offset.pos.x: %d", m_LoadedMap_data_offset.pos.x);
				return -1;
			}
			m_LoadedMap_offset_8px.x += 1;
		break;
		case DIRECT_DOWN:
			// higher or equal??
			if ((m_LoadedMap_offset_8px.y + 1) > m_LoadedMap_bounds_8px.h) {
				/* There is no more tiles to the bottom. */
				//debug("data_offset.pos.y: %d", m_LoadedMap_data_offset.pos.y);
				return -1;
			}
			m_LoadedMap_offset_8px.y += 1;
		break;
		default:
			/* Unhandled direction. */
			return -1;
		break;
	}

	return 0;
}

/*************************************************************************************************/

void GameMapProcessor::move_map_32px(const int x, const int y)
{
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < TILE_8PX_IN_TILE_32PX; ++j) {
			this->move_map_8px(1, 0);
		}
	}

	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < TILE_8PX_IN_TILE_32PX; ++j) {
			this->move_map_8px(0, 1);
		}
	}
}

/*************************************************************************************************/

int GameMapProcessor::check_static_collision(const int x, const int y)
{
	// TODO:
	for (unsigned int layer = 0; layer < m_LoadedMap->m_LayersCount; ++layer) {
		//m_LoadedMap->m_CollisionMap[layer]
	}
	return 0;
}

/*************************************************************************************************/
/* Private Functions Declaration																 */
/*************************************************************************************************/

void GameMapProcessor::draw_LoadedMap(void)
{
	unsigned int i;

	for (i = 0; i < m_LoadedMap->m_LayersCount; ++i) {

		u16* screen_mem = (u16*)bgGetMapPtr(m_LoadedMap->m_Background[i].id);

		draw_LayerQuarter(FIRST_QUARTER, m_LoadedMap->m_Background[i].data, screen_mem);
		// TODO: support more sizes.
		if (m_LoadedMap->m_Background[i].size  != BgSize_T_512x512) {
			continue;
		}
		draw_LayerQuarter(SECOND_QUARTER, m_LoadedMap->m_Background[i].data, screen_mem);
		draw_LayerQuarter(THIRD_QUARTER, m_LoadedMap->m_Background[i].data, screen_mem);
		draw_LayerQuarter(FOURTH_QUARTER, m_LoadedMap->m_Background[i].data, screen_mem);
	}
}

/*************************************************************************************************/

void GameMapProcessor::draw_LayerQuarter(
	const en_screen_quarter screen_quarter,
	const unsigned short *origin,
	u16 *dest)
{
	const unsigned int map_width = m_LoadedMap->m_SizeTile_8px.w;
	const unsigned int mem_to_copy = TILES_TO_CP*TILE_LEN_BYTES;
	const unsigned int map_data_offset = m_LoadedMap_offset_8px.x +
											m_LoadedMap_offset_8px.y*m_LoadedMap->m_SizeTile_8px.w;
	int origin_offset = 0;
	int dest_offset = 0;
	int origin_quarter_offset = 0;
	int dest_quarter_offset = 0;
	int origin_vertical_offset = 0;
	int dest_vertical_offset = 0;
	
	switch (screen_quarter) {
		case FIRST_QUARTER:
		break;
		case SECOND_QUARTER:
			// TODO: Find out why these values.
			origin_quarter_offset = 32;
			dest_quarter_offset = 128*8; // offset to the left size of the screen (128*8 tiles).
		break;
		case FOURTH_QUARTER:
			origin_quarter_offset = 32;
			dest_quarter_offset = 128*8;
		case THIRD_QUARTER:
			origin_vertical_offset = VERTICAL_OFFSET;
			dest_vertical_offset = VERTICAL_OFFSET*VERTICAL_OFFSET*TILE_LEN_BYTES;
		break;
		default:
			debug("Invalid quarter received.");
		break;
	}
	
	for(int iy = 0; iy < 32; iy++) {

		origin_offset = ((origin_vertical_offset + iy) * map_width) + origin_quarter_offset + map_data_offset;
		dest_offset = (iy * TILES_TO_CP) + dest_quarter_offset + dest_vertical_offset;
		dmaCopy(origin + origin_offset, dest + dest_offset,  mem_to_copy);
	}
}

