#include "Sala.h"

Sala::Sala()
{
	srand(time(0));

	loaded = false;
	saving = false;
	isP2 = false;
	selecaoLoja = 0;
	voltarLoja = false;
	p2EstaNaLoja = false;
	p2Pausou = false;
	selecaoPause = 0;
	desenharBuff = false;
	desenharBuff2 = false;
	fimJogo = false;
}

Sala::~Sala()
{
	exit(0);
}

void Sala::inicializar(int f)
{
	// Tempo
	gTempo.inicializar();
	ticks = ticksPodeMachucar = ticksPodeMachucar2 = tickBuff = gTempo.getTicks();
	

	// * Sala *
	carregarSala(f);
	salaAtual = f;

	// * Personagem *	
	inicializarPlayer();
	if (isP2)
	{
		inicializarPlayer2();
	}
	
	// * Inimigo *
	carregarInim();
	
	// * Moedas *
	carregarMoedas();
	

	// * Baú de Tesouro *
	carregarBau();

	// * Inventário *
	carregarInventario();

	// * Assets *
	carregarAssets();
	
	// Booleanos 
	loja = false;
	pause = false;
	sair = false;
	next = false;
	previous = false;
	posX = 1;
	posY = 1;
	for (int i = 0; i < nInimigos; i++)
	{
		posXinim[i] = 1;
		posYinim[i] = 1;
	}

}

void Sala::atualizar()
{

	if (!loja && !pause)
	{
		// PAUSE E LOJA
		if (gTeclado.pressionou[TECLA_L])
		{
			loja = true;
		}
		//if (gTeclado.pressionou[TECLA_ESC])
		if (gTeclado.pressionou[TECLA_P])
		{
			pause = true;
		}

		
		if (gJoysticks.player1.pressionou[BOTAO_XBOX_START])
		{
			pause = true;
		}
		
		if (gJoysticks.player2.pressionou[BOTAO_XBOX_START])
		{
			pause = true;
			p2Pausou = true;
		}
		

		// * Sala *
		tiles[31].avancarAnimacao();

		for (int l = 0; l < nLinhas; l++) {
			for (int c = 0; c < nColunas; c++)
				tiles[mapaSala[c][l]].desenhar(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c, tiles[0].getAltura() / 2 + tiles[0].getAltura() * l);
		}

		
		// * Tesouro *
		for (int i = 0; i < nBau; i++) {
			bau[i].sprBau.desenhar(bau[i].xBau, bau[i].yBau);
		}

		// * Desenhar Itens *
		for (int i = 0; i < nItens; i++) {
			item[i].desenhar();
		}
		utilizarItens();

		
		
		// * Moedas *	
		for (int i = 0; i < nCoin; i++) {
			if (coin[i].goldDisponivel) {
				coin[i].sprGold.desenhar(coin[i].xGold, coin[i].yGold);
				coin[i].sprGold.avancarAnimacao();
			}
		}

		// * Inimigo *
		for (int i = 0; i < nInimigos; i++) {
			posXinim[i] = inimigos[i]->getX() / tiles[0].getLargura();
			posYinim[i] = inimigos[i]->getY() / tiles[0].getAltura();
		}

		for (int i = 0; i < nInimigos; i++)
		{
			if (inimigos[i]->getVivo()) { // a sprite pisca quando ele está ferido
				if (inimigos[i]->getPodeMachucar())
					inimigos[i]->desenhar();
				else {
					int random = rand() % 2;
					if (random)
						inimigos[i]->desenhar();
				}
			}
		}

		movimentarInimigo();


		// * Personagem *
		if (personagem->getVivo()) {
			posX = personagem->getX() / tiles[0].getLargura();
			posY = personagem->getY() / tiles[0].getAltura();
			if (personagem->getPodeMachucar()) // a sprite pisca quando ele está ferido
				personagem->desenhar();

			else {
				int random = rand() % 2;
				if (random)
					personagem->desenhar();
			}
			movimentarPlayer();
			personagem->atacar();
		}

		if (isP2)
		{
			if (personagem2->getVivo()) {
				posX2 = personagem2->getX() / tiles[0].getLargura();
				posY2 = personagem2->getY() / tiles[0].getAltura();
				if (personagem2->getPodeMachucar()) // a sprite pisca quando ele está ferido
					personagem2->desenhar();

				else {
					int random = rand() % 2;
					if (random)
						personagem2->desenhar();
				}
				movimentarPlayer2();
				personagem2->atacar();
			}
		}

		//Desenhar Buff
		if (desenharBuff)
		{
			spriteBuff.desenhar(personagem->getX(), personagem->getY());
		}

		if (gTempo.getTempoAteTickAtual(tickBuff) > 0.8)
		{
			desenharBuff = false;
		}

		if (desenharBuff2)
		{
			spriteBuff.desenhar(personagem2->getX(), personagem2->getY());
		}

		if (gTempo.getTempoAteTickAtual(tickBuff) > 0.8)
		{
			desenharBuff2 = false;
		}
		// * Inventário *
		if (exibirInventario)
			desenharInventario();
		if (gTeclado.pressionou[TECLA_I] || gJoysticks.player1.pressionou[BOTAO_XBOX_VOLTAR] || gJoysticks.player2.pressionou[BOTAO_XBOX_VOLTAR])
			exibirInventario = !exibirInventario;

		// * Colisão *
		testarColisao();

		// * Textos *
		escreverInfos();

		// TROCA FASE
	
		if (isP2)
		{
			if (personagem2->getVidas() <= 0)
			{
				isP2 = false;
			}
		}
		if (mapaSala[posX][posY] == 31 && salaAtual > 1)
		{
			previous = true;
		}
		if (mapaSala[posX][posY] == 33 && salaAtual < 15)
		{
			next = true;
		}
		if (isP2)
		{
			if (mapaSala[posX2][posY2] == 31 && salaAtual > 1)
			{
				previous = true;
			}
			if (mapaSala[posX2][posY2] == 33 && salaAtual < 15)
			{
				next = true;
			}
		}

		if (salaAtual == 15)
		{
			if (mapaSala[posX][posY] == 33)
			{
				fimJogo = true;
			}
			if (mapaSala[posX2][posY2] == 33)
			{
				fimJogo = true;
			}
		}

		//Anim bau

		for (int i = 0; i < nBau; i++)
		{
			if (bau[i].abriu)
			{
				bau[i].sprBau.setFrame(1);
			}
			else
			{
				bau[i].sprBau.setFrame(0);
			}
		}
	}
	
	else   // LOJA E PAUSE
	{
		if (loja)		{
			abrirLoja();
		}

		if (pause)		{
			pausarJogo();
		}
	}

}


#pragma region Personagem

void Sala::inicializarPlayer()
{
	switch (per)
	{
	case 1:	personagem = new PSkeleton;
		break;
	case 2:	personagem = new PKnight;
		break;
	case 3: personagem = new PArcher;
		break;
	default:
		break;
	}

	personagem->inicializar();
	personagem->carregarAudio();

	// Personagem no mapa
	for (int l = 0; l < nLinhas; l++) {
		for (int c = 0; c < nColunas; c++) {
			if (mapaSala[c][l] == 31) {
				personagem->setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c);
				personagem->setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * (l+1));
				break;
			}
		}
	}
}


void Sala::inicializarPlayer2()
{
	switch (per2)
	{
	case 1:	personagem2 = new PSkeleton;
		break;
	case 2:	personagem2 = new PKnight;
		break;
	case 3: personagem2 = new PArcher;
		break;
	default:
		break;
	}

	personagem2->inicializar();
	personagem2->carregarAudio();

	personagem2->setIsP2();

	// Personagem no mapa
	personagem2->setX(personagem->getX() + personagem->getSprite().getLargura());
	personagem2->setY(personagem->getY());

}

