#pragma once
#include "Personagem.h"
class PSkeleton :
	public Personagem
{
protected:
	Sprite spritePSkeleton;
	Uint64 cooldown;
	bool podeAtacar, mirando;

public:
	PSkeleton();
	~PSkeleton();

	void inicializar();
	void desenhar();

	void parado();
	void andarEsq();
	void andarDir();
	void andarCima();
	void andarBaixo();
	void atacar();

	void setMorto();
	Sprite getSprite() { return spritePSkeleton; };
};

