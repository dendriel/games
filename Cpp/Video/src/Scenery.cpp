/*
 * Scenery.cpp
 *
 *  Created on: 29/07/2013
 *      Author: vitor
 */

#include "Scenery.h"

#include <unistd.h>

#include "enemies.h"
#include "objects.h"
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
	m_CollDomain_dynamic.build_collAreas(area_size);
	m_CollDomain_static.build_collAreas(area_size);

	under_layer0->set_viewpoint(layer, 0);
	m_UnderLayer_list.push_back(under_layer0);

	video.push_under_layer(under_layer0->m_Viewpoints[0]);
}

/*************************************************************************************************/

Scenery::~Scenery(void)
{
	cout << "Scenery destroyed." << endl;
}

/*************************************************************************************************/

void Scenery::add_element(void *element)
{
	CollisionElement *collElement = (CollisionElement *)element;
	m_Video.add_visualElement((VisualElement *)element);

	if (collElement->type() == INANIMATED) {
		m_CollDomain_static.add_collisionElement((CollisionElement *)element);
	}
	else {
		m_CollDomain_dynamic.add_collisionElement((CollisionElement *)element);
	}

	cout << "Element added to scenery." << endl;
}

/*************************************************************************************************/

void Scenery::play(void)
{
	Character player;
	this->add_element(&player);

	GiantSpider crit(200, 200);
	this->add_element(&crit);

	Rock1 rock(120, 120);
	this->add_element(&rock);
	this->add_element(new Rock1(160, 160));

	m_Video.start();

	en_ctrl_actions action;

	while((action = m_Control.get_action()) != CTRL_EXIT) {
		switch (action) {
					// UP;
					case CTRL_MOVE_UP:
						player.move_up();
						break;
					// RIGHT
					case CTRL_MOVE_RIGHT:
						player.move_right();
						break;
					// DOWN:
					case CTRL_MOVE_DOWN:
						player.move_down();
						break;
					// LEFT
					case CTRL_MOVE_LEFT:
						player.move_left();
						break;
					case CTRL_NONE:
						player.stand();
						break;
					// STAND
					case CTRL_SUMMON:
						this->add_element(new GiantSpider(200, 200));
						break;
					default:
						cout << "invalid action: " << action << endl;
						break;
					}
		usleep(player.m_Speed_ms*MILI);
	}

	m_Control.get_keyDown();
	m_Video.freeze();
	m_Control.get_keyDown();
}
