#pragma once
#include "Tela.h"
class TelaRanking :
	public Tela
{
public:
	TelaRanking();
	~TelaRanking();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar();
	void finalizar();

protected:

	stack <Tela *>* telas;
	Sprite fundo;

};

