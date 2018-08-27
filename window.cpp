#include "window.h"

Window::Window(Ponto wc, Ponto v, Ponto u)
{
    this->wc = wc;
    this->v = v;
    this->u = u;
}

Ponto Window::get_v()
{
    return this->v;
}

Ponto Window::get_u()
{
    return this->u;
}

Ponto Window::get_wc()
{
    return this->wc;
}

void Window::rotate(double angle)
{
    Matriz m = Matriz().rotate(angle, Ponto(0,0));
    this->v = m.exec_transform(this->v);
    
    this->u = m.exec_transform(this->u);
}

void Window::scale(Ponto scale)
{
    Matriz m = Matriz().scale(scale, Ponto(0,0));
    this->v = m.exec_transform(this->v);
    
    this->u = m.exec_transform(this->u);
}	 	  	 	    	 	    		    	    	  	 	


void Window::translate(Ponto p)
{
    Matriz m = Matriz().translate(p);
    this->wc = m.exec_transform(this->wc);
}
   