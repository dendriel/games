#include <allegro.h>

#include "system.h"
#include "system_defines.h"


system_return_code system_engine_init(void)
{
	int ret;

	/* Init allegro engine general support. */
	ret = allegro_init();
	if (ret != 0) {
		// TODO: put debug.
		return SYSTEM_RET_ERROR;
	}

	/* Init keyboard I/O support. */
	install_keyboard();

	/* Init mouse support. TODO: maybe will not be used. */
    //install_mouse();

	/* Init time operation support. TODO: move this init*/
    install_timer();				//	Inicia Suporte para Operações com tempo.	//

    return SYSTEM_RET_SUCCESS;
}

system_return_code system_media_init(void)
{
	int ret;

	/* Set color depth configurations. */
	//TODO: verify return code.
	set_color_depth(SYSTEM_COLOR_BITS);

//    if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, MAX_X, MAX_Y, VMAX_X, VMAX_Y)) //FULLSCREEN MODE
	/* Starts the graphic window. */
	ret = set_gfx_mode(GFX_SAFE,
						SYSTEM_MAX_X,
						SYSTEM_MAX_Y,
						SYSTEM_VMAX_X,
						SYSTEM_VMAX_Y);
	if (ret != 0) {
        //allegro_message("Erro ao carregar GFX (modo seguro falhou...)\nErro: %s", allegro_error);
		return SYSTEM_RET_ERROR;
    }

	return SYSTEM_RET_SUCCESS;
}

void system_engine_exit()
{
	allegro_exit();
}

