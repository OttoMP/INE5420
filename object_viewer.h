#ifndef OBJECT_VIEWER_H
#define OBJECT_VIEWER_H

#include <gtkmm/listbox.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>

#include "canvas.h"
#include "dialog_add_object.h"

class ObjectViewer : public Gtk::Box {
    public:
        ObjectViewer(
             Canvas& window,
             Gtk::TextView& text_log);

        std::string get_selected_object_name();
        int get_selected_object_id();

    protected:
        void on_add_objects_clicked();
        void on_rm_objects_clicked();

        Gtk::Button                         bt_add_objects;
        Gtk::Button                         bt_rm_objects;
        Gtk::ButtonBox                      b_add_rm_objects;
        Gtk::Box                            b_objects;
        Gtk::ScrolledWindow                 w_objects;
        Gtk::ListBox                        object_viewer;

        Canvas& canvas_ref;
        Gtk::TextView& text_log_ref;
};

#endif
	 	  	 	    	 	    		    	    	  	 	
