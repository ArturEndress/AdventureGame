#include "PKnight.h"

PKnight::PKnight()
{
	idPersonagem = Knight;
	x = gJanela.getLargura()/2;

	pAtaque = 10;
	pVitais = 15;
	pDefesa = 12;

}

PKnight::~PKnight()
{
}

void PKnight::inicializar()
{
	
	if (!gRecursos.carregouSpriteSheet("PKnight"))
		gRecursos.carregarSpriteSheet("PKnight", "Sprites/knight1.png", 8, 9);
	gRecursos.getSpriteSheet("PKnight")->setNumFramesDaAnimacao(4, 6);
	gRecursos.getSpriteSheet("PKnight")->setNumFramesDaAnimacao(5, 6);
	gRecursos.getSpriteSheet("PKnight")->setNumFramesDaAnimacao(6, 6);
	gRecursos.getSpriteSheet("PKnight")->setNumFramesDaAnimacao(7, 6);
	spritePKnight.setSpriteSheet("PKnight");
	
	spritePKnight.setAnimacao(2);

	spritePKnight.setVelocidadeAnimacao(8);


	efeito = new Efeito[2];

	efeito[0].inicializar("espadaHB", "sprites/hitboxEspd.png", 1, 1);
	efeito[1].inicializar("espada", "sprites/espada.png", 1, 3);

	gTempo.inicializar();
	tick = gTempo.getTicks();

}

void PKnight::desenhar()
{
		spritePKnight.desenhar(x, y);	

		efeito[1].desenhar();
		if (efeito[1].getAtivo())
		{
			efeito[1].atualizarAnim();
		}
		
}

void PKnight::parado()
{
	for (int i = 0; i < 2; i++)
	{
		if (pos == pcima)
		{
			if (!isP2)
			{

				if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
				{
					spritePKnight.setAnimacao(4);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			else
			{

				if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
				{
					spritePKnight.setAnimacao(4);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			//spritePKnight.setAnimacao(0);

			efeito[i].setX(x);
			efeito[i].setY(y - spritePKnight.getAltura() / 2);
			efeito[i].setRot(0);

		}

		else if (pos == pesq) {
			if (!isP2)
			{
				if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
				{
					spritePKnight.setAnimacao(5);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			else
			{
				if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
				{
					spritePKnight.setAnimacao(5);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			//spritePKnight.setAnimacao(1);

			efeito[i].setX(x - spritePKnight.getLargura() / 2);
			efeito[i].setY(y);
			efeito[i].setRot(270);

		}

		else if (pos == pbaixo) {
			if (!isP2)
			{
				if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A])
				{
					spritePKnight.setAnimacao(6);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			else
			{
				if (gJoysticks.player2.segurando[BOTAO_XBOX_A])
				{
					spritePKnight.setAnimacao(6);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			//spritePKnight.setAnimacao(2);

			efeito[i].setX(x);
			efeito[i].setY(y + spritePKnight.getAltura() / 2);
			efeito[i].setRot(180);

		}

		else if (pos == pdir) {
			if (!isP2)
			{
				if (gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A]) {
					spritePKnight.setAnimacao(7);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			else
			{
				if (gJoysticks.player2.segurando[BOTAO_XBOX_A]) {
					spritePKnight.setAnimacao(7);
					spritePKnight.setVelocidadeAnimacao(5);
					spritePKnight.avancarAnimacao();
				}
				else
				{
					spritePKnight.setFrame(0);
				}
			}
			//spritePKnight.setAnimacao(3);

			efeito[i].setX(x + spritePKnight.getLargura() / 2);
			efeito[i].setY(y);
			efeito[i].setRot(90);

		}

		else
		{
			spritePKnight.setAnimacao(2);
			spritePKnight.setVelocidadeAnimacao(8);
			efeito[i].setX(x);
			efeito[i].setY(y + spritePKnight.getAltura() / 2);
			efeito[i].setRot(0);
		}
	}
}

void PKnight::andarEsq()
{
	x -= 2;
	if (!isP2)
	{
		if (!gTeclado.segurando[TECLA_ESPACO] && !gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(1);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(5);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	else
	{
		if (!gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(1);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(5);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	for (int i = 0; i < 2; i++)
	{
		efeito[i].setX(x - spritePKnight.getLargura() / 2);
		efeito[i].setY(y);
		efeito[i].setRot(270);
	}
}

void PKnight::andarDir()
{

	x += 2;
	if (!isP2)
	{
		if (!gTeclado.segurando[TECLA_ESPACO] && !gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(3);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(7);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	else
	{

		if (!gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(3);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(7);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x + spritePKnight.getLargura() / 2);
		efeito[i].setY(y);
		efeito[i].setRot(90);
	}
}

void PKnight::andarCima()
{

	y -= 2;
	if (!isP2)
	{
		if (!gTeclado.segurando[TECLA_ESPACO] && !gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(0);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(4);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	else
	{
		if (!gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(0);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(4);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x);
		efeito[i].setY(y - spritePKnight.getAltura() / 2);
		efeito[i].setRot(0);
	}
}

void PKnight::andarBaixo()
{

	y += 2;
	if (!isP2)
	{
		if (!gTeclado.segurando[TECLA_ESPACO] && !gJoysticks.player1.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(2);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(6);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	else
	{
		if (!gJoysticks.player2.segurando[BOTAO_XBOX_A])
		{
			spritePKnight.setAnimacao(2);
			spritePKnight.setVelocidadeAnimacao(8);
			spritePKnight.avancarAnimacao();
		}
		else
		{
			spritePKnight.setAnimacao(6);
			spritePKnight.setVelocidadeAnimacao(5);
			spritePKnight.avancarAnimacao();
		}
	}
	for (int i = 0; i < 2; i++)
	{

		efeito[i].setX(x);
		efeito[i].setY(y + spritePKnight.getAltura() / 2);
		efeito[i].setRot(180);
	}
}

void PKnight::setMorto()
{
	if (pVitais < 0)
	{
		spritePKnight.~Sprite();
		vivo = false;
	}
}

void PKnight::atacar()
{
	if (!isP2)
	{
		if ((gTeclado.segurando[TECLA_ESPACO] || gJoysticks.player1.segurando[BOTAO_XBOX_A] )&& !efeito[0].getAtivo())
		{
			efeito[0].setAtivo(true);
			efeito[1].setAtivo(true);
			tick = gTempo.getTicks();
		}
	}
	else
	{
		if (gJoysticks.player2.segurando[BOTAO_XBOX_A] && !efeito[0].getAtivo())
		{
			efeito[0].setAtivo(true);
			efeito[1].setAtivo(true);
			tick = gTempo.getTicks();
		}
	}
	if (gTempo.getTempoAteTickAtual(tick) > 0.2)
	{
		efeito[0].setAtivo(false);
	}
}
