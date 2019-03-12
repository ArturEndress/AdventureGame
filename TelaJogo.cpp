#include "TelaJogo.h"

TelaJogo::TelaJogo()
{
	loaded = false;
	
	getSave = false;
	saving = false;
}

TelaJogo::~TelaJogo()
{
}

void TelaJogo::inicializar(stack<Tela*>* telas)
{
	this->telas = telas;
		
	// Assets
	carregarAudios();

	// Musica
	gMusica.tocar("musica", true);
		
}

void TelaJogo::atualizar()
{
	desenhar();


	// * Sala *
	salas.top()->atualizar();


	if (!getSave)
	{
		saving = salas.top()->getSaving();

		if (saving)
		{
			getSave = true;
		}
	}
	
	if (saving)
	{
		//save();
		salaAtual = salas.top()->getSalaAtual();
		while (!salas.empty())
		{
			salas2.push(salas.top());
			salas.pop();
		}
		while (!salas2.empty())
		{
			salas2.top()->setSalaSave(salaAtual);
			salas2.top()->save();
			salas.push(salas2.top());
			salas2.pop();
		}
		while (!salas.empty())
		{
			salas2.push(salas.top());
			salas.pop();
		}
		for (int i = 0; i < salaAtual; i++)
		{
			salas.push(salas2.top());
			salas2.pop();
		}

		salas.top()->setSaving(false);
		getSave = false;
	}
	

	if (salas.top()->getPrevious())
	{
		salas2.push(salas.top());
		salas.pop();
		salas.top()->setNextPrevious();
		salas.top()->setPosPrev();
		salas.top()->setMoedas(salas2.top()->getMoedas());
		salas.top()->setPontos(salas2.top()->getPontos());
		salas.top()->setVida(salas2.top()->getVida(), salas.top()->getVida());
		salas.top()->setIni(salas2.top()->getIni());
		salas.top()->setFim(salas2.top()->getFim());
		salas.top()->setEstado(salas2.top()->getPlayerVivo());
		salas.top()->setP2(salas2.top()->getIsP2());
		if (salas.top()->getIsP2())
		{
			salas.top()->setMoedas2(salas2.top()->getMoedas2());
			salas.top()->setPontos2(salas2.top()->getPontos2());
			salas.top()->setVida2(salas2.top()->getVida2(), salas.top()->getVida2());
			salas.top()->setIni2(salas2.top()->getIni2());
			salas.top()->setFim2(salas2.top()->getFim2());
			salas.top()->setEstado2(salas2.top()->getPlayer2Vivo());
		}
	}
	else if (salas.top()->getNext())
	{
		salas2.top()->setNextPrevious();
		salas2.top()->setPosNext();
		salas2.top()->setMoedas(salas.top()->getMoedas());
		salas2.top()->setPontos(salas.top()->getPontos());
		salas2.top()->setVida(salas.top()->getVida(), salas2.top()->getVida());
		salas2.top()->setIni(salas.top()->getIni());
		salas2.top()->setFim(salas.top()->getFim());
		salas2.top()->setP2(salas.top()->getIsP2());

		if (salas2.top()->getIsP2())
		{
			salas2.top()->setMoedas2(salas.top()->getMoedas2());
			salas2.top()->setPontos2(salas.top()->getPontos2());
			salas2.top()->setVida2(salas.top()->getVida2(), salas2.top()->getVida2());
			salas2.top()->setIni2(salas.top()->getIni2());
			salas2.top()->setFim2(salas.top()->getFim2());
		}

		salas.push(salas2.top());
		salas2.pop();
	}
	
	
	// * MORTE * //
	if (salas.top()->getIsP2())
	{
		if (!salas.top()->getPlayer2Vivo())
		{
			if (!salas.top()->getPlayerVivo())
			{

				TelaFim *telaFim = new TelaFim;
				telas->pop();
				telaFim->inicializar(telas);
				telas->push(telaFim);
			}
		}
	} 
	else
	{
		if (!salas.top()->getPlayerVivo()) {

			TelaFim *telaFim = new TelaFim;
			telas->pop();
			telaFim->inicializar(telas);
			telas->push(telaFim);
		}
	}

	
	
	if (salas.top()->getSair() == true) {
		telas->pop();
	}
	// FIM DE JOGO

	if (salas.top()->getFimJogo())
	{

		TelaFim *telaFim = new TelaFim;
		telas->pop();
		telaFim->inicializar(telas);
		telas->push(telaFim);

	}
}



void TelaJogo::carregarAudios()
{
	// Música
	if (!gRecursos.carregouMusica("musica"))	{
		gRecursos.carregarMusica("musica", "sons/Winds Of Stories.ogg");
	}
}


	

