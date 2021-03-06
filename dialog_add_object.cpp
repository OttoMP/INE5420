#include "dialog_add_object.h"
#include <iostream>

AddObjectDialog::AddObjectDialog(Canvas& drawing_area,
                                 Gtk::TextView& text_log)
    : canvas(drawing_area),       // Receive reference from parameter
      log(text_log),              // Receive reference from parameter
      l_x("Coordenada x"),        // Initialize Label for Entry
      l_y("Coordenada y"),        // Initialize Label for Entry
      l_z("Coordenada z"),        // Initialize Label for Entry
      l_name("Nome do Objeto"),   // Initialize Label for Entry
      fill_button("Preencher Poligono"), // Initialize fill button
      add_dot_button("Adicionar Ponto"), // Initialize add button
      tb_poly("Polígono"),
      tb_bezier("Bezier"),
      tb_spline("Spline")
{
    Gtk::Box* info_box = Gtk::manage(
                                new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    Gtk::Box* toggle_box = Gtk::manage(
                                new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));

  // Setting configurations for dialog
    set_title("Adicionar Objeto");
    set_border_width(0);
    set_size_request(350, 350);
    get_content_area()->set_spacing(7);

  // Setting default texts for Entrys
    e_x.set_text("0");
    e_y.set_text("0");
    e_z.set_text("0");
    e_name.set_text("Novo Polígono");

  // Adding child widgets to internal box of dialog
    get_content_area()->pack_start(*info_box);
    get_content_area()->pack_start(*toggle_box);
    info_box->pack_start(l_x);
    info_box->pack_start(e_x);
    info_box->pack_start(l_y);
    info_box->pack_start(e_y);
    info_box->pack_start(l_z);
    info_box->pack_start(e_z);
    info_box->pack_start(l_name);
    info_box->pack_start(e_name);
    info_box->pack_start(fill_button);
    toggle_box->pack_start(tb_poly);
    toggle_box->pack_start(tb_bezier);
    toggle_box->pack_start(tb_spline);
    get_content_area()->pack_start(add_dot_button);

    // Adding a "close" and a "ok" button to the bottom of the dialog
    add_button("_Close", Gtk::RESPONSE_DELETE_EVENT);
    add_button("_OK", Gtk::RESPONSE_CLOSE);
    signal_response().connect(sigc::mem_fun(*this, &AddObjectDialog::on_dialog_response));

  // Setting Buttons function
    add_dot_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::on_add_dot_button_clicked));
    tb_poly.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::poly_toggled));
    tb_bezier.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::bezier_toggled));
    tb_spline.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::spline_toggled));

  /* This makes it so the button is the default.
   * Simply hitting the "Enter" key will cause this button to activate. */
    set_default_response(Gtk::RESPONSE_CLOSE);

    show_all_children();
}	 	  	 	    	 	    		    	    	  	 	

AddObjectDialog::~AddObjectDialog()
{
}

/*  Close button function
 *  Before the dialogs closes it sets the ID and Name of the
 *  polygon being created and send to the canvas. The text log
 *  updates telling the name of the polygon recently created
 */
void AddObjectDialog::on_dialog_response(int response_id) {
    switch (response_id)
  {
  case Gtk::RESPONSE_CLOSE:
      if(tb_poly.get_active()) {
        Poligono polygon(e_name.get_text(), new_dots);
        polygon.set_id(canvas.get_last_id()+1);

        if(fill_button.get_active()) {
            polygon.set_filled(true);
        }

        canvas.add_poligono(polygon);
        log.get_buffer()->set_text(log.get_buffer()->get_text()
                                   +"Polígono '"
                                   +polygon.get_nome()
                                   +"' adicionado\n");
        hide();
      } else if(tb_bezier.get_active()) {
        Curva2D bezier(e_name.get_text(), new_dots);
        bezier.set_id(canvas.get_last_id()+1);

        canvas.add_curva(bezier);
        log.get_buffer()->set_text(log.get_buffer()->get_text()
                                   +"Curva Bezier '"
                                   +bezier.get_nome()
                                   +"' adicionada\n");
        hide();
      } else if(tb_spline.get_active()) {	 	  	 	    	 	    		    	    	  	 	
        Poligono polygon(e_name.get_text(), new_dots);
        polygon.set_id(canvas.get_last_id()+1);
        polygon.set_filled(fill_button.get_active());

        canvas.add_poligono(polygon);
        log.get_buffer()->set_text(log.get_buffer()->get_text()
                                   +"Curva Spline '"
                                   +polygon.get_nome()
                                   +"' adicionada\n");
        hide();
      } else {
        log.get_buffer()->set_text(log.get_buffer()->get_text()
                                   +"Tipo de objeto não especificado. "
                                   +"Cancelando operação\n");
        hide();
      }
    break;

  case Gtk::RESPONSE_DELETE_EVENT:
    log.get_buffer()->set_text(log.get_buffer()->get_text()
                               +"Adicionar Objeto cancelado\n");
    hide();
    break;

  default:
    std::cout << "Unexpected response_id=" << response_id << std::endl;
    break;
  };
}

/*  Add Object function
 *  Read the text from entries and call function add_ponto from Poligono
 *  sending coordinates x and y collected by the entries as parameters.
 *  The log updates telling the user the coordinates recently added
 */
void AddObjectDialog::on_add_dot_button_clicked() {	 	  	 	    	 	    		    	    	  	 	
    new_dots.push_back(Ponto(atof(e_x.get_text().c_str()),
                             atof(e_y.get_text().c_str()),
                             atof(e_z.get_text().c_str())));

    log.get_buffer()->set_text(log.get_buffer()->get_text()
                               +"Ponto adicionado na coordenada ("
                               +e_x.get_text()
                               +","
                               +e_y.get_text()
                               +","
                               +e_z.get_text()
                               +")\n");
}

void AddObjectDialog::poly_toggled() {
    if (tb_poly.get_active()) {
        tb_spline.set_active(false);
        tb_bezier.set_active(false);
    }
}

void AddObjectDialog::bezier_toggled() {
    if (tb_bezier.get_active()) {
        tb_poly.set_active(false);
        tb_spline.set_active(false);
    }
}

void AddObjectDialog::spline_toggled() {
    if (tb_spline.get_active()) {
        tb_poly.set_active(false);
        tb_bezier.set_active(false);
    }
}
	 	  	 	    	 	    		    	    	  	 	
