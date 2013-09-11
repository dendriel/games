/*
 * BackgroundControl.cpp
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#include "GameVideo.h"

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
#define MAP_H_SIZE 184
#define VERTICAL_OFFSET 32
#define NO_VERTICAL_OFFSET 0


/*************************************************************************************************/
/* Public Functions Declaration																	 */
/*************************************************************************************************/

GameVideo::GameVideo(void):
m_LoadedMap(0)
{
	m_LoadedMap_offset.x = 0;
	m_LoadedMap_offset.y = 0;

	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
}

/*************************************************************************************************/

void GameVideo::load_Map(GameMap *map)
{
	load_Map(map, map->m_CharStartPoint.x, map->m_CharStartPoint.y);
}

/*************************************************************************************************/

void GameVideo::load_Map(GameMap *map, const int x, const int y)
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
	for (i = 0; i < map->m_LayersCount; ++i) {

		u16* screen_mem = (u16*)bgGetMapPtr(map->m_Background[i].id);

		draw_LayerQuarter(FIRST_QUARTER, map->m_Background[i].data, screen_mem,map->m_SizeTile.w);
		draw_LayerQuarter(SECOND_QUARTER, map->m_Background[i].data, screen_mem,map->m_SizeTile.w);
		draw_LayerQuarter(THIRD_QUARTER, map->m_Background[i].data, screen_mem,map->m_SizeTile.w);
		draw_LayerQuarter(FOURTH_QUARTER, map->m_Background[i].data, screen_mem,map->m_SizeTile.w);
	}

	m_LoadedMap = map;
	scroll_Background(x, y);
}

/*************************************************************************************************/

void GameVideo::scroll_Background(const int x, const int y)
{
	unsigned int i;

	/* Check bounds. Map will be always start at origin 0,0. */
	if ( ((m_LoadedMap_offset.x + x) < 0) || ((m_LoadedMap_offset.y + y) < 0) ||
		 ((m_LoadedMap_offset.x + x) > (int)SCREEN_DRAW_BOUND_X(m_LoadedMap->m_SizePixel.w)) ||
		 ((m_LoadedMap_offset.y + y) > (int)SCREEN_DRAW_BOUND_Y(m_LoadedMap->m_SizePixel.h)) ) {
		debug("Invalid bounds; x: %d; y: %d", (m_LoadedMap_offset.x + x), (m_LoadedMap_offset.y + y));
		return;
	}

	m_LoadedMap_offset.x += x;
	m_LoadedMap_offset.y += y;

	for (i = 0; i < m_LoadedMap->m_LayersCount; ++i) {
		bgSetScroll(m_LoadedMap->m_Background[i].id, m_LoadedMap_offset.x, m_LoadedMap_offset.y);
	}

	bgUpdate();
}

/*************************************************************************************************/

void GameVideo::scroll_Layer(const unsigned int layer_index, const int x, const int y)
{
	bgSetScroll(m_LoadedMap->m_Background[layer_index].id, x, y);

	bgUpdate();
}

/*************************************************************************************************/
/* Private Functions Declaration																 */
/*************************************************************************************************/

void GameVideo::draw_LayerQuarter(
	const en_screen_quarter screen_quarter,
	const unsigned short *origin,
	u16 *dest,
	const size_t bg_weight_tiles//, const unsigned int data_offset
	)
{
	/*
	 * TODO: I believe that the map data is organized as follow:
	 * 1111|3333
	 * 1111|3333
	 * ---------
	 * 2222|4444
	 * 2222|4444
	 *  Then, because of this whe can't copy the data continuously.
	 */
	const unsigned int mem_to_copy = TILES_TO_CP*TILE_LEN_BYTES;
	int origin_offset = 0;
	int dest_offset = 0;
	int origin_quarter_offset = 0;
	int dest_quarter_offset = 0;
	int origin_vertical_offset = 0;
	int dest_vertical_offset = 0;
	
	switch (screen_quarter) {
		case SECOND_QUARTER:
			// TODO: Find out why these values.
			origin_quarter_offset = 32;
			dest_quarter_offset = 32*32;
		break;
		case FOURTH_QUARTER:
			origin_quarter_offset = 32;
			dest_quarter_offset = 32*32;
		case THIRD_QUARTER:
			origin_vertical_offset = VERTICAL_OFFSET;
			dest_vertical_offset = VERTICAL_OFFSET*VERTICAL_OFFSET*TILE_LEN_BYTES;
		break;
		// Default choice.
		case FIRST_QUARTER:
		default:
			debug("Invalid quarter received.");
		break;
	}
	
	for(int iy = 0; iy < 32; iy++) 	{

		origin_offset = ((origin_vertical_offset + iy) * bg_weight_tiles) + origin_quarter_offset;
		dest_offset = (iy * TILES_TO_CP) + dest_quarter_offset + dest_vertical_offset;
		dmaCopy(origin + origin_offset, dest + dest_offset,  mem_to_copy);
	}	
}
