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
    button_zoom_out("ZOOM OUT"),   // creates the move buttons with its respectives labels.
    window_ref(window)
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

void WindowMenu::button_up_clicked() {
    window_ref.move_up(10);
}

void WindowMenu::button_down_clicked() {
    window_ref.move_down(10);
}

void WindowMenu::button_right_clicked() {
    window_ref.move_right(10);
}

void WindowMenu::button_left_clicked() {
    window_ref.move_left(10);
}

void WindowMenu::zoom_in_clicked() {
    window_ref.zoom_in(0.1);
}

void WindowMenu::zoom_out_clicked() {
    window_ref.zoom_out(0.1);
}

/*
void WindowMenu::zoom_out_clicked() {
    window_ref.zoom_out(0.1);
    Poligono triangulo("Triangulo");
    triangulo.add_ponto(Ponto(0,0));
    triangulo.add_ponto(Ponto(10,10));
    triangulo.add_ponto(Ponto(1,20));
    window_ref.add_poligono(triangulo);
    
    Poligono ponto("Ponto");
    ponto.add_ponto(Ponto(50,50));
    window_ref.add_poligono(ponto);
    
    Poligono reta("Reta");
    reta.add_ponto(Ponto(10,50));
    reta.add_ponto(Ponto(100,100));
    window_ref.add_poligono(reta);
    
    Poligono poligono("Ponto");
    poligono.add_ponto(Ponto(20,5));
    poligono.add_ponto(Ponto(25,15));
    poligono.add_ponto(Ponto(20,30));
    poligono.add_ponto(Ponto(50,70));
    poligono.add_ponto(Ponto(17,30));
    window_ref.add_poligono(poligono);
}	 	  	 	    	 	    		    	    	  	 	
*/