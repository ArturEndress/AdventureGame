#pragma once
#include "libUnicornio.h"
#include "TelaMenu.h"


class Jogo
{
protected:
	// TELAS
	stack <Tela *> telas;
	Tela *telaAtual;

public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();
	void executar();
	
};

