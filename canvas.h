#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>
#include "poligono.h"

class Canvas : public Gtk::DrawingArea {
    public:
        Canvas();
        virtual ~Canvas();

        int get_last_id();
        // Navigation Functions
        void zoom_in(double factor);
        void zoom_out(double factor);
        void move_up(double step);
        void move_down(double step);
        void move_right(double step);
        void move_left(double step);

        // Viewport Transforms
        double vp_transform_x(double x, double width);
        double vp_transform_y(double y, double height);

        //
        void add_poligono(Poligono pol);
        void rem_poligono(Poligono pol);

    protected:
        //Override default signal handler:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

        // Internal parameters
        double scale;
        double x_dislocate;
        double y_dislocate;
        std::list<Poligono> display_file;
};

#endif //CANVAS_H