void Sala::movimentarPlayer()
{
	
	// condições de movimentação, levando em consideração os tiles
	if (mapaObjetos[posX + 1][posY] < 0)
		personagem->setPodeAndar(dir, true);
	else
		personagem->setPodeAndar(dir, false);
	if (mapaObjetos[posX - 1][posY] < 0)
		personagem->setPodeAndar(esq, true);
	else
		personagem->setPodeAndar(esq, false);
	if (mapaObjetos[posX][posY + 1] < 0)
		personagem->setPodeAndar(baixo, true);
	else
		personagem->setPodeAndar(baixo, false);
	if (mapaObjetos[posX][posY - 1] < 0)
		personagem->setPodeAndar(cima, true);
	else
		personagem->setPodeAndar(cima, false);
	
	personagem->andar();	
}

void Sala::movimentarPlayer2()
{
	if (posX2 <= 0)
	{
		posX2 = 1;
	}
	if (posY2 <= 0)
	{
		posY2 = 1;
	}
	// condições de movimentação, levando em consideração os tiles
	if (mapaObjetos[posX2 + 1][posY2] < 0)
		personagem2->setPodeAndar(dir, true);
	else
		personagem2->setPodeAndar(dir, false);
	if (mapaObjetos[posX2 - 1][posY2] < 0)
		personagem2->setPodeAndar(esq, true);
	else
		personagem2->setPodeAndar(esq, false);
	if (mapaObjetos[posX2][posY2 + 1] < 0)
		personagem2->setPodeAndar(baixo, true);
	else
		personagem2->setPodeAndar(baixo, false);
	if (mapaObjetos[posX2][posY2 - 1] < 0)
		personagem2->setPodeAndar(cima, true);
	else
		personagem2->setPodeAndar(cima, false);

	personagem2->andar();
}
void Sala::escreverInfos()
{
	// Moedas
	qtdMoedas.setString("Gold P1: " + to_string(personagem->getMoedas()));
	qtdMoedas.desenhar(200, 20, 0);

	// Vidas
	qtdVidas.setString("HP P1: " + to_string(personagem->getVidas()));
	qtdVidas.desenhar(100, 20, 0);

	// Pontuação
	//qtdPontos.setString("Pontos: " + to_string(personagem->getPontos()));
	//qtdPontos.desenhar(100, 40, 0);


	if (isP2)
	{
		// Moedas
		qtdMoedas.setString("Gold P2: " + to_string(personagem2->getMoedas()));
		qtdMoedas.desenhar(700, 20, 0);

		// Vidas
		qtdVidas.setString("HP P2: " + to_string(personagem2->getVidas()));
		qtdVidas.desenhar(800, 20, 0);
	}
}

void Sala::utilizarItens()
{
	if (personagem->getVivo()) {
		if (gTeclado.pressionou[TECLA_KP_1] || gJoysticks.player1.pressionou[BOTAO_XBOX_X]) {
			if (inventario.getNodo(0))
			{
				if (personagem->getVidas() + 5 <= 20)
				{
					personagem->atualizarVidas(5);

					spot.tocar();
				}

				else {
					spot.tocar();
					for (int i = 0; i < 20; i++) {
						if (personagem->getVidas() < 20)
							personagem->atualizarVidas(1);
						else
							break;
					}
				}
			}

			inventario.remover(0);
		}

		else if (gTeclado.pressionou[TECLA_KP_2] || gJoysticks.player1.pressionou[BOTAO_XBOX_Y]) {

			if (inventario.getNodo(1))	{
				personagem->setpAtaque(personagem->getPAtaque() + 1);

				sbuff.tocar();
				desenharBuff = true;
				tickBuff = gTempo.getTicks();
			}
			inventario.remover(1);
		}

		else if (gTeclado.pressionou[TECLA_KP_3] || gJoysticks.player1.pressionou[BOTAO_XBOX_B]) {

			for (int i = 0; i < nInimigos; i++)	{
				if (inventario.getNodo(2))	{
					inimigos[i]->setpAtaque(inimigos[i]->getPAtaque() - 1);

					sdebuff.tocar();

					inimigos[i]->setEfeito(true);
				}
			}
			inventario.remover(2);
		}
	}

	if (isP2)
	{
		if (personagem2->getVivo()) {
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_X]) {
				if (inventario2.getNodo(0))
				{
					if (personagem2->getVidas() + 5 <= 20)
					{
						personagem2->atualizarVidas(5);

						spot.tocar();
					}

					else {
						spot.tocar();

						for (int i = 0; i < 20; i++) {
							if (personagem2->getVidas() < 20)
								personagem2->atualizarVidas(1);
							else
								break;
						}
					}
				}

				inventario2.remover(0);
			}

			else if (gJoysticks.player2.pressionou[BOTAO_XBOX_Y]) {

				if (inventario2.getNodo(1)) {
					personagem2->setpAtaque(personagem2->getPAtaque() + 1);

					sbuff.tocar();

					desenharBuff2 = true;
					tickBuff = gTempo.getTicks();
				}
				inventario2.remover(1);
			}

			else if (gJoysticks.player2.pressionou[BOTAO_XBOX_B]) {

				if (inventario2.getNodo(2))
				{
					sdebuff.tocar();
				}

				for (int i = 0; i < nInimigos; i++) {
					if (inventario2.getNodo(2)) {
						inimigos[i]->setpAtaque(inimigos[i]->getPAtaque() - 1);

						inimigos[i]->setEfeito(true);
					}
				}
				inventario2.remover(2);
			}
		}
	}
}

#pragma endregion


#pragma region Inimigos

void Sala::carregarInim()
{
	posXinim = new int[nInimigos];
	posYinim = new int[nInimigos];
	dirInim = new int[nInimigos];
	carregouDir = false;

	for (int i = 0; i < nInimigos; i++) {
		sorteioInim = rand() % 3;
		if (sorteioInim == 0)
		{
			inimigos.push_back(new IniGrue);
		}
		else if (sorteioInim == 1)
		{
			inimigos.push_back(new IniBat);
		}
		else
		{
			inimigos.push_back(new IniAranha);
		}
		inimigos[i]->inicializar();
	}
	if (!loaded)
	{

		for (int i = 0; i < nInimigos; i++) {
			do {
				linhaInim = rand() % 24;
				colunaInim = rand() % 32;

				inimigos[i]->setX(32 / 2 + 32 * colunaInim);
				inimigos[i]->setY(32 / 2 + 32 * linhaInim);

			} while (mapaObjetos[colunaInim][linhaInim] != -2);
		}
	}
}

