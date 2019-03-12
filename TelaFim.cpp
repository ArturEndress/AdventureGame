#include "TelaFim.h"

TelaFim::TelaFim()
{
	ativo = false;
}


TelaFim::~TelaFim()
{
}

void TelaFim::inicializar(stack<Tela*>* telas)
{
	this->telas = telas;

	// Fundo da tela
	if (!gRecursos.carregouSpriteSheet("TelaFim"))
	{
		gRecursos.carregarSpriteSheet("TelaFim", "telas/TelaFim.png");
	}
	fundoFim.setSpriteSheet("TelaFim");
}

void TelaFim::atualizar()
{
	desenhar();

	// Botão Voltar
	//bVoltar.atualizar();

	if (bVoltar.estaAbaixado()) {
		// (antigo) telaAtual = tInicial;
		telas->pop(); // desempilha a tela de seleção e volta para o Menu
	}

	if (gTeclado.pressionou[TECLA_S] || gJoysticks.player1.pressionou[BOTAO_XBOX_BAIXO] || gJoysticks.player2.pressionou[BOTAO_XBOX_BAIXO])
	{
		ativo = true;
	}
	if (gTeclado.pressionou[TECLA_W] || gJoysticks.player1.pressionou[BOTAO_XBOX_CIMA] || gJoysticks.player2.pressionou[BOTAO_XBOX_CIMA])
	{
		ativo = false;
	}

	if (ativo)
	{
		bVoltar.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A] || gJoysticks.player2.pressionou[BOTAO_XBOX_A])
		{
			bVoltar.setEstado(BOTAOSPRITE_ABAIXADO);
		}
	}
	else
	{
		bVoltar.setEstado(BOTAOSPRITE_NORMAL);
	}
}

void TelaFim::desenhar()
{
	// Fundo
	fundoFim.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// Botão Voltar
	bVoltar.setPos(gJanela.getLargura() / 2, 700);
	bVoltar.desenhar();
}

void TelaFim::finalizar()
{
	gRecursos.descarregarSpriteSheet("TelaFim");
}
