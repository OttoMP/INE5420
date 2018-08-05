#ifndef CANVAS_H
#define CANVAS_H

#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea {
    public:
        Canvas();
        virtual ~Canvas();

    protected:
        //Override default signal handler:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        bool draw_line(const Cairo::RefPtr<Cairo::Context>& cr);
        bool draw_circle(const Cairo::RefPtr<Cairo::Context>& cr);
};

#endif //CANVAS_H
