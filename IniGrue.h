#pragma once
#include "Inimigo.h"
class IniGrue :
	public Inimigo
{
protected:
	Sprite sprGrue;

public:
	IniGrue();
	~IniGrue();

	void inicializar();
	void desenhar();

	// Movimentação
	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();

	
};

