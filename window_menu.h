#ifndef GTKMM_BUTTONBOX_H
#define GTKMM_BUTTONBOX_H

#include <gtkmm.h>
#include "canvas.h"

class WindowMenu : public Gtk::Frame {
    public:
        WindowMenu(bool horizontal,
             const Glib::ustring& title,
             gint spacing,
             Gtk::ButtonBoxStyle layout,
             Canvas& window);

    protected:
        Gtk::Button button_up, button_down, button_left, button_right;
        Gtk::Button button_zoom_in, button_zoom_out;

        //Signal handlers:
        void on_button_clicked(Glib::ustring data);
        void draw_line_button_clicked(Canvas& window);
};

#endif //GTKMM_BUTTONBOX_H
