#ifndef STAGE16_H_
#define STAGE16_H_

#include "StageDefault.h"

#include "SDL.h"

class Stage16: public StageDefault
{
public:
	Stage16(SDL_Renderer *renderer);
	virtual ~Stage16();
};

#endif /* STAGE16_H_ */
