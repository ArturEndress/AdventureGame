#include "Inventario.h"

Inventario::Inventario()
{
	// Começa vazio
	ini = NULL;
	fim = NULL;
} 

Inventario::~Inventario()
{
}


void Inventario::add(int tipo)
{
	// Criando novo item
	NodoItem *novo = new NodoItem;
	novo->ant = NULL;
	novo->prox = NULL;
	novo->ID = tipo;
	novo->qtd = 1;

	//Se inv. estiver vazio, insere nodo novo
	if (estaVazio()) 
	{
		ini = novo;
		fim = novo;
	}

	//Senão, se o inventário já possui alguns nodos
	else 
	{
		//Procura o item na lista por ordem de ID
		NodoItem* aux = ini;
		while (aux != NULL && aux->ID < tipo)
		{
			aux = aux->prox;
		}

		//Se ainda não existe o item, insere no fim
		if (aux == NULL) 
		{
			novo->ant = fim;
			fim->prox = novo;
			fim = novo;
		}

		else { 
			//Posicionando aux de acordo com o ID

			//Se já te item, incrementa o contador no nodo em aux
			if (aux->ID == tipo)
			{
				if (aux->qtd < 9)
				{
					aux->qtd++;
				}
			}
			
			//Insere no início da lista 
			else if (aux == ini) 
			{
				novo->prox = aux; 
				ini->ant = novo;
				ini = novo;
			}

			//Insere entre dois nodos quaisquer diferentes de ini e fim
			else 
			{
				novo->ant = aux->ant;
				novo->prox = aux;

				aux->ant->prox = novo;
				aux->ant = novo;
			}
		}
	}
}

void Inventario::remover(int tipo)
{
	if (!estaVazio())
	{
		//Procura item na lista
		NodoItem *aux = getNodo(tipo);

		if (aux)
		{
			//Se encontra, diminui um
			aux->qtd--;

			if (aux->qtd == 0)
			{
				if (ini == fim) // 1 elemento na lista
				{
					//delete ini;
					ini = NULL;
					fim = NULL;
				}
				else if (aux == ini)
				{
					ini = ini->prox;
					ini->ant = NULL;
					delete aux;
				}
				else if (aux == fim)
				{
					fim = fim->ant;
					fim->prox = NULL;
					delete aux;
				}
				else
				{
					aux->ant->prox = aux->prox;
					aux->prox->ant = aux->ant;
					delete aux;
				}
			}
		}
	}
}

bool Inventario::estaVazio()
{
	if (ini == NULL) 
		return true;
	return false;
}

NodoItem * Inventario::getNodo(int tipo)
{
	NodoItem* aux = ini;
	while (aux != NULL && aux->ID != tipo)
	{
		aux = aux->prox;
	}
	return aux;
}

