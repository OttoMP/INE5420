#ifndef OBJETO_H
#define OBJETO_H

#include <list>
#include <string>
using std::string;

#include "ponto.h"
#include "matriz.h"

class Objeto : public Objeto{

protected:
	std::list<Ponto> pontos;
	std::list<Ponto> pontos_scn;
	Ponto center = Ponto(0, 0);
	string nome;
	double brush_size = 1;
    int id = 0;

public:

	void set_brush_size(double brush);
	//void set_color(double r, double g, double b);
	void set_pontos(std::list<Ponto> pontos);
	void set_nome(string nome);
	void set_id(int new_id);


    std::list<Ponto> get_pontos();
    double get_brush_size();
	int get_tipo();
	string get_nome();
	int get_size();
    int get_id() const;
    Ponto get_center();

    void exec_transform(Matriz transform);
    void exec_update_scn(Matriz transform);

    bool operator==(const Objeto& a);
};

#endif //OBJETO_H
