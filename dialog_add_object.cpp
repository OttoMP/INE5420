#include "dialog_add_object.h"
#include <iostream>

AddObjectDialog::AddObjectDialog(Canvas& drawing_area,
                                 Gtk::TextView& text_log)
    : canvas(drawing_area),       // Receive reference from parameter
      log(text_log),              // Receive reference from parameter
      new_poly(""),
      l_x("Coordenada x"),        // Initialize Label for Entry
      l_y("Coordenada y"),        // Initialize Label for Entry
      l_name("Nome do Objeto"),   // Initialize Label for Entry
      fill_button("Preencher Poligono"), // Initialize fill button
      add_dot_button("Adicionar Ponto") // Initialize add button
{
  // Setting configurations for dialog
    set_title("Adicionar Objeto");
    set_border_width(0);
    set_size_request(350, 350);

  // Setting default texts for Entrys
    e_x.set_text("0");
    e_y.set_text("0");
    e_name.set_text("Novo Polígono");

  // Adding child widgets to internal box of dialog
    get_content_area()->pack_start(l_x);
    get_content_area()->pack_start(e_x);
    get_content_area()->pack_start(l_y);
    get_content_area()->pack_start(e_y);
    get_content_area()->pack_start(l_name);
    get_content_area()->pack_start(e_name);
    get_content_area()->pack_start(add_dot_button);
    get_content_area()->pack_start(fill_button);

    // Adding a "close" button to the bottom of the dialog
    add_button("_Close", Gtk::RESPONSE_CLOSE);
    signal_response().connect(sigc::mem_fun(*this, &AddObjectDialog::on_dialog_response));

  // Setting Buttons function
    add_dot_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::on_add_dot_button_clicked));
    fill_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::on_fill_button_clicked));

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
  case Gtk::RESPONSE_DELETE_EVENT:
    new_poly.set_nome(e_name.get_text());
    new_poly.set_id(canvas.get_last_id()+1);
    canvas.add_poligono(new_poly);
    log.get_buffer()->set_text(log.get_buffer()->get_text()
                               +"Polígono '"
                               +new_poly.get_nome()
                               +"' adicionado\n");
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
    new_poly.add_ponto(Ponto(atof(e_x.get_text().c_str()),
                       atof(e_y.get_text().c_str())));
    log.get_buffer()->set_text(log.get_buffer()->get_text()
                               +"Ponto adicionado na coordenada ("
                               +e_x.get_text()
                               +","
                               +e_y.get_text()
                               +")\n");
}

/*  Fill Object function
 *  Set the attrbute filled from polygon
 */
void AddObjectDialog::on_fill_button_clicked() {
    if(new_poly.get_filled()) {
        new_poly.set_filled(false);
        log.get_buffer()->set_text(log.get_buffer()->get_text()
                                   +"O Polígono não será preenchido\n");
    }
    else {
        new_poly.set_filled(true);
        log.get_buffer()->set_text(log.get_buffer()->get_text()
                                   +"O Polígono será preenchido\n");
    }
}
	 	  	 	    	 	    		    	    	  	 	
