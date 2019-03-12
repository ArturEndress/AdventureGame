#include "TelaContinuar.h"

TelaContinuar::TelaContinuar()
{
}


TelaContinuar::~TelaContinuar()
{
}

void TelaContinuar::inicializar(stack<Tela*>* telas)
{
	this->telas = telas;

	// Fundo da tela
	if (!gRecursos.carregouSpriteSheet("telaC"))
	{
		gRecursos.carregarSpriteSheet("telaC", "telas/TelaContinuar.png");
	}
	fundo.setSpriteSheet("telaC");
}

void TelaContinuar::atualizar()
{
	desenhar();

	if (gTeclado.pressionou[TECLA_2])
	{

		// Desempilha a tela de seleção para que a do topo seja a do Menu
		telas->pop();

		// Cria e empilha tela de jogo
		TelaJogo *telaJogo = new TelaJogo;

		telaJogo->inicializar(telas);	
		//telaJogo->setLoaded();

		for (int i = 0; i < 15; i++)
		{		
			telaJogo->salas2.push(new Sala);
			
			telaJogo->salas2.top()->setLoaded();
			telaJogo->salas2.top()->load(14 - i);
			
		}
		
		telaJogo->salas.push(telaJogo->salas2.top());
		telaJogo->salas2.pop();
		while (telaJogo->salas.top()->getSalaAtual() != telaJogo->salas.top()->getSalaSave())
		{
			telaJogo->salas.push(telaJogo->salas2.top());
			telaJogo->salas2.pop();
		}
		
		telas->push(telaJogo);

	}

	// Botão Voltar
	bVoltar.atualizar();

	if (bVoltar.estaClicado()) {
		telas->pop(); // desempilha a tela de seleção e volta para o Menu
	}
}

void TelaContinuar::desenhar()
{
	// Fundo
	fundo.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// Botão Voltar
	bVoltar.setPos(gJanela.getLargura() / 2, 700);
	bVoltar.desenhar();

	// Slots
	// ...
}

void TelaContinuar::finalizar()
{
	gRecursos.descarregarSpriteSheet("telaC");
}
