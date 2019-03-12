#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(1024, 768, true);

	// TELAS

	TelaMenu *telaIni = new TelaMenu;
	//inicializacao da tela
	telaIni->inicializar(&telas);
	//colocar na pilha
	telas.push(telaIni);
}

void Jogo::finalizar()
{	
	uniFinalizar();
}

void Jogo::executar()
{
	while (!gTeclado.pressionou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		// TELAS
		telaAtual = telas.top();
		telaAtual->atualizar();

		uniTerminarFrame();
	}
}