void Sala::movimentarInimigo()
{
	// O inimigo se movimenta sozinho em posições aleatórias, dentro dos tiles caminháveis
	if (!carregouDir) {
		for (int i = 0; i < nInimigos; i++) {
			dirInim[i] = rand() % 4;
			inimigos[i]->setDir(dirInim[i]);
		}
		carregouDir = true;
	}

	for (int i = 0; i < nInimigos; i++) {
		if (inimigos[i]->getVivo()) {
			int random = rand() % 2 + 2;

			if (gTempo.getTempoAteTickAtual(ticks) > random) {
				dirInim[i] = rand() % 4;
				inimigos[i]->setDir(dirInim[i]);

				ticks = gTempo.getTicks();
			}
		}
	}

	for (int i = 0; i < nInimigos; i++)
	{
		inimigos[i]->knockBack();

		if (inimigos[i]->getKnockBack())
		{
			inimigos[i]->parado();

			if (inimigos[i]->getDirKnB() == pesq && mapaObjetos[posXinim[i] - 1][posYinim[i]] >= 0)
				inimigos[i]->setX(inimigos[i]->getX() + 5);

			if (inimigos[i]->getDirKnB() == pdir && mapaObjetos[posXinim[i] + 1][posYinim[i]] >= 0)
				inimigos[i]->setX(inimigos[i]->getX() - 5);

			if (inimigos[i]->getDirKnB() == pcima && mapaObjetos[posXinim[i]][posYinim[i] - 1] >= 0)
				inimigos[i]->setY(inimigos[i]->getY() + 5);

			if (inimigos[i]->getDirKnB() == pbaixo && mapaObjetos[posXinim[i]][posYinim[i] + 1] >= 0)
				inimigos[i]->setY(inimigos[i]->getY() - 5);
		}

		if (!inimigos[i]->getKnockBack())
		{
			// Testando se o próximo tile é caminhável, senão sorteia outra direção

			if (mapaObjetos[posXinim[i]][posYinim[i]] >= 0)
			{
				inimigos[i]->parado();
				//inimigos[i]->setMorto();
			}
			else
			{

				switch (inimigos[i]->getDir())
				{
				case Left:
					if (mapaObjetos[posXinim[i] - 1][posYinim[i]] < 0)
						inimigos[i]->andarEsq();
					else {
						dirInim[i] = rand() % 4;
						inimigos[i]->setDir(dirInim[i]);
					}
					break;

				case Right:
					if (mapaObjetos[posXinim[i] + 1][posYinim[i]] < 0)
						inimigos[i]->andarDir();
					else {
						dirInim[i] = rand() % 4;
						inimigos[i]->setDir(dirInim[i]);
					}
					break;

				case Up:
					if (mapaObjetos[posXinim[i]][posYinim[i] - 1] < 0)
						inimigos[i]->andarCima();
					else {
						dirInim[i] = rand() % 4;
						inimigos[i]->setDir(dirInim[i]);
					}
					break;

				case Down:
					if (mapaObjetos[posXinim[i]][posYinim[i] + 1] < 0)
						inimigos[i]->andarBaixo();
					else {
						dirInim[i] = rand() % 4;
						inimigos[i]->setDir(dirInim[i]);
					}
					break;

				default:
					inimigos[i]->parado();
					break;
				}
			}
		}
	}
	/*if (gTeclado.pressionou[TECLA_N] && salaAtual < 15)
	{
		next = true;
	}
	if (gTeclado.pressionou[TECLA_B] && salaAtual > 1)
	{
		previous = true;
	}*/
}

void Sala::setPosNext()
{
	for (int l = 0; l < nLinhas; l++) {
		for (int c = 0; c < nColunas; c++) {
			if (mapaSala[c][l] == 31) {
				personagem->setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c);
				personagem->setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * (l + 1));
				break;
			}
		}
	}

	if (isP2)
	{
		personagem2->setX(personagem->getX() + personagem->getSprite().getLargura());
		personagem2->setY(personagem->getY());
	}
}

void Sala::setPosPrev()
{
	for (int l = 0; l < nLinhas; l++) {
		for (int c = 0; c < nColunas; c++) {
			if (mapaSala[c][l] == 33) {
				personagem->setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * c);
				personagem->setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * (l + 1));
				break;
			}
		}
	}

	if (isP2)
	{
		personagem2->setX(personagem->getX() + personagem->getSprite().getLargura());
		personagem2->setY(personagem->getY());
	}
}

#pragma endregion


#pragma region Sala

void Sala::carregarSala(int s)
{
	string name, path, arqName;
	int nID, nAnim, nFrames, nTiles;
	ifstream arquivoSala;
	
	arqName = "salas/sala" + to_string(s) + ".txt";

	arquivoSala.open(arqName);
	if (arquivoSala.is_open())
	{
		arquivoSala >> nInimigos;
		arquivoSala >> nItens;
		arquivoSala >> nTiles;

		tiles = new Sprite[nTiles];

		for (int t = 0; t < nTiles; t++) {
			arquivoSala >> nID >> name >> path >> nAnim >> nFrames;
			if (!gRecursos.carregouSpriteSheet(name))
				gRecursos.carregarSpriteSheet(name, path, nAnim, nFrames);
			tiles[nID].setSpriteSheet(name);
		}

		arquivoSala >> nColunas >> nLinhas;

		mapaSala = new int*[nColunas];
		mapaObjetos = new int*[nColunas];

		for (int c = 0; c < nColunas; c++) {
			mapaSala[c] = new int[nLinhas];
			mapaObjetos[c] = new int[nLinhas];
		}

		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				arquivoSala >> mapaSala[c][l];

		for (int l = 0; l < nLinhas; l++)
			for (int c = 0; c < nColunas; c++)
				arquivoSala >> mapaObjetos[c][l];

		arquivoSala.close();
	}
	else {
		//exit(0);
	}
}

void Sala::carregarAssets()
{
	// * Textos *
	// Textos Infos Personagem
	if (!gRecursos.carregouFonte("calibrib")) {
		gRecursos.carregarFonte("calibrib", "calibrib.ttf", 20);
	}
	qtdVidas.setFonte("calibrib");
	qtdMoedas.setFonte("calibrib");
	//qtdPontos.setFonte("calibrib");

	// Texto Inventário
	if (!gRecursos.carregouFonte("fonte1"))	{
		gRecursos.carregarFonte("fonte1", "fonte_padrao.ttf", 18);
	}
	txt.setFonte("fonte1");
	txt.setCor(0, 0, 0);

	// * Sons *
	if (!gRecursos.carregouAudio("coin")) {
		gRecursos.carregarAudio("coin", "sons/coin.wav");
	}

	scoin.setAudio("coin");

	if (!gRecursos.carregouAudio("monstro")) {
		gRecursos.carregarAudio("monstro", "sons/monstro.wav");
	}
	smonstro.setAudio("monstro");

	if (!gRecursos.carregouAudio("pot")) {
		gRecursos.carregarAudio("pot", "sons/pot.wav");
	}
	spot.setAudio("pot");

	if (!gRecursos.carregouAudio("buff")) {
		gRecursos.carregarAudio("buff", "sons/buff.wav");
	}
	sbuff.setAudio("buff");

	if (!gRecursos.carregouAudio("debuff")) {
		gRecursos.carregarAudio("debuff", "sons/debuff.wav");
	}
	sdebuff.setAudio("debuff");

	// * Loja *
	if (!gRecursos.carregouSpriteSheet("loja")) {
		gRecursos.carregarSpriteSheet("loja", "sprites/store.png");
	}
	fundoLoja.setSpriteSheet("loja");

	// * Botões *
	// Fundo da tela
	if (!gRecursos.carregouSpriteSheet("fundoPause"))
		gRecursos.carregarSpriteSheet("fundoPause", "sprites/menu/PAUSA1.png");
	fundoPause.setSpriteSheet("fundoPause");

	// Continuar
	if (!gRecursos.carregouSpriteSheet("bContinuar"))
		gRecursos.carregarSpriteSheet("bContinuar", "sprites/menu/cont.png", 3, 1);
	bContinuar.setSpriteSheet("bContinuar");

	// Sair
	if (!gRecursos.carregouSpriteSheet("bSair"))
		gRecursos.carregarSpriteSheet("bSair", "sprites/menu/sair.png", 3, 1);
	bSair.setSpriteSheet("bSair");

	// Loja
	if (!gRecursos.carregouSpriteSheet("bLoja"))
		gRecursos.carregarSpriteSheet("bLoja", "sprites/menu/loja.png", 3, 1);
	bLoja.setSpriteSheet("bLoja");

	// Voltar
	if (!gRecursos.carregouSpriteSheet("bVoltar"))
		gRecursos.carregarSpriteSheet("bVoltar", "sprites/menu/volta.png", 3, 1);
	bVoltar.setSpriteSheet("bVoltar");


	// SpriteBuff
	if (!gRecursos.carregouSpriteSheet("buff"))
		gRecursos.carregarSpriteSheet("buff", "sprites/efeitoBuff.png", 1, 1);
	spriteBuff.setSpriteSheet("buff");
}

