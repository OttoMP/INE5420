#include "poligono.h"

Poligono::Poligono(Objeto o)
{
    this->id = o.get_id();
    this->nome = o.get_nome();
    this->pontos = o.get_pontos();
    this->center = o.get_center();
    this->brush_size = o.get_brush_size();
    this->pontos_scn = o.get_pontos_scn();
    this->tipo = 1;
}

Poligono::Poligono(string nome)
{
	this->nome = nome;
    this->tipo = 1;
}

Poligono::Poligono(string nome, int id, bool filled, std::list<Ponto> pontos)
{
	this->nome = nome;
    this->id = id;
    this->filled = filled;
    this->pontos = pontos;
    this->tipo = 1;
}

Poligono::Poligono(string nome, std::list<Ponto> pontos)
{
    this->nome = nome;
    this->pontos = pontos;
    this->tipo = 1;
}

void Poligono::add_ponto(Ponto p)
{
    if (this->get_size() == 0)
    {
        this->center = p;
    }
    else
    {
        this->center =
            Ponto((this->center.get_x()*this->get_size() + p.get_x())/(this->get_size()+1),
                  (this->center.get_y()*this->get_size() + p.get_y())/(this->get_size()+1));
    }
    this->pontos.push_back(p);
    this->pontos_scn.push_back(Ponto(0,0));
}

void Poligono::add_ponto(double x, double y)
{
	Ponto p(x,y);
  this->add_ponto(p);
}

void Poligono::add_ponto(double x, double y, double z)
{
	Ponto p(x,y,z);
  this->add_ponto(p);
}

std::list<Ponto> Poligono::draw(double scale)
{
    std::list<Ponto> d = this->pontos_scn;

    if (this->get_size() > 2)
    {
        Ponto p((this->pontos_scn.front().get_x() + this->pontos_scn.back().get_x())/2,
        (this->pontos_scn.front().get_y() + this->pontos_scn.back().get_y())/2,
         this->pontos_scn.back().get_z());
       d.push_back(p);
       d.push_front(p);
    }
    else if (this->get_size() == 1)
    {
        d.push_back(Ponto(this->pontos_scn.front().get_x(), this->pontos_scn.front().get_y()
        + this->brush_size/scale, this->pontos_scn.front().get_z()));
    }

    return d;
}

void Poligono::set_filled(bool fill) {
    this->filled = fill;
}

bool Poligono::get_filled() {
    return this->filled;
}

Objeto Poligono::to_objeto()
{
    Objeto o = Objeto();
    o.set_id(this->id);
    o.set_nome(this->nome);
    o.set_pontos(this->pontos);
    o.set_pontos_scn(this->pontos_scn);
    o.set_brush_size(this->brush_size);
    o.set_center(this->center);
    o.set_tipo(this->tipo);
    return o;
}