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
#include "SDL_ttf.h"

#include "GameVideo.h"
#include "GameAtlas.h"
#include "GameStage.h"
#include "VisualElement.h"
#include "Bug.h"


//Screen dimension constants
#define SCREEN_WIDTH 764
#define SCREEN_HEIGHT 640
#define GAME_FRAMERATE 60
#define SLEEP_BETWEEN_UPDATE 1000/GAME_FRAMERATE

class GamePlay
{
private:
	GameVideo *screen;
	GameAtlas *atlas;
	GameStage *stage;
	VisualElement *background;
	Bug *player;
	std::vector<VisualElement *> box_list;
	std::vector<int> map_state;
	unsigned short int num_of_target;	// aux variable that will contain the size of target_pos_list.
	unsigned short int box_on_target;
	std::vector<GameStage *> stage_list;
	SDL_Point stage_offset;
	TTF_Font *text_font;

	/**
	 * @brief Initialize everything that is necessary for the game.
	 */
	void initResources(void);
	void finalizeResources(void);

	/**
	 * @brief Show main menu.
	 */
	void showMainMenu(void);
	void hideMainMenu(void);

	/**
	 * @brief Controls the game loop (pop, load and play stages. Check for victory condition).
	 */
	void mainLoop(void);

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

	void showStageIntro(const unsigned int stage);

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
	 * @brief Starts the main engine.
	 */
	void play(void);
};

#endif /* GAMEPLAY_H_ */
