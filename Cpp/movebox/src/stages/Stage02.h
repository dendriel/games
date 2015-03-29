/*
 * Stage02.h
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#ifndef STAGE02_H_
#define STAGE02_H_

#include "StageDefault.h"

#include "SDL.h"

class Stage02: public StageDefault
{
public:
	Stage02(SDL_Renderer *renderer);
	virtual ~Stage02();
};

#endif /* STAGE02_H_ */
