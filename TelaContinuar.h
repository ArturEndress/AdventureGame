#pragma once
#include "Tela.h"
#include "TelaJogo.h"

class TelaContinuar :
	public Tela
{
public:
	TelaContinuar();
	~TelaContinuar();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar();
	void finalizar();

protected:

	stack <Tela *>* telas;

	Sprite fundo;

	BotaoSprite slot1, slot2, slot3;
};

