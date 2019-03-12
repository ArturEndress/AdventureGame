#include "Tela.h"

Tela::Tela()
{
	carregarBotoes();
}


Tela::~Tela()
{
}

void Tela::carregarBotoes()
{
	// 1 Jogador
	if (!gRecursos.carregouSpriteSheet("bNovo"))
		gRecursos.carregarSpriteSheet("bNovo", "sprites/menu/1p.png", 3, 1);
	bNovo.setSpriteSheet("bNovo");

	// 2 Jogadores
	if (!gRecursos.carregouSpriteSheet("b2players"))
		gRecursos.carregarSpriteSheet("b2players", "sprites/menu/2p.png", 3, 1);
	b2players.setSpriteSheet("b2players");

	// Continuar
	if (!gRecursos.carregouSpriteSheet("bContinuar"))
		gRecursos.carregarSpriteSheet("bContinuar", "sprites/menu/cont.png", 3, 1);
	bContinuar.setSpriteSheet("bContinuar");

	// Sair
	if (!gRecursos.carregouSpriteSheet("bSair"))
		gRecursos.carregarSpriteSheet("bSair", "sprites/menu/sair.png", 3, 1);
	bSair.setSpriteSheet("bSair");

	// Voltar
	if (!gRecursos.carregouSpriteSheet("bVoltar"))
		gRecursos.carregarSpriteSheet("bVoltar", "sprites/menu/volta.png", 3, 1);
	bVoltar.setSpriteSheet("bVoltar");

	// Ok
	if (!gRecursos.carregouSpriteSheet("bOk"))
		gRecursos.carregarSpriteSheet("bOk", "sprites/menu/ok.png", 3, 1);
	bOk.setSpriteSheet("bOk");


	// Creditos
	if (!gRecursos.carregouSpriteSheet("bCreditos"))
		gRecursos.carregarSpriteSheet("bCreditos", "sprites/menu/creditos.png", 3, 1);
	bCreditos.setSpriteSheet("bCreditos");

	// Loja
	if (!gRecursos.carregouSpriteSheet("bLoja"))
		gRecursos.carregarSpriteSheet("bLoja", "sprites/menu/loja.png", 3, 1);
	bLoja.setSpriteSheet("bLoja");
	
}
