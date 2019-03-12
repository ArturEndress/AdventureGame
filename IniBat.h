#pragma once
#include "Inimigo.h"
class IniBat :
	public Inimigo
{
protected:
	Sprite sprMorcego;

public:
	IniBat();
	~IniBat();

	void inicializar();
	void desenhar();

	// Movimentação
	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
};

