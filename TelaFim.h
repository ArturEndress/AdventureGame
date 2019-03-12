#pragma once
#include "Tela.h"
class TelaFim :
	public Tela
{
public:
	TelaFim();
	~TelaFim();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar();
	void finalizar();

protected:

	stack <Tela *>* telas;
	Sprite fundoFim;

	bool ativo;
};

