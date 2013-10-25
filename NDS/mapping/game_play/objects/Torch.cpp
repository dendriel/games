/*
 * Torch.cpp
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#include "Torch.h"
#include "sprites_data.h"

static st_rect Torch_rect_size(0,0,32,32);
#define TORCH_OBJECT_NAME "torch"

Torch::Torch(const unsigned int x_8px, const unsigned int y_8px, bool display):
GameObject(Torch_rect_size,
		(u8*)torch_data_256Tiles,
		x_8px, y_8px,
		GAMEOBJECT_TYPE_0,
		SPRITE_FACING_NONE,
		TORCH_OBJECT_NAME,
		display)
{}

