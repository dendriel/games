/*
 * Maze2.h
 *
 *  Created on: 08/09/2013
 *      Author: vitor
 */

#ifndef MAZE2_H_
#define MAZE2_H_

#include "maze2_data.h"

class Maze2: public GameMap {

public:
	/**
	 * \brief Class constructor.
	 */
	Maze2(void)
	{
		const size_t bg_max = 2;
		const unsigned int tile_base = 1;

		/* Map size in pixels. */
		const unsigned int size_pixel_w = 512;
		const unsigned int size_pixel_h = 512;

		/* Map size in tiles 8x8 pixels. */
		m_SizeTile_8px.w = size_pixel_w/8;
		m_SizeTile_8px.h = size_pixel_h/8;

		/* Map size in tiles 32x32 pixels. */
		m_SizeTile_32px.w = size_pixel_w/32;
		m_SizeTile_32px.h = size_pixel_h/32;

		/* How much layers there is in the map. */
		m_LayersCount = bg_max;

		/* Hold backgrounds data. */
		for (size_t i = 0; i < bg_max; ++i) {
			m_Background[i].layer = i;
			m_Background[i].size = BgSize_T_512x512;
			m_Background[i].type = BgType_Text8bpp;
			m_Background[i].tileBase = tile_base;
			/* Inverse drawing priority. */
			m_Background[i].prio = (bg_max-1)-i;
		}

		m_Background[0].data = maze2_layer1Map;
		m_Background[1].data = maze2_layer2Map;
		for (size_t base = 4, old = 0, i = 0; i < bg_max; ++i) {
			/* Which gives 0, 4, 12.
			 * Just to refresh: "Thompson and Dennis Ritchie favored simplicity over perfection."
			 * and, "KISS" Keep It Simply, Stupid.
			 */
			m_Background[i].dataBase = (i*base) + old;
			old = m_Background[i].dataBase;
		}

		//!< Hold the tiles palette for every background.
		m_Tiles = maze2SharedTiles;

		//!< Hold the tiles length.
		m_TilesLen = maze2SharedTilesLen;

		//!< Background palette.
		m_Palette = maze2SharedPal;

		//!< Background palette length.
		m_PaletteLen = maze2SharedPalLen;
	}
};

#endif /* MAZE2_H_ */
