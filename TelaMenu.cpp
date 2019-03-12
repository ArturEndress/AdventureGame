#include "TelaMenu.h"

TelaMenu::TelaMenu()
{
	selecao = 0;
}


TelaMenu::~TelaMenu()
{
}

void TelaMenu::inicializar(stack<Tela*>* telas)
{
	this->telas = telas;

	// Fundo da tela
	if (!gRecursos.carregouSpriteSheet("TelaMenu"))
	{
		gRecursos.carregarSpriteSheet("TelaMenu", "telas/TelaMenu.png");
	}
	fundoMenu.setSpriteSheet("TelaMenu");

}

void TelaMenu::atualizar()
{
	// Fundo e Botões
	desenhar();

	// Botoes

	// 1 Player
	if (selecao == 0)
	{
		bNovo.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		
		b2players.setEstado(BOTAOSPRITE_NORMAL);
		bContinuar.setEstado(BOTAOSPRITE_NORMAL);
		bCreditos.setEstado(BOTAOSPRITE_NORMAL);
		bSair.setEstado(BOTAOSPRITE_NORMAL);

		if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
		{
			bNovo.setEstado(BOTAOSPRITE_ABAIXADO);
		}
	}
	// 2 Players
	if (selecao == 1)
	{
		b2players.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		
		bNovo.setEstado(BOTAOSPRITE_NORMAL);
		bContinuar.setEstado(BOTAOSPRITE_NORMAL);
		bCreditos.setEstado(BOTAOSPRITE_NORMAL);
		bSair.setEstado(BOTAOSPRITE_NORMAL);

		if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
		{
			b2players.setEstado(BOTAOSPRITE_ABAIXADO);
		}
	}
	// Continuar
	if (selecao == 2)
	{
		bContinuar.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		
		bNovo.setEstado(BOTAOSPRITE_NORMAL);
		b2players.setEstado(BOTAOSPRITE_NORMAL);
		bCreditos.setEstado(BOTAOSPRITE_NORMAL);
		bSair.setEstado(BOTAOSPRITE_NORMAL);

		if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
		{
			bContinuar.setEstado(BOTAOSPRITE_ABAIXADO);
		}
	}
	// Créditos
	if (selecao == 3)
	{
		bCreditos.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		
		bNovo.setEstado(BOTAOSPRITE_NORMAL);
		b2players.setEstado(BOTAOSPRITE_NORMAL);
		bContinuar.setEstado(BOTAOSPRITE_NORMAL);
		bSair.setEstado(BOTAOSPRITE_NORMAL);

		if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
		{
			bCreditos.setEstado(BOTAOSPRITE_ABAIXADO);
		}
	}
	// Sair
	if (selecao == 4)
	{
		bSair.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);

		bNovo.setEstado(BOTAOSPRITE_NORMAL);
		b2players.setEstado(BOTAOSPRITE_NORMAL);
		bContinuar.setEstado(BOTAOSPRITE_NORMAL);
		bCreditos.setEstado(BOTAOSPRITE_NORMAL);
		

		if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
		{
			bSair.setEstado(BOTAOSPRITE_ABAIXADO);
		}
	}


	if (selecao<4)
	{
		if (gTeclado.pressionou[TECLA_S] || gJoysticks.player1.pressionou[BOTAO_XBOX_BAIXO])
		{
			selecao++;
		}
	}
	if (selecao>0)
	{
		if (gTeclado.pressionou[TECLA_W] || gJoysticks.player1.pressionou[BOTAO_XBOX_CIMA])
		{
			selecao--;
		}
	}


	// TELAS
	
	//Seleção Char 2 Players
	if (b2players.estaAbaixado())
	{
		TelaSelecaoChar *telaSChar = new TelaSelecaoChar;
		// inicializa
		telaSChar->inicializar(telas);
		telaSChar->setIsP2();
		// empilha
		telas->push(telaSChar);
	}
	// Seleção de Char
	if (bNovo.estaAbaixado())
	{
		TelaSelecaoChar *telaSChar = new TelaSelecaoChar;
		// inicializa
		telaSChar->inicializar(telas);
		// empilha
		telas->push(telaSChar);
	}

	// Continuar  ESTÁ DANDO ERRO QUADO SALVA COM PLAYER 2 MORTO - REVER
	//if (bContinuar.estaAbaixado())
	//{
	//	// Cria e empilha tela de jogo
	//	int size;
	//	ifstream file("save.txt", ios::in | ios::binary | ios::ate);
	//	if (file.is_open())
	//	{
	//		size = file.tellg();
	//	}
	//	if (size > 0)
	//	{
	//		TelaJogo *telaJogo = new TelaJogo;

	//		telaJogo->inicializar(telas);

	//		for (int i = 0; i < 15; i++)
	//		{
	//			telaJogo->salas2.push(new Sala);
	//			
	//			telaJogo->salas2.top()->setLoaded();
	//			telaJogo->salas2.top()->load(14 - i);
	//			
	//		}
	//		telaJogo->salas.push(telaJogo->salas2.top());
	//		telaJogo->salas2.pop();
	//		while (telaJogo->salas.top()->getSalaAtual() != telaJogo->salas.top()->getSalaSave())
	//		{
	//			telaJogo->salas.push(telaJogo->salas2.top());
	//			telaJogo->salas2.pop();
	//		}
	//		//telaJogo->setLoaded();
	//		telas->push(telaJogo);
	//	}
	//}

	// Créditos
	if (bCreditos.estaAbaixado())
	{
		TelaCreditos *telaCred = new TelaCreditos;
		// inicializa
		telaCred->inicializar(telas);
		// empilha
		telas->push(telaCred);
	}

	// Sair do Jogo
	else if (bSair.estaAbaixado())
	{
		gEventos.sair = true;
	}

}

void TelaMenu::desenhar()
{
	// Fundo da tela
	fundoMenu.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	
	// Botões
	bNovo.setPos(gJanela.getLargura() / 2, 300);
	bNovo.desenhar();

	b2players.setPos(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	b2players.desenhar();

	bContinuar.setPos(gJanela.getLargura() / 2, 468);
	bContinuar.desenhar();

	bCreditos.setPos(gJanela.getLargura() / 2, 600);
	bCreditos.desenhar();	

	bSair.setPos(gJanela.getLargura() / 2, 680);
	bSair.desenhar();

}

void TelaMenu::finalizar()
{
	gRecursos.descarregarSpriteSheet("TelaMenu");
}


