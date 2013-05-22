#include "system.h"
#include "system_defines.h"


int main (void)
{
	int ret;

	ret = system_engine_init();
	if (ret != SYSTEM_RET_SUCCESS) {
		//TODO: log message
		return -1;
	}

	ret = system_media_init();
	if (ret != SYSTEM_RET_SUCCESS) {
		//TODO: log message
		return -1;
	}

	//cfg_iniciaConfig();						//	config.c		//
	//
	//iniciaItems();							//	item.c			//
	//
	//iniciaChar();							//	charEngine.c	//
	//
	//pcl_carregaMapa(1, 12, 9, sul);			//	gameEngine.c	//

	//pcl_principal(1);						//	gameEngine.c	//
    

	system_engine_exit();

    return 0;
}


