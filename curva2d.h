#ifndef CURVA2D_H
#define CURVA2D_H

#include "window.h"
#define PRECISION 10; // nivel de detalhamento da curva (quantidade inicial de pontos para uma curva, aumenta com o zoom)

class Curva2D : public Objeto{

private:
	std::list<Ponto> pontos;
	std::list<Ponto> pontos_scn;
	Ponto center = Ponto(0, 0);
	string nome;
	double brush_size = 1;
    int id = 0;

public:
	Curva2D(int id, string nome);

	void add_curva(Ponto p1, Ponto p4, Ponto r1, Ponto r4);

    std::list<Ponto> draw(double scale);

	int get_num_curvas();

};

#endif //CURVA2D_H
