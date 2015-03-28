/*
 * GamePlay.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <vector>

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
	VisualElement *player;
	std::vector<VisualElement *> box_list;
	std::vector<SDL_Point> target_pos_list;

	/**
	 * @brief Initialize everything that is necessary for the game.
	 */
	void initResources(void);
	void finalizeResources(void);
	/**
	 * @brief Load the background and look for the objects of the map (player, boxes and targets).
	 */
	void loadMap(GameStage *stage, VisualElement *background);
	/**
	 * @brief Load the visual elements that were collected in the loadMap phase.
	 */
	void loadVisualElements(void);

	void unload(void);
	void loop(void);

public:
	GamePlay();
	virtual ~GamePlay();

	void load();
};

#endif /* GAMEPLAY_H_ */
