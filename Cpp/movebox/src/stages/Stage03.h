/*
 * Stage03.h
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#ifndef STAGE03_H_
#define STAGE03_H_

#include "StageDefault.h"

#include "SDL.h"

class Stage03: public StageDefault
{
public:
	Stage03(SDL_Renderer *renderer);
	virtual ~Stage03();
};

#endif /* STAGE03_H_ */
