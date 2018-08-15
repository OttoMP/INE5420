#include "window_menu.h"
#include <iostream>

WindowMenu::WindowMenu(const Glib::ustring& title,
       gint spacing,
       Canvas& window)
  : Gtk::Frame(title), // initialize parent widget
    button_up("UP"),                 /* creates the navigation buttons */
    button_down("DOWN"),             /* with its respectives labels.   */
    button_left("LEFT"),             /**/
    button_right("RIGHT"),           /**/
    button_zoom_in("ZOOM IN"),       /**/
    button_zoom_out("ZOOM OUT"),     /**/
    button_rotate_left("R. LEFT"),   /**/
    button_rotate_right("R. RIGHT"), /**/
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

  // Setting buttons functions
    button_up.signal_clicked().connect(
              sigc::mem_fun(*this, &WindowMenu::button_up_clicked));
    button_down.signal_clicked().connect(
              sigc::mem_fun(*this, &WindowMenu::button_down_clicked));
    button_right.signal_clicked().connect(
              sigc::mem_fun(*this, &WindowMenu::button_right_clicked));
    button_left.signal_clicked().connect(
              sigc::mem_fun(*this, &WindowMenu::button_left_clicked));
    button_zoom_in.signal_clicked().connect(
            sigc::mem_fun(*this, &WindowMenu::zoom_in_clicked));
    button_zoom_out.signal_clicked().connect(
            sigc::mem_fun(*this, &WindowMenu::zoom_out_clicked));
    button_rotate_left.signal_clicked().connect(
            sigc::mem_fun(*this, &WindowMenu::rotate_left_clicked));
    button_rotate_right.signal_clicked().connect(
            sigc::mem_fun(*this, &WindowMenu::rotate_right_clicked));

    grid->attach(button_up, 1, 0, 1, 1);
    grid->attach(button_down, 1, 1, 1, 1);
    grid->attach(button_left, 0, 1, 1, 1);
    grid->attach(button_right, 2, 1, 1, 1);
    grid->attach(button_zoom_in, 0, 0, 1, 1);
    grid->attach(button_zoom_out, 2, 0, 1, 1);
    grid->attach(button_rotate_left, 0, 2, 1, 1);
    grid->attach(button_rotate_right, 2, 2, 1, 1);
}

/*  Function called when button UP is clicked
 *  calls function move_up from drawing window
 */
void WindowMenu::button_up_clicked() {
    window_ref.move_up(10);
}

/*  Function called when button DOWN is clicked
 *  calls function move_down from drawing window
 */
void WindowMenu::button_down_clicked() {
    window_ref.move_down(10);
}

/*  Function called when button RIGHT is clicked
 *  calls function move_right from drawing window
 */
void WindowMenu::button_right_clicked() {
    window_ref.move_right(10);
}

/*  Function called when button LEFT is clicked
 *  calls function move_left from drawing window
 */
void WindowMenu::button_left_clicked() {
    window_ref.move_left(10);
}

/*  Function called when button ZOON IN is clicked
 *  calls function zoom_in from drawing window
 */
void WindowMenu::zoom_in_clicked() {
    window_ref.zoom_in(0.1);
}

/*  Function called when button ZOOM OUT is clicked
 *  calls function zoom_out from drawing window
 */
void WindowMenu::zoom_out_clicked() {
    window_ref.zoom_out(0.1);
}

/*  Function called when button R. LEFT is clicked
 *  calls function rotate_left from drawing window
 */
void WindowMenu::rotate_left_clicked() {
//    window_ref.rotate_left(10);
}

/*  Function called when button R. RIGHT is clicked
 *  calls function rotate_right from drawing window
 */
void WindowMenu::rotate_right_clicked() {
//    window_ref.rotate_right(10);
}
