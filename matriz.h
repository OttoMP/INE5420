#ifndef MATRIZ_H
#define MATRIZ_H

#define DIMENSOES 4
#define PI 3.14159265
#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include "ponto.h"

class Matriz{

public:
	double matriz[DIMENSOES][DIMENSOES] = {};

	Matriz();
	
    void set_matriz(double matriz[DIMENSOES][DIMENSOES]);
    void set_matriz_delta(double delta);
    
    double get_pos(int x, int y);
    void get_matriz(double matriz[DIMENSOES][DIMENSOES]);

    Matriz translate(Ponto vector);
    Matriz rotate(double angle, Ponto rotation_center, Ponto eixo);
    Matriz scale(Ponto scale, Ponto center);

    Matriz multiplication(Matriz m);
    Matriz multiplication(double c);
    
    Ponto exec_transform(Ponto p);
    
    void transpose();
    Matriz get_rotation_matriz(double angle, int eixo);
    double calc_angulo(double x1, double y1, double x2, double y2);

};

#endif //MATRIZ_H
	 	  	 	    	 	    		    	    	  	 	
