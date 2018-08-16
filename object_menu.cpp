#include "object_menu.h"
#include <iostream>

ObjectMenu::ObjectMenu(const Glib::ustring& title,
       gint spacing,
       Canvas& window,
       Gtk::ListBox& object_viewer,
       Gtk::TextView& text_log)
  : Gtk::Frame(title),       // initialize parent widget
    button_rotate("ROTATE"), /* creates buttons              */
    button_move("MOVE"),     /* with its respectives labels. */
    button_resize("RESIZE"), /**/
    window_ref(window),      // initialize reference to window using parameter
    object_viewer_ref(object_viewer), // initialize reference to object_viewer
    text_log_ref(text_log) // initialize reference to text_log
{
  // Create Grid to hold the buttons
    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());

  // Setting border of parent widget
    set_border_width(10);
    add(*grid);

  // Setting default texts for entries
    e_move_x.set_text("0");
    e_move_y.set_text("0");
    e_scale.set_text("1");
    e_angle.set_text("90");

  // Setting the appearance of th Grid
    grid->set_border_width(5);
    grid->set_row_spacing(spacing);
    grid->set_column_spacing(spacing);

  // Setting buttons functions
    button_rotate.signal_clicked().connect(
              sigc::mem_fun(*this, &ObjectMenu::rotate_clicked));
    button_move.signal_clicked().connect(
              sigc::mem_fun(*this, &ObjectMenu::move_clicked));
    button_resize.signal_clicked().connect(
              sigc::mem_fun(*this, &ObjectMenu::resize_clicked));

  // Add buttons to Grid
    grid->attach(button_rotate, 0, 0, 1, 1);
    grid->attach(e_angle, 1, 0, 1, 1);
    grid->attach(button_move, 0, 1, 1, 1);
    grid->attach(e_move_x, 1, 1, 1, 1);
    grid->attach(e_move_y, 2, 1, 1, 1);
    grid->attach(button_resize, 0, 2, 1, 1);
    grid->attach(e_scale, 1, 2, 1, 1);
}

/*  Function called when button ROTATE is clicked
 *  calls function rotate_object from drawing window
 */
void ObjectMenu::rotate_clicked() {
//    window_ref.rotate_object(10);
}

/*  Function called when button MOVE is clicked
 *  calls function move_object from drawing window
 */
void ObjectMenu::move_clicked() {
//    window_ref.move_object(10);
}

/*  Function called when button RESIZE is clicked
 *  calls function resize_object from drawing window
 */
void ObjectMenu::resize_clicked() {
//    window_ref.resize_object(10);
}
