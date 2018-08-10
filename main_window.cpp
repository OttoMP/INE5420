#include "main_window.h"
#include "window_menu.h"
#include <iostream>

MainWindow::MainWindow()
  : b_menu(Gtk::ORIENTATION_VERTICAL),
    b_view(Gtk::ORIENTATION_VERTICAL),
    b_objects(Gtk::ORIENTATION_VERTICAL),
    f_window_menu("Window"),
    f_view("Viewport"),
    f_log("Log"),
    bt_box(Gtk::ORIENTATION_VERTICAL),
    add_objects("New Object"),
    rm_objects("Remove"),
    transfer_poly("Novo Polígono")
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

  // Left area contains application menu
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

void MainWindow::fill_buffer() {
  buffer_log = Gtk::TextBuffer::create();
  buffer_log->set_text("Ready to type");
}

void MainWindow::create_window_menu() {
  // Include Move buttons
    f_window_menu.set_border_width(10);
    f_window_menu.add(bt_box);
    bt_box.pack_start(*Gtk::manage(
              new WindowMenu(false, "Move Buttons", 5,
                  Gtk::BUTTONBOX_START, canvas)),
          Gtk::PACK_EXPAND_WIDGET);
}

void MainWindow::create_objects_viewer() {
  // Object Viewer Buttons
    b_objects.pack_start(b_add_rm_objects, Gtk::PACK_SHRINK, 0);
    b_add_rm_objects.add(add_objects);
    b_add_rm_objects.add(rm_objects);

  // Objects Viewer Configurations
    w_objects.set_border_width(5);
    w_objects.add(view_objects);
    w_objects.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    b_objects.set_border_width(10);
    b_objects.pack_start(w_objects, Gtk::PACK_SHRINK, 0);

  // Create the Tree model:
    ref_view_objects = Gtk::ListStore::create(m_Columns);
    view_objects.set_model(ref_view_objects);

  // Add the TreeView's view columns:
  // This number will be shown with the default numeric formatting.
    view_objects.append_column("ID", m_Columns.m_col_id);
    view_objects.append_column("Name", m_Columns.m_col_name);
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

  // Log Buffers
    fill_buffer();
    text_log.set_buffer(buffer_log);
}


// ---------BUTTONS CLICKED FUNCTIONS-------

void MainWindow::on_add_objects_clicked() {
    std::cout << "Add Object" << std::endl;
    std::cout << transfer_poly.get_nome() << std::endl;
    Poligono new_polygon = add_object_dialog();
    std::cout << new_polygon.get_nome() << std::endl;
    std::cout << new_polygon.get_nome() << std::endl;
    int id = canvas.add_poligono(new_polygon);
    // Fill the TreeView's model

    Gtk::TreeModel::Row row = *(ref_view_objects->append());
    row[m_Columns.m_col_id] = id;
    row[m_Columns.m_col_name] = new_polygon.get_nome();
}	 	  	 	    	 	    		    	    	  	 	

void MainWindow::on_rm_objects_clicked(int ID) {
    std::cout << "Rm Object" << std::endl;
    //canvas.rm_object();
//    gtk_list_store_remove(view_objects, 0);
}

Poligono MainWindow::add_object_dialog() {
    Poligono new_polygon("?");
    AddObjectDialog dialog(new_polygon);
    dialog.run();
    return new_polygon;
}
