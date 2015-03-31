/*
 * GamePlay.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vitor
 */

#include "GamePlay.h"

#include <iostream>
#include <sstream>

#include <assert.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "GameText.h"
#include "default_stages.h"

using namespace std;


GamePlay::GamePlay()
{
	initResources();
}

GamePlay::~GamePlay()
{
	finalizeResources();
}

void GamePlay::initResources(void)
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		assert_exit("SDL could not initialize! SDL_Error: " << SDL_GetError());
	}


	if( !(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
	{
		assert_exit("SDL_image could not initialize! SDL_image Error: " << IMG_GetError());
	}

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		assert_exit("SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError());
	}

	// Load global font.
	text_font = TTF_OpenFont( "fonts/04B_30__.ttf", 40);
	if(text_font == NULL)
	{
		assert_exit("Failed to load lazy font! SDL_ttf Error: " << TTF_GetError());
	}

	screen = new GameVideo();
	screen->init(GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	screen->setIcon("images/bug_icon.png");

	box_on_target = 0;
	num_of_target = 0;
	stage_offset = {0, 0};

	createStageList();

	// Load UI images (manually =P).
	atlas = new GameAtlas();
	atlas->addTexture("images/game_title_561x101.png", screen->renderer());
	atlas->addTexture("images/exit_game_blue_button_241x64.png", screen->renderer());
	atlas->addTexture("images/start_game_blue_button_241x64.png", screen->renderer());
}


void GamePlay::finalizeResources(void)
{
	// Free resources.
	delete(atlas);
	atlas = NULL;
	delete(screen);
	screen = NULL;

	TTF_CloseFont(text_font);
	text_font = NULL;

	// Quit SDL subsystems.
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GamePlay::createStageList(void)
{
	// Fill stage list.
	stage_list.push_back(new Stage17(screen->renderer()));
	stage_list.push_back(new Stage16(screen->renderer()));
	stage_list.push_back(new Stage15(screen->renderer()));
	stage_list.push_back(new Stage14(screen->renderer()));
	stage_list.push_back(new Stage13(screen->renderer()));
	stage_list.push_back(new Stage12(screen->renderer()));
	stage_list.push_back(new Stage11(screen->renderer()));
	stage_list.push_back(new Stage10(screen->renderer()));
	stage_list.push_back(new Stage09(screen->renderer()));
	stage_list.push_back(new Stage08(screen->renderer()));
	stage_list.push_back(new Stage07(screen->renderer()));
	stage_list.push_back(new Stage06(screen->renderer()));
	stage_list.push_back(new Stage05(screen->renderer()));
	stage_list.push_back(new Stage04(screen->renderer()));
	stage_list.push_back(new Stage03(screen->renderer()));
	stage_list.push_back(new Stage02(screen->renderer()));
	stage_list.push_back(new Stage01(screen->renderer()));
}

void GamePlay::play(void)
{
	SDL_Event e;

	showMainMenu();

	// Handle events on queue
	while( true )
	{
		SDL_PollEvent( &e );

		//User requests quit
		if( e.type == SDL_QUIT )
		{
			debug("Quit game!");
			return;
		}
		else if ( e.type == SDL_MOUSEBUTTONDOWN )
		{
			int x;
			int y;
			SDL_GetMouseState(&x, &y);

			// Start game button.
			if (Utils::checkInsideBounds(x, y, Utils::alignMiddle(0, SCREEN_WIDTH, 241), 300, 241, 64))
			{
				hideMainMenu();
				// Check if player quit.
				if (mainLoop() == 2)
				{
					return;
				}
				showMainMenu();
			}
			else if (Utils::checkInsideBounds(x, y, Utils::alignMiddle(0, SCREEN_WIDTH, 241), 400, 241, 64))
			{
				debug("Quit game!");
				return;
			}

		}

		screen->update();
		SDL_Delay(SLEEP_BETWEEN_UPDATE);
	}

	hideMainMenu();
}

void GamePlay::showMainMenu(void)
{
	srand(int(screen));
	int bg = rand() % stage_list.size();
	stage = stage_list[bg];

	loadStage();

	VisualElement *title = new VisualElement({Utils::alignMiddle(0, SCREEN_WIDTH, 561), 50}, "images/game_title_561x101.png");
	title->setSize({0, 0, 561, 101});

	VisualElement *start_game = new VisualElement({Utils::alignMiddle(0, SCREEN_WIDTH, 241), 300}, "images/start_game_blue_button_241x64.png");
	start_game->setSize({0, 0, 241, 64});

	VisualElement  *exit_button = new VisualElement({Utils::alignMiddle(0, SCREEN_WIDTH, 241), 400}, "images/exit_game_blue_button_241x64.png");
	exit_button->setSize({0, 0, 241, 64});

	screen->addElement(title);
	screen->addElement(start_game);
	screen->addElement(exit_button);

	screen->update();
}

void GamePlay::hideMainMenu(void)
{
	unloadStage();
}

void GamePlay::showStageIntro(const unsigned int stage, const unsigned int stage_max)
{
	GameText trans_msg;
	ostringstream sstream;
	sstream << "Stage " << stage;
	string text = sstream.str();

	trans_msg.setText(text_font, text, {0xff, 0xff, 0xff}, screen->renderer());
	trans_msg.setPos({Utils::alignMiddle(0, SCREEN_WIDTH, trans_msg.size().w), SCREEN_HEIGHT/2 - trans_msg.size().h});
	screen->addElement(&trans_msg);

	sstream.str("");
	sstream << GAME_TITLE << " - " << text << "/" << stage_max;
	screen->setTitle(sstream.str());
	screen->update();
	SDL_Delay(CHANGE_STAGE_DELAY_MS);
	screen->removeElement(&trans_msg);
}

void GamePlay::showGameOver(void)
{
	GameText gameover_msg;
	GameText gameover_msg2;

	gameover_msg.setText(text_font, GAMEOVER_MSG_1, {0xff, 0xff, 0xff}, screen->renderer());
	gameover_msg.setPos({Utils::alignMiddle(0, SCREEN_WIDTH, gameover_msg.size().w), SCREEN_HEIGHT/2 - gameover_msg.size().h});
	screen->addElement(&gameover_msg);


	gameover_msg2.setText(text_font, GAMEOVER_MSG_2, {0xff, 0xff, 0xff}, screen->renderer());
	gameover_msg2.setPos({Utils::alignMiddle(0, SCREEN_WIDTH, gameover_msg2.size().w), SCREEN_HEIGHT/2 + gameover_msg.size().h});
	screen->addElement(&gameover_msg2);

	screen->update();
	SDL_Delay(GAMEOVER_DELAY_MS);
	screen->removeElement(&gameover_msg);
	screen->removeElement(&gameover_msg2);
}

int GamePlay::mainLoop(void)
{
	const unsigned int stage_max = stage_list.size();
	unsigned int stage_counter = 1;
	bool stage_restarted = false;
	int state;

	// Stage list must have at least one stage.
	assert(stage_list.size() > 0);

	stage = stage_list[stage_list.size() - 1];
	stage_list.pop_back();

	do
	{
		// Load stage data.
		loadStage();

		// Display stage introduction if just entered here..
		if (stage_restarted != true)
		{
			showStageIntro(stage_counter, stage_max);
		}

		// Play stage.
		state = stageLoop();

		// Restart level.
		if (state == 1)
		{
			// Unload stage data.
			unloadStage();
			// Set stage restarted to avoid showing intro message again.
			stage_restarted = true;
			// Continue with the same stage from beginning.
			continue;
		}
		// Quit game.
		else if (state == 2)
		{
			return 2;
		}

		if (stage_list.size() == 0)
		{
			// Show game over before losing the stage background.
			showGameOver();
		}

		// Unload stage data.
		unloadStage();

		// Remove stage.
		delete(stage);
		stage = NULL;

		// Pop a new stage.
		if (stage_list.size() > 0)
		{
			stage = stage_list[stage_list.size() - 1];
			stage_list.pop_back();
			stage_counter++;
			stage_restarted = false;
		}
		else
		{
			stage = NULL;
		}

	} while (stage != NULL);

	createStageList();

	return 0;
}

void GamePlay::loadStage()
{
	// Fill atlas.
	atlas->addSheet(stage->sheet());
	screen->loadAtlas(atlas);

	background = new VisualElement();

	loadMap();
}

void GamePlay::unloadStage(void)
{
	// Clear screen.
	screen->removeAllElements();
	screen->loadAtlas(NULL);

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		delete(*iter);
	}
	box_list.clear();

	delete(player);
	player = NULL;

	delete(background);
	background = NULL;

	atlas->clearAllSheets();

	num_of_target = 0;
	box_on_target = 0;

	// Clear current id map.
	map_state.clear();

	stage_offset = {0, 0};

	screen->update();
}

void GamePlay::loadMap()
{
	int *map_arr = stage->map_arr();
	SDL_Rect map_size = stage->map_size();
	SDL_Rect map_size_pixel = stage->map_size_pixel();

	SDL_Texture *texture = SDL_CreateTexture(this->screen->renderer(),
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			map_size_pixel.w,
			map_size_pixel.h);

	SDL_SetRenderTarget(this->screen->renderer(), texture);

	// Calculate stage offset.
	if ( SCREEN_WIDTH > map_size_pixel.w)
	{
		stage_offset.x = (SCREEN_WIDTH - map_size_pixel.w) / 2;
	}

	if (SCREEN_HEIGHT > map_size_pixel.h)
	{
		stage_offset.y = (SCREEN_HEIGHT - map_size_pixel.h) / 2;
	}

	for (int h = 0; h < map_size.h; h++)
	{
		for (int w = 0; w < map_size.w; w++)
		{
			int pos = h*map_size.w + w;
			int tile_id = map_arr[pos];

			map_state.push_back(tile_id);

			// 0 = empty tile.
			if (tile_id == 0)
			{
				continue;
			}

			// Look for player starting position.
			if (tile_id == stage->player_id())
			{
				// If this position is the player position, change the internal map state to ground.
				map_state[map_state.size() - 1] = stage->ground_id();

				player = new Bug(stage->player_sprite(), w*64 + stage_offset.x, h*64 + stage_offset.y);
				//player = new Bug(stage->player_sprite(), w*64, h*64);
				// Draw ground in the background instead of the player. The player will be drawn latter.
				tile_id = map_state[map_state.size() - 1];
			}
			// Look for boxes starting position.
			else if ( (tile_id == stage->box_id()) || (tile_id == stage->box_done_id()) )
			{
				VisualElement *box = new VisualElement({w*64 + stage_offset.x, h*64 + stage_offset.y});
				box->addSprite(stage->box_done_sprite());
				box->addSprite(stage->box_sprite());
				box_list.push_back(box);

				// If box is over a target.
				if (tile_id == stage->box_done_id())
				{
					box->setSprite(stage->box_done_sprite());
					num_of_target++;
					box_on_target++;
					// Draw ground in the background instead of the box. The box will be drawn latter.
					tile_id = stage->target_id();
				}
				else
				{
					// Draw ground in the background instead of the box. The box will be drawn latter.
					tile_id = stage->ground_id();
				}
			}
			// Look for targets starting position.
			else if (tile_id == stage->target_id())
			{
				num_of_target++;
			}

			Spritesheet *sheet = this->atlas->getSheet(tile_id);
			GameSprite *sprite = sheet->getSprite(tile_id);
			SDL_Rect destn = {w*64, h*64, 64, 64};

			SDL_RenderCopy(screen->renderer(), sheet->texture(), &sprite->frame, &destn);
		}
	}

	background->setPos(stage_offset);
	background->setTexture(texture);
	background->setSize(map_size_pixel);

	// Restore default rendering target.
	SDL_SetRenderTarget(screen->renderer(), NULL);

	// Load moveable Elements.
	loadVisualElements();

	// Can't start a level that is already finished.
	assert(box_on_target < num_of_target);
}

void GamePlay::loadVisualElements(void)
{
	screen->addElement(background);
	screen->addElement(player);

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		screen->addElement(*iter);
	}
}

/**
 * Return codes.
 * 0 = stage cleared.
 * 1 = replay stage.
 * 2 = Player exited the game.
 */
int GamePlay::stageLoop(void)
{
	SDL_Event e;

	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_KEYUP);

	/**
	 * We want to allow the player to move one square per key press/release. So we will keep track
	 * of the key status here. Can move only if the key was released.
	 */
	bool can_move = true;

	// Handle events on queue
	while( true )
	{
		SDL_PollEvent( &e );

		//User requests quit
		if( e.type == SDL_QUIT )
		{
			cout << "Quit game!" << endl;
			return 2;
		}
		//User presses a key
		else if ( (e.type == SDL_KEYDOWN) && can_move)
		{
			// Restart stage.
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				return 1;
			}
			// Skip stage.
			else if (e.key.keysym.sym == SDLK_BACKSPACE)
			{
				return 0;
			}
			// Move player.
			else
			{
				movePlayer(e.key.keysym.sym);
				can_move = false;
			}
		}
		else if ( e.type == SDL_KEYUP)
		{
			can_move = true;
		}

		SDL_FlushEvent(SDL_KEYDOWN);
		SDL_FlushEvent(SDL_KEYUP);
		screen->update();

		if (levelFinished() == true)
		{
			cout << "Victory!" << endl;
			return 0;
		}

		SDL_Delay(SLEEP_BETWEEN_UPDATE);
	}

	return 0;
}

