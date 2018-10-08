#include "poligono.h"

Poligono::Poligono(Objeto o)
{
    this->id = o.get_id();
    this->nome = o.get_nome();
    this->pontos = o.get_pontos();
    this->center = o.get_center();
    this->brush_size = o.get_brush_size();
    this->pontos_scn = o.get_pontos_scn();
    this->filled = o.get_filled();
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
    for(auto i = pontos.begin(); i != pontos.end(); i++) {
        add_ponto(*i);
    }
    this->tipo = 1;
}

Poligono::Poligono(string nome, std::list<Ponto> pontos)
{
    this->nome = nome;
    this->tipo = 1;
    for(auto i = pontos.begin(); i != pontos.end(); i++) {
        add_ponto(*i);
    }	 	  	 	    	 	    		    	    	  	 	
}



std::list<Ponto> Poligono::draw(double scale)
{
    std::list<Ponto> d = this->pontos_scn;

    if (this->get_size() > 2)
    {
        Ponto p((this->pontos_scn.front().get_x() + this->pontos_scn.back().get_x())/2,
        (this->pontos_scn.front().get_y() + this->pontos_scn.back().get_y())/2,
        (this->pontos_scn.front().get_z() + this->pontos_scn.back().get_z())/2);
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
    o.set_filled(this->filled);
    return o;
}	 	  	 	    	 	    		    	    	  	 	
