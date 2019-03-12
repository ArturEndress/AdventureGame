#include "IniGrue.h"

IniGrue::IniGrue()
{
	pAtaque = rand() % 11 + 2;
	pDefesa = 6;
	pVitais = 10;

	iniId = grue;
}

IniGrue::~IniGrue()
{
}

void IniGrue::inicializar()
{
	if (!gRecursos.carregouSpriteSheet("Grue"))
		gRecursos.carregarSpriteSheet("Grue", "Sprites/grue2.png", 4, 3);
	sprGrue.setSpriteSheet("Grue");

	sprGrue.setVelocidadeAnimacao(5);
	sprIni = sprGrue;
}

void IniGrue::desenhar()
{
	sprGrue.desenhar(x, y);

	if (gTempo.getTempoAteTickAtual(tick) > 1)
		podeMachucar = true;

}

void IniGrue::parado()
{
	sprGrue.setAnimacao(2);
}

void IniGrue::andarEsq()
{
	x -= 1;
	sprGrue.setAnimacao(1);
	sprGrue.avancarAnimacao();
}

void IniGrue::andarDir()
{
	x +=1;
	sprGrue.setAnimacao(3);
	sprGrue.avancarAnimacao();
}

void IniGrue::andarCima()
{
	y -= 1;
	sprGrue.setAnimacao(0);
	sprGrue.avancarAnimacao();
}

void IniGrue::andarBaixo()
{
	y += 1;
	sprGrue.setAnimacao(2);
	sprGrue.avancarAnimacao();
}
