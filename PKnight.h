#pragma once
#include "Personagem.h"
class PKnight :
	public Personagem
{
protected:
	Sprite spritePKnight;
	Uint64 tick;

public:
	PKnight();
	~PKnight();

	void inicializar();
	void desenhar();

	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
	void setMorto();

	void atacar();

	Sprite getSprite() { return spritePKnight; };
};

