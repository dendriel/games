/*
 * Rock1.cpp
 *
 *  Created on: 01/08/2013
 *      Author: vitor
 */


#include "Rock1.h"

#include "utils.h"

Rock1::Rock1(const int x, const int y, const string image, const unsigned int positions, const unsigned int views):
Object(x, y, image, positions, views)
{
	for (unsigned int i = 0; i < array_length(rock1_coll_vertices); ++i) {
		add_vertex(rock1_coll_vertices[i]);
	}
	cout << "Rock1 created!" << endl;
}
