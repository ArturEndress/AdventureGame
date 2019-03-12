#pragma once
#include "libUnicornio.h"
#include "Sala.h"
#include <vector>


class Tela
{
public:
	Tela();
	~Tela();

	virtual void inicializar(stack <Tela *>* telas) = 0;
	virtual void atualizar() = 0;
	virtual void desenhar() = 0;
	virtual void finalizar() = 0;
	
	// Botões
	void carregarBotoes();
	BotaoSprite bNovo, bContinuar, bVoltar, bOk, b2players, bCreditos, bSair, bLoja;

	
	// Salas
	Sala sala;

	stack<Sala*> salas, salas2, salasSave, salasSave2;
};

