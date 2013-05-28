#include "includes.h"

//**********************************//
//	Developer Vitor Rozsa			//
//	E-mail: vitor.rozsa@hotmail.com	//
//**********************************//

void main (void){
	
	cfg_iniciaMidia();						//	config.c		//
	
	cfg_iniciaConfig();						//	config.c		//
	
	iniciaItems();							//	item.c			//
	
	iniciaChar();							//	charEngine.c	//
	
	pcl_carregaMapa(1, 12, 9, sul);			//	gameEngine.c	//

	pcl_principal(1);						//	gameEngine.c	//
    
    allegro_exit();	

    return;
}