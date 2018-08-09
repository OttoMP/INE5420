#include "dialog_add_object.h"
#include <iostream>

AddObjectDialog::AddObjectDialog(Poligono& poly_from_window)
    : new_poly{poly_from_window},
      l_x("Coordenada x"),
      l_y("Coordenada y"),
      l_name("Nome do Objeto"),
      add_Dot_button("Adicionar Ponto")
{
    set_title("Adicionar Objeto");
    set_border_width(0);
    set_size_request(300, 300);

    get_content_area()->pack_start(l_x);
    get_content_area()->pack_start(e_x);
    get_content_area()->pack_start(l_y);
    get_content_area()->pack_start(e_y);
    get_content_area()->pack_start(l_name);
    get_content_area()->pack_start(e_name);
    get_content_area()->pack_start(add_Dot_button);

    /* Add a "close" button to the bottom of the dialog */
    add_button("_Close", Gtk::RESPONSE_CLOSE);
    signal_response().connect(sigc::mem_fun(*this, &AddObjectDialog::on_dialog_response));

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


void AddObjectDialog::on_dialog_response(int response_id) {
    switch (response_id)
  {
  case Gtk::RESPONSE_CLOSE:
  case Gtk::RESPONSE_DELETE_EVENT:
    hide();
    break;
  default:
    std::cout << "Unexpected response_id=" << response_id << std::endl;
    break;
  };
}

void AddObjectDialog::on_add_Dot_button_clicked() {
    int x, y;
    string nome;

    x = atoi(e_x.get_text().c_str());
    y = atoi(e_y.get_text().c_str());
    nome = e_name.get_text();

    new_poly.addPonto(x, y);
    new_poly.setNome(nome);
}
