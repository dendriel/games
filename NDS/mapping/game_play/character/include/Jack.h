/*
 * Jack.h
 *
 *  Created on: 12/10/2013
 *      Author: vitor
 */

#ifndef JACK_H_
#define JACK_H_

#include "GameCharacter.h"
#include "util.h"

/**
 * \brief Player character class.
 */
class Jack: public GameCharacter {
public:
	/**
	 * \brief Class constructor.
	 */
	Jack(const unsigned int x = SPRITE_SCREEN_CENTER_X, const unsigned int y = SPRITE_SCREEN_CENTER_Y);
};

#endif /* JACK_H_ */
