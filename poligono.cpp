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

void Poligono::add_ponto(Ponto p)
{
    if (this->get_size() == 0)
    {
        this->center = p;
    }
    else
    {
        this->center = Ponto((this->center.get_x()*this->get_size() + p.get_x())/(this->get_size()+1),(this->center.get_y()*this->get_size() + p.get_y())/(this->get_size()+1));
    }
    this->pontos.push_back(p);
    
    
}

void Poligono::add_ponto(int coordx, int coordy) {
    Ponto p(coordx, coordy);
     if (this->get_size() == 0)
    {
        this->center = p;
    }
    else
    {	 	  	 	    	 	    		    	    	  	 	
        this->center = Ponto((this->center.get_x()*this->get_size() + p.get_x())/(this->get_size()+1),(this->center.get_y()*this->get_size() + p.get_y())/(this->get_size()+1));
    }
    this->pontos.push_back(p);
}

void Poligono::add_ponto(int coordx, int coordy, int coordz) {
    Ponto p(coordx, coordy, coordz);
    this->pontos.push_back(p);
}

void Poligono::set_brush_size(double brush)
{
    this->brush_size = brush;
}

std::list<Ponto> Poligono::draw()
{
    std::list<Ponto> d = this->pontos;

    if (this->get_size() > 2)
    {
        Ponto p((this->pontos.front().get_x() + this->pontos.back().get_x())/2,
        (this->pontos.front().get_y() + this->pontos.back().get_y())/2, this->pontos.back().get_z());
       d.push_back(p);
       d.push_front(p);
    }
    else if (this->get_size() == 1)
    {
        d.push_back(Ponto(this->pontos.front().get_x(), this->pontos.front().get_y()
        + this->brush_size, this->pontos.front().get_z()));
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

int Poligono::get_id() {
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
    for (std::list<Ponto>::iterator pt = this->pontos.begin(); pt != this->pontos.end(); pt++)
    {
        *pt = transform.exec_transform(*pt);
    }	 	  	 	    	 	    		    	    	  	 	
    this->center = transform.exec_transform(center);
}
