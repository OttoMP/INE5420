#include "object_menu.h"
#include <iostream>

ObjectMenu::ObjectMenu(const Glib::ustring& title,
       gint spacing,
       Canvas& window,
       Gtk::TextView& text_log,
       ObjectViewer& object_viewer)
  : Gtk::Frame(title),       // initialize parent widget
    button_rotate("ROTATE"), /* creates buttons              */
    button_move("MOVE"),     /* with its respectives labels. */
    button_resize("RESIZE"), /**/
    window_ref(window),      // initialize reference to window using parameter
    text_log_ref(text_log), // initialize reference to text_log
    object_viewer_ref(object_viewer) // initialize reference to object_viewer
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
    int id = object_viewer_ref.get_selected_object_id();
    int angle = atoi(e_angle.get_text().c_str());
//    window_ref.rotate_object(id, angle);
    text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                       +"Polígono '"
                                       +object_viewer_ref.get_selected_object_name()
                                       +"' rotacionado "
                                       +std::to_string(angle)
                                       +" graus\n");
}

/*  Function called when button MOVE is clicked
 *  calls function move_object from drawing window
 */
void ObjectMenu::move_clicked() {
    int id = object_viewer_ref.get_selected_object_id();
    int x = atoi(e_move_x.get_text().c_str());
    int y = atoi(e_move_y.get_text().c_str());
//    window_ref.move_object(id, x, y);
    text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                       +"Polígono '"
                                       +object_viewer_ref.get_selected_object_name()
                                       +"' movido para ("
                                       +std::to_string(x)
                                       +", "
                                       +std::to_string(y)
                                       +")\n");
}

/*  Function called when button RESIZE is clicked
 *  calls function resize_object from drawing window
 */
void ObjectMenu::resize_clicked() {
    int id = object_viewer_ref.get_selected_object_id();
    int scale = atoi(e_scale.get_text().c_str());
//    window_ref.resize_object(id, scale);
    text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                       +"Polígono '"
                                       +object_viewer_ref.get_selected_object_name()
                                       +"' aumentado em "
                                       +std::to_string(scale)
                                       +" vezes\n");
}
