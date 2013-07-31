/*
 * Scenery.cpp
 *
 *  Created on: 29/07/2013
 *      Author: vitor
 */

#include "Scenery.h"
#include "viewpoints.h"


/* Testing purpose only! */
#include "utils.h"
#include <time.h>
#include "scen0.h"



/*************************************************************************************************/

Scenery::Scenery(Video& video):
m_Video(video)
{
	VisualElement *under_layer0 = new(VisualElement);
	SDL_Surface *layer = NULL;

	/* Testing purpose only! */
	size_t layer_len = array_length(layer0);
	srand(time(NULL)*(int)(this));
	/* Remove this thing. */
	for (unsigned int i = 0; i < layer_len; ++i) {
		layer0[i] = (rand() % 4) + 4;
	}/* Testing purpose only until here! */

	if (build_layer(&layer, layer0_bounds, layer0) != 0) {
		cout << "Failed to build scenery under layer." << endl;
		return;
	}

	st_element_pos area_size = {layer0_bounds.x*TILE_SIZE, layer0_bounds.y*TILE_SIZE};
	m_CollDomain.build_collAreas(area_size);

	under_layer0->set_viewpoint(layer, 0);
	m_UnderLayer_list.push_back(under_layer0);

	video.push_under_layer(under_layer0->m_Viewpoints[0]);
}

/*************************************************************************************************/

Scenery::~Scenery(void)
{
	cout << "Scenery destroyed." << endl;
}
