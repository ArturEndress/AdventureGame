#pragma once
#include "Item.h"
#define maxItens 10

const string nomes_pocoes[3] = { "potHP", "potMP", "veneno" };

struct NodoItem
{
	int ID;
	int qtd;
	Item item;
	NodoItem *ant, *prox;

}; class Inventario

{
public:
	Inventario();
	~Inventario();

	void add(int tipo);
	void remover(int tipo);
	
	NodoItem *getIni() { return ini; }
	NodoItem *getFim() { return fim; }
	void setIni(NodoItem* ini) { this -> ini = ini; }
	void setFim(NodoItem* fim) { this->fim = fim; }


	bool estaVazio();
	NodoItem* getNodo(int tipo);

protected:
	NodoItem * ini, *fim;

};

