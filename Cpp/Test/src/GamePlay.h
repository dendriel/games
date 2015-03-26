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
#include "VisualElement.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GamePlay
{
private:
	GameVideo *screen;
	GameAtlas *atlas;
	GameStage *stage;
	VisualElement *backgroud;

	/**
	 * @brief Initialize everything that is necessary for the game.
	 */
	void initResources(void);
	void finalizeResources(void);
	void loadBackground(GameStage *stage, VisualElement *background);

	void unload(void);
	void loop(void);

public:
	GamePlay();
	virtual ~GamePlay();

	void load();
};

#endif /* GAMEPLAY_H_ */
