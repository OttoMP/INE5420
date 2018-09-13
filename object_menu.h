#ifndef GTKMM_OBJECTMENU_H
#define GTKMM_OBJECTMENU_H

#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/listbox.h>
#include <gtkmm/textview.h>
#include <gtkmm/entry.h>

#include "canvas.h"
#include "ponto.h"
#include "objeto.h"
#include "object_viewer.h"
#include "descritorOBJ.h"

class ObjectMenu : public Gtk::Frame {
    public:
        ObjectMenu(const Glib::ustring& title,
             gint spacing,
             Canvas& window,
             Gtk::TextView& text_log,
             ObjectViewer& object_viewer);

    protected:
        // Object changing functions
        Gtk::Button button_rotate_poly, button_move, button_resize;
        Gtk::Button button_rotate_center, button_rotate_dot;

        // Entries slots for button functions
        Gtk::Entry  e_move_x, e_move_y, e_scale, e_angle;
        Gtk::Entry  e_file;

        // Labels for entries
        Gtk::Label l_angle, l_dot, l_scale;
        Gtk::Label l_file;

        // Reference to drawing area
        Canvas& window_ref;

        //Reference to Text Log
        Gtk::TextView& text_log_ref;

         //Reference to Object Viewer
        ObjectViewer& object_viewer_ref;

         // Read Write buttons
        Gtk::Button button_read_file, button_write_file;

         // Object descriptor
        descritorObj d_obj;

        //Signal handlers:
        void rotate_poly_clicked();
        void rotate_center_clicked();
        void rotate_dot_clicked();
        void move_clicked();
        void resize_clicked();
        void write_file();
        void read_file();
};

#endif //GTKMM_OBJECTMENU_H
	 	  	 	    	 	    		    	    	  	 	
