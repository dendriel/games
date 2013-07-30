/*
 * Scenery.cpp
 *
 *  Created on: 29/07/2013
 *      Author: vitor
 */

#include "Scenery.h"
#include "viewpoints.h"

/*************************************************************************************************/

Scenery::Scenery(Video& video):
m_Video(video)
{
	VisualElement *under_layer0 = new(VisualElement);
	SDL_Surface *layer = NULL;
	SDL_Rect layer_bound;
	layer_bound.x = 20;
	layer_bound.y = 15;

	if (build_layer(&layer, layer_bound, layer0) != 0) {
		cout << "Failed to build scenery under layer." << endl;
		return;
	}
	under_layer0->set_viewpoint(layer, 0);
	m_UnderLayer_list.push_back(under_layer0);

	video.push_under_layer(under_layer0->m_Viewpoints[0]);
}


