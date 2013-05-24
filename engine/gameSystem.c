#include <allegro.h>

#include "gameSystem.h"
#include "gameSystem_defines.h"
#include "gameVideo.h"

#include "debug.h"

/*************************************************************************************************/

void gameSystem_main(void)
{
	int ret;

	ret = gameSystem_engine_init();
	if (ret != GAME_RET_SUCCESS) {
		debug("Failed to initialize game system engine.");
		exit(-1);
	}

	ret = gameSystem_media_init();
	if (ret != GAME_RET_SUCCESS) {
		debug("Failed to initialize game media dependences.");
		exit(-1);
	}


	gameVideo_init();
	sleep(3);

	//cfg_iniciaConfig();						//	config.c		//
	//
	//iniciaItems();							//	item.c			//
	//
	//iniciaChar();							//	charEngine.c	//
	//
	//pcl_carregaMapa(1, 12, 9, sul);			//	gameEngine.c	//

	//pcl_principal(1);						//	gameEngine.c	//
    

	gameSystem_engine_exit();
}

/*************************************************************************************************/

game_return_code gameSystem_engine_init(void)
{
	int ret;

	/* Init allegro engine general support. */
	ret = allegro_init();
	if (ret != 0) {
		debug("Failed to initialize allegro engine.");
		return GAME_RET_ERROR;
	}

	/* Init keyboard I/O support. */
	install_keyboard();

	/* Init mouse support. TODO: maybe will not be used. */
    //install_mouse();

	/* Init time operation support. TODO: move this init*/
    install_timer();				//	Inicia Suporte para Operações com tempo.	//

    return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

game_return_code gameSystem_media_init(void)
{
	int ret;

	/* Set color depth configurations. */
	//TODO: verify return code.
	set_color_depth(GAMESYSTEM_COLOR_BITS);

//    if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, MAX_X, MAX_Y, VMAX_X, VMAX_Y)) //FULLSCREEN MODE
	/* Starts the graphic window. */
	ret = set_gfx_mode(GFX_SAFE,
						GAMESYSTEM_MAX_X,
						GAMESYSTEM_MAX_Y,
						GAMESYSTEM_VMAX_X,
						GAMESYSTEM_VMAX_Y);
	if (ret != 0) {
        //allegro_message("Erro ao carregar GFX (modo seguro falhou...)\nErro: %s", allegro_error);
		return GAME_RET_ERROR;
    }

	return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

void gameSystem_engine_exit()
{
	allegro_exit();
}

