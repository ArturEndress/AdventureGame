#pragma once
#include "Personagem.h"

#define MAX_FLECHAS 10
class PArcher :
	public Personagem
{
protected:
	Sprite spritePArcher;
	bool podeAtirar;
	Uint64 tempo;
	Som sflecha;

public:
	PArcher();
	~PArcher();

	void inicializar();
	void desenhar();

	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
	void setMorto();

	void atacar();

	Sprite getSprite() { return spritePArcher; };
};

