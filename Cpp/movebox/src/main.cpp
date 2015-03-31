/*
 * main.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: vitor.rozsa
 */

// Internal libs.
#include "GamePlay.h"


using namespace std;

int main(int argc, char *argv[])
{
	GamePlay *game = new GamePlay();

	game->play();

	free(game);

	return 0;
}
