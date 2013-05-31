#include <allegro.h>
#include <fcntl.h>
#include <pthread.h>

#include "game_defines.h"
#include "game_structs.h"
#include "gameSystem.h"
#include "gameSystem_defines.h"
#include "gameVideo.h"
#include "gameVideo_defines.h"

#include "mixedAPI.h"
#include "mixedAPI_defines.h"
#include "debug.h"


/*************************************************************************************************/
/**
 *	\b Requests to the gameVideo module to halt.
 *	\r GAME_RET_SUCCESS if could sucessfully send the request;
 *	GAME_RET_ERROR otherwise.
 */
static en_game_return_code gameSystem_halt_video(void);


static en_game_return_code gameSystem_add_scenery_into_screen(void);

/*************************************************************************************************/

void gameSystem_main(void)
{
	int ret;
	int **th_ret = NULL;
	pthread_t mod_th_list[GAMESYSTEM_MAX_TH_ID];

	debug("Initialize allegro engine general elements...");
	ret = gameSystem_engine_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game system engine.");
		exit(-1);
	}

	debug("Initialize allegro engine media...");
	ret = gameSystem_media_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game media dependences.");
		exit(-1);
	}

	debug("Initialize gameVideo module...");
	ret = gameVideo_init(&mod_th_list[GAMESYSTEM_VIDEO_TH_ID]);
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game video module.");
		exit(-1);
	}

	sleep(1); // wait the gameVideo sub-module to take place.testing purpose
	// Testing purpose only.
	debug("Add scenary element into the screen...");
	gameSystem_add_scenery_into_screen();

	sleep(5);

	debug("Sending halt solicitation to gameVideo module...");
	gameSystem_halt_video();
	pthread_join(mod_th_list[GAMESYSTEM_VIDEO_TH_ID], (void *)&th_ret);
	debug("gameVideo module halted.");

	//cfg_iniciaConfig();						//	config.c		//
	//
	//iniciaItems();							//	item.c			//
	//
	//iniciaChar();							//	charEngine.c	//
	//
	//pcl_carregaMapa(1, 12, 9, sul);			//	gameEngine.c	//

	//pcl_principal(1);						//	gameEngine.c	//
    
	debug("Uninstall allegro elements...");
	gameSystem_engine_exit();

	debug("Exiting...");
}

/*************************************************************************************************/

// TESTING PURPOSE ONLY!!!!
static en_game_return_code gameSystem_add_scenery_into_screen(void)
{
	en_mixed_return_code ret;
	mqd_t gvideo_mqueue;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	ret = mixed_open_mqueue(&gvideo_mqueue,
							GAMEVIDEO_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_SEND_MODE);
	if (ret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Fill the message. */
	msg.id = GAMEBRAIN_MOD_ID;
	msg.type = GAME_ACTION_ADD_SCREEN_ELEM;

	/* Fill visual elements. */
	msg.v_elem.type = GAMEVIDEO_VTYPE_SCEN_STATIC;
	msg.v_elem.h = 20;
	msg.v_elem.v = 25;
	msg.v_elem.image = load_bitmap("./media/img/campo_batalha.bmp", NULL);

	if (!msg.v_elem.image) {
		critical("Failed to load scenery bitmap.");
		mixed_close_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);
	}

	ret = mq_send(gvideo_mqueue, (void *)&msg, GAME_MQUEUE_SIZE, GAME_MQUEUE_PRIO_1);

	if (ret != 0) {
		critical("Failed to send message. errno: %d; msg: %s\n", errno, strerror(errno));
		mixed_close_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);
		return GAME_RET_ERROR;
	}

	mixed_close_mqueue_sender(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);

	return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

static en_game_return_code gameSystem_halt_video(void)
{
	en_mixed_return_code ret;
	mqd_t gvideo_mqueue;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	ret = mixed_open_mqueue(&gvideo_mqueue,
							GAMEVIDEO_MQUEUE_NAME,
							GAME_MQUEUE_SIZE,
							GAME_MQUEUE_SEND_MODE);
	if (ret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	/* Fill the message. */
	msg.id = GAMESYSTEM_MOD_ID;
	msg.type = GAME_ACTION_HALT_MODULE;

	ret = mq_send(gvideo_mqueue, (void *)&msg, GAME_MQUEUE_SIZE, GAME_MQUEUE_PRIO_0);
	if (ret != 0) {
		critical("Failed to send message. errno: %d; msg: %s\n", errno, strerror(errno));
		mixed_close_mqueue(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);
		return GAME_RET_ERROR;
	}

	mixed_close_mqueue_sender(&gvideo_mqueue, GAMEVIDEO_MQUEUE_NAME);

	return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

en_game_return_code gameSystem_engine_init(void)
{
	int ret;

	/* Init allegro engine general support. */
	ret = allegro_init();
	if (ret != 0) {
		critical("Failed to initialize allegro engine.");
		return GAME_RET_ERROR;
	}

	/* Init time operation support. */
	ret = install_timer();
	if (ret != 0) {
		critical("Failed to install allegro timer support.");
		return GAME_RET_ERROR;
	}

	/* Init keyboard I/O support. */
	ret = install_keyboard();
	if (ret != 0) {
		critical("Failed to install allegro keyboard support.");
		return GAME_RET_ERROR;
	}

	/* Init mouse support. TODO: maybe will not be used. */
    //install_mouse();


    return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

en_game_return_code gameSystem_media_init(void)
{
	int ret;
	int card_mode;

	/* Set color depth configurations. */
	set_color_depth(GAMESYSTEM_COLOR_BITS);

#if defined(RUN_FULLSCREEN)
	card_mode = GFX_AUTODETECT_FULLSCREEN;
#else
	card_mode = GFX_SAFE;
#endif
	/* Starts the graphic window. */
	ret = set_gfx_mode(card_mode,
						GAMESYSTEM_MAX_X,
						GAMESYSTEM_MAX_Y,
						GAMESYSTEM_VMAX_X,
						GAMESYSTEM_VMAX_Y);
	if (ret != 0) {
		critical("Failed to setup graphic interface.");
		return GAME_RET_ERROR;
    }

	return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

void gameSystem_engine_exit()
{
	remove_keyboard();

	remove_timer();

	allegro_exit();
}

/*************************************************************************************************/


