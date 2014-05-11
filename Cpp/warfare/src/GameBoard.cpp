/*
 * GameBoard.cpp
 *
 *  Created on: 08/05/2014
 *      Author: vitor
 */

#include <iostream>
#include <Windows.h>
#include "assert.h"
#include "GameBoard.h"
#include "Controller.h"

#include "VisualElement.h"

#include "scen0.h"

//!< Default tile set data source.
#define TILESET_SOURCE "image/basic_tileset_128x128.bmp"
//!< Default tile size.
#define TILE_SIZE 32
#define RED 255
#define GREEN 0
#define BLUE 255
#define BPP 32

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
 * on the endianness (byte order) of the machine.
 */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

//!< Checks and print error if the operation fails.
#define CHK_NULL(_f)\
{\
	if ((_f) == NULL) {\
		cout << "Error occurred at " << #_f << endl;\
		return -1;\
	}\
}

GameBoard::GameBoard(Video& video, unsigned int width, unsigned int height):
m_Video(video),
m_Width(width),
m_Height(height)
{
	// TODO Auto-generated constructor stub

}

GameBoard::~GameBoard() {
	// TODO Auto-generated destructor stub
}

/**
 * \brief Build a scenery layer.
 * \param layer The surface that will contain the builded layer.
 * \param layer_bounds Contain the matrix maximum x and y.
 * \param tile_list The tile array.
 * \param source The tile set data source.
 * \return 0 for success; -1 for error.
 */
int build_layer_hex(SDL_Surface **layer,
		const st_element_pos layer_bounds,
		const unsigned int *tile_list,
		const string& source,
		const st_element_pos tile_size);

int load_surface(const char *source, SDL_Surface **surface);

void GameBoard::draw()
{
	Controller control;
	//VisualElement foo(100, 100);

	//SDL_Surface *img = NULL;
	//assert(load_surface("resources/sprites/warrior.bmp", &img) == 0);
	//foo.set_viewpoint(img, 0);

	SDL_Surface *board = NULL;
	st_element_pos tsize = {72,72};
	build_layer_hex(&board, layer0_bounds, layer0, "resources/tilesets/land.bmp", tsize);

	//m_Video.add_visualElement(&foo);

	m_Video.push_under_layer(board);

	m_Video.start();

	control.get_keyDown();
}


int load_surface(const char *source, SDL_Surface **surface)
{
	SDL_Surface *image_source;

	CHK_NULL(image_source = SDL_LoadBMP(source));
	CHK_NULL((*surface = SDL_DisplayFormat(image_source)));

	SDL_SetColorKey(*surface , SDL_SRCCOLORKEY, SDL_MapRGB((*surface)->format, RED, GREEN, BLUE));

	return 0;
}

/*************************************************************************************************/
/**
 * \brief Find x from a matrix with the array index.
 * \parameter index The position of the element in array representation.
 * \parameter x_max The width of the matrix.
 * \return The x coordinate in matrix representation.
 */
inline unsigned int find_x(const unsigned int index, const unsigned int x_max)
{
	return ((index % x_max) );
}
/**
 * \brief Find y from a matrix with the array index.
 * \parameter index The position of the element in array representation.
 * \parameter x_max The width of the matrix.
 * \parameter x The x coordinate that must be previous calculated.
 * \return The y coordinate in matrix representation.
 */
inline unsigned int find_y(const unsigned int index, const unsigned int x_max, const unsigned int x)
{
	return (((index - x)/x_max) );
}

#define hex_x_offset(px, py, hw) ((py%2 == 0)? px*hw : ((hw/2)+px*hw))
#define hex_y_offset(px, py, hh) ((py%2 == 0)? ((py == 0)? 0 : (py/2)*hh + (py/2)*hh/2) : (hh/4)*3*py)

int build_layer_hex(SDL_Surface **layer, const st_element_pos layer_bounds,
		const unsigned int *tile_list,
		const string& source,
		const st_element_pos tile_size)
{
	SDL_Surface *source_tileset = NULL;
	SDL_Surface *layer_temp = NULL;
	SDL_Rect tile_data = {0, 0, tile_size.x, tile_size.y};
	SDL_Rect draw_offset = {0, 0, 0, 0};
	const unsigned int tile_list_size = layer_bounds.x * layer_bounds.y;

	/* Load map tile set. */
	CHK_NULL((source_tileset = SDL_LoadBMP(source.c_str())));
	SDL_SetColorKey(source_tileset , SDL_SRCCOLORKEY, SDL_MapRGB(source_tileset->format, RED, GREEN, BLUE));

	/* Create layer surface.*/
	CHK_NULL((layer_temp = SDL_CreateRGBSurface(SDL_SWSURFACE,
			layer_bounds.x*tile_size.x + tile_size.x, layer_bounds.y*tile_size.y,
			BPP, rmask, gmask, bmask, amask)));

	for (unsigned int i = 0; i < tile_list_size; ++i) {
		unsigned int x;
		unsigned int y;

		x = find_x(i, layer_bounds.x);
		y = find_y(i, layer_bounds.x, x);
		draw_offset.x = hex_x_offset(x, y, tile_size.x);
		draw_offset.y = hex_y_offset(x, y, tile_size.y);
		cout << "Ploting: " << x << ", " << y << " even? " << (y%2 == 0) <<endl;
		cout << "offset: " << draw_offset.x << ", " << draw_offset.y << endl;

		tile_data.x = tile_size.x * find_x(tile_list[i], 4);
		tile_data.y = 0;

		SDL_BlitSurface(source_tileset, &tile_data, layer_temp, &draw_offset);
	}

	CHK_NULL((*layer = SDL_DisplayFormat(layer_temp)));
	/* Set transparency */
	//SDL_SetColorKey(*layer , SDL_SRCCOLORKEY, SDL_MapRGB((*layer)->format, RED, GREEN, BLUE));

	return 0;
}
