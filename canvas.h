#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea {
    public:
        Canvas();
        virtual ~Canvas();
        void zoom_in(double factor);
        void zoom_out(double factor);
        void move_up(double step);
        void move_down(double step);
        void move_right(double step);
        void move_left(double step);
        double vp_transform_x(double x, double width);
        double vp_transform_y(double y, double height);

    protected:
        //Override default signal handler:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        double scale;
        double x_dislocate;
        double y_dislocate;
};

#endif //CANVAS_H
