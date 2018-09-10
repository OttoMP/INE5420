#include "object_viewer.h"

ObjectViewer::ObjectViewer(
             Canvas& canvas,
             Gtk::TextView& text_log)
    : bt_add_objects("New Object"),
      bt_rm_objects("Remove"),
      canvas_ref(canvas),
      text_log_ref(text_log)
{
    set_orientation(Gtk::ORIENTATION_VERTICAL);
  // Object Viewer Buttons
    pack_start(b_add_rm_objects, Gtk::PACK_SHRINK, 0);
    b_add_rm_objects.add(bt_add_objects);
    b_add_rm_objects.add(bt_rm_objects);

  // Objects Viewer Configurations
    w_objects.set_border_width(5);
    w_objects.add(object_viewer);
    w_objects.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    set_border_width(10);
    pack_start(w_objects, Gtk::PACK_SHRINK, 0);

  // Button functions
    bt_add_objects.signal_clicked().connect(
              sigc::mem_fun(*this, &ObjectViewer::on_add_objects_clicked));
    bt_rm_objects.signal_clicked().connect(
              sigc::mem_fun(*this, &ObjectViewer::on_rm_objects_clicked));


}

// ---------BUTTONS CLICKED FUNCTIONS-------

void ObjectViewer::on_add_objects_clicked() {
    AddObjectDialog dialog(canvas_ref, text_log_ref);
    dialog.run();

    int id = canvas_ref.get_last_id();
    std::string name = canvas_ref.get_last_name();

    if(id != 0) {
        auto row = Gtk::manage(new Gtk::ListBoxRow);
        auto label = Gtk::manage(new Gtk::Label);
        label->set_text(std::to_string(id)+" "+name);
        label->set_name(label->get_text());
        row->add(*label);
        row->show_all_children();
        object_viewer.append(*row);
        row->show();
    }
}

void ObjectViewer::on_rm_objects_clicked() {
    if (object_viewer.get_selected_row() == nullptr) {
        text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                   +"Nenhum objeto selecionado\n");
        return;
    }
    canvas_ref.rm_objeto(get_selected_object_id());
    text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                       +"Polígono '"
                                       +get_selected_object_name()
                                       +"' removido\n");
    object_viewer.remove(*object_viewer.get_selected_row());
}

std::string ObjectViewer::get_selected_object_name() {
    using namespace std;
    if (object_viewer.get_selected_row() == nullptr) {
        text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                   +"Nenhum objeto selecionado\n");
        return "";
    }
    string name =object_viewer.get_selected_row()->get_child()->get_name();

    istringstream iss(name);
    vector<string> info;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(info));

    string full_name;

    for(auto i = 1; i < info.size(); i++) {
        if(i == info.size()-1)
            full_name += info[i];
        else
            full_name += info[i]+" ";
    }

    return full_name;
}

int ObjectViewer::get_selected_object_id() {
    using namespace std;
    if (object_viewer.get_selected_row() == nullptr) {
        text_log_ref.get_buffer()->set_text(text_log_ref.get_buffer()->get_text()
                                   +"Nenhum objeto selecionado\n");
        return 0;
    }

    string name =object_viewer.get_selected_row()->get_child()->get_name();

    istringstream iss(name);
    vector<string> info;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(info));

    string id = info[0];

    return atoi(id.c_str());
}
