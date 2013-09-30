/*
 * GameMapProcessor.cpp
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#include "GameMapProcessor.h"

#include <assert.h>
#include <string.h>

/* References */
#include "nds/arm9/video.h"
#include "nds/arm9/console.h"
#include "nds/arm9/input.h"
#include "nds/arm9/background.h"

/* Game related includes */
#include "util.h"

/* Scenery */
#include "maze1.h"


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
	memset(&m_ScrollOffset, 0, sizeof(m_ScrollOffset));
	memset(&m_LoadedMap_data_offset, 0, sizeof(m_LoadedMap_data_offset));

	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
}

/*************************************************************************************************/

void GameMapProcessor::load_Map(GameMap *map)
{
	load_Map(map, map->m_CharStartPoint.x, map->m_CharStartPoint.y);
}

/*************************************************************************************************/

void GameMapProcessor::load_Map(GameMap *map, const int x, const int y)
{
	size_t i;

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

	//consoleInit(0, 3, BgType_Text4bpp, BgSize_T_512x512, 31, 3, true, true);

	/* Set map palette. */
	dmaCopy(map->m_Tiles, bgGetGfxPtr(map->m_Background[0].id), map->m_TilesLen);
	dmaCopy(map->m_Palette, BG_PALETTE, map->m_PaletteLen);

	/* Draw map. TODO: maybe for smaller maps this will try to copy invalid data. */

	m_LoadedMap = map;

	/* Find scroll bounds. */
	//if (m_LoadedMap->m_background[0].size == BgSize_T_512x512) {
		m_ScrollOffset.w = 512 - SCREEN_WIDTH;
		m_ScrollOffset.h = 512 - SCREEN_HEIGHT;
	//}
	/* Find map data loading bounds. */
	m_LoadedMap_data_offset.w = (m_LoadedMap->m_SizeTile32.w - 512/32);
	m_LoadedMap_data_offset.h = (m_LoadedMap->m_SizeTile32.h - 512/32);

	m_ScrollOffset.pos.x = x;
	m_ScrollOffset.pos.y = y;

	draw_LoadedMap();
}

/*************************************************************************************************/

void GameMapProcessor::scroll_Background(const int x, const int y)
{
	/* Can't offset more than 1 tile per frame. */
	if ((x > TILE_SIZE || x < TILE_SIZE*-1) || (y > TILE_SIZE || y < TILE_SIZE*-1)) {
		return;
	}

	unsigned int i;
	en_direction load_data = DIRECT_NONE;
	const int new_scroll_x = m_ScrollOffset.pos.x + x;
	const int new_scroll_y = m_ScrollOffset.pos.y + y;

	/* Check bounds. Map will always start at origin 0,0. */
	if (new_scroll_x < 0) {
		load_data = DIRECT_LEFT;
	}
	else if (new_scroll_y < 0) {
		load_data = DIRECT_UP;
	}
	else if (new_scroll_x > (int)m_ScrollOffset.w) {
		load_data = DIRECT_RIGHT;
	}
	else if (new_scroll_y > (int)m_ScrollOffset.h) {
		load_data = DIRECT_DOWN;
	}

	if (load_data) {
		debug("Direction: %d", load_data);
		if (load_MapData(load_data) != 0) {
			// map limits reached.
			debug("Invalid bounds");
			return;
		}
	}

	m_ScrollOffset.pos.x += x;
	m_ScrollOffset.pos.y += y;

	for (i = 0; i < m_LoadedMap->m_LayersCount; ++i) {
		bgSetScroll(m_LoadedMap->m_Background[i].id, m_ScrollOffset.pos.x, m_ScrollOffset.pos.y);
	}

	draw_LoadedMap();
	bgUpdate();
}

/*************************************************************************************************/

int GameMapProcessor::load_MapData(en_direction direction)
{
	switch(direction) {
		case DIRECT_LEFT:
			if ((m_LoadedMap_data_offset.pos.x - 1) < 0) {
				/* There is no more tiles to the left. */
				debug("data_offset.pos.x: %d", m_LoadedMap_data_offset.pos.x);
				return -1;
			}
			m_LoadedMap_data_offset.pos.x -= 1;
			m_ScrollOffset.pos.x += TILE_SIZE;
		break;
		case DIRECT_UP:
			if ((m_LoadedMap_data_offset.pos.y - 1) < 0) {
				/* There is no more tiles to the top. */
				debug("data_offset.pos.y: %d", m_LoadedMap_data_offset.pos.y);
				return -1;
			}
			m_LoadedMap_data_offset.pos.y -= 1;
			m_ScrollOffset.pos.y += TILE_SIZE;
		break;
		case DIRECT_RIGHT:
			if ((m_LoadedMap_data_offset.pos.x + 1) > (int)m_LoadedMap_data_offset.w) {
				/* There is no more tiles to the right. */
				debug("data_offset.pos.x: %d", m_LoadedMap_data_offset.pos.x);
				debug("m_LoadedMap_data_offset.w: %d", m_LoadedMap_data_offset.w);
				return -1;
			}
			m_LoadedMap_data_offset.pos.x += 1;
			m_ScrollOffset.pos.x -= TILE_SIZE;
		break;
		case DIRECT_DOWN:
			if ((m_LoadedMap_data_offset.pos.y + 1) > (int)m_LoadedMap_data_offset.h) {
				/* There is no more tiles to the bottom. */
				debug("data_offset.pos.y: %d", m_LoadedMap_data_offset.pos.y);
				return -1;
			}
			m_LoadedMap_data_offset.pos.y += 1;
			m_ScrollOffset.pos.y -= TILE_SIZE;
		break;
		default:
			/* Unhandled direction. */
			return -1;
		break;
	}

	debug("data_offset.pos.x: %d; scroll.x: %d", m_LoadedMap_data_offset.pos.x, m_ScrollOffset.pos.x);
	debug("data_offset.pos.y: %d; scroll.y: %d", m_LoadedMap_data_offset.pos.y, m_ScrollOffset.pos.y);

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
	const unsigned int map_width = m_LoadedMap->m_SizeTile.w;
	const unsigned int mem_to_copy = TILES_TO_CP*TILE_LEN_BYTES;
	const unsigned int map_data_offset = m_LoadedMap_data_offset.pos.x*4 + m_LoadedMap_data_offset.pos.y*m_LoadedMap->m_SizeTile.w*4;
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

