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

void Canvas::add_poligono(Poligono pol){
    display_file.push_back(pol);
    queue_draw();
}

void Canvas::rem_poligono(Poligono pol){
    //display_file.remove(pol);
    queue_draw();
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
  // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->scale(scale, scale);
    cr->set_source_rgb(0.8, 0.0, 0.0);

    for (std::list<Poligono>::iterator pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        std::list<Ponto> pontos= pol->draw();
        cr->set_line_width(pol->getBrushSize());
        cr->move_to(vp_transform_x(pontos.back().getX(), width), vp_transform_y(pontos.back().getY(), height));
        for (std::list<Ponto>::iterator pt = pontos.begin(); pt != pontos.end(); pt++)
            {
                cr->line_to(vp_transform_x(pt->getX(), width), vp_transform_y(pt->getY(), height));
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

double Canvas::vp_transform_x(double x, double width){
    return (x - x_dislocate) / width * width;
}

double Canvas::vp_transform_y(double y, double height){
    return (1-(y - y_dislocate)/height) * height;
}
