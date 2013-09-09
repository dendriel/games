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
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
}

/*************************************************************************************************/

void GameVideo::load_Map(GameMap *map)
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

	/* Draw map. */
	for (i = 0; i < map->m_LayersCount; ++i) {

		u16* background = (u16*)bgGetMapPtr(map->m_Background[i].id);

		/* Draw top half. */
		copy_LayerChunk(NO_VERTICAL_OFFSET, map->m_SizeTile.w, map->m_Background[i].data, background);

		/* Give an offset to start drawing the bottom half. */
		background += VERTICAL_OFFSET*VERTICAL_OFFSET*TILE_LEN_BYTES;

		/* Draw bottom half. */
		copy_LayerChunk(VERTICAL_OFFSET, map->m_SizeTile.w, map->m_Background[i].data, background);
	}

	m_LoadedMap = map;
}

/*************************************************************************************************/

void GameVideo::scroll_Background(const int x, const int y)
{
	unsigned int i;
	for (i = 0; i < m_LoadedMap->m_LayersCount; ++i) {
		bgSetScroll(m_LoadedMap->m_Background[i].id, x, y);
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

void GameVideo::copy_LayerChunk(
	const int vertical_offset,
	const size_t bg_weight_tiles,
	const unsigned short *bg_data,
	u16 *destination)
{
	int origin_offset = 0;
	int dest_offset = 0;
	const unsigned int mem_to_copy = TILES_TO_CP*TILE_LEN_BYTES;

	for(int iy = 0; iy < 32; iy++) 	{

		origin_offset = (iy + vertical_offset) * bg_weight_tiles;
		dest_offset = iy * TILES_TO_CP;

		/* Copy the left half. */
		dmaCopy(bg_data + origin_offset, destination + dest_offset,  mem_to_copy);

		/* Copy the right  half. */
		origin_offset += 32;	// bottom-right half map's data offset;
		dest_offset += 32 * 32;	// bottom-right half destination's data offset;
		dmaCopy(bg_data + origin_offset, destination + dest_offset,  mem_to_copy);
	}
}

