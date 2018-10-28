#ifndef GTKMM_WINDOWMENU_H
#define GTKMM_WINDOWMENU_H

#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>

#include "canvas.h"

class WindowMenu : public Gtk::Frame {
    public:
        WindowMenu(const Glib::ustring& title,
             gint spacing,
             Canvas& window);

    protected:
        // Child Widgets
        // Navigation buttons
        Gtk::Button button_move;
        // Zoom function buttons
        Gtk::Button button_zoom_in, button_zoom_out;
        // Window rotate buttons
        Gtk::Button button_rotate;
        // Reference to drawing area
        Canvas& window_ref;

        // Entries slots for button functions
        Gtk::Entry e_move_x, e_move_y, e_move_z;
        Gtk::Label l_coord;

        //Signal handlers:
        void button_move_clicked();
        void button_rotate_clicked();
        void zoom_in_clicked();
        void zoom_out_clicked();
};

#endif //GTKMM_WINDOWMENU_H


