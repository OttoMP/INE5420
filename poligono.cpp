#include "poligono.h"


Poligono::Poligono(string nome)
{
	this->nome = nome;
}

Poligono::Poligono(string nome, std::list<Ponto> pontos)
{
    this->nome = nome;
    this->pontos = pontos;
}

void Poligono::addPonto(Ponto p)
{
    this->pontos.push_back(p);
}

void Poligono::addPonto(int coordx, int coordy) {
    Ponto p(coordx, coordy);
    this->pontos.push_back(p);
}

void Poligono::addPonto(int coordx, int coordy, int coordz) {
    Ponto p(coordx, coordy, coordz);
    this->pontos.push_back(p);
}

void Poligono::setBrushSize(double brush)
{
    this->brush_size = brush;
}

std::list<Ponto> Poligono::draw()
{
    std::list<Ponto> d = this->pontos;

    if (this->getSize() > 2)
    {
       Ponto p((this->pontos.front().getX() + this->pontos.back().getX())/2,
        (this->pontos.front().getY() + this->pontos.back().getY())/2);
       d.push_back(p);
       d.push_front(p);
    }
    else if (this->getSize() == 1)
    {
        d.push_back(Ponto(this->pontos.front().getX(), this->pontos.front().getY()
        + this->brush_size, this->pontos.front().getZ()));
    }

    return d;
}

int Poligono::getSize()
{
    return this->pontos.size();
}

double Poligono::getBrushSize()
{
    return this->brush_size;
}

string Poligono::getNome()
{
    return this->nome;
}

void Poligono::setNome(string nome) {
    this->nome = nome;
}
