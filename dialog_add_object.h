#ifndef DIALOG_ADD_OBJECT_H
#define DIALOG_ADD_OBJECT_H

#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/textview.h>

#include "poligono.h"
#include "canvas.h"

class AddObjectDialog : public Gtk::Dialog {
public:
    AddObjectDialog(Canvas& drawing_window, Gtk::TextView& text_log);
    virtual ~AddObjectDialog();

protected:
  // Internal reference to text log to send updates to the user
    Gtk::TextView& log;

  // Internal reference to the drawing area
    Canvas& canvas;

  // List of Dots to be used in the object
    std::list<Ponto> new_dots;

  // Polygon being created by the dialog
    Poligono new_poly;

  //Signal handlers:
    void on_dialog_response(int response_id);
    void on_add_dot_button_clicked();
    void poly_toggled();
    void bezier_toggled();
    void spline_toggled();

  //Child widgets: l_ indicates a Label and e_ indicates an Entry
    Gtk::Label  l_x, l_y, l_name;
    Gtk::Entry  e_x, e_y, e_name;
    Gtk::Button add_dot_button;
    Gtk::ToggleButton tb_poly, tb_bezier, tb_spline, fill_button;
};

#endif //DIALOG_ADD_OBJECT_H
	 	  	 	    	 	    		    	    	  	 	
