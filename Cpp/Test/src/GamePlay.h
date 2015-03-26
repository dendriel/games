/*
 * GamePlay.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_


#include "SDL.h"

#include "GameVideo.h"
#include "GameAtlas.h"
#include "GameStage.h"

class GamePlay
{
private:
	GameVideo *screen;
	GameAtlas *atlas;
	GameStage *stage;

	/**
	 * @brief Initialize everything that is necessary for the game.
	 */
	void initResources(void);
	void finalizeResources(void);

	SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer);
	Spritesheet *createSpritesheet(SDL_Renderer *renderer);

	void unload(void);
	void loop(void);

public:
	GamePlay();
	virtual ~GamePlay();

	void load();
};

#endif /* GAMEPLAY_H_ */
