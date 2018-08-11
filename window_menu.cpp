#include "window_menu.h"
#include <iostream>

WindowMenu::WindowMenu(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout,
       Canvas& window)
  : Gtk::Frame(title), // initialize parent widget
    button_up("UP"),               /* creates the navigation buttons */
    button_down("DOWN"),           /* with its respectives labels.   */
    button_left("LEFT"),           /**/
    button_right("RIGHT"),         /**/
    button_zoom_in("ZOOM IN"),     /**/
    button_zoom_out("ZOOM OUT"),   /**/
    window_ref(window) // initialize reference to window using parameter
{
  // Create ButtonBox to hold the buttons
    Gtk::ButtonBox* bbox = nullptr;

  // Setting orientation of ButtonBox
    if(horizontal)
        bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL) );
    else
        bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

    // Setting border of parent widget
    set_border_width(10);
    add(*bbox);

  // Setting the appearance of the Button Box
    bbox->set_border_width(5);
    bbox->set_layout(layout);
    bbox->set_spacing(spacing);

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

  // Adding buttons to box
    bbox->add(button_up);
    bbox->add(button_down);
    bbox->add(button_left);
    bbox->add(button_right);
    bbox->add(button_zoom_in);
    bbox->add(button_zoom_out);
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