void Sala::carregarItens()
{
	string path, arqName, nome;
	int nAnim, nFrames, nID;
	ifstream arquivoItens;
	Item *carregarItens;

	arqName = "itens.txt";

	arquivoItens.open(arqName);
	if (arquivoItens.is_open())
	{
		arquivoItens >> itensCarreg;

		carregarItens = new Item[itensCarreg];
		nomeItens = new string[itensCarreg];
		itensPath = new string[itensCarreg];
		tipoItem = new int[itensCarreg];

		for (int t = 0; t < itensCarreg; t++) 
		{
			arquivoItens >> nID >> nome >> path >> nAnim >> nFrames;
			if (!gRecursos.carregouSpriteSheet(nome))
				gRecursos.carregarSpriteSheet(nome, path, nAnim, nFrames);
			nomeItens[nID] = nome;
			itensPath[nID] = path;
			tipoItem[nID] = nID;
		}
		arquivoItens.close();
	}
	else {
		//exit(0);
	}
}

void Sala::carregarMoedas()
{
	if (!loaded)
	{
		nCoin = rand() % 3 + 1;
	}
	coin = new Gold[nCoin];

	if (!gRecursos.carregouSpriteSheet("gold"))
		gRecursos.carregarSpriteSheet("gold", "sprites/gold.png", 1, 8);

	for (int i = 0; i < nCoin; i++) {
		coin[i].sprGold.setSpriteSheet("gold");
		coin[i].sprGold.setVelocidadeAnimacao(7);
	}

	for (int i = 0; i < nCoin; i++) {
		do {
			linhaInim = rand() % 24;
			colunaInim = rand() % 32;

			coin[i].xGold = tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaInim;
			coin[i].yGold = tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaInim;

		} while (mapaObjetos[colunaInim][linhaInim] != -1);
	}
}

void Sala::carregarBau()
{
	if (!loaded)
	{
		nBau = rand() % 2 + 1;
	}
	bau = new Bau[nBau];

	if (!gRecursos.carregouSpriteSheet("bau"))
		gRecursos.carregarSpriteSheet("bau", "sprites/chest.png", 1, 2); // depois inverter a imagem pra funcionar animação

	for (int i = 0; i < nBau; i++) {
		bau[i].sprBau.setSpriteSheet("bau");
		if (!loaded)
		{
			do {
				linhaInim = rand() % 24;
				colunaInim = rand() % 32;

				bau[i].xBau = tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaInim;
				bau[i].yBau = tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaInim;

			} while (mapaObjetos[colunaInim][linhaInim] != -1);
		}
	}
}

void Sala::carregarInventario()
{
	if (!gRecursos.carregouSpriteSheet("canvasInventario"))
	{
		gRecursos.carregarSpriteSheet("canvasInventario", "sprites/fundoInv.png");
	}

	exibirInventario = false;
	canvasI.setSpriteSheet("canvasInventario");
	if (!loaded)
	{
		carregarItens();
	}
	item = new Item[nItens];

	if (!loaded)
	{
		for (int i = 0; i < nItens; i++) {
			sorteioItens = rand() % itensCarreg;
			item[i].inicializar(nomeItens[sorteioItens], itensPath[sorteioItens], 1, 1);
			item[i].setTipo(sorteioItens);
		}

		for (int i = 0; i < nItens; i++) {
			do {
				linhaItem = rand() % 24;
				colunaItem = rand() % 32;

				item[i].setX(tiles[0].getLargura() / 2 + tiles[0].getLargura() * colunaItem);
				item[i].setY(tiles[0].getAltura() / 2 + tiles[0].getAltura() * linhaItem);

			} while (mapaObjetos[colunaItem][linhaItem] != -1);
		}
	}
}

void Sala::desenharInventario()
{
	txt.setCorAzul(0);
	txt.setCorVerde(0);
	txt.setCorVermelho(0);
	txt.setFonte("fonte");
	txt.setEscala(0.7,0.7);
	canvasI.desenhar(200, 100);
	txt.setAlinhamento(TEXTO_CENTRALIZADO);
	txt.setString("Inventário");

	txt.desenhar(200, 50);

	NodoItem *aux = inventario.getIni();
	Sprite sprAux;
	float x = 70.0, y = 100.0;
	
	for (int i = 0; i < 3; i++)
	{
		sprAux.setSpriteSheet(nomes_pocoes[i]);
		sprAux.desenhar(x, y + 15);

		if (inventario.getNodo(i) == NULL)
		{
			txt.setString(to_string(0));
		}
		else
		{
			txt.setString(to_string(inventario.getNodo(i)->qtd));
		}

		txt.desenhar(x, y + 50);

		txt.setString("NUM" + to_string(i + 1));
		txt.desenhar(x, y - 20);
		x += sprAux.getLargura() + 40;
	}

	if (isP2)
	{
		txt.setCorAzul(0);
		txt.setCorVerde(0);
		txt.setCorVermelho(0);
		txt.setFonte("fonte");
		txt.setEscala(0.7, 0.7);
		canvasI.desenhar(800, 100);
		txt.setAlinhamento(TEXTO_CENTRALIZADO);
		txt.setString("Inventário");

		txt.desenhar(800, 50);

		NodoItem *aux = inventario2.getIni();
		Sprite sprAux;
		float x = 670.0, y = 100.0;

		for (int i = 0; i < 3; i++)
		{
			sprAux.setSpriteSheet(nomes_pocoes[i]);
			sprAux.desenhar(x, y + 15);

			if (inventario2.getNodo(i) == NULL)
			{
				txt.setString(to_string(0));
			}
			else
			{
				txt.setString(to_string(inventario2.getNodo(i)->qtd));
			}

			txt.desenhar(x, y + 50);

			txt.setString("NUM" + to_string(i + 1));
			txt.desenhar(x, y - 20);
			x += sprAux.getLargura() + 40;
		}
	}
}

