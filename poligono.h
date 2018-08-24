#ifndef POLIGONO_H
#define POLIGONO_H

#include <list>
#include <string>
using std::string;

#include "ponto.h"
#include "matriz.h"

class Poligono{

private:
	std::list<Ponto> pontos;
	Ponto center = Ponto(0, 0);
	string nome;
	double brush_size = 1;
    int id = 0;
    bool filled = false;

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
    int get_id();
    void set_id(int new_id);
    Ponto get_center();
    void exec_transform(Matriz transform);
    void set_filled(bool fill);
    bool get_filled();

};

#endif //POLIGONO_H

