#include "canvas.h"
#include <cairomm/context.h>
#include "ponto.h"
#include "poligono.h"

Canvas::Canvas()
    : scale(1),
      x_dislocate(0),
      y_dislocate(0)
{
}

Canvas::~Canvas()
{
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
//-----------------------------------------------------------------------------------------------------    
    std::list<Poligono> display_file;
    
    Poligono triangulo("Triangulo");
    triangulo.addPonto(Ponto(0,0));
    triangulo.addPonto(Ponto(10,10));
    triangulo.addPonto(Ponto(1,20));
    display_file.push_back(triangulo);
    
    Poligono ponto("Ponto");
    ponto.addPonto(Ponto(50,50));
    display_file.push_back(ponto);
    
    Poligono reta("Reta");
    reta.addPonto(Ponto(10,50));
    reta.addPonto(Ponto(100,100));
    display_file.push_back(reta);
    
    Poligono poligono("Ponto");
    poligono.addPonto(Ponto(20,5));
    poligono.addPonto(Ponto(25,15));
    poligono.addPonto(Ponto(20,30));
    poligono.addPonto(Ponto(50,70));
    poligono.addPonto(Ponto(17,30));
    display_file.push_back(poligono);
    
    
//-----------------------------------------------------------------------------------------------------  
  // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->scale(scale, scale);
    
    

    //cr->set_line_width(10.0);
  // draw red lines out from the center of the window
    cr->set_source_rgb(0.8, 0.0, 0.0);
    
    for (std::list<Poligono>::iterator pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        std::list<Ponto> pontos= pol->draw();
        cr->set_line_width(pol->getBrushSize());
        cr->move_to(x_dislocate + pontos.back().getX(), y_dislocate + pontos.back().getY());
        for (std::list<Ponto>::iterator pt = pontos.begin(); pt != pontos.end(); pt++)
            {
                cr->line_to(x_dislocate + pt->getX(), y_dislocate + pt->getY());
            }
    }

    cr->stroke();

    return true;
}

void Canvas::zoom_in(double factor) {
    scale += factor;
    queue_draw();
}

void Canvas::zoom_out(double factor) {
    scale -= factor;
    queue_draw();
}

void Canvas::move_up(double step) {
    y_dislocate += step;
    queue_draw();
}

void Canvas::move_down(double step) {
    y_dislocate -= step;
    queue_draw();
}

void Canvas::move_right(double step) {
    x_dislocate -= step;
    queue_draw();
}

void Canvas::move_left(double step) {
    x_dislocate += step;
    queue_draw();
}
