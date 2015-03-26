/*
 * Stage.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vitor
 */

#ifndef GAMESTAGE_H_
#define GAMESTAGE_H_

#include <string>

#include "Spritesheet.h"

class GameStage
{
protected:
	std::string _texture_name;
	Spritesheet *_sheet;

public:
	GameStage();
	virtual ~GameStage();

	inline std::string texture_name(void)
	{
		return _texture_name;
	}

	inline Spritesheet *sheet(void)
	{
		return _sheet;
	}
};

#endif /* GAMESTAGE_H_ */
