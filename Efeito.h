#pragma once
#include "libUnicornio.h"

enum direcao {n,o,s,l};
class Efeito
{
	int rot, dir;
	float x, y;
	bool ativo, pegarDir;
public:
	Efeito();
	~Efeito();

	void inicializar(string nome, string path, int nAnim, int nFrames);
	float getX() { return x; };
	float getY() { return y; };
	int getRot() { return rot; };
	bool getAtivo() { return ativo; };
	bool getPegarDir() { return pegarDir; };
	Sprite getSprite() { return sprite; };
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	void setRot(int rot){ this->rot = rot; };
	void setAtivo(bool ativo) { this->ativo = ativo; };
	void setDir(int dir) { this->dir = dir; };
	void setPegarDir(bool pegarDir) { this->pegarDir = pegarDir; };
	void desenhar();
	void movimentar();
	void atualizarAnim();


	Sprite sprite;
};

