#ifndef WINDOW_H
#define WINDOW_H

#include "ponto.h"
#include "matriz.h"

class Window{

private:
	Ponto wc = Ponto(0,0);
	Ponto v = Ponto(0,0);
	Ponto u = Ponto(0,0);
	

public:
	Window(Ponto wc, Ponto v, Ponto u);

	Ponto get_v();
	
	Ponto get_u();
	
	Ponto get_wc();

  void translate(Ponto p);
  void rotate(double angle);
  void scale(double factor);	
};

#endif //WINDOW_H