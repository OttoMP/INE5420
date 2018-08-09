#ifndef POLIGONO_H
#define POLIGONO_H

#include <list>
#include <string>
using std::string;

#include "ponto.h"

class Poligono{

private:
	std::list<Ponto> pontos;
	string nome;
	double brush_size = 1;

public:
	Poligono(string nome);
	Poligono(string nome, std::list<Ponto> pontos);
	
	
	void addPonto(Ponto p);
	void setBrushSize(double brush);
	//void setColor(double r, double g, double b);

    std::list<Ponto> draw();
    double getBrushSize();
	int getTipo();
	string getNome();
	int getSize();

};

#endif //POLIGONO_H