#pragma once
#include "Inimigo.h"
class IniAranha :
	public Inimigo
{
protected:
	Sprite sprAranha;

public:
	IniAranha();
	~IniAranha();

	void inicializar();
	void desenhar();

	// Movimenta��o
	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
};

