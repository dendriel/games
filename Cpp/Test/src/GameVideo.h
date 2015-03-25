/*
 * GameVideo.h
 *
 *  Created on: Mar 24, 2015
 *      Author: vitor
 */

#ifndef GAMEVIDEO_H_
#define GAMEVIDEO_H_

#include <string>
#include <vector>
#include <map>

#include "SDL.h"

#include "GameAtlas.h"
#include "VisualElement.h"

class GameVideo
{
private:
	SDL_Window *window;
	SDL_Renderer *_renderer;
	std::vector<VisualElement *> element_list;
	GameAtlas *atlas;

public:
	GameVideo();
	virtual ~GameVideo();

	/**
	 * @brief Allocate resources for game video.
	 */
	void init(std::string label="My Game", unsigned int width=800, unsigned int height=600);

	/**
	 * @brief Free resources from game video.
	 */
	void finalize(void);

	SDL_Renderer *renderer() const { return _renderer;}

	/**
	 * @brief Update screen.
	 */
	void update(void);

	/**
	 * @brief Load atlas in game video so it can search the visual element sprite information.
	 */
	void loadAtlas(GameAtlas *atlas);

	/**
	 * @brief Add element into the drawing list.
	 */
	void addElement(VisualElement *element);
};

#endif /* GAMEVIDEO_H_ */
