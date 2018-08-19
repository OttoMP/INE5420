#ifndef GTKMM_OBJECTMENU_H
#define GTKMM_OBJECTMENU_H

#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/listbox.h>
#include <gtkmm/textview.h>
#include <gtkmm/entry.h>

#include "canvas.h"
#include "object_viewer.h"

class ObjectMenu : public Gtk::Frame {
    public:
        ObjectMenu(const Glib::ustring& title,
             gint spacing,
             Canvas& window,
             Gtk::TextView& text_log,
             ObjectViewer& object_viewer);

    protected:
        // Object changing functions
        Gtk::Button button_rotate, button_move, button_resize;
        // Entries slots for button functions
        Gtk::Entry  e_move_x, e_move_y, e_scale, e_angle;
        // Reference to drawing area
        Canvas& window_ref;
        //Reference to Text Log
        Gtk::TextView& text_log_ref;
        //Reference to Object Viewer
        ObjectViewer& object_viewer_ref;

        //Signal handlers:
        void rotate_clicked();
        void move_clicked();
        void resize_clicked();
};

#endif //GTKMM_OBJECTMENU_H
	 	  	 	    	 	    		    	    	  	 	
