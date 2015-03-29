/*
 * StageDefault.h
 *
 *  Created on: Mar 29, 2015
 *      Author: vitor
 */

#ifndef STAGEDEFAULT_H_
#define STAGEDEFAULT_H_

#include "GameStage.h"

#include "SDL.h"

class StageDefault: public GameStage
{
public:
	StageDefault(SDL_Renderer *renderer);
	virtual ~StageDefault();
};

#endif /* STAGEDEFAULT_H_ */
