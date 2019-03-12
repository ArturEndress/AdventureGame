#pragma once
#include "Tela.h"

class TelaCreditos :
	public Tela
{
public:
	TelaCreditos();
	~TelaCreditos();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar();
	void finalizar();

protected:

	stack <Tela *>* telas;
	Sprite fundo;

	bool ativo;
	
};