void GamePlay::movePlayer(SDL_Keycode dir)
{
	SDL_Point orientation;

	switch(dir)
	{
		case SDLK_UP:
		case SDLK_w:
			orientation = {0, -1};
			break;

		case SDLK_DOWN:
		case SDLK_s:
			orientation = {0, 1};
			break;

		case SDLK_LEFT:
		case SDLK_a:
			orientation = {-1, 0};
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			orientation = {1, 0};
			break;

		default:
			return;
	}

	checkMove(&orientation);
}

// I don't like very much passing pointer to such small variable, but.. looks like we will save some
// memory.
void GamePlay::checkMove(SDL_Point *orientation)
{
	SDL_Point origin = { (player->posX() - stage_offset.x) / 64, (player->posY() - stage_offset.y) / 64};
	SDL_Rect map_size = stage->map_size();

	SDL_Point destn;

	// Set target position in the matrix.
	destn = {origin.x + orientation->x, origin.y + orientation->y};

	// Translate matrix position to array position.
	int pos = destn.y*map_size.w + destn.x;
	int tile_id = map_state[pos];

	//debug("Move to " << tile_id);

	// Move box.
	if ( (tile_id == stage->box_id()) || (tile_id == stage->box_done_id()) )
	{
		SDL_Point destn_after = {origin.x + orientation->x*2, origin.y + orientation->y*2};
		int pos_after =  destn_after.y*map_size.w + destn_after.x;
		int tile_id_after = map_state[pos_after];

		if ( (tile_id_after != stage->ground_id()) &&
				(tile_id_after != stage->target_id()) )
		{
			// The box can,'t move if the next tile isn't ground or target.
			return;
		}

		VisualElement *box = getBoxAt(&destn);
		box->addPos({orientation->x * 64, orientation->y * 64});

		// Next position is a target.
		if (map_state[pos_after] == stage->target_id())
		{
			map_state[pos_after] = stage->box_done_id();
			box->setSprite(stage->box_done_sprite());
			box_on_target++;
		}
		else
		{
			map_state[pos_after] = stage->box_id();
			box->setSprite(stage->box_sprite());
		}

		// Free the position.
		if (map_state[pos] == stage->box_done_id())
		{
			map_state[pos] = stage->target_id();
			box_on_target--;
		}
		else
		{
			map_state[pos] = stage->ground_id();
		}

		// Move the player.
		//player->setPos({destn.x * 64, destn.y * 64});
		player->addPos({orientation->x*64, orientation->y*64});
	}
	else if ( (tile_id == stage->ground_id()) || (tile_id == stage->target_id()) )
	{
		player->addPos({orientation->x*64, orientation->y*64});
	}

	return;
}

VisualElement *GamePlay::getBoxAt(SDL_Point *pos)
{
	SDL_Point pos_pixels = {pos->x * 64 + stage_offset.x, pos->y *64 + stage_offset.y};

	for(std::vector<VisualElement *>::iterator iter=box_list.begin(); iter != box_list.end(); iter++)
	{
		VisualElement *box = *iter;

		if ( (box->posX() == pos_pixels.x) && (box->posY() == pos_pixels.y) )
		{
			return box;
		}
	}

	cout << "The box at position " << pos_pixels.x << "," << pos_pixels.y << " was not found!" << endl;
	assert(0);
	return NULL;
}
