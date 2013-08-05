/*
 * CollisionElement.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef COLLISIONELEMENT_H_
#define COLLISIONELEMENT_H_

#include <iostream>
#include <vector>
#include "SDL/SDL.h"

using namespace std;

typedef enum {
	INANIMATED = 0,
	ANIMATED
} en_collElement_type;

typedef enum {
	VERTEX_POINT_UPLEFT = 0,
	VERTEX_POINT_UPRIGHT = 1,
	VERTEX_POINT_DOWNLEFT = 2,
	VERTEX_POINT_DOWNRIGHT = 3,

} en_vertex_points;

typedef struct {
	SDL_Rect point;
	double area_id[4];	//!< One area ID for each vertex point.
	// callback
} st_collVertex;

class CollisionElement {
private:
	const en_collElement_type m_Type;

public:
	CollisionElement(const en_collElement_type type = INANIMATED);

	en_collElement_type type(void);

	/**
	 * \brief Add a vertex into the list.
	 * \parameter vertex The vertex that will be added in the list.
	 */
	void add_vertex(const st_collVertex& vertex);

public:
	vector<st_collVertex> m_Vertices;
};


#endif /* COLLISIONELEMENT_H_ */
