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
	inline void loadAtlas(GameAtlas *atlas)
	{
		this->atlas = atlas;
	}

	/**
	 * @brief Add element into the drawing list.
	 */
	inline void addElement(VisualElement *element)
	{
		element_list.push_back(element);
	}

	inline void removeElement(VisualElement *element)
	{
		for (std::vector<VisualElement *>::iterator iter = element_list.begin(); iter != element_list.end(); iter++)
		{
			if (*iter == element)
			{
				element_list.erase(iter);
				return;
			}
		}
		assert_exit("VisualElement was not found in the list.");
	}

	/**
	 * @brief Clear elements list.
	 */
	inline void removeAllElements(void)
	{
		element_list.clear();
	}
};

#endif /* GAMEVIDEO_H_ */
