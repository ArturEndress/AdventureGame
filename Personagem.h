#include"libUnicornio.h"
#include "Efeito.h"
#pragma once
using namespace std;

#define qtdPer 3 
enum idPer { Knight, Skeleton, Archer };
enum dir { esq, dir, cima, baixo };
enum Pos { pcima, pesq, pbaixo, pdir };

class Personagem
{
protected:

	//* Atributos *
	//string nome;
	int idPersonagem, pos;

	int pAtaque, pDefesa, pVitais, moedas, pontos;
	float x = 400, y = 400;
	bool vivo, podeAndar[4], podeMachucar, isP2;

	// Efeitos
	Efeito *efeito;

	Som sflecha, sExplosao;

	//CONTROLES
	Joystick joystick1, joystick2;

public:
	Personagem();
	~Personagem();

	//**** Métodos **
	//** Gets e Sets ***
	inline int getId() { return idPersonagem; };

	bool getPodeMachucar() { return podeMachucar; };
	void setPodeMachucar(bool podeMachucar) { this->podeMachucar = podeMachucar; };

	void setIsP2() { isP2 = true; }

	// * Vida *
	inline int getVidas() { return pVitais; };
	bool getVivo() { return vivo; };
	void atualizarVidas(int pVitais);
	void setVidas(int vidas) { pVitais = vidas; }
	void setVivo() { vivo = true; }
	void setEstado(bool estado) { vivo = estado; }


	// * Ataque e Defesa *
	int getPAtaque() { return pAtaque; };
	void setpAtaque(int pAtaque) { this->pAtaque = pAtaque; };
	int getPDefesa() { return pDefesa; };
	void setPDefesa(int pDefesa) { this->pDefesa = pDefesa; };

	// * Moedas *
	int getMoedas() { return moedas; };
	void setMoedas(int moedas) { if(moedas<14001) this->moedas = moedas; };

	// * Pontuação *
	int getPontos() { return pontos; };
	void setPontos(int pontos) { this->pontos = pontos; };

	// * Posição *
	float getX() { return x; };
	void setX(float newX) { x = newX; };
	float getY() { return y; };
	void setY(float newY) { y = newY; };
	void setPodeAndar(int dir, bool andar) { podeAndar[dir] = andar; };
	bool getPodeAndar(int dir) { return podeAndar[dir]; };
	int getPos() { return pos; };
	void setPos(int pos) { this->pos = pos; }

	void carregarAudio();

	//*** Abstratos ***
	void andar();

	//*** Virtuais ***
	virtual void inicializar() = 0; // carrega e seta sprites
	virtual void desenhar() = 0;
	virtual Sprite getSprite() = 0;

	virtual void parado() = 0;
	virtual void andarEsq() = 0;
	virtual void andarDir() = 0;
	virtual void andarCima() = 0;
	virtual void andarBaixo() = 0;
	virtual void setMorto() = 0;

	virtual void atacar() = 0;

	// Efeito
	Sprite getSpriteEfeito(int i) { return efeito[i].getSprite(); };
	float getEfeitoX(int i) { return efeito[i].getX(); };
	float getEfeitoY(int i) { return efeito[i].getY(); };
	bool getEfeitoAtivo(int i) { return efeito[i].getAtivo(); };
	void setEfeitoAtivo(int i, bool ativo) { efeito[i].setAtivo(ativo); };

};

