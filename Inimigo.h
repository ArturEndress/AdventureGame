#include <iostream>
#include"libUnicornio.h"
#include "Personagem.h"
#pragma once


enum idInim { morcego, grue, aranha};
enum dirInim {Left, Right, Up, Down};


class Inimigo
	{
	protected:
		Sprite sprIni;

		Efeito efeito;

		Uint64 tick, tKnB, tickEfeito;
	
		int qtdIni, pDefesa, pVitais, pAtaque, dir, dirKnb, iniId;
		float x, y;
		bool vivo, podeAndar[4], podeMachucar, knb, efeitoAtivo;

	public:
		Inimigo();
		~Inimigo();

		//*** Virtuais ***

		// Movimentação
		virtual void parado() = 0;
		virtual void andarEsq() = 0;
		virtual void andarDir() = 0;
		virtual void andarCima() = 0;
		virtual void andarBaixo() = 0;

		virtual void desenhar()=0;
		virtual void inicializar() = 0;

		// Sprite
		Sprite getSprite() { return sprIni; };
				
		bool getPodeAndar() { return podeAndar; };
		void setPodeAndar(int dir, bool podeAndar) { this->podeAndar[dir] = podeAndar; };
		void setDir(int dir) { this->dir = dir; };
		int getDir() { return dir; };

		void setEfeito(bool efeito);
		
		// * Vida *
		inline int getVidas() { return pVitais; }
		bool getVivo() { return vivo; }
		void setVivo(bool vivo) { this->vivo = vivo; }
		void setMorto() { vivo = false; }
		
		void atualizarVidas(int pVitais);
		void setVidas(int vidas) { pVitais = vidas; }
		void setPodeMachucar();
		bool getPodeMachucar() { return podeMachucar; }
		void atualizarTick(Uint64 tick) { this->tick = tick; }

		// * Ataque e Defesa *
		int getPAtaque() { return pAtaque; };
		void setpAtaque(int pAtaque) { this->pAtaque = pAtaque; }
		int getPDefesa() { return pDefesa; };
		void setPDefesa(int pDefesa) { this->pDefesa = pDefesa; }
		
		// Posição
		float getX() { return x; }
		float getY() { return y; }
		void setX(float x) { this->x = x; }
		void setY(float y) { this->y = y; }
		void knockBack();
		void setKnockBack();
		void setDirKnockBack(int dirKnb) { this->dirKnb = dirKnb; }
		void ativouKnockBack(bool knb) { this->knb = knb; }
		bool getKnockBack() { return knb; }
		int getDirKnB() { return dirKnb; }

		//ID TIPO
		int getID() { return iniId; }

		
		
	};

