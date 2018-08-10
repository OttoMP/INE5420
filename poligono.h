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
	
	
	void add_ponto(Ponto p);
	void add_ponto(int coordx, int coordy);
	void add_ponto(int coordx, int coordy, int coordz);
	void set_brush_size(double brush);
	//void set_color(double r, double g, double b);

    std::list<Ponto> draw();
    double get_brush_size();
	int get_tipo();
	string get_nome();
    void set_nome(string nome);
	int get_size();

};

#endif //POLIGONO_H	 	  	 	    	 	    		    	    	  	 	
