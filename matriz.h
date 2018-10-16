#ifndef MATRIZ_H
#define MATRIZ_H

#define DIMENSOES 4
#define PI 3.14159265
#define _USE_MATH_DEFINES

#include <math.h>
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
    Matriz rotate(double angle, Ponto rotation_center);
    Matriz scale(Ponto scale, Ponto center);

    Matriz multiplication(Matriz m);
    Matriz multiplication(double c);
    
    Ponto exec_transform(Ponto p);
    
    void transpose();
    Matriz get_rotation_matrix(double angle, int eixo);
    double calc_angulo(Ponto a, Ponto b);

};

#endif //MATRIZ_H
	 	  	 	    	 	    		    	    	  	 	
