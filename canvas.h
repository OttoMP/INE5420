#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>
#include <list>
#include "poligono.h"
#include <cairomm/context.h>
#include "ponto.h"
#include "poligono.h"
#include "matriz.h"

class Canvas : public Gtk::DrawingArea {
    public:
        Canvas();
        virtual ~Canvas();

        // Functions used in setting the id's of display_file's polygons
        int get_last_id();
        std::string get_last_name();

        // Navigation Functions
        void zoom_in(double factor);
        void zoom_out(double factor);
        void move_up(double step);
        void move_down(double step);
        void move_right(double step);
        void move_left(double step);

        // Transforming Functions
        void rotate_object(int id, double angle);
        void rotate_point(int id, double angle, Ponto reference);
        void move_object(int id, Ponto distancia);
        void resize_object(int id, Ponto escala);

        // Viewport Transforms
        double vp_transform_x(double x, double width);
        double vp_transform_y(double y, double height);

        // Functions used to add or remove polygons from drawing area
        void add_poligono(Poligono pol);
        void rm_poligono(int id);

    protected:
        // Function used to draw all objects from display_file
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

        // Internal parameters

        // Parameter setting the zoom
        double scale;

        // Parameter setting how much the view dislocate from the center in the x axis
        double x_dislocate;

        // Parameter setting how much the view dislocate from the center in the y axis
        double y_dislocate;

        // List of all objects currently drawn in the canvas
        std::list<Poligono> display_file;

        //Clipping functions
        void clipping_line(Poligono line, Ponto tl, Ponto br);
        void clipping_poly(Poligono poly, double height, double width, double scale);
        bool inside_view(Ponto p, Ponto tl, Ponto br);
};

#endif //CANVAS_H


