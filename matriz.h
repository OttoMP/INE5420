#ifndef MATRIZ_H
#define MATRIZ_H

#define DIMENSOES 4
#define PI 3.14159265
#define _USE_MATH_DEFINES

#include <math.h>
#include "ponto.h"

class Matriz{

public:
	double matriz[4][4] = {};

	Matriz();

    Matriz translate(Ponto vector);
    Matriz rotate(double angle, Ponto rotation_center);
    Matriz scale(Ponto scale, Ponto center);

    Matriz multiplication(Matriz m);
    
    Ponto exec_transform(Ponto p);

};

#endif //MATRIZ_H
