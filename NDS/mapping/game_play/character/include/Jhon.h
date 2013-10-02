/*
 * Jhon.h
 *
 *  Created on: 26/09/2013
 *      Author: vitor
 */

#ifndef JHON_H_
#define JHON_H_

#include "GameCharacter.h"
#include "util.h"

/* Game resources */
#include "man.h"

/**
 * \brief Player character class.
 */
class Jhon: public GameCharacter {
public:
	/**
	 * \brief Class constructor.
	 */
	Jhon(const unsigned int x = SPRITE_SCREEN_CENTER_X, const unsigned int y = SPRITE_SCREEN_CENTER_Y);
};


#endif /* JHON_H_ */
