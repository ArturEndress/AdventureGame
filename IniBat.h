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

	// Movimenta��o
	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
};

