#ifndef GTKMM_OBJECTMENU_H
#define GTKMM_OBJECTMENU_H

#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/listbox.h>

#include "canvas.h"

class ObjectMenu : public Gtk::Frame {
    public:
        ObjectMenu(const Glib::ustring& title,
             gint spacing,
             Canvas& window,
             Gtk::ListBox& object_viewer);

    protected:
        // Object changing functions
        Gtk::Button button_rotate, button_move, button_resize;
        // Reference to drawing area
        Canvas& window_ref;
        //Reference to Object viewer
        Gtk::ListBox& object_viewer_ref;

        //Signal handlers:
        void rotate_clicked();
        void move_clicked();
        void resize_clicked();
};

#endif //GTKMM_OBJECTMENU_H
