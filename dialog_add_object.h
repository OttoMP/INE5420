#ifndef DIALOG_ADD_OBJECT_H
#define DIALOG_ADD_OBJECT_H

#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>

#include "poligono.h"
#include "canvas.h"

class AddObjectDialog : public Gtk::Dialog {
public:
    AddObjectDialog(Canvas& drawing_window);
    virtual ~AddObjectDialog();

protected:
  // Internal reference to the drawing area
    Canvas& canvas;
    Poligono new_poly;

  //Signal handlers:
    void on_dialog_response(int response_id);
    void on_add_Dot_button_clicked();

  //Child widgets: l_ indicates a Label and e_ indicates an Entry
    Gtk::Label  l_x, l_y, l_name;
    Gtk::Entry  e_x, e_y, e_name;
    Gtk::Button add_Dot_button;
};

#endif //DIALOG_ADD_OBJECT_H

