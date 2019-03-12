#include "PArcher.h"

PArcher::PArcher()
{
	idPersonagem = Archer;
	x = gJanela.getLargura() / 1.5;

	pAtaque = 6;
	pVitais = 15;
	pDefesa = 8;

}

PArcher::~PArcher()
{}

void PArcher::inicializar()
{
	// Personagem 
	if (!gRecursos.carregouSpriteSheet("PArcher"))
		gRecursos.carregarSpriteSheet("PArcher", "Sprites/archer.png", 8, 13);
	gRecursos.getSpriteSheet("PArcher")->setNumFramesDaAnimacao(0, 9);
	gRecursos.getSpriteSheet("PArcher")->setNumFramesDaAnimacao(1, 9);
	gRecursos.getSpriteSheet("PArcher")->setNumFramesDaAnimacao(2, 9);
	gRecursos.getSpriteSheet("PArcher")->setNumFramesDaAnimacao(3, 9);
	spritePArcher.setSpriteSheet("PArcher");

	spritePArcher.setVelocidadeAnimacao(8);
	spritePArcher.setAnimacao(2);

	// Flechas	
	efeito = new Efeito[MAX_FLECHAS];
	for (int i = 0; i < MAX_FLECHAS; i++)
		efeito[i].inicializar("flecha", "sprites/flecha.png", 4, 1);
	
	// Tempo (usado nas flechas)
	gTempo.inicializar();
	tempo = gTempo.getTicks();
}

void PArcher::desenhar()
{
	// Personagem 
	spritePArcher.desenhar(x, y);

	// Flechas
	for (int i = 0; i < MAX_FLECHAS; i++)
		efeito[i].desenhar();

}

void PArcher::parado()
{
	// Animações usando o arco e direção das flechas

	// Para cima
	if (pos == pcima) {

		if (!isP2)
		{
			if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(4);
				spritePArcher.avancarAnimacao();
			}
		}
		else
		{
			if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(4);
				spritePArcher.avancarAnimacao();
			}
		}
	}

	// Para a esquerda
	else if (pos == pesq) {
		if (!isP2)
		{

			if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(5);
				spritePArcher.avancarAnimacao();
			}
		}
		else
		{
			if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(5);
				spritePArcher.avancarAnimacao();
			}
		}
	}

	// Para baixo
	else if (pos == pbaixo) {
		if (!isP2)
		{
			if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(6);
				spritePArcher.avancarAnimacao();
			}
		}
		else
		{
			if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(6);
				spritePArcher.avancarAnimacao();
			}
		}
	}

	// Para a direita
	else if (pos == pdir) {
		if (!isP2)
		{
			if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A]) {
				spritePArcher.setAnimacao(7);
				spritePArcher.avancarAnimacao();
			}
		}
		else
		{
			if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(7);
				spritePArcher.avancarAnimacao();
			}
		}
	}

	// Antes de se movimentar, não recebeu posição e inicia parado e para baixo
	else {
		if (!isP2)
		{
			if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A]) {
				spritePArcher.setAnimacao(6);
				spritePArcher.avancarAnimacao();
			}
		}
		else
		{
			if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
			{
				spritePArcher.setAnimacao(6);
				spritePArcher.avancarAnimacao();
			}
		}
	}

}

void PArcher::andarEsq()
{
	// Personagem 
	x -= 2;

	spritePArcher.setAnimacao(1);
	spritePArcher.avancarAnimacao();
	pos = pesq;
	if (!isP2)
	{
		if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(5);
		}
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(5);
		}
	}
}

void PArcher::andarDir()
{
	// Personagem 	
	x += 2;
	spritePArcher.setAnimacao(3);
	spritePArcher.avancarAnimacao();
	pos = pdir;


	if (!isP2)
	{
		if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(7);
		}
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(7);
		}
	}
}

void PArcher::andarCima()
{
	// Personagem 	
	y -= 2;
	spritePArcher.setAnimacao(0);
	spritePArcher.avancarAnimacao();
	pos = pcima;

	if (!isP2)
	{
		if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(4);
		}
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(4);
		}
	}
}

void PArcher::andarBaixo()
{
	// Personagem 	
	y += 2;
	spritePArcher.setAnimacao(2);
	spritePArcher.avancarAnimacao();
	pos = pbaixo;

	if (!isP2)
	{
		if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(6);
		}
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePArcher.setAnimacao(6);
		}
	}
}

void PArcher::setMorto()
{
	if (pVitais < 0)
	{
		spritePArcher.~Sprite();
		vivo = false;
	}
}

void PArcher::atacar()
{
	// Flechas

	// Movimentação das flechas

	for (int i = 0; i < MAX_FLECHAS; i++) {
		efeito[i].movimentar();
	}

	// Tempo entre flechadas
	if (gTempo.getTempoAteTickAtual(tempo) > 0.5)
		podeAtirar = true;

	if (podeAtirar)
		for (int i = 0; i < MAX_FLECHAS; i++)
			if (!efeito[i].getAtivo())
				if (!isP2)
				{
					if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A]) {

						sflecha.setAudio("sflecha");

						efeito[i].setX(x);
						efeito[i].setY(y);
						efeito[i].setAtivo(true);
						efeito[i].setDir(pos);
						//efeito[i].setPegarDir(false);
						sflecha.tocar();
						tempo = gTempo.getTicks();
						podeAtirar = false;
						if (pos == pbaixo)
						{
							efeito[i].setRot(180);
						}
						else if (pos == pcima)
						{
							efeito[i].setRot(0);
						}
						else if (pos == pesq)
						{
							efeito[i].setRot(270);
						}
						else if (pos == pdir)
						{
							efeito[i].setRot(90);
						}

						break;
					}
				}
				else
				{
					if (gJoysticks.player2.segurando[BOTAO_XBOX_A]) {

						sflecha.setAudio("sflecha");

						efeito[i].setX(x);
						efeito[i].setY(y);
						efeito[i].setAtivo(true);
						efeito[i].setDir(pos);
						//efeito[i].setPegarDir(false);
						sflecha.tocar();
						tempo = gTempo.getTicks();
						podeAtirar = false;
						if (pos == pbaixo)
						{
							efeito[i].setRot(180);
						}
						else if (pos == pcima)
						{
							efeito[i].setRot(0);
						}
						else if (pos == pesq)
						{
							efeito[i].setRot(270);
						}
						else if (pos == pdir)
						{
							efeito[i].setRot(90);
						}

						break;
					}
				}
				

	// Destruir flechas que saem da janela

	for (int i = 0; i < MAX_FLECHAS; i++)
	{
		// Em Largura
		if (efeito[i].getX() > gJanela.getLargura() + efeito[i].getSprite().getLargura() / 2 ||
			efeito[i].getX() < -efeito[i].getSprite().getLargura() / 2)
		{
			efeito[i].setAtivo(false);
			efeito[i].setPegarDir(true);
		}

		// Em Altura
		if (efeito[i].getY() > gJanela.getAltura() + efeito[i].getSprite().getAltura() / 2 ||
			efeito[i].getY() < -efeito[i].getSprite().getAltura() / 2)
		{
			efeito[i].setAtivo(false);
			efeito[i].setPegarDir(true);
		}
	}
}

