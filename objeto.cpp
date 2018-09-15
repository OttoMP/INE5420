#include "objeto.h"

Objeto::Objeto()
{
    this->id = -1;
    this->nome = "";
}

void Objeto::set_brush_size(double brush)
{
    this->brush_size = brush;
}

std::list<Ponto> Objeto::get_pontos() {
    return this->pontos;
}


std::list<Ponto> Objeto::get_pontos_scn()
{
    return this->pontos_scn;
}

void Objeto::set_pontos(std::list<Ponto> pontos) {
    this->pontos = pontos;
    for (auto i = pontos.begin(); i != pontos.end(); i++) {
        this->pontos_scn.push_back(Ponto(0,0));
    }
}

void Objeto::set_pontos_scn(std::list<Ponto> pontos_scn) {
    this->pontos_scn = pontos_scn;
}

void Objeto::set_center(Ponto center)
{
    this->center = center;
}

void Objeto::set_tipo(int tipo)
{
    this->tipo = tipo;
}

int Objeto::get_size()
{
    return this->pontos.size();
}

double Objeto::get_brush_size()
{
    return this->brush_size;
}

int Objeto::get_tipo()
{
    return this->tipo;
}

string Objeto::get_nome()
{
    return this->nome;
}

void Objeto::set_nome(string nome) {
    this->nome = nome;
}

int Objeto::get_id() const{
    return this->id;
}

void Objeto::set_id(int new_id) {
    this->id = new_id;
}

Ponto Objeto::get_center()
{
    return this->center;
}

void Objeto::set_filled(bool fill) {
    this->filled = fill;
}

bool Objeto::get_filled() {
    return this->filled;
}

void Objeto::exec_transform(Matriz transform)
{
    this->center = transform.exec_transform(center);
    for (auto pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt = transform.exec_transform(*pt);
    }
}

void Objeto::exec_update_scn(Matriz transform)
{
    auto pt2 = this->pontos_scn.begin();
    for (auto pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt2 = transform.exec_transform(*pt);
        pt2++;
    }

}

bool Objeto::operator==(const Objeto& a) {
    return this->get_id() == a.get_id();
}

