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
	std::list<Ponto> pontos_scn;
	Ponto center = Ponto(0, 0);
	string nome;
	double brush_size = 1;
    int id = 0;
    bool filled = false;

public:
	Poligono(string nome);
	Poligono(string nome, int id, bool filled, std::list<Ponto> pontos);
	Poligono(string nome, std::list<Ponto> pontos);


	void add_ponto(Ponto p);
	void add_ponto(double x, double y);
	void add_ponto(double x, double y, double z);
	void set_brush_size(double brush);
	//void set_color(double r, double g, double b);

    std::list<Ponto> draw(double scale);
    std::list<Ponto> get_pontos();
    double get_brush_size();
	int get_tipo();
	string get_nome();
    void set_nome(string nome);
	int get_size();
    int get_id() const;
    void set_id(int new_id);
    Ponto get_center();
    void exec_transform(Matriz transform);
    void exec_update_scn(Matriz transform);
    bool operator==(const Poligono& a);
    void set_filled(bool fill);
    bool get_filled();

};

#endif //POLIGONO_H
