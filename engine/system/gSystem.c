#include <allegro.h>
#include <fcntl.h>
#include <pthread.h>

#include "gSystem.h"
#include "gSystem_defines.h"
#include "game_defines.h"
#include "game_structs.h"
#include "gVideo.h"
#include "gVideo_defines.h"
#include "gBrain_video_intf.h"
#include "gBrain.h"
#include "gBrain_defines.h"

#include "mixedAPI.h"
#include "debug.h"


/*************************************************************************************************/
/**
 *	\b Hold game modules threads ID. Used to whe halting the game (join the threads).
 */
static pthread_t mod_th_list[GSYSTEM_MAX_TH_ID];


/*************************************************************************************************/
/**
 *	\b Initialize game system basics and launch modules threads.
 */
static void gSystem_init(void);

/*************************************************************************************************/
/**
 *	\b Join the game modules threads and free the resources.
 */
static void gSystem_exit();

/*************************************************************************************************/
/**
 *	\d Initialize the allegro library and install components (keyboard, mouse)
 *	\r GAME_RET_SUCCESS for successfuly execution;
 *	GAME_RET_ERROR for error in the execution.
 */
static en_game_return_code gSystem_engine_init(void);

/*************************************************************************************************/
/**
 *	\d Initialize the media components (audio, video).
 *	\r GAME_RET_SUCCESS for successfuly execution;
 *	GAME_RET_ERROR for error in the execution.
 */
static en_game_return_code gSystem_media_init(void);

/*************************************************************************************************/
/**
 *	\b Initialize basic game modules.
 */
static void gSystem_init_modules(void);

/*************************************************************************************************/
/**
 *	\b Send halt request to the given module.
 *	\p module The mqueue name of the module to be halted.
 *	\r GAME_RET_SUCCESS if could send the request; GAME_RET_ERROR otherwise.
 */
static en_game_return_code gSystem_halt_module(const char *module);

/*************************************************************************************************/
/**
 *	\b Halt the game modules.
 */
static void gSystem_finish_modules(void);

/*************************************************************************************************/

static void gSystem_test_load_scenery(void);

/*************************************************************************************************/

void gSystem_main(void)
{
	debug("Starting the game system...");
	gSystem_init();

	sleep(1); // wait the gameVideo sub-module to take place.testing purpose
	gSystem_test_load_scenery();
	sleep(3);

	debug("Finishing the game system...");
	gSystem_exit();

	debug("Exiting...");
}

/*************************************************************************************************/

static void gSystem_test_load_scenery(void)
{
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	msg.id = GSYSTEM_MOD_ID;
	msg.type = GAME_ACTION_LOAD_SCENERY;

	// Testing purpose only.
	debug("Add scenary element into the screen...");
	mixed_mqueue_send(GBRAIN_MQUEUE_NAME, GAME_MQUEUE_PRIO_2, &msg);
}

/*************************************************************************************************/

static void gSystem_init(void)
{
	en_game_return_code ret;

	debug("Initialize allegro engine general elements...");
	ret = gSystem_engine_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game system engine.");
		exit(-1);
	}

	debug("Initialize allegro engine media...");
	ret = gSystem_media_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game media dependences.");
		gSystem_exit();
		exit(-1);
	}

	gSystem_init_modules();
}

/*************************************************************************************************/

static void gSystem_init_modules(void)
{
	en_game_return_code ret;

	debug("Initialize game video module...");
	ret = gVideo_init(&mod_th_list[GSYSTEM_VIDEO_TH_ID]);
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game video module.");
		gSystem_exit();
		exit(-1);
	}

	debug("Initialize game brain module...");
	ret = gBrain_init(&mod_th_list[GSYSTEM_BRAIN_TH_ID]);
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game brain module.");
		gSystem_exit();
		exit(-1);
	}
}

/*************************************************************************************************/

static void gSystem_finish_modules(void)
{
	unsigned int id;
	int th_ret;

	debug("Sending halt solicitation to game video module...");
	gSystem_halt_module(GVIDEO_MQUEUE_NAME);

	debug("Sending halt solicitation to game brain module...");
	gSystem_halt_module(GBRAIN_MQUEUE_NAME);

	for (id = 1; id < GSYSTEM_MAX_TH_ID; id++) {
		pthread_join(mod_th_list[id], (void *)&th_ret);
		debug("Module %d has halted with value %d.", id, th_ret);
	}

	debug("The game modules were halted.");
}

/*************************************************************************************************/

static en_game_return_code gSystem_halt_module(const char *module)
{
	en_mixed_return_code ret;
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	/* Fill the message. */
	msg.id = GSYSTEM_MOD_ID;
	msg.type = GAME_ACTION_HALT_MODULE;

	ret = mixed_mqueue_send(module,
								GAME_MQUEUE_PRIO_0,
								&msg);
	if (ret != MIXED_RET_SUCCESS) {
		return GAME_RET_ERROR;
	}

	return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

static en_game_return_code gSystem_engine_init(void)
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

static en_game_return_code gSystem_media_init(void)
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

static void gSystem_exit()
{
	/* Halt the game modules before releasing the resources. */
	gSystem_finish_modules();

	remove_keyboard();

	remove_timer();

	allegro_exit();
}

/*************************************************************************************************/


