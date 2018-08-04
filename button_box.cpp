#include "button_box.h"
#include <iostream>

ButtonBox::ButtonBox(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout)
  : Gtk::Frame(title),
    button_up("UP"),
    button_down("DOWN"),
    button_left("LEFT"),
    button_right("RIGHT")   // creates the move buttons with its respectives labels.
{
    Gtk::ButtonBox* bbox = nullptr;

  // Setting orientation of ButtonBox
    if(horizontal)
        bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL) );
    else
        bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

    bbox->set_border_width(5);

    add(*bbox);

  // Setting the appearance of the Button Box
    bbox->set_layout(layout);
    bbox->set_spacing(spacing);

  // Setting buttons functions
    button_up.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &ButtonBox::on_button_clicked), "GO UP"));
    button_down.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &ButtonBox::on_button_clicked), "GO DOWN"));
    button_left.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &ButtonBox::on_button_clicked), "GO LEFT"));
    button_right.signal_clicked().connect(sigc::bind<Glib::ustring>(
              sigc::mem_fun(*this, &ButtonBox::on_button_clicked), "GO RIGHT"));

  // Adding buttons to box
    bbox->add(button_up);
    bbox->add(button_down);
    bbox->add(button_left);
    bbox->add(button_right);
}

void ButtonBox::on_button_clicked(Glib::ustring data) {
  std::cout << data << std::endl;
}
