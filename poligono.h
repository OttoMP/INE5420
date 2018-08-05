#ifndef POLIGONO_H
#define POLIGONO_H

#include <string>
using std::string;

#include "ponto.h"
#include "lista_enc.hpp" 

class Poligono{

private:
	ListaEnc<Ponto> pontos;
	string nome;
	int tipo;

public:
	Poligono(string nome);
	void addPonto(Ponto p);

	ListaEnc<Reta> draw();

	int getTipo();
	int getSize();

}

#endif //POLIGONO_H