void Sala::abrirLoja()
{
	// Fundo
	fundoLoja.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	// Botão voltar
	//bVoltar.atualizar();
	bVoltar.setPos(gJanela.getLargura() / 2, 600);
	bVoltar.desenhar();

	if (!p2EstaNaLoja)
	{
		if (gTeclado.pressionou[TECLA_S] || gJoysticks.player1.pressionou[BOTAO_XBOX_BAIXO])
		{
			voltarLoja = true;
		}
		if (gTeclado.pressionou[TECLA_W] || gJoysticks.player1.pressionou[BOTAO_XBOX_CIMA])
		{
			voltarLoja = false;
		}
	}
	else
	{
		if (gJoysticks.player2.pressionou[BOTAO_XBOX_BAIXO])
		{
			voltarLoja = true;
		}
		if (gJoysticks.player2.pressionou[BOTAO_XBOX_CIMA])
		{
			voltarLoja = false;
		}
	}

	if (voltarLoja)
	{
		bVoltar.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		if (!p2EstaNaLoja)
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
		bVoltar.setEstado(BOTAOSPRITE_NORMAL);
	}

	if (bVoltar.estaAbaixado()) {
		loja = false;
	}

	if (gTeclado.pressionou[TECLA_L])
	{
		loja = false;
	}

	txt.setAlinhamento(TEXTO_CENTRALIZADO);
	txt.setString("LOJA");
	txt.setCorAzul(255);
	txt.setCorVerde(255);
	txt.setCorVermelho(255);
	txt.setFonte("fonte");
	txt.desenhar(gJanela.getLargura() / 2, 50);

	gGraficos.desenharTexto("GOLD: ", 50, 50, 255, 255, 255, 255, 0, 0);
	gGraficos.desenharTexto(to_string(personagem->getMoedas()), 200, 50, 255, 255, 255, 255, 0, 0);

	if (isP2)
	{
		gGraficos.desenharTexto("GOLD P2: ", 50, 100, 255, 255, 255, 255, 0, 0);
		gGraficos.desenharTexto(to_string(personagem2->getMoedas()), 200, 100, 255, 255, 255, 255, 0, 0);
	}

	Sprite spr1, spr2, spr3;
	float x = gJanela.getLargura() / 2 - 60, y = 380.0;
	float sprX[3], sprY[3];
	int preco[3] = { 5000, 1000, 1000 };

	for (int i = 0; i < 3; i++)
	{
		spr1.setSpriteSheet(nomes_pocoes[i]);

		gGraficos.desenharTexto(to_string(preco[i]), x - 12, y + 19, 255, 255, 255, 255, 0, 0);
		spr1.desenhar(x, y);

		sprX[i] = x;
		sprY[i] = y;

		if (uniTestarColisaoPontoComSprite(gMouse.x, gMouse.y, spr1, x, y, 0))
		{
			if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
			{
				if (personagem->getMoedas() >= preco[i])
				{
					personagem->setMoedas(personagem->getMoedas() - preco[i]);
					inventario.add(i);
					scoin.tocar();
				}

			}
		}
		x += spr1.getLargura() + 25;
	}
	Quad retan;
	retan.larg = 60;
	retan.alt = 60;
	retan.x = (sprX[selecaoLoja] - 30);
	retan.y = (sprY[selecaoLoja] - 30);

	
	if (!voltarLoja)
	{
		gGraficos.desenharRetangulo(retan, 10, 10, 10);

		if (!p2EstaNaLoja)
		{
			if (selecaoLoja > 0)
			{
				if (gTeclado.pressionou[TECLA_A] || gJoysticks.player1.pressionou[BOTAO_XBOX_ESQ])
				{
					selecaoLoja--;
				}
			}
			if (selecaoLoja < 2)
			{
				if (gTeclado.pressionou[TECLA_D] || gJoysticks.player1.pressionou[BOTAO_XBOX_DIR])
				{
					selecaoLoja++;
				}
			}

			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				if (personagem->getMoedas() >= preco[selecaoLoja])
				{
					personagem->setMoedas(personagem->getMoedas() - preco[selecaoLoja]);
					inventario.add(selecaoLoja);
					scoin.tocar();
				}

			}
		}
		else
		{
			if (selecaoLoja > 0)
			{
				if (gJoysticks.player2.pressionou[BOTAO_XBOX_ESQ])
				{
					selecaoLoja--;
				}
			}
			if (selecaoLoja < 2)
			{
				if (gJoysticks.player2.pressionou[BOTAO_XBOX_DIR])
				{
					selecaoLoja++;
				}
			}

			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				if (personagem2->getMoedas() >= preco[selecaoLoja])
				{
					personagem2->setMoedas(personagem2->getMoedas() - preco[selecaoLoja]);
					inventario2.add(selecaoLoja);
					scoin.tocar();
				}

			}
		}
	}


}

