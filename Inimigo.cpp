#include "Inimigo.h"

Inimigo::Inimigo()
{
	x = 0;
	y = 0;

	vivo = true;
	podeMachucar = true;
	dirKnb = 0;

	efeitoAtivo = false;

	gTempo.inicializar();

	tick = gTempo.getTicks();
	tKnB = gTempo.getTicks();
	tickEfeito = gTempo.getTicks();
	knb = false;

	efeito.inicializar("efeitoDebuff", "sprites/efeitoDebuff.png", 1, 1);

}


Inimigo::~Inimigo()
{	
}

void Inimigo::setEfeito(bool efeito)
{
	efeitoAtivo = efeito;
	tickEfeito = gTempo.getTicks();
}

void Inimigo::atualizarVidas(int pVitais)
{
	this->pVitais += pVitais;
	if (this->pVitais > 0)
		vivo = true;
	else
		vivo = false;
}

void Inimigo::setPodeMachucar()
{
	if (podeMachucar) {
		podeMachucar = false;
		tick = gTempo.getTicks();
	}
}

void Inimigo::knockBack()
{
	if (gTempo.getTempoAteTickAtual(tKnB) > 0.2)
		knb = false;

	if (knb) {
		if (dirKnb == pesq)
			x -= 5;

		else if (dirKnb == pdir)
			x += 5;

		else if (dirKnb == pcima)
			y -= 5;

		else if (dirKnb == pbaixo)
			y += 5;
	}

	if (efeitoAtivo)
	{
		efeito.setX(x);
		efeito.setY(y);
		efeito.desenhar();
	}
	if (gTempo.getTempoAteTickAtual(tickEfeito) > 0.8)
	{
		efeitoAtivo = false;
	}
}

void Inimigo::setKnockBack()
{
	tKnB = gTempo.getTicks();
	knb = true;
}
