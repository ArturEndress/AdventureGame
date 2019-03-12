#pragma once
#include "Tela.h"
#include "TelaSelecaoChar.h"
#include "TelaContinuar.h"
#include "TelaCreditos.h"
#include "TelaRanking.h"

class TelaMenu :
	public Tela
{
public:
	TelaMenu();
	~TelaMenu();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar();
	void finalizar();

protected:

	int selecao;
	stack <Tela *>* telas;
	Sprite fundoMenu;
		
};

