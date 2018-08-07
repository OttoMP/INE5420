#include "canvas.h"
#include <cairomm/context.h>

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

  // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->scale(scale, scale);

    cr->set_line_width(10.0);
  // draw red lines out from the center of the window
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->move_to(x_dislocate, y_dislocate);
    cr->line_to(x_dislocate+xc, y_dislocate+yc);
    cr->line_to(x_dislocate, y_dislocate+height);
    cr->move_to(x_dislocate+xc, y_dislocate+yc);
    cr->line_to(x_dislocate+width, y_dislocate+yc);
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
