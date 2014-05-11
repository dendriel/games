/*
 * scen0.h
 *
 *  Created on: 30/07/2013
 *      Author: vitor
 */

#ifndef SCEN0_H_
#define SCEN0_H_


/**
 * Structures.
 */
//!< Represents a cartographic position.
typedef struct {
	int x;
	int y;
} st_element_pos;


/* TESTING PURPOSE ONLY!!! */
unsigned int layer0[] = {
		1,1,1,1,1,1,1,1, //1
		2,0,0,0,0,0,0,1,
		2,1,1,1,1,1,1,1,
		2,0,0,0,0,0,0,1,
		2,0,0,0,0,0,1,1, //5
		2,0,0,0,0,0,1,1,
		2,3,3,3,3,1,1,1,
		2,3,3,3,3,3,3,3,
};

st_element_pos layer0_bounds = {8, 8};

#endif /* SCEN0_H_ */
