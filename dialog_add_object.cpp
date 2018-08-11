#include "dialog_add_object.h"
#include <iostream>

AddObjectDialog::AddObjectDialog(Canvas& drawing_area)
    : canvas{drawing_area}, // Receive reference from parameter
      new_poly(""),
      l_x("Coordenada x"),        // Initialize Label for Entry
      l_y("Coordenada y"),
      l_name("Nome do Objeto"),
      add_Dot_button("Adicionar Ponto")
{
  // Setting configurations for dialog
    set_title("Adicionar Objeto");
    set_border_width(0);
    set_size_request(300, 300);

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
    get_content_area()->pack_start(add_Dot_button);

    // Adding a "close" button to the bottom of the dialog
    add_button("_Close", Gtk::RESPONSE_CLOSE);
    signal_response().connect(sigc::mem_fun(*this, &AddObjectDialog::on_dialog_response));

  // Setting Add Button function
    add_Dot_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AddObjectDialog::on_add_Dot_button_clicked));

  /* This makes it so the button is the default.
   * Simply hitting the "Enter" key will cause this button to activate. */
    set_default_response(Gtk::RESPONSE_CLOSE);

    show_all_children();
}

AddObjectDialog::~AddObjectDialog()
{
}

/*  Close button function
 *  when called close dialog
 */
void AddObjectDialog::on_dialog_response(int response_id) {
    switch (response_id)
  {
  case Gtk::RESPONSE_CLOSE:
  case Gtk::RESPONSE_DELETE_EVENT:
    new_poly.set_nome(e_name.get_text());
    new_poly.set_id(canvas.get_last_id()+1);
    canvas.add_poligono(new_poly);
    hide();
    break;
  default:
    std::cout << "Unexpected response_id=" << response_id << std::endl;
    break;
  };
}

/*  Add Object function
 *  Read the text from entrys and call function add_ponto from Poligono
 *  sending coordinates x and y
 */
void AddObjectDialog::on_add_Dot_button_clicked() {
    new_poly.add_ponto(atoi(e_x.get_text().c_str()),
                       atoi(e_y.get_text().c_str()));
}

