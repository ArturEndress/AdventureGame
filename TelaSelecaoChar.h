#pragma once
#include "Tela.h"
#include "TelaJogo.h"

// Personagens
#include "PKnight.h"
#include "PSkeleton.h"
#include "PArcher.h"
#include <fstream>
#include <vector>

class TelaSelecaoChar :
	public Tela
{
public:
	TelaSelecaoChar();
	~TelaSelecaoChar();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar();
	void finalizar();

	void setIsP2() { isP2 = true; }
	void setChoseP1() { choseP1 = true; }
	void setPer(int i) { per = i; }

protected:

	stack <Tela *>* telas;
	Sprite fundoSelChar;

	// Personagens
	vector<Personagem*> personagens;
	bool setouPersonagem = false, isP2, choseP1;


	Texto texto;

	int per, per2, selecao, selecaoAtivo;
	
};

