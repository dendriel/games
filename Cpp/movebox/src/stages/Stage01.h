/*
 * Stage01.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#ifndef STAGE01_H_
#define STAGE01_H_

#include "StageDefault.h"

#include "SDL.h"

class Stage01: public StageDefault
{
public:
	Stage01(SDL_Renderer *renderer);
	virtual ~Stage01();
};

#endif /* STAGE01_H_ */
