/*
 * CollisionElement.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef COLLISIONELEMENT_H_
#define COLLISIONELEMENT_H_

#include <vector>
#include "SDL/SDL.h"

using namespace std;

typedef enum {
	INANIMATED = 0,
	ANIMATED
} en_collElement_type;

typedef struct {
	SDL_Rect point;
	double area_id;
	// callback
} st_collVertex;

class CollisionElement {
private:
	const en_collElement_type m_Type;

public:
	CollisionElement(const en_collElement_type type = INANIMATED);

	inline en_collElement_type type(void)
	{
		return m_Type;
	}

	/**
	 * \brief Add a vertex into the list.
	 * \parameter vertex The vertex that will be added in the list.
	 */
	void add_vertex(const st_collVertex& vertex);

public:
	vector<st_collVertex> m_Vertices;
};


#endif /* COLLISIONELEMENT_H_ */