void Sala::pausarJogo()
{
	// Botões
	fundoPause.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

	bContinuar.setPos(512, 450);
	//bContinuar.atualizar();
	bContinuar.desenhar();

	bLoja.setPos(512, 525);
	//bLoja.atualizar();
	bLoja.desenhar();

	bSair.setPos(512, 600);
	//bSair.atualizar();
	bSair.desenhar();

	if (selecaoPause == 0)
	{
		bContinuar.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		bLoja.setEstado(BOTAOSPRITE_NORMAL);
		bSair.setEstado(BOTAOSPRITE_NORMAL);
		if (!p2Pausou)
		{
			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				bContinuar.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
		else
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				bContinuar.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
	}
	else if (selecaoPause== 1)
	{
		bContinuar.setEstado(BOTAOSPRITE_NORMAL);
		bLoja.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);
		bSair.setEstado(BOTAOSPRITE_NORMAL);

		if (!p2Pausou)
		{
			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				bLoja.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
		else
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				bLoja.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
	}
	else if (selecaoPause == 2)
	{
		bContinuar.setEstado(BOTAOSPRITE_NORMAL);
		bLoja.setEstado(BOTAOSPRITE_NORMAL);
		bSair.setEstado(BOTAOSPRITE_COM_MOUSE_EM_CIMA);

		if (!p2Pausou)
		{
			if (gTeclado.pressionou[TECLA_ENTER] || gJoysticks.player1.pressionou[BOTAO_XBOX_A])
			{
				bSair.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
		else
		{
			if (gJoysticks.player2.pressionou[BOTAO_XBOX_A])
			{
				bSair.setEstado(BOTAOSPRITE_ABAIXADO);
			}
		}
	}

	if (!p2Pausou)
	{
		if (gTeclado.pressionou[TECLA_S] || gJoysticks.player1.pressionou[BOTAO_XBOX_BAIXO])
		{
			if (selecaoPause < 2)
			{
				selecaoPause++;
			}
		}
		if (gTeclado.pressionou[TECLA_W] || gJoysticks.player1.pressionou[BOTAO_XBOX_CIMA])
		{
			if (selecaoPause > 0)
			{
				selecaoPause--;
			}
		}
	}
	else
	{
		if (gJoysticks.player2.pressionou[BOTAO_XBOX_BAIXO])
		{
			if (selecaoPause < 2)
			{
				selecaoPause++;
			}
		}
		if (gJoysticks.player2.pressionou[BOTAO_XBOX_CIMA])
		{
			if (selecaoPause > 0)
			{
				selecaoPause--;
			}
		}
	}

	//if (gTeclado.pressionou[TECLA_P])
	if (bContinuar.estaAbaixado()) {
		pause = false;
	}

	if (bLoja.estaAbaixado()) {
		loja = true;
		pause = false;
		if (p2Pausou)
		{
			p2EstaNaLoja = true;
		}
	}

	else if (bSair.estaAbaixado()) {
		// voltar pro menu desempilhando 				
		saving = true;
		sair = true;
		//pause = false;
	}
}
#pragma endregion

void Sala::testarColisao()
{
	// Itens no chão
	for (int i = 0; i < nItens; i++) {
		if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
			item[i].getSprite(), item[i].getX(), item[i].getY(), 0, true)) {
			if (!item[i].getPegou()) {
				// Pega o item do chão
				item[i].setPegou();
				// Adiciona ao inventário
				inventario.add(item[i].getTipo());
			}
		}
	}

	if (isP2)
	{
		for (int i = 0; i < nItens; i++) {
			if (uniTestarColisaoSpriteComSprite(personagem2->getSprite(), personagem2->getX(), personagem2->getY(), 0,
				item[i].getSprite(), item[i].getX(), item[i].getY(), 0, true)) {
				if (!item[i].getPegou()) {
					// Pega o item do chão
					item[i].setPegou();
					// Adiciona ao inventário
					inventario2.add(item[i].getTipo());
				}
			}
		}
	}

	// * Bau *
	for (int i = 0; i < nBau; i++) {
		if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
			bau[i].sprBau, bau[i].xBau, bau[i].yBau, 0, true))
			if (!bau[i].abriu) {
				// Animação do baú
				bau[i].abriu = true;
				
				personagem->setPontos(personagem->getPontos() + 100); // + 100 pontos

				// Sorteio do baú
				int random = uniRandEntre(0, 100);
				if (random <= 20) {	// Item aleatório
					int randItem = rand() % itensCarreg;
					inventario.add(randItem);
				}
				else { // Ouro aleatório
					int ouros = (uniRandEntre(1, 6) * 1000);
					personagem->setMoedas(personagem->getMoedas() + ouros);
					scoin.tocar();
				}
			}
	}

	if (isP2)
	{
		for (int i = 0; i < nBau; i++) {
			if (uniTestarColisaoSpriteComSprite(personagem2->getSprite(), personagem2->getX(), personagem2->getY(), 0,
				bau[i].sprBau, bau[i].xBau, bau[i].yBau, 0, true))
				if (!bau[i].abriu) {
					// Animação do baú
					bau[i].abriu = true;

					personagem2->setPontos(personagem2->getPontos() + 100); // + 100 pontos

																		  // Sorteio do baú
					int random = uniRandEntre(0, 100);
					if (random <= 20) {	// Item aleatório
						int randItem = rand() % itensCarreg;
						inventario2.add(randItem);
					}
					else { // Ouro aleatório
						int ouros = (uniRandEntre(1, 6) * 1000);
						personagem2->setMoedas(personagem->getMoedas() + ouros);
						scoin.tocar();
					}
				}
		}
	}

	// Moedas do chão (valem 100 gold)
	for (int i = 0; i < nCoin; i++) {
		if (coin[i].goldDisponivel) // se a moeda ainda estiver no chão
			if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
				coin[i].sprGold, coin[i].xGold, coin[i].yGold, 0)) {
				personagem->setMoedas(personagem->getMoedas() + 100); // aumenta as moedas do personagel
				coin[i].goldDisponivel = false; // pega a moeda e tira do mapa
				scoin.tocar();
			}
	}

	if (isP2)
	{
		for (int i = 0; i < nCoin; i++) {
			if (coin[i].goldDisponivel) // se a moeda ainda estiver no chão
				if (uniTestarColisaoSpriteComSprite(personagem2->getSprite(), personagem2->getX(), personagem2->getY(), 0,
					coin[i].sprGold, coin[i].xGold, coin[i].yGold, 0)) {
					personagem2->setMoedas(personagem2->getMoedas() + 100); // aumenta as moedas do personagel
					coin[i].goldDisponivel = false; // pega a moeda e tira do mapa
					scoin.tocar();
				}
		}
	}

	// Colisão de Player com Inimigos
	for (int i = 0; i < nInimigos; i++) {
		if (personagem->getVivo() && inimigos[i]->getVivo()) // testa se estão vivos
			if (personagem->getPodeMachucar()) { // se o personagem não está machucado
				if (uniTestarColisaoSpriteComSprite(personagem->getSprite(), personagem->getX(), personagem->getY(), 0,
					inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true))
				{
					if (inimigos[i]->getPAtaque() - personagem->getPDefesa() > 0) // se o inimigo tem mais pontos de ataque que o personagem tem defesa
						personagem->atualizarVidas(-(inimigos[i]->getPAtaque() - personagem->getPDefesa())); // diminui a vida com a relação PA Inimigo - PD Personagem
					else
						personagem->atualizarVidas(-1); // senão, diminui a vida po player em 1 ponto
					personagem->setPodeMachucar(false);
					ticksPodeMachucar = gTempo.getTicks();
				}
			}
		if (personagem->getVidas() < 0)
			personagem->atualizarVidas(1);

	}

	if (isP2)
	{
		for (int i = 0; i < nInimigos; i++) {
			if (personagem2->getVivo() && inimigos[i]->getVivo()) // testa se estão vivos
				if (personagem2->getPodeMachucar()) { // se o personagem não está machucado
					if (uniTestarColisaoSpriteComSprite(personagem2->getSprite(), personagem2->getX(), personagem2->getY(), 0,
						inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true))
					{
						if (inimigos[i]->getPAtaque() - personagem2->getPDefesa() > 0) // se o inimigo tem mais pontos de ataque que o personagem tem defesa
							personagem2->atualizarVidas(-(inimigos[i]->getPAtaque() - personagem2->getPDefesa())); // diminui a vida com a relação PA Inimigo - PD Personagem
						else
							personagem2->atualizarVidas(-1); // senão, diminui a vida po player em 1 ponto
						personagem2->setPodeMachucar(false);
						ticksPodeMachucar2 = gTempo.getTicks();
					}
				}
			if (personagem2->getVidas() < 0)
				personagem2->atualizarVidas(1);

		}
	}

	// Personagens individualmente

	for (int i = 0; i < nInimigos; i++) {
		if (inimigos[i]->getVivo() && personagem->getVivo()) {
			if (personagem->getEfeitoAtivo(0)) {
			
				// Knight
				if (personagem->getId() == Knight) {
					if (uniTestarColisaoSpriteComSprite(personagem->getSpriteEfeito(0), personagem->getEfeitoX(0), personagem->getEfeitoY(0), 0,
						inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true) && inimigos[i]->getPodeMachucar()) {
						bool acertou = true;
						if (acertou) {
							inimigos[i]->setDirKnockBack(personagem->getPos());
							personagem->setPontos(personagem->getPontos() + 5);							
						}
						if (personagem->getPAtaque() - inimigos[i]->getPDefesa() > 0) {
							inimigos[i]->atualizarVidas(-(personagem->getPAtaque() - inimigos[i]->getPDefesa()));
							smonstro.tocar();
						}
						else {
							inimigos[i]->atualizarVidas(-1);
							smonstro.tocar();
						}
						inimigos[i]->setPodeMachucar();
						inimigos[i]->setKnockBack();
					}
				}

				// Esqueleto
				if (personagem->getId() == Skeleton) {
					if (uniTestarColisaoSpriteComSprite(personagem->getSpriteEfeito(0), personagem->getEfeitoX(0), personagem->getEfeitoY(0), 0,
						inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true) && inimigos[i]->getPodeMachucar()) {
						if (personagem->getPAtaque() - inimigos[i]->getPDefesa() > 0) {
							inimigos[i]->atualizarVidas(-(personagem->getPAtaque() - inimigos[i]->getPDefesa()));
							smonstro.tocar();
						}
						else {
							inimigos[i]->atualizarVidas(-1);
							smonstro.tocar();
						}
						personagem->setPontos(personagem->getPontos() + 5);
						inimigos[i]->setPodeMachucar();
					}
				}
			}

			// Arqueiro (flechas)
			if (personagem->getId() == Archer) {
				for (int t = 0; t < MAX_FLECHAS; t++) {
					if (uniTestarColisaoSpriteComSprite(personagem->getSpriteEfeito(t), personagem->getEfeitoX(t), personagem->getEfeitoY(t), 0,
						inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true) && inimigos[i]->getPodeMachucar()) {
						if (personagem->getEfeitoAtivo(t))  {
							if (personagem->getPAtaque() - inimigos[i]->getPDefesa() > 0)  {
								inimigos[i]->atualizarVidas(-(personagem->getPAtaque() - inimigos[i]->getPDefesa()));
								smonstro.tocar();
							}
							else  {
								inimigos[i]->atualizarVidas(-1);								
								smonstro.tocar();
							}
							inimigos[i]->setPodeMachucar();
							personagem->setPontos(personagem->getPontos() + 5);
							personagem->setEfeitoAtivo(t, false);

						}
					}
				}
			}
		}

		// Se Player 2

		if (isP2)
		{
			if (inimigos[i]->getVivo() && personagem2->getVivo()) {
				if (personagem2->getEfeitoAtivo(0)) {

					// Knight
					if (personagem2->getId() == Knight) {
						if (uniTestarColisaoSpriteComSprite(personagem2->getSpriteEfeito(0), personagem2->getEfeitoX(0), personagem2->getEfeitoY(0), 0,
							inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true) && inimigos[i]->getPodeMachucar()) {
							bool acertou = true;
							if (acertou) {
								inimigos[i]->setDirKnockBack(personagem2->getPos());
								personagem2->setPontos(personagem2->getPontos() + 5);
							}
							if (personagem2->getPAtaque() - inimigos[i]->getPDefesa() > 0) {
								inimigos[i]->atualizarVidas(-(personagem2->getPAtaque() - inimigos[i]->getPDefesa()));
								smonstro.tocar();
							}
							else {
								inimigos[i]->atualizarVidas(-1);
								smonstro.tocar();
							}
							inimigos[i]->setPodeMachucar();
							inimigos[i]->setKnockBack();
						}
					}

					// Esqueleto
					if (personagem2->getId() == Skeleton) {
						if (uniTestarColisaoSpriteComSprite(personagem2->getSpriteEfeito(0), personagem2->getEfeitoX(0), personagem2->getEfeitoY(0), 0,
							inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true) && inimigos[i]->getPodeMachucar()) {
							if (personagem2->getPAtaque() - inimigos[i]->getPDefesa() > 0) {
								inimigos[i]->atualizarVidas(-(personagem2->getPAtaque() - inimigos[i]->getPDefesa()));
								smonstro.tocar();
							}
							else {
								inimigos[i]->atualizarVidas(-1);
								smonstro.tocar();
							}
							personagem2->setPontos(personagem2->getPontos() + 5);
							inimigos[i]->setPodeMachucar();
						}
					}
				}

				// Arqueiro (flechas)
				if (personagem2->getId() == Archer) {
					for (int t = 0; t < MAX_FLECHAS; t++) {
						if (uniTestarColisaoSpriteComSprite(personagem2->getSpriteEfeito(t), personagem2->getEfeitoX(t), personagem2->getEfeitoY(t), 0,
							inimigos[i]->getSprite(), inimigos[i]->getX(), inimigos[i]->getY(), 0, true) && inimigos[i]->getPodeMachucar()) {
							if (personagem2->getEfeitoAtivo(t)) {
								if (personagem2->getPAtaque() - inimigos[i]->getPDefesa() > 0) {
									inimigos[i]->atualizarVidas(-(personagem2->getPAtaque() - inimigos[i]->getPDefesa()));
									smonstro.tocar();
								}
								else {
									inimigos[i]->atualizarVidas(-1);
									smonstro.tocar();
								}
								inimigos[i]->setPodeMachucar();
								personagem2->setPontos(personagem2->getPontos() + 5);
								personagem2->setEfeitoAtivo(t, false);

							}
						}
					}
				}
			}
		}
	}

	// Tempo pro personagem nao ser machucado
	if (gTempo.getTempoAteTickAtual(ticksPodeMachucar) > 1) {
		personagem->setPodeMachucar(true);
	}
	if (isP2)
	{
		if (gTempo.getTempoAteTickAtual(ticksPodeMachucar2) > 1) {
			personagem2->setPodeMachucar(true);
		}
	}
}

