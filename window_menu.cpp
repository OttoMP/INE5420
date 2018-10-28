#include "window_menu.h"

WindowMenu::WindowMenu(const Glib::ustring& title,
       gint spacing,
       Canvas& window)
  : Gtk::Frame(title), // initialize parent widget
    button_zoom_in("ZOOM IN"),              /**/
    button_zoom_out("ZOOM OUT"),           /**/
    button_rotate("ROTATE"),         /**/
    button_move("MOVE TO COORDINATE"),   /**/
    window_ref(window) // initialize reference to window using parameter
{
  // Create Grid to hold the buttons
    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());


  // Setting border of parent widget
    set_border_width(10);
    add(*grid);

  // Setting the appearance of th Grid
    grid->set_border_width(5);
    grid->set_row_spacing(spacing);
    grid->set_column_spacing(spacing);

  // Setting default texts for entries
    e_move_x.set_text("0");
    e_move_y.set_text("0");
    e_move_z.set_text("0");
    l_coord.set_text("Reference Coordinates");

  // Setting buttons functions
    button_zoom_in.signal_clicked().connect(
            sigc::mem_fun(*this, &WindowMenu::zoom_in_clicked));
    button_zoom_out.signal_clicked().connect(
            sigc::mem_fun(*this, &WindowMenu::zoom_out_clicked));
    button_move.signal_clicked().connect(
              sigc::mem_fun(*this, &WindowMenu::button_move_clicked));
    button_rotate.signal_clicked().connect(
              sigc::mem_fun(*this, &WindowMenu::button_rotate_clicked));

  // Add Buttons to Grid
    grid->attach(button_move, 0, 0, 1, 1);
    grid->attach(button_rotate, 1, 0, 1, 1);
    grid->attach(l_coord, 0, 1, 1, 1);
    grid->attach(e_move_x, 1, 1, 1, 1);
    grid->attach(e_move_y, 2, 1, 1, 1);
    grid->attach(e_move_z, 3, 1, 1, 1);
}

/*  Function called when button ZOON IN is clicked
 *  calls function zoom_in from drawing window
 */
void WindowMenu::zoom_in_clicked() {
    window_ref.zoom_in(1.1);
}

/*  Function called when button ZOOM OUT is clicked
 *  calls function zoom_out from drawing window
 */
void WindowMenu::zoom_out_clicked() {
    window_ref.zoom_out(1.1);
}

/*
 *
 *
 */
void WindowMenu::button_move_clicked() {
}

/*
 *
 *
 */
void WindowMenu::button_rotate_clicked() {
}
