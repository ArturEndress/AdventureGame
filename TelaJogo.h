#pragma once
#include "Tela.h"
#include "Sala.h"
#include "TelaFim.h"

class TelaJogo :
	public Tela
{
public:
	TelaJogo();
	~TelaJogo();

	void inicializar(stack <Tela *>* telas);
	void atualizar();
	void desenhar() {};
	void finalizar() {};

	void carregarAudios();
	void setPersonagem(int p) { sala.setPersonagem(p); }	

	void setLoaded() { loaded = true ; }


protected:
	stack <Tela *>* telas;
	bool loaded, getSave, saving;
	bool versize;
	int size, salaAtual;
	
};

