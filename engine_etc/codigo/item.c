#include "includes.h"

//	Classes			Tipo				//
//										//
//		A	1	 equipamentos/armas		//
//		B	2		  cura				//
//		C	3							//
//		D	4							//
//		E	5	 estático(inútil)		//


//	int ID;				//	ID geral do item.		//
//	char nome[20];		//	Nome do item.			//
//	char descricao[50];	//	Breve descricao do item.//
//	int classe;			//	Classe de item.			//
//	int preco_comprar;	//	Preco de compra.		//
//	int preco_vender;	// 	Preco de venda.			//



ITEM item[100];

void iniciaItems() {
	
	item[1].ID = 1;
	strcpy(item[1].nome, "Maca");
	strcpy(item[1].descricao, "Uma bela maca vermelha.");
	item[1].classe = E;
	item[1].preco_comprar = 0;
	item[1].preco_vender = 3;
	
	
	item[2].ID = 2;
	strcpy(item[2].nome, "Pocao de cura");
	strcpy(item[2].descricao, "Regenera cerca de 20% do HP.");
	item[2].classe = B;
	item[2].preco_comprar = 50;
	item[2].preco_vender = 0;
	item[2].curaHP = pequena;
	item[2].curaMP = 0;
	item[2].curaSTS = 0;
	
	item[3].ID = 3;
	strcpy(item[3].nome, "Espada curta.");
	strcpy(item[3].descricao, "Espada curta. Ataque: 7 Defesa: 3");
	strcpy(item[3].descricao, "1234567890123456789212345678931234567894123456789");
	item[3].classe = A;
	item[3].preco_comprar = 70;
	item[3].preco_vender = 35;
	item[3].ataque = 7;
	item[3].defesa = 3;
	item[3].atributo = nenhum;

	item[1].ID = 4;
	strcpy(item[4].nome, "Ovos");
	strcpy(item[4].descricao, "Ovos de pato.");
	item[4].classe = E;
	item[4].preco_comprar = 0;
	item[4].preco_vender = 5;
	
	return;
}

