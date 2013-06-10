#include <allegro.h>
#include <fcntl.h>
#include <pthread.h>

#include "gSystem.h"
#include "gSystem_defines.h"
#include "gSystem_structs.h"

#include "game_defines.h"
#include "game_structs.h"

#include "gSystem_loop.h"
#include "gVideo.h"
#include "gVideo_defines.h"
#include "gBrain.h"
#include "gBrain_defines.h"
#include "gController.h"
#include "gController_defines.h"

#include "mixedAPI.h"
#include "debug.h"


/*************************************************************************************************/
/**
 *	\b Hold game modules general informations. Keep order with en_gsystem_tid from gSystem_defines.
 */
static st_mod_data Gsystem_modules[] = {
	{0, "System"	, GSYSTEM_MQUEUE_NAME		, (void *)gSystem_init		, true	, false},
	{0, "Brain"		, GBRAIN_MQUEUE_NAME		, (void *)gBrain_init		, true	, false},
	{0, "Video"		, GVIDEO_MQUEUE_NAME		, (void *)gVideo_init		, true	, false},
	{0, "Controller", GCONTROLLER_MQUEUE_NAME	, (void *)gController_init	, true	, false}
};

/**************************************************************************************************/
/**
 *	\b Game system module name. Used to debug.
 */
char Gsystem_label[GAME_MOD_LABEL_SIZE] = "";

/*************************************************************************************************/
/**
 *	\b Initialize game system basics and launch modules threads.
 */
static void gSystem_init_basics(void);

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
	debug("", "Starting the game system...");
	gSystem_init_basics();

	sleep(1); // wait the gameVideo sub-module to take place.testing purpose
	gSystem_test_load_scenery();

	/* Go to game system main loop. */
	gSystem_loop();

	debug(Gsystem_label, "Finishing the game system...");
	gSystem_exit();

	debug(Gsystem_label, "Exiting...");
}

/*************************************************************************************************/

en_game_return_code gSystem_init(pthread_t *thread_id, const char mod_name[GAME_MOD_LABEL_SIZE])
{
	if (strlen(mod_name)) {
		strncpy(Gsystem_label, mod_name, sizeof(Gsystem_label));
	}

	*thread_id = -1;

	return GAME_RET_SUCCESS;
}

/*************************************************************************************************/

static void gSystem_test_load_scenery(void)
{
	st_game_msg msg;

	memset(&msg, 0, sizeof(msg));

	msg.id = GSYSTEM_MOD_ID;
	msg.type = GAME_ACTION_LOAD_SCENERY;

	// Testing purpose only.
	debug("", "Add scenary element into the screen...");
	mixed_mqueue_send(GBRAIN_MQUEUE_NAME, GAME_MQUEUE_PRIO_2, &msg);
}

/*************************************************************************************************/

static void gSystem_init_basics(void)
{
	en_game_return_code ret;

	debug("", "Initialize allegro engine general elements...");
	ret = gSystem_engine_init();
	if (ret != GAME_RET_SUCCESS) {
		critical("Failed to initialize game system engine.");
		exit(-1);
	}

	debug("", "Initialize allegro engine media...");
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
	unsigned int mod;

	/* Launch each module in the list. */
	for(mod = 0; mod < GSYSTEM_MAX_TID; mod++) {

		if (Gsystem_modules[mod].execute) {
			debug(Gsystem_label, "Initialize game %s module...", Gsystem_modules[mod].label);
			ret = Gsystem_modules[mod].mod_init(&Gsystem_modules[mod].tid, Gsystem_modules[mod].label);

			if (ret != GAME_RET_SUCCESS) {
				critical("Failed to initialize game %s module.", Gsystem_modules[mod].label);
				gSystem_exit();
				exit(-1);
			}
			Gsystem_modules[mod].initialized = true;
		}
	}
}

/*************************************************************************************************/

static void gSystem_finish_modules(void)
{
	unsigned int mod;
	int th_ret;

	/* Send halt solicitation. mod=0 is the own system module. */
	for (mod = 1; mod < GSYSTEM_MAX_TID; mod++) {

		if (Gsystem_modules[mod].initialized) {
			debug(Gsystem_label, "Sending halt solicitation to game %s module...", Gsystem_modules[mod].label);
			gSystem_halt_module(Gsystem_modules[mod].mqueue);
		}
	}

	/* Receive acknowledge. */
	for (mod = 1; mod < GSYSTEM_MAX_TID; mod++) {

		if (Gsystem_modules[mod].initialized) {
			pthread_join(Gsystem_modules[mod].tid, (void *)&th_ret);
			debug(Gsystem_label, "Module %s has halted with value %d.", Gsystem_modules[mod].label, th_ret);
		}
	}

	debug(Gsystem_label, "The game modules were halted.");
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


