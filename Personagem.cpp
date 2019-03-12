#include "Personagem.h"

Personagem::Personagem()
{
	pDefesa = 7;
	pVitais = uniRandEntre(2, 12);
	moedas = 0;
	pontos = 0;
	podeMachucar = true;
	pos = pbaixo;
	vivo = true;
	isP2 = false;
}

Personagem::~Personagem()
{}

void Personagem::atualizarVidas(int pVitais)
{
	// Usado no teste de colisão
	this->pVitais += pVitais;
	if (this->pVitais <= 0)
		vivo = false;

}


void Personagem::carregarAudio()
{
	// Archer
	if (!gRecursos.carregouAudio("sflecha"))	{
		gRecursos.carregarAudio("sflecha", "sons/flecha.wav");
	}
	sflecha.setAudio("sflecha");

	// Skeleton
	if (!gRecursos.carregouAudio("sExplosao"))	{
		gRecursos.carregarAudio("sExplosao", "sons/explosao.mp3");
	}	
	sExplosao.setAudio("sExplosao");

}

void Personagem::andar()
{
	// Movimentação testando as posições
	if (!isP2)
	{
		if (gTeclado.segurando[TECLA_W] || gJoysticks.player1.segurando[BOTAO_XBOX_CIMA])
		{
			pos = pcima;
			if (podeAndar[cima])
				andarCima();
		}

		else if (gTeclado.segurando[TECLA_A] || gJoysticks.player1.segurando[BOTAO_XBOX_ESQ])
		{
			pos = pesq;
			if (podeAndar[esq])
				andarEsq();
		}

		else if (gTeclado.segurando[TECLA_D] || gJoysticks.player1.segurando[BOTAO_XBOX_DIR])
		{
			pos = pdir;
			if (podeAndar[dir])
				andarDir();
		}

		else if (gTeclado.segurando[TECLA_S] || gJoysticks.player1.segurando[BOTAO_XBOX_BAIXO])
		{
			pos = pbaixo;
			if (podeAndar[baixo])
				andarBaixo();
		}
		else
			parado();
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_CIMA])
		{
			pos = pcima;
			if (podeAndar[cima])
				andarCima();
		}

		else if (gJoysticks.player2.segurando[BOTAO_XBOX_ESQ])
		{
			pos = pesq;
			if (podeAndar[esq])
				andarEsq();
		}

		else if (gJoysticks.player2.segurando[BOTAO_XBOX_DIR])
		{
			pos = pdir;
			if (podeAndar[dir])
				andarDir();
		}

		else if (gJoysticks.player2.segurando[BOTAO_XBOX_BAIXO])
		{
			pos = pbaixo;
			if (podeAndar[baixo])
				andarBaixo();
		}
		else
			parado();
	}
}


