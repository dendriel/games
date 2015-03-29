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
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class GamePlay
{
private:
	GameVideo *screen;
	GameAtlas *atlas;
	GameStage *stage;
	VisualElement *background;
	VisualElement *player;
	std::vector<VisualElement *> box_list;
	std::vector<int> map_state;
	unsigned short int num_of_target;	// aux variable that will contain the size of target_pos_list.
	unsigned short int box_on_target;
	std::vector<GameStage *> stage_list;

	/**
	 * @brief Initialize everything that is necessary for the game.
	 */
	void initResources(void);
	void finalizeResources(void);
	/**
	 * @brief Load the background and look for the objects of the map (player, boxes and targets).
	 */
	void loadMap();
	/**
	 * @brief Load the visual elements that were collected in the loadMap phase.
	 */
	void loadVisualElements(void);
	/**
	 * @brief In-game loop. Catch and dispatch player actions.
	 */
	int stageLoop(void);

	/**
	 * @brief Load stage data to play.
	 */
	void loadStage(void);
	void unloadStage(void);

	void movePlayer(SDL_Keycode dir);
	void checkMove(SDL_Point *target);
	VisualElement *getBoxAt(SDL_Point *pos);

	inline bool levelFinished(void)
	{
		return (num_of_target == box_on_target);
	}

public:
	GamePlay();
	virtual ~GamePlay();

	/**
	 * @brief Controls the game loop (pop, load and play stages. Check for victory condition).
	 */
	void mainLoop(void);
};

#endif /* GAMEPLAY_H_ */
