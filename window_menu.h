#ifndef GTKMM_WINDOWMENU_H
#define GTKMM_WINDOWMENU_H

#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>

#include "canvas.h"

class WindowMenu : public Gtk::Frame {
    public:
        WindowMenu(const Glib::ustring& title,
             gint spacing,
             Canvas& window);

    protected:
        // Child Widgets
        // Navigation buttons
        Gtk::Button button_up, button_down, button_left, button_right;
        // Zoom function buttons
        Gtk::Button button_zoom_in, button_zoom_out;
        // Window rotate buttons
        Gtk::Button button_rotate_left, button_rotate_right;
        // Reference to drawing area
        Canvas& window_ref;

        //Signal handlers:
        void zoom_in_clicked();
        void zoom_out_clicked();
        void rotate_left_clicked();
        void rotate_right_clicked();
        void button_up_clicked();
        void button_down_clicked();
        void button_right_clicked();
        void button_left_clicked();
};

#endif //GTKMM_WINDOWMENU_H

	 	  	 	    	 	    		    	    	  	 	
