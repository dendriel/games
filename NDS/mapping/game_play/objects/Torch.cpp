/*
 * Torch.cpp
 *
 *  Created on: 13/10/2013
 *      Author: vitor
 */

#include "Torch.h"

static st_rect Torch_rect_size(0,0,32,32);

Torch::Torch(const unsigned int x_8px, const unsigned int y_8px):
GameObject(Torch_rect_size, (u8*)torch_dataTiles, x_8px, y_8px, SPRITE_FACING_NONE)
{}

