#include "window_menu.h"
#include <iostream>

WindowMenu::WindowMenu(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout,
       Canvas& window)
  : Gtk::Frame(title),
    button_up("UP"),
    button_down("DOWN"),
    button_left("LEFT"),
    button_right("RIGHT"),
    button_zoom_in("ZOOM IN"),
    button_zoom_out("ZOOM OUT")   // creates the move buttons with its respectives labels.
{
    Gtk::ButtonBox* bbox = nullptr;

  // Setting orientation of ButtonBox
    if(horizontal)
        bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL) );
    else
        bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

    bbox->set_border_width(5);

    set_border_width(10);
    add(*bbox);

  // Setting the appearance of the Button Box
    bbox->set_layout(layout);
    bbox->set_spacing(spacing);

  // Setting buttons functions
    button_up.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &WindowMenu::on_button_clicked), "GO UP"));
    button_down.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &WindowMenu::on_button_clicked), "GO DOWN"));
    button_left.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &WindowMenu::on_button_clicked), "GO LEFT"));
    button_right.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &WindowMenu::on_button_clicked), "GO RIGHT"));
    button_zoom_in.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &WindowMenu::on_button_clicked), "ZOOM IN"));
    button_zoom_out.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &WindowMenu::on_button_clicked), "ZOOM OUT"));

  // Adding buttons to box
    bbox->add(button_up);
    bbox->add(button_down);
    bbox->add(button_left);
    bbox->add(button_right);
    bbox->add(button_zoom_in);
    bbox->add(button_zoom_out);
}

void WindowMenu::on_button_clicked(Glib::ustring data) {
  std::cout << data << std::endl;
}
/*
void WindowMenu::draw_line_button_clicked(Canvas& window) {
    window.draw_line();
}*/
