#ifndef CURVA2D_H
#define CURVA2D_H

#include "window.h"
#include "objeto.h"
#include <list>
#include <string>
#include "ponto.h"

class Curva2D : public Objeto{

public:
	Curva2D(int id, string nome);
    Curva2D(string nome, std::list<Ponto> pontos);
	Curva2D(Objeto o);

	int add_curva(Ponto p1, Ponto p4, Ponto r1, Ponto r4);
    void set_pontos(std::list<Ponto> pontos);
    std::list<Ponto> draw(double scale, double wmin_x, double wmax_x, double wmin_y, double wmax_y);

	int get_num_curvas();

	Objeto to_objeto();

};

#endif //CURVA2D_H

