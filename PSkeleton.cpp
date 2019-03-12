#include "PSkeleton.h"

PSkeleton::PSkeleton()
{
	idPersonagem = Skeleton;
	x = gJanela.getLargura() / 3;

	pAtaque = 7;
	pVitais = 15;
	pDefesa = 6;
}


PSkeleton::~PSkeleton()
{}

void PSkeleton::inicializar()
{
	// Personagem

	if (!gRecursos.carregouSpriteSheet("PSkeleton"))
		gRecursos.carregarSpriteSheet("PSkeleton", "Sprites/skel.png", 8, 9);
	gRecursos.getSpriteSheet("PSkeleton")->setNumFramesDaAnimacao(4, 6);
	gRecursos.getSpriteSheet("PSkeleton")->setNumFramesDaAnimacao(5, 6);
	gRecursos.getSpriteSheet("PSkeleton")->setNumFramesDaAnimacao(6, 6);
	gRecursos.getSpriteSheet("PSkeleton")->setNumFramesDaAnimacao(7, 6);
	spritePSkeleton.setSpriteSheet("PSkeleton");

	spritePSkeleton.setVelocidadeAnimacao(8);

	// Munição
	efeito = new Efeito[2];
	efeito[0].inicializar("explosao", "sprites/explosao.png", 1, 12);
	efeito[0].getSprite().setAnimacao(0, false);

	efeito[1].inicializar("mira", "sprites/mira.png", 1, 1);
	// Tempo, para a munição
	gTempo.inicializar();
	cooldown = gTempo.getTicks();
	podeAtacar = true;
}

void PSkeleton::desenhar()
{
	spritePSkeleton.desenhar(x, y);
	if (!podeAtacar)
	{
		if (efeito[0].getAtivo()) {
			efeito[0].desenhar();
			efeito[0].atualizarAnim();
		}
	}
	if (mirando)
	{
		efeito[1].desenhar();
		if (!isP2)
		{
			if (gJoysticks.player1.segurando[BOTAO_XBOX_BAIXO])
			{
				if (efeito[1].getY() < gJanela.getAltura())
				{
					efeito[1].setY(efeito[1].getY() + 4);
				}
			}
			if (gJoysticks.player1.segurando[BOTAO_XBOX_CIMA])
			{
				if (efeito[1].getY() > 0)
				{
					efeito[1].setY(efeito[1].getY() - 4);
				}
			}
			if (gJoysticks.player1.segurando[BOTAO_XBOX_ESQ])
			{
				if (efeito[1].getX() > 0)
				{
					efeito[1].setX(efeito[1].getX() - 4);
				}
			}
			if (gJoysticks.player1.segurando[BOTAO_XBOX_DIR])
			{
				if (efeito[1].getX() < gJanela.getLargura())
				{
					efeito[1].setX(efeito[1].getX() + 4);
				}
			}
		}
		else
		{
			if (gJoysticks.player2.segurando[BOTAO_XBOX_BAIXO])
			{
				if (efeito[1].getY() < gJanela.getAltura())
				{
					efeito[1].setY(efeito[1].getY() + 4);
				}
			}
			if (gJoysticks.player2.segurando[BOTAO_XBOX_CIMA])
			{
				if (efeito[1].getY() > 0)
				{
					efeito[1].setY(efeito[1].getY() - 4);
				}
			}
			if (gJoysticks.player2.segurando[BOTAO_XBOX_ESQ])
			{
				if (efeito[1].getX() > 0)
				{
					efeito[1].setX(efeito[1].getX() - 4);
				}
			}
			if (gJoysticks.player2.segurando[BOTAO_XBOX_DIR])
			{
				if (efeito[1].getX() < gJanela.getLargura())
				{
					efeito[1].setX(efeito[1].getX() + 4);
				}
			}
		}
	}
	else
	{
		efeito[1].setX(x);
		efeito[1].setY(y);
	}
	efeito[1].setAtivo(mirando);
}

void PSkeleton::parado()
{
	spritePSkeleton.setAnimacao(2);
}

void PSkeleton::andarEsq()
{
	if (!mirando)
	{
		x -= 2;
		spritePSkeleton.setAnimacao(1);
		spritePSkeleton.avancarAnimacao();
		pos = pesq;
	}
	
}

void PSkeleton::andarDir()
{
	if (!mirando)
	{
		x += 2;
		spritePSkeleton.setAnimacao(3);
		spritePSkeleton.avancarAnimacao();
	}
	
}

void PSkeleton::andarCima()
{
	if (!mirando)
	{
		y -= 2;
		spritePSkeleton.setAnimacao(0);
		spritePSkeleton.avancarAnimacao();
	}
	
}

void PSkeleton::andarBaixo()
{
	if (!mirando)
	{
		y += 2;
		spritePSkeleton.setAnimacao(2);
		spritePSkeleton.avancarAnimacao();
	}
	
	
}

void PSkeleton::setMorto()
{
	if (pVitais < 0)
	{
		spritePSkeleton.~Sprite();
		vivo = false;
	}
}

void PSkeleton::atacar()
{
	// Esta personagem ataca com o uso do mouse

	if (podeAtacar) {
		
		if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
		{
			sExplosao.setAudio("sExplosao");
			sExplosao.tocar();

			efeito[0].setAtivo(true);
			efeito[0].setX(gMouse.x);
			efeito[0].setY(gMouse.y);

			podeAtacar = false;
			cooldown = gTempo.getTicks();
		}
		if (mirando)
		{
			if (!isP2)
			{
				if (gJoysticks.player1.pressionou[BOTAO_XBOX_A])
				{
					sExplosao.setAudio("sExplosao");
					sExplosao.tocar();

					efeito[0].setAtivo(true);
					efeito[0].setX(efeito[1].getX());
					efeito[0].setY(efeito[1].getY());

					podeAtacar = false;
					cooldown = gTempo.getTicks();
				}
			}
			else
			{
				if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
				{
					sExplosao.setAudio("sExplosao");
					sExplosao.tocar();

					efeito[0].setAtivo(true);
					efeito[0].setX(efeito[1].getX());
					efeito[0].setY(efeito[1].getY());

					podeAtacar = false;
					cooldown = gTempo.getTicks();
				}
			}
		}
	}

	if (!isP2)
	{
		if (gJoysticks.player1.segurando[BOTAO_XBOX_RB])
		{
			mirando = true;
		}
		else
		{
			mirando = false;
		}
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_RB])
		{
			mirando = true;
		}
		else
		{
			mirando = false;
		}
	}
	// Espaço de tempo entre cada efeito, pra não ser fácil demais
	if (gTempo.getTempoAteTickAtual(cooldown) > 3) {
		podeAtacar = true;
	}
}
