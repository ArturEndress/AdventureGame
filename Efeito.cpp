#include "Efeito.h"

Efeito::Efeito()
{
}


Efeito::~Efeito()
{
}

void Efeito::inicializar(string nome, string path, int nAnim, int nFrames)
{
	x = 0;
	y = 0;
	rot = 0;
	ativo = false;
	pegarDir = true;
	dir = s;
	if (!gRecursos.carregouSpriteSheet(nome))
	{
		gRecursos.carregarSpriteSheet(nome, path, nAnim, nFrames);
	}
	sprite.setSpriteSheet(nome);

}

void Efeito::desenhar()
{
	if (ativo)
	{
		sprite.desenhar(x, y, rot);
	}
}

void Efeito::movimentar()
{
	if (ativo)
	{

		if (dir == n)
		{
			y -= 5;

			if (y < sprite.getAltura() / 2)
			{
				ativo = false;
			}
		}
		else if (dir == s)
		{
			y += 5;

			if (y > gJanela.getAltura() + sprite.getAltura() / 2)
			{
				ativo = false;
			}
		}
		else if (dir == l)
		{
			x += 5;

			if (x > gJanela.getLargura() + sprite.getLargura() / 2)
			{
				ativo = false;
			}
		}
		else if (dir == o)
		{
			x -= 5;

			if (x < sprite.getLargura() / 2)
			{
				ativo = false;
			}
		}
	}
}

void Efeito::atualizarAnim()
{
	sprite.setVelocidadeAnimacao(5);
	sprite.avancarAnimacao();
	if (sprite.terminouAnimacao())
	{
		ativo = false;
	}
}
