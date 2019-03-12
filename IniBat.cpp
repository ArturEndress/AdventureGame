#include "IniBat.h"

IniBat::IniBat()
{
	pAtaque = rand() % 11 + 2;
	pDefesa = 3;
	pVitais = 6;

	iniId = morcego;
}


IniBat::~IniBat()
{
}

void IniBat::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("Morcego"))
		gRecursos.carregarSpriteSheet("Morcego", "Sprites/bat.png", 4, 8);
	sprMorcego.setSpriteSheet("Morcego");

	sprMorcego.setVelocidadeAnimacao(8);

	sprIni = sprMorcego;
}

void IniBat::desenhar()
{
	sprMorcego.desenhar(x, y);

	if (gTempo.getTempoAteTickAtual(tick) > 1)
		podeMachucar = true;
}

void IniBat::parado()
{
	sprMorcego.setAnimacao(2);
}

void IniBat::andarEsq()
{
	x -= 3;
	sprMorcego.setAnimacao(1);
	sprMorcego.avancarAnimacao();
}

void IniBat::andarDir()
{
	x += 3;
	sprMorcego.setAnimacao(3);
	sprMorcego.avancarAnimacao();
}

void IniBat::andarCima()
{
	y -= 3;
	sprMorcego.setAnimacao(0);
	sprMorcego.avancarAnimacao();
}

void IniBat::andarBaixo()
{
	y += 3;
	sprMorcego.setAnimacao(2);
	sprMorcego.avancarAnimacao();
}
