#include "poligono.h"


Poligono::Poligono(string nome)
{
	this->nome = nome;
}

Poligono::Poligono(string nome, int id, bool filled, std::list<Ponto> pontos)
{
	this->nome = nome;
    this->id = id;
    this->filled = filled;
    this->pontos = pontos;
}

Poligono::Poligono(string nome, std::list<Ponto> pontos)
{
    this->nome = nome;
    this->pontos = pontos;
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

void Poligono::add_ponto(double x, double y, double z)
{
	Ponto p(x,y,z);
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

void Poligono::set_brush_size(double brush)
{
    this->brush_size = brush;
}

std::list<Ponto> Poligono:: get_pontos() {
    return this->pontos;
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

int Poligono::get_size()
{
    return this->pontos.size();
}

double Poligono::get_brush_size()
{
    return this->brush_size;
}

string Poligono::get_nome()
{
    return this->nome;
}

void Poligono::set_nome(string nome) {
    this->nome = nome;
}

int Poligono::get_id() const{
    return this->id;
}

void Poligono::set_id(int new_id) {
    this->id = new_id;
}

Ponto Poligono::get_center()
{
    return this->center;
}

void Poligono::exec_transform(Matriz transform)
{
    this->center = transform.exec_transform(center);
    for (auto pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt = transform.exec_transform(*pt);
    }
}

void Poligono::exec_update_scn(Matriz transform)
{
    auto pt2 = this->pontos_scn.begin();
    for (auto pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt2 = transform.exec_transform(*pt);
        pt2++;
    }

}

bool Poligono::operator==(const Poligono& a) {
    return this->get_id() == a.get_id();
}

void Poligono::set_filled(bool fill) {
    this->filled = fill;
}

bool Poligono::get_filled() {
    return this->filled;
}
