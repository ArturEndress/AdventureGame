#include "TelaRanking.h"

TelaRanking::TelaRanking()
{
}


TelaRanking::~TelaRanking()
{
}

void TelaRanking::inicializar(stack<Tela*>* telas)
{
	this->telas = telas;

	// Fundo da tela
	if (!gRecursos.carregouSpriteSheet("telaR"))
	{
		gRecursos.carregarSpriteSheet("telaR", "telas/TelaR.png");
	}
	fundo.setSpriteSheet("telaR");
	
}

void TelaRanking::atualizar()
{
	desenhar();
	// Botão Voltar
	bVoltar.atualizar();

	if (bVoltar.estaClicado()) {		
		telas->pop(); // desempilha a tela de seleção e volta para o Menu
	}
}

void TelaRanking::desenhar()
{
	// Fundo
	fundo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// Botão Voltar
	bVoltar.setPos(gJanela.getLargura() / 2, 700);
	bVoltar.desenhar();
}

void TelaRanking::finalizar()
{
	gRecursos.descarregarSpriteSheet("telaR");
}
