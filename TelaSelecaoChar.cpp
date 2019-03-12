#include "TelaSelecaoChar.h"

TelaSelecaoChar::TelaSelecaoChar()
{
	isP2 = false;
	choseP1 = false;
	selecao = 0;
	selecaoAtivo = 0;
}

TelaSelecaoChar::~TelaSelecaoChar()
{
}

void TelaSelecaoChar::inicializar(stack<Tela*>* telas)
{
	this->telas = telas;

	// Fundo da tela
	if (!gRecursos.carregouSpriteSheet("telaSelecao"))
	{
		gRecursos.carregarSpriteSheet("telaSelecao", "telas/TelaChar.png");
	}
	fundoSelChar.setSpriteSheet("telaSelecao");

	// Personagens
	personagens.push_back(new PSkeleton);
	personagens.push_back(new PKnight);
	personagens.push_back(new PArcher);

	for (int i = 0; i < 3; i++)
		personagens[i]->inicializar();


	if (!gRecursos.carregouFonte("fonte1")) {
		gRecursos.carregarFonte("fonte1", "fonte_padrao.ttf", 18);
	}
	texto.setFonte("fonte1");
	texto.setCor(255, 255, 255);

	texto.setEscala(1, 1);
	
}

void TelaSelecaoChar::atualizar()
{
	// Desenhar Personagens e Botões
	desenhar();

	texto.setAlinhamento(TEXTO_CENTRALIZADO);
	if (!choseP1)
	{
		texto.setString("SELECIONE O PLAYER 1");
	}
	else
	{
		texto.setString("SELECIONE O PLAYER 2");
	}
	texto.desenhar(gJanela.getLargura() / 2, 50);

	// Escolher Personagem
	if (!choseP1)
	{
		if (selecaoAtivo == 0)
		{
			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				per = selecao + 1;
				setouPersonagem = true;
			}
		}
	}
	else
	{
		if (selecaoAtivo == 0)
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				per2 = selecao + 1;
				setouPersonagem = true;
			}
		}
	}
	// * BOTÕES *

	if (!choseP1)
	{
		if (selecaoAtivo < 2)
		{
			if (gTeclado.pressionou[TECLA_S] || gJoysticks.player1.pressionou[BOTAO_XBOX_BAIXO])
			{
				selecaoAtivo++;
			}
		}
		if (selecaoAtivo > 0)
		{
			if (gTeclado.pressionou[TECLA_W] || gJoysticks.player1.pressionou[BOTAO_XBOX_CIMA])
			{
				selecaoAtivo--;
			}
		}
	}
	else
	{
		if (selecaoAtivo < 2)
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_BAIXO])
			{
				selecaoAtivo++;
			}
		}
		if (selecaoAtivo > 0)
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_CIMA])
			{
				selecaoAtivo--;
			}
		}
	}

	// Ok
	if (selecaoAtivo == 1)
	{
		bVoltar.setEstado(BOTAOSPRITE_NORMAL);
		bOk.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		if (!choseP1)
		{
			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				bOk.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
		else
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				bOk.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
	}
	else if (selecaoAtivo == 2)
	{
		bOk.setEstado(BOTAOSPRITE_NORMAL);
		bVoltar.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		if (!choseP1)
		{
			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				bVoltar.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
		else
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				bVoltar.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
	}
	else
	{
		bOk.setEstado(BOTAOSPRITE_NORMAL);
		bVoltar.setEstado(BOTAOSPRITE_NORMAL);
	}
	//bOk.atualizar();


	if (setouPersonagem) {
		if (bOk.estaAbaixado()) {

			// Desempilha a tela de seleção para que a do topo seja a do Menu
			telas->pop();

			// Cria e empilha tela de jogo
			if (!isP2)
			{
				TelaJogo *telaJogo = new TelaJogo;

				telaJogo->inicializar(telas);
				for (int i = 0; i < 15; i++)
				{
					telaJogo->salas2.push(new Sala);
					telaJogo->salas2.top()->setPersonagem(per);

					if (choseP1)
					{
						telaJogo->salas2.top()->setPersonagem2(per2);

						telaJogo->salas2.top()->setIsP2();
					}
					telaJogo->salas2.top()->inicializar(15 - i);

				}
				telaJogo->salas.push(telaJogo->salas2.top());
				telaJogo->salas2.pop();
				telas->push(telaJogo);
			}
			else
			{
				TelaSelecaoChar *telaSelecaoChar = new TelaSelecaoChar;

				telaSelecaoChar->inicializar(telas);

				telaSelecaoChar->setChoseP1();
				telaSelecaoChar->setPer(per);

				telas->push(telaSelecaoChar);
			}

		}
	}
	

	// Voltar
	//bVoltar.atualizar();

	if (bVoltar.estaAbaixado()) {
		telas->pop(); // desempilha a tela de seleção e volta para o Menu
	}

}

void TelaSelecaoChar::desenhar()
{
	// Fundo
	fundoSelChar.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// Desenhar Personagens
	for (int p = 0; p < 3; p++) {
		personagens[p]->parado();
		personagens[p]->desenhar();

	}
	// Botão Voltar
	bVoltar.setPos(gJanela.getLargura() / 2, 700);
	bVoltar.desenhar();

	// Botão Ok
	bOk.setPos(gJanela.getLargura() / 2, 630);
	bOk.desenhar();

	//	Desenhar seleção
	Quad retan;
	retan.larg = personagens[selecao]->getSprite().getLargura();
	retan.alt = personagens[selecao]->getSprite().getAltura();
	retan.x = (personagens[selecao]->getX() - personagens[selecao]->getSprite().getLargura() / 2);
	retan.y = (personagens[selecao]->getY() - personagens[selecao]->getSprite().getAltura() / 2);

	
	if (selecaoAtivo == 0)
	{
		gGraficos.desenharRetangulo(retan, 30, 200, 230);


		if (!choseP1)
		{
			if (selecao > 0)
			{
				if (gTeclado.pressionou[TECLA_A] || gJoysticks.player1.pressionou[BOTAO_XBOX_ESQ])
				{
					selecao--;
				}
			}
			if (selecao < 2)
			{
				if (gTeclado.pressionou[TECLA_D] || gJoysticks.player1.pressionou[BOTAO_XBOX_DIR])
				{
					selecao++;
				}
			}
		}
		else
		{
			if (selecao > 0)
			{
				if (gJoysticks.player2.pressionou[BOTAO_XBOX_ESQ])
				{
					selecao--;
				}
			}
			if (selecao < 2)
			{
				if (gJoysticks.player2.pressionou[BOTAO_XBOX_DIR])
				{
					selecao++;
				}
			}
		}
	}

}

void TelaSelecaoChar::finalizar()
{
	gRecursos.descarregarSpriteSheet("telaSelecao");
}