void Sala::save()
{
	Dados dados;
	dados.per = per;
	if (isP2)
	{
		dados.per2 = per2;
	}
	
	//Sala
	dados.sala = salaSave;

	//// nome
	//for (int i = 0; i < personagem->getNome().size(); i++)
	//{
	//	dados.nome[i] = personagem->getNome()[i];
	//}
	//if (isP2)
	//{
	//	for (int i = 0; i < personagem2->getNome().size(); i++)
	//	{
	//		dados.nome2[i] = personagem2->getNome()[i];
	//	}
	//}

	// posição
	dados.xPlayer = personagem->getX();
	dados.yPlayer = personagem->getY();
	dados.dirPer = personagem->getPos();
	dados.posX = posX;
	dados.posY = posY;

	for (int i = 0; i < 4; i++)
	{
		dados.podeAndar[i] = personagem->getPodeAndar(i);
	}
	if (isP2)
	{
		// posição
		dados.xPlayer2 = personagem2->getX();
		dados.yPlayer2 = personagem2->getY();
		dados.dirPer2 = personagem2->getPos();
		dados.posX2 = posX2;
		dados.posY2 = posY2;

		for (int i = 0; i < 4; i++)
		{
			dados.podeAndar2[i] = personagem2->getPodeAndar(i);
		}
	}
	
	// infos
	dados.gold = personagem->getMoedas();
	dados.pontos = personagem->getPontos();
	dados.playerVivo = personagem->getVivo();
	if (isP2)
	{
		dados.gold2 = personagem2->getMoedas();
		dados.pontos2 = personagem2->getPontos();
		dados.playerVivo2 = personagem2->getVivo();
	}
	// pVitais, pAtaque, pDefesa
	dados.hp = personagem->getVidas();
	dados.pAtaque = personagem->getPAtaque();
	dados.pDefesa = personagem->getPDefesa();

	if (isP2)
	{
		dados.hp2 = personagem2->getVidas();
		dados.pAtaque2 = personagem2->getPAtaque();
		dados.pDefesa2 = personagem2->getPDefesa();
	}
	//Inventario
	if (!inventario.estaVazio())
	{
		if (inventario.getNodo(potHp) == NULL)
		{
			dados.hpPot = 0;
		}
		else
		{
		dados.hpPot = inventario.getNodo(potHp)->qtd;
		}


		if (inventario.getNodo(potMp) == NULL)
		{
			dados.mpPot = 0;
		}
		else
		{
			dados.mpPot = inventario.getNodo(potMp)->qtd;
		}

		if (inventario.getNodo(veneno) == NULL)
		{
			dados.poison = 0;
		}
		else
		{
			dados.poison = inventario.getNodo(veneno)->qtd;
		}
	}
	else
	{
		dados.hpPot = 0;
		dados.mpPot = 0;
		dados.poison = 0;

	}

	if (isP2)
	{
		if (!inventario2.estaVazio())
		{
			if (inventario2.getNodo(potHp) == NULL)
			{
				dados.hpPot2 = 0;
			}
			else
			{
				dados.hpPot2 = inventario2.getNodo(potHp)->qtd;
			}


			if (inventario2.getNodo(potMp) == NULL)
			{
				dados.mpPot2 = 0;
			}
			else
			{
				dados.mpPot2 = inventario2.getNodo(potMp)->qtd;
			}

			if (inventario2.getNodo(veneno) == NULL)
			{
				dados.poison2 = 0;
			}
			else
			{
				dados.poison2 = inventario2.getNodo(veneno)->qtd;
			}
		}
		else
		{
			dados.hpPot2 = 0;
			dados.mpPot2 = 0;
			dados.poison2 = 0;

		}
	}
	// Numeros

	dados.nInim = nInimigos;
	dados.nItens = nItens;
	dados.nBau = nBau;
	dados.nCoin = nCoin;


	// Itens 

	for (int i = 0; i < nItens; i++)
	{
		//dados.item[i] = item[i];
		dados.tipoItem[i] = item[i].getTipo();
		dados.pegouItem[i] = item[i].getPegou();
		dados.xItem[i] = item[i].getX();
		dados.yItem[i] = item[i].getY();
	}

	// Inimigos

	for (int i = 0; i < nInimigos; i++)
	{
		//dados.inimigo[i] = inimigos[i];
		dados.xInim[i] = inimigos[i]->getX();
		dados.yInim[i] = inimigos[i]->getY();
		dados.dirInim[i] = inimigos[i]->getDir();
		dados.vivo[i] = inimigos[i]->getVivo();
		dados.atkInim[i] = inimigos[i]->getPAtaque();
		dados.defInim[i] = inimigos[i]->getPDefesa();
		dados.hpInim[i] = inimigos[i]->getVidas();
		dados.iniId[i] = inimigos[i]->getID();
		dados.iniPosX[i] = posXinim[i];
		dados.iniPosY[i] = posYinim[i];
		for (int j = 0; j < 4; j++)
		{
			dados.iniPodeAndar[i][j];
		}
	}

	//Bau

	for (int i = 0; i < nBau; i++)
	{
		dados.xBau[i] = bau[i].xBau;
		dados.yBau[i] = bau[i].yBau;
		dados.abriuBau[i] = bau[i].abriu;
	}

	// COIN

	for (int i = 0; i < nCoin; i++)
	{
		dados.xCoin[i] = coin[i].xGold;
		dados.yCoin[i] = coin[i].yGold;
		dados.pegouCoin[i] = coin[i].goldDisponivel;
	}

	fstream saidaSave;
	if (salaAtual == 1)
	{
		saidaSave.open("save.txt", ios::out | ios::binary | ios::beg);

	}
	else
	{	
		saidaSave.open("save.txt", ios::out| ios::binary | ios::app);
	}
	// | ios::app

	if (!saidaSave.is_open())
	{
		cout << "Erro " << endl;
	}
	else
	{
		saidaSave.write(reinterpret_cast<const char*>(&dados), sizeof(Dados));
	}
		saidaSave.close();
}


