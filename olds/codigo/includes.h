#include <stdio.h>
#include <string.h>
#include <time.h>

#include <allegro.h>

#include "defines.h"
//**********************************//
//	Developer Vitor Rozsa			//
//	E-mail: vitor.rozsa@hotmail.com	//
//	Última atualização: 07/25/2010	//
//**********************************//

/*-----------------*\
|*----Variáveis----*|
\*-----------------*/
#define COLOR_BITS    32

#define MAX_X         800
#define MAX_Y         600
#define VMAX_X          0
#define VMAX_Y          0

#define DIGI_CARD     DIGI_AUTODETECT
#define MIDI_CARD     MIDI_AUTODETECT

//	Para Data Files.	//
#define DAT_MAPA	0


BITMAP *_mapa;		//	Mapa.				//
BITMAP *_menu[10];
BITMAP *_menuItens[10];
BITMAP *_ponteiro;
BITMAP *_menu_batalha;
BITMAP *_batalha;

BITMAP *BUFFER; 	//	*Double Buffering.	//
BITMAP *SBUFFER;
BITMAP *LOAD;

PALETTE palette;

//	FONTES		//
FONT *sans_serif20;
FONT *sans_serif18;

int mapa_id;
int mapaID;
int charID;

//2400/1760 | 75/55 | horizontal/vertical//
/*-----------------*\
|*-----Funções-----*|
\*-----------------*/
//________________________________________________________
//--------------------------------------------------------
//-------Configurações.		prefixo: cfg_
//---------------------------
void cfg_iniciaMidia(void);									//	congig.c	//

void cfg_iniciaConfig(void);								//	congig.c	//	

void cfg_iniciaChar(void);									//	congig.c	//

void cfg_iniciaBitmaps(void);								//	congig.c	//

void cfg_iniciaFontes(void);								//	congig.c	//

BITMAP *carregaBitmap(BITMAP *bitmap, char endereco[50]);	//	congig.c	//

FONT *carregaFonte(FONT *nome, char endereco[50]);			//	congig.c	//


//________________________________________________________
//--------------------------------------------------------
//-------Principal.		prefixo: pcl_
//---------------------------
void pcl_principal(int id);																//	gameEngine.c	//

void pcl_atualizaMapa(void);															//	gameEngine.c	//

void pcl_carregaMapa (int mapa_id, int heroi_mapaPosH, int heroi_mapaPosV, int LOOK);	//	gameEngine.c	//


void moveChar(int move);

void menu(void);

void andar(int direcao);

void batalha(void);

void moveMapa(int move);

void mudaDirecao (int pos);

void menuDrawText(int menu_pos);

void menuItens();

void iniciaItems(void);

void menuItens(void);

void atualizaMenuItens(BITMAP *menuItens, int ponteiroPosx, int ponteiroPosy, int pagina);

void atualizaMI2(int k, int kmax);

void teclaAcao(void);

void encontraItem(int posx, int posy);



void teletransporte(int hh, int hv);

//void anima_ataque(int id, int pos);

//void batalha(void);

void menu(void);
//________________________________________________________
//--------------------------------------------------------
//-------Ações.	prefixo: ac_
//---------------------------
void ac_encontraItem(int posx, int posy);			//	acoes.c	//

void ac_teletransporte(int hh, int hv);  			//	acoes.c	//
//________________________________________________________
//--------------------------------------------------------
//-------Declaração de Mapas.	prefixo: map_
//---------------------------
void map_Mapa1(int hposh, int hposv, int LOOK);		//	mapa1.c		//

void map_Caverna1(int hposh, int hposv, int LOOK);	//	caverna1.c	//

/*-----------------*\
|*---Estruturas----*|
\*-----------------*/

typedef struct _charItem{
	
	int ID;
	int quantidade;
} charItem;

struct PERSONAGEM{
	
	BITMAP *BMP[20]; 				//	Imagens do Personagem.	//
	
	//*************************\
	//*******Localização*****\\/
	int POSH;				//	Posição horizontal na tela. 0 -> 800									//
	int POSV;				//	Posição vertical na tela.	0 -> 600									//
	int LOOK;				//	Posição em que está voltado. 0 = norte; 1 = leste; 2 = sul; 3 = oeste	//
	int MapaPos[2]; 		//	Posição do mapa em que o player se encontra. Por Matriz. H[0] V[1]		//
	
	//*************************\
	//*******Atributos*******\\/
	char nome[20];
	
	int forca;
	int habilidade;
	int resistencia;
	int agilidade;
	int inteligencia;
	int destreza;
	int poder_de_fogo;
	
	int arma;
	int escudo;
	int armadura;
	int helmo;
	int botas;
	
	int ataque;
	int defesa;
	int vita_max;
	int mana_max;
	int vita;
	int mana;
	int magia;
	
	//****Itens****//
	int moedas;
	charItem item[100];	//	[0][0] = ID do item /**\ [0][1] = quantidade	//
	int itemCont;
	
};

typedef struct _ITEM{
	
//	Caracteristicas Gerais.
//----------------------------------------
	BITMAP *BMP;		//	Imagem se necessário.		//
	int ID;				//	ID geral do item.			//
	char nome[20];		//	Nome do item.				//
	char descricao[50];	//	Breve descricao do item.	//
	int classe;			//	Classe de item.				//
	int preco_comprar;	//	Preco de compra.			//
	int preco_vender;	// 	Preco de venda.				//
	
//	Itens Classe A.	Equipamentos
//----------------------------------------	
	int ataque;
	int defesa;
	int atributo;
	
//	Itens Classe B.	Poções
//----------------------------------------	
	int curaHP;			//	Quantidade de HP a curar.		//
	int curaMP;			//	Quantidade de MP a curar.		//
	int curaSTS;		//	Tipo de status que pode curar.	//
	
} ITEM;

typedef struct atitude{
	
	int acao;				// 	0 = nada; 1 = caminho bloqueado; 2 = item normal; 3 = teletransporte;	//
	int ID;					// 	ID da acao.																//
	int itemID; 			// 	Item a ser recebido.													//
	int quant;				// 	Quantidade de itens.													//
	BITMAP *substituir;		// 	Imagem que sera sobreposta a primeira.									//
	int subs;				// 	Flag que avisara que existe imagem para subs.							//
	
	int look;				//	Para onde o heroi estará voltado.										//
	int mapaid;				//	ID do mapa que será carregado.											//
	int hposh;				//	Heroi pos no mapa;														//
	int hposv;				//	Heroi pos no mapa;														//
	
} atitude;

struct MAPA{
	
	BITMAP *BMP[50];				//	Define todas as imagens no mapa.	0 = Layer 1; 1 = Layer 2;	//
	int posx;						//	Posição horizontal do mapa na tela. 	[0 -> -1600]			//
	int posy;						//	Posição vertical do mapa na tela.		[0 -> -1152]			//
	atitude matriz[75][55]; 		//	Matriz de ações que podem ser chamadas pelo heroi.				//
	int largura;					//	Largura total do mapa. Horizontal.								//
	int altura;						//	Altura total do mapa.  Vertical.								//
	int MH;							//	Largura total do mapa em área.	(largura / 32)					//
	int MV;							//	Altura total do mapa em área.	(altura  / 32)					//
	
};

typedef struct _ANIMATAQUE {
	
	char nome[20];
	BITMAP *BMP[3];
	
} ANIMATAQUE;