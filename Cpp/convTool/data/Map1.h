/*
 * Map1.h
 *
 *  Created on: 19/09/2013
 *      Author: vitor
 */

#ifndef MAP1_H_
#define MAP1_H_

#include "GameMap.h"
#include "map1_data.h"
#include "mytiles_tileset.h"

class Map1: public GameMap {
public:
	/**
	 * \brief Class constructor.
	 */
	Map1(void) {
		//!< How much layers there is in the map.
		m_LayersCount = 1;

		/* Hold backgrounds data. */
		for (size_t i = 0; i < m_LayersCount; ++i) {
		//	m_Background[i].layer = i;
			//m_Background[i].size = BgSize_T_256x256;
			//m_Background[i].type = BgType_Text8bpp;
			//m_Background[i].tileBase = tile_base;
			/* Inverse drawing priority. */
			//m_Background[i].prio = (bg_max-1)-i;

			m_Background[i].tileset.map = mytiles_map;
			m_Background[i].tileset.data = mytiles_sharedTiles;
			m_Background[i].tileset.len_bytes = mytiles_len_bytes;
			m_Background[i].tileset.len_memb = mytiles_len_memb;
			m_Background[i].tileset.dim_tiles.w = mytiles_width_tiles;
			m_Background[i].tileset.dim_tiles.h = mytiles_height_tiles;

			m_Background[i].palette = mytiles_sharedPal;
			m_Background[i].palette_len_bytes = mytiles_sharedPalLen;
		}

		m_Background[0].data = map1_Map;
		m_Background[0].width_tiles = map1_WidthTiles;
		m_Background[0].height_tiles = map1_HeightTiles;

		//m_Background[1].data = Layer_2Map;
		//m_Background[2].data = Layer_3Map;
		//for (size_t base = 4, old = 0, i = 0; i < m_LayersCount; ++i) {
			/* Which gives 0, 4, 12.
			 * Just to refresh: "Thompson and Dennis Ritchie favored simplicity over perfection."
			 * and, "KISS" Keep It Simply, Stupid.
			 */
		//	m_Background[i].dataBase = (i*base) + old;
		//	old = m_Background[i].dataBase;
		//}

		//!< Character starting point.
		//m_CharStartPoint.x = 3;
		//m_CharStartPoint.y = 3;
	}
};

#endif /* MAP1_H_ */