void Sala::load(int sala)
{
	//LOAD

	//ifstream entradaSave;
	fstream entradaSave("save.txt", ios::in | ios::binary);


	if (entradaSave.is_open())
	{
		Dados dados;

		int pos = (sala) * sizeof(Dados);
		entradaSave.seekg(pos);

		entradaSave.read(reinterpret_cast<char *>(&dados), sizeof(Dados));

		// PLAYER
		isP2 = dados.isP2;
		per = dados.per;
		if (isP2)
		{
			per2 = dados.per2;
		}
		
		// Numeros
		nInimigos = dados.nInim;
		nItens = dados.nItens;
		nBau = dados.nBau;
		nCoin = dados.nCoin;

		inicializar(sala + 1);

		//Sala

		salaSave = dados.sala;

		string nome, nome2;
		for (int i = 0; i < 15; i++)
		{
			if (dados.nome[i] > 0)
			{
				nome += dados.nome[i];
			}
			if (isP2)
			{
				if (dados.nome2[i] > 0)
				{
					nome2 += dados.nome2[i];
				}
			}
		}
		/*personagem->nomearPersonagem(nome);
		if (isP2)
		{
			personagem2->nomearPersonagem(nome2);
		}*/

		// posição
		personagem->setX(dados.xPlayer);
		personagem->setY(dados.yPlayer);
		personagem->setPos(dados.dirPer);
		posX = dados.posX;
		posY = dados.posY;
		personagem->setEstado(dados.playerVivo);
		for (int i = 0; i < 4; i++)
		{
			personagem->setPodeAndar(i, dados.podeAndar[i]);
		}

		if (isP2)
		{
			personagem2->setX(dados.xPlayer2);
			personagem2->setY(dados.yPlayer2);
			personagem2->setPos(dados.dirPer2);
			posX2 = dados.posX2;
			posY2 = dados.posY2;
			personagem2->setEstado(dados.playerVivo2);
			for (int i = 0; i < 4; i++)
			{
				personagem2->setPodeAndar(i, dados.podeAndar2[i]);
			}
		}
		// infos
		personagem->setMoedas(dados.gold);
		personagem->setPontos(dados.pontos);
		if (isP2)
		{
			personagem2->setMoedas(dados.gold2);
			personagem2->setPontos(dados.pontos2);
		}
		// pVitais, pAtaque, pDefesa
		personagem->setVidas(dados.hp);
		personagem->setpAtaque(dados.pAtaque);
		personagem->setPDefesa(dados.pDefesa);
		personagem->setVivo();

		if (isP2)
		{
			personagem2->setVidas(dados.hp2);
			personagem2->setpAtaque(dados.pAtaque2);
			personagem2->setPDefesa(dados.pDefesa2);
			personagem2->setVivo();
		}

		// Inventario
		
		for (int i = 0; i < dados.hpPot; i++)
		{
			inventario.add(potHp);
		}
		for (int i = 0; i < dados.mpPot; i++)
		{
			inventario.add(potMp);
		}
		for (int i = 0; i < dados.poison; i++)
		{
			inventario.add(veneno);
		}

		if (isP2)
		{
			for (int i = 0; i < dados.hpPot2; i++)
			{
				inventario2.add(potHp);
			}
			for (int i = 0; i < dados.mpPot2; i++)
			{
				inventario2.add(potMp);
			}
			for (int i = 0; i < dados.poison2; i++)
			{
				inventario2.add(veneno);
			}
		}

		for (int i = 0; i < nItens; i++)
		{
			//item[i] = dados.item[i];
			item[i].setTipo(dados.tipoItem[i]);
			if (item[i].getTipo() == potHp)
			{
				item[i].inicializar("potHP", "sprites/itens/potHP.png", 1, 1);
				item[i].getSprite().setSpriteSheet("potHP");

			}
			else if (item[i].getTipo() == potMp)
			{
				item[i].inicializar("potMP", "sprites/itens/potMP.png", 1, 1);
				item[i].getSprite().setSpriteSheet("potMP");
			}
			else if (item[i].getTipo() == veneno)
			{
				item[i].inicializar("veneno", "sprites/itens/poison.png", 1, 1);
				item[i].getSprite().setSpriteSheet("veneno");
			}
			item[i].setItem(dados.pegouItem[i]);
			item[i].setX(dados.xItem[i]);
			item[i].setY(dados.yItem[i]);
		}


		for (int i = 0; i < nInimigos; i++)
		{

			if (dados.iniId[i] == grue)
			{
				inimigos[i] = new IniGrue;
			}
			else if (dados.iniId[i] == aranha)
			{
				inimigos[i] = new IniAranha;
			}
			else if (dados.iniId[i] == morcego)
			{
				inimigos[i] = new IniBat;
			}

			inimigos[i]->inicializar();

			inimigos[i]->setX(dados.xInim[i]);
			inimigos[i]->setY(dados.yInim[i]);
			inimigos[i]->setDir(dados.dirInim[i]);
			inimigos[i]->setVivo(dados.vivo[i]);
			inimigos[i]->setpAtaque(dados.atkInim[i]);
			inimigos[i]->setPDefesa(dados.defInim[i]);
			inimigos[i]->setVidas(dados.hpInim[i]);
			posXinim[i] = dados.iniPosX[i];
			posYinim[i] = dados.iniPosY[i];
			for (int j = 0; j < 4; j++)
			{
				inimigos[i]->setPodeAndar(j, dados.iniPodeAndar[i][j]);
			}
		}

		//Bau
		for (int i = 0; i < nBau; i++)
		{
			bau[i].xBau = dados.xBau[i];
			bau[i].yBau = dados.yBau[i];
			bau[i].abriu = dados.abriuBau[i];

			bau[i].sprBau.setSpriteSheet("bau");
		}

		//Coin

		for (int i = 0; i < nCoin; i++)
		{
			coin[i].xGold = dados.xCoin[i];
			coin[i].yGold = dados.yCoin[i];
			coin[i].goldDisponivel = dados.pegouCoin[i];

			coin[i].sprGold.setSpriteSheet("gold");
			coin[i].sprGold.setVelocidadeAnimacao(7);
		}

	}
	entradaSave.close();
	
}
