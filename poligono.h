#ifndef POLIGONO_H
#define POLIGONO_H

#include "ponto.h"
#include "objeto.h"
#include <list>
#include <string>

class Poligono : public Objeto{

protected:
    bool filled = false;

public:
	Poligono(Objeto o);
	Poligono(string nome);
	Poligono(string nome, int id, bool filled, std::list<Ponto> pontos);
	Poligono(string nome, std::list<Ponto> pontos);


	void add_ponto(Ponto p);
	void add_ponto(double x, double y);
	void add_ponto(double x, double y, double z);
	
  std::list<Ponto> draw(double scale);

  void set_filled(bool fill);
  bool get_filled();

	Objeto to_objeto();

};

#endif //POLIGONO_H
