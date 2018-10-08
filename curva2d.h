#ifndef CURVA2D_H
#define CURVA2D_H

#define XBORDER 0.9
#define YBORDER 0.9

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
    std::list<Ponto> draw(double scale);
    std::list<Ponto> draw_spline(double scale, Matriz cart_to_scn);

	int get_num_curvas();

	Objeto to_objeto();
	
	
	


private:
    std::list<Ponto> draw_curve_fwd_diff( int n, 
                      double x, double Dx, double D2x, double D3x, double D4x,
                      double y, double Dy, double D2y, double D3y, double D4y,
                      double z, double Dz, double D2z, double D3z, double D4z,
                      Matriz cart_to_scn);
    void get_coef(double matriz[4][4], double p1, double p2, double p3, double p4, double* result);
    void get_coef2(double matriz[4][4], double p1, double p2, double p3, double p4, double* result);
    bool is_clippable(Ponto p);
};

#endif //CURVA2D_H

	 	  	 	    	 	    		    	    	  	 	
