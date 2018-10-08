#ifndef POLIGONO_H
#define POLIGONO_H

#include "ponto.h"
#include "objeto.h"
#include <list>
#include <string>

class Poligono : public Objeto{

public:
	Poligono(Objeto o);
	Poligono(string nome);
	Poligono(string nome, int id, bool filled, std::list<Ponto> pontos);
	Poligono(string nome, std::list<Ponto> pontos);



	
    std::list<Ponto> draw(double scale);



	Objeto to_objeto();

};

#endif //POLIGONO_H
	 	  	 	    	 	    		    	    	  	 	
