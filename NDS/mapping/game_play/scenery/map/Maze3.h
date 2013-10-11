/*
 * Maze3.h
 *
 *  Created on: 24/09/2013
 *      Author: vitor
 */

#ifndef MAZE3_H_
#define MAZE3_H_

#include "map1_data.h"
#include "Mytiles_ts.h"
#include "util.h"

class Maze3: public GameMap {
private:
	//TODO: this data don't need to be a GameMap attribute (update: maybe must be).
	Mytiles_ts m_Tileset;

public:
	/**
	 * \brief Class constructor.
	 */
	Maze3(void)
	{
		const size_t bg_max = 1;
		const unsigned int tile_base = 1;

		/* Map size in tiles 8x8 pixels. */
		m_SizeTile_8px.w = map1_data_width_memb;
		m_SizeTile_8px.h = map1_data_height_memb;

		/* Map size in tiles 32x32 pixels. */
		m_SizeTile_32px.w = map1_data_width_memb/4;
		m_SizeTile_32px.h = map1_data_height_memb/4;

		/* How much layers there is in the map. */
		m_LayersCount = bg_max;

		/* Hold backgrounds data. */
		for (size_t i = 0; i < bg_max; ++i) {
			m_Background[i].layer = i;
			m_Background[i].size = BgSize_T_256x256;
			m_Background[i].type = BgType_Text8bpp;
			m_Background[i].tileBase = tile_base;
			/* Inverse drawing priority. */
			m_Background[i].prio = (bg_max-1)-i;

			/* Set Static Collision domain for this background. */
			for (unsigned int pos = 0; pos < (sizeof(map1_data_raw)/4); pos++) {

				const unsigned int coll_map_index = map1_data_raw[pos];
				const unsigned int coll_type = m_Tileset.collision_map[coll_map_index];

				m_CollisionMap[i].push_back(coll_type);
			}
		}

		m_Background[0].data = map1_data_map;

		for (size_t base = 4, old = 0, i = 0; i < bg_max; ++i) {
			/* Which gives 0, 4, 12.
			 * Just to refresh: "Thompson and Dennis Ritchie favored simplicity over perfection."
			 * and, "KISS" Keep It Simply, Stupid.
			 */
			m_Background[i].dataBase = (i*base) + old;
			old = m_Background[i].dataBase;
		}

		//!< Hold the tiles palette for every background.
		m_Tiles = m_Tileset.data;

		//!< Hold the tiles length.
		m_TilesLen =  m_Tileset.data_len_bytes;

		//!< Background palette.
		m_Palette = m_Tileset.pallete;

		//!< Background palette length.
		m_PaletteLen = m_Tileset.pallete_len_bytes;
	}
};


#endif /* MAZE3_H_ */
