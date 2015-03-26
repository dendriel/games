/*
 * main.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: vitor.rozsa
 */

#include <stdlib.h>

// Internal libs.
#include "GamePlay.h"

#include "Stage01.h"


using namespace std;


int main(int argc, char *argv[])
{
	GamePlay *game = new GamePlay();

	game->load();

	free(game);

	return 0;
}
