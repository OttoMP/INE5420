#include "main_window.h"
#include "window_menu.h"
#include <iostream>

MainWindow::MainWindow()
  : b_menu(Gtk::ORIENTATION_VERTICAL),
    b_view(Gtk::ORIENTATION_VERTICAL),
    b_objects(Gtk::ORIENTATION_VERTICAL),
    f_window_menu("Viewport Options"),
    f_view("Viewport"),
    f_log("Log"),
    bt_box(Gtk::ORIENTATION_VERTICAL),
    add_objects("New Object"),
    rm_objects("Remove")
{
  // Main Window Configurations
    set_title("Main Window");
    set_border_width(5);
    set_default_size(1024,768);

  // Divide Main Window in two areas
    add(main_pane);

  // Populate Main Window
    create_viewport();
    create_window_menu();
    create_objects_viewer();
    create_log();

  // Left area contains object viewer and application menu
  // Right area contains viewport and log
    main_pane.add1(b_menu);
    main_pane.add2(b_view);

  // Include child widgets in left area
    b_menu.pack_start(b_objects, Gtk::PACK_EXPAND_WIDGET, 10);
    b_menu.pack_start(f_window_menu, Gtk::PACK_EXPAND_WIDGET, 10);

  // Include child widgets in right area
    b_view.pack_start(f_view, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view.pack_start(f_log, Gtk::PACK_EXPAND_WIDGET, 10);

  // Button functions
    add_objects.signal_clicked().connect(
              sigc::mem_fun(*this, &MainWindow::on_add_objects_clicked));
    rm_objects.signal_clicked().connect(sigc::bind<int>(
              sigc::mem_fun(*this, &MainWindow::on_rm_objects_clicked), 0));

  // The final step is to display this newly created widget
    show_all_children();

}

MainWindow::~MainWindow() {}

void MainWindow::create_window_menu() {
  // Include Move buttons
    f_window_menu.set_border_width(10);
    f_window_menu.add(bt_box);
    bt_box.pack_start(*Gtk::manage(
              new WindowMenu("Move Buttons", 5, canvas)),
          Gtk::PACK_EXPAND_WIDGET);
}

void MainWindow::create_objects_viewer() {
  // Object Viewer Buttons
    b_objects.pack_start(b_add_rm_objects, Gtk::PACK_SHRINK, 0);
    b_add_rm_objects.add(add_objects);
    b_add_rm_objects.add(rm_objects);

  // Objects Viewer Configurations
    w_objects.set_border_width(5);
    w_objects.add(object_viewer);
    w_objects.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    b_objects.set_border_width(10);
    b_objects.pack_start(w_objects, Gtk::PACK_SHRINK, 0);
}

void MainWindow::create_viewport() {
  // Include canvas in viewport
    f_view.set_border_width(10);
    f_view.add(canvas);
}

void MainWindow::create_log() {
  // Log Configurations
    w_log.set_border_width(5);
    w_log.add(text_log);
    w_log.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    f_log.set_border_width(10);
    f_log.add(w_log);
    text_log.set_editable(false);

    text_log.get_buffer()->set_text("Waiting for instructions...\n");
}


// ---------BUTTONS CLICKED FUNCTIONS-------

void MainWindow::on_add_objects_clicked() {
    AddObjectDialog dialog(canvas, text_log);
    dialog.run();

    int id = canvas.get_last_id();
    std::string name = canvas.get_last_name();

    auto row = Gtk::manage(new Gtk::ListBoxRow);
    auto label = Gtk::manage(new Gtk::Label);
    label->set_text(std::to_string(id)+" "+name);
    row->add(*label);
    row->show_all_children();
    object_viewer.append(*row);
    row->show();
}

void MainWindow::on_rm_objects_clicked(int ID) {
    object_viewer.remove(*object_viewer.get_selected_row());
    //std::cout << object_viewer.get_selected_row()->get_children()[0]->get_text() << std::endl;


    //canvas.rm_object();
//    gtk_list_store_remove(view_objects, 0);
}
