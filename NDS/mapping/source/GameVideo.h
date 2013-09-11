/*
 * BackgroundControl.h
 *
 *  Created on: 07/09/2013
 *      Author: vitor
 */

#ifndef GAMEVIDEO_H_
#define GAMEVIDEO_H_

#include <nds.h>

#include "GameMap.h"
#include "util.h"


class GameVideo {
private:
	GameMap *m_LoadedMap;
	st_offset m_LoadedMap_offset;

public:

	/**
	 * \brief Class constructor.
	 */
	GameVideo(void);

	/**
	* \brief Load the given map into the game.
	* \parameter map Map to be loaded.
	* \parameter x Starting horizontal position of the map.
	* \parameter y Starting vertical position of the map.
	* \note First form will use the own map specified starting point.
	*/
	void load_Map(GameMap *map);
	void load_Map(GameMap *map, const int x, const int y);

	/**
	 * \brief Scroll the Layer_index by x,y offset.
	 * \parameter layer_index The layer index
	 * \parameter x Horizontal offset.
	 * \parameter x Vertical offset.
	 */
	void scroll_Layer(const unsigned int bg_index, const int x, const int y);

	/**
	 * \brief Scroll all the background layers by x,y offset.
	 * \parameter x Horizontal offset.
	 * \parameter x Vertical offset.
	 */
	void scroll_Background(const int x, const int y);

private:

	/**
	 * \brief Copy the half screen data from Layer_index.
	 * \parameter vertical_offset used to copy the half-bottom screen data.
	 * \parameter bg_weight_tiles Used to offset until the next line when copying a half.
	 * \parameter bg_data The background data to copy.
	 * \parameter destination A reference to the destination.
	 */
	void copy_LayerChunk(
			const int vertical_offset,
			const size_t bg_weight_tiles,
			const unsigned short *bg_data,
			u16 *destination);
	
	void draw_LayerQuarter(
		const en_screen_quarter screen_quarter,
		const unsigned short *origin,
		u16 *dest,
		const size_t bg_weight_tiles);
};

#endif /* GAMEVIDEO_H_ */
