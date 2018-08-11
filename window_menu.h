#ifndef GTKMM_BUTTONBOX_H
#define GTKMM_BUTTONBOX_H

#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/buttonbox.h>

#include "canvas.h"

class WindowMenu : public Gtk::Frame {
    public:
        WindowMenu(bool horizontal,
             const Glib::ustring& title,
             gint spacing,
             Gtk::ButtonBoxStyle layout,
             Canvas& window);

    protected:
        // Child Widgets
        // Navigation buttons
        Gtk::Button button_up, button_down, button_left, button_right;
        // Zoom function buttons
        Gtk::Button button_zoom_in, button_zoom_out;
        // Reference to drawing area
        Canvas& window_ref;

        //Signal handlers:
        void zoom_in_clicked();
        void zoom_out_clicked();
        void button_up_clicked();
        void button_down_clicked();
        void button_right_clicked();
        void button_left_clicked();
};

#endif //GTKMM_BUTTONBOX_H

