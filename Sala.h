#pragma once

#include "libUnicornio.h"
#include "Inventario.h"
#include <ctime>

#include "PKnight.h"	// Personagens
#include "PSkeleton.h"
#include "PArcher.h"

#include "IniAranha.h"	// Inimigos
#include "IniBat.h"
#include "IniGrue.h"

struct Dados
{
	// Player 
	char nome[15], nome2[15];
	float xPlayer, yPlayer, xPlayer2, yPlayer2, xInim[10], yInim[10], xBau[2], yBau[2], xCoin[2], yCoin[3], xItem[5], yItem[5];
	int hp, hp2, gold, gold2, pontos, pontos2, pAtaque, pAtaque2, pDefesa, pDefesa2, dirPer, dirPer2, dirInim[10], atkInim[10], defInim[10], hpInim[10], nInim, nItens, nBau, nCoin, per, per2, iniId[10], 
		posX, posY, posX2, posY2, iniPosX[10], iniPosY[10], tipoItem[5], hpPot, mpPot, poison, hpPot2, mpPot2, poison2, sala;
	bool vivo[10], abriuBau[2], pegouCoin[3], podeAndar[4], podeAndar2[4], iniPodeAndar[10][4], pegouItem[5], isP2, playerVivo, playerVivo2;
	
};

struct Bau
{
	// Baú de Tesouro
	Sprite sprBau;
	float xBau = 0, yBau = 0;
	bool abriu = false;
};

struct Gold
{
	// Moedas no mapa
	Sprite sprGold;
	int xGold = 0, yGold = 0;
	bool goldDisponivel = true;
};

class Sala
{
protected:
#pragma region Atributos
	// Sala
	Sprite * tiles = 0;
	int nColunas = 0, nLinhas = 0, **mapaSala, **mapaObjetos, salaAtual, salaSave;
	bool next, previous, fimJogo;

	// Personagens
	Personagem *personagem, *personagem2;
	Texto qtdVidas, qtdMoedas, qtdPontos;
	void escreverInfos();
	int posX, posX2, posY, posY2, per, per2;
	Uint64 ticks, ticksPodeMachucar, ticksPodeMachucar2, tickBuff;

	Efeito buff;

	Sprite spriteBuff;
	bool desenharBuff, desenharBuff2;

	// Inimigos
	vector<Inimigo*>inimigos;
	string *nomeInim, *iniPath, *sprInim;
	int sorteioInim, linhaInim, colunaInim, *dirInim, *posXinim, *posYinim, inimCarreg, nInimigos, *inimHp, *inimDef;
	bool carregouDir;

	// Gold
	Gold *coin;
	int nCoin;

	// Baú de Tesouro
	Bau *bau;
	int nBau;

	// Inventário
	Inventario inventario, inventario2;
	string *nomeItens, *itensPath;
	Item *item;
	int sorteioItens, linhaItem, colunaItem, itensCarreg, *tipoItem, nItens;
	bool exibirInventario, exibirInventario2;
	Sprite canvasI;
	Texto txt;

	// Sons
	Som scoin, smonstro, spot, sbuff, sdebuff;

	//Loja
	int selecaoLoja;
	bool loja, p2EstaNaLoja, voltarLoja;
	Sprite fundoLoja;
	BotaoSprite bVoltar;

	// Pause
	int selecaoPause;
	bool pause, sair, p2Pausou;
	Sprite fundoPause;
	BotaoSprite bContinuar, bSair, bLoja;

	//Load Save
	bool loaded, saving;

	// 2 Players
	bool isP2;

#pragma endregion

public:

#pragma region Métodos
	Sala();
	~Sala();
	
	// Sala
	void inicializar(int f);
	void atualizar();
	void carregarSala(int s);
	
	void abrirLoja();
	void pausarJogo();
	void carregarAssets();
	bool getSair() { return sair; }
	
	bool getNext() { return next; }
	bool getPrevious() { return previous; }
	void setNextPrevious() { next = previous = false; }

	bool getFimJogo() { return fimJogo; }
	void setLoaded() { loaded = true; }
	
	// Personagem
	void inicializarPlayer();
	void movimentarPlayer();

	int getPersonagem() { return per; }
	void setPersonagem(int per) { this->per = per; };
	//	void setNome(string nome) { personagem->nomearPersonagem(nome); };
	
	bool getPlayerVivo() { return personagem->getVivo(); };
	bool getPlayer2Vivo() { return personagem2->getVivo(); };
	void setEstado(bool vivo) { personagem->setEstado(vivo); }
	void setEstado2(bool vivo) { personagem2->setEstado(vivo); }
	int getVida() { return personagem->getVidas(); }
	void setVida(int v, int a) { personagem->atualizarVidas(-a + v); }
	int getVida2() { return personagem2->getVidas(); }
	void setVida2(int v, int a) { personagem2->atualizarVidas(-a + v); }
	
	int getMoedas() { return personagem->getMoedas(); }
	void setMoedas(int m) { personagem->setMoedas(m); }	
	int getPontos() { return personagem->getPontos(); };
	void setPontos(int p) { personagem->setPontos(p); };

	int getMoedas2() { return personagem2->getMoedas(); }
	void setMoedas2(int m) { personagem2->setMoedas(m); }
	int getPontos2() { return personagem2->getPontos(); };
	void setPontos2(int p) { personagem2->setPontos(p); };
		
	float getX() { return personagem->getX(); }
	float getY() { return personagem->getY(); }
	void setX(float x) { personagem->setX(x); }
	void setY(float y) { personagem->setY(y); }
	void setPosNext();
	void setPosPrev();

	// Player 2
	void setIsP2() { isP2 = true; }
	bool getIsP2() { return isP2; }
	void setP2(bool isP2) { this->isP2 = isP2; }

	void inicializarPlayer2();
	void movimentarPlayer2();
	void setPersonagem2(int per) { per2 = per; };


	// Inimigos
	void carregarInim(); 
	void movimentarInimigo();

	// Inventário
	void carregarMoedas();
	void carregarBau();
	void carregarInventario(); 
	void carregarItens();
	void desenharInventario();
	void utilizarItens();
	NodoItem *getIni() { return inventario.getIni(); }
	NodoItem *getFim() { return inventario.getFim(); }
	void setIni(NodoItem* ini) { inventario.setIni(ini); }
	void setFim(NodoItem* fim) { inventario.setFim(fim); }
	NodoItem *getIni2() { return inventario2.getIni(); }
	NodoItem *getFim2() { return inventario2.getFim(); }
	void setIni2(NodoItem* ini) { inventario2.setIni(ini); }
	void setFim2(NodoItem* fim) { inventario2.setFim(fim); }


	// Colisões
	void testarColisao();

	// Save
	void save();
	void load(int sala);
	int getSalaAtual() { return salaAtual; }
	void setSalaAtual(int i) { salaAtual = i; }
	void setSalaSave(int i) { salaSave = i; }
	int getSalaSave() { return salaSave; }
	bool getSaving() { return saving; }
	void setSaving(bool saving) { this->saving = saving; }
#pragma endregion	
};

