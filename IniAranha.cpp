#include "IniAranha.h"

IniAranha::IniAranha()
{
	pAtaque = rand() % 11 + 2;
	pDefesa = 5;
	pVitais = 8;

	iniId = aranha;
}


IniAranha::~IniAranha()
{
}

void IniAranha::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("Aranha"))
		gRecursos.carregarSpriteSheet("Aranha", "Sprites/spider.png", 5, 10);
	gRecursos.getSpriteSheet("Aranha")->setNumFramesDaAnimacao(4, 4);
	sprAranha.setSpriteSheet("Aranha");

	sprAranha.setVelocidadeAnimacao(6);

	sprIni = sprAranha;
}

void IniAranha::desenhar()
{
	sprAranha.desenhar(x, y);

	if (gTempo.getTempoAteTickAtual(tick) > 1)
		podeMachucar = true;
}

void IniAranha::parado()
{
	sprAranha.setAnimacao(2);
}

void IniAranha::andarEsq()
{
	x -= 2;
	sprAranha.setAnimacao(1);
	sprAranha.avancarAnimacao();
}

void IniAranha::andarDir()
{
	x += 2;
	sprAranha.setAnimacao(3);
	sprAranha.avancarAnimacao();
}

void IniAranha::andarCima()
{
	y -= 2;
	sprAranha.setAnimacao(0);
	sprAranha.avancarAnimacao();
}

void IniAranha::andarBaixo()
{
	y += 2;
	sprAranha.setAnimacao(2);
	sprAranha.avancarAnimacao();
}
