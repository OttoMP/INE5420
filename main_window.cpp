#include "main_window.h"
#include "window_menu.h"
#include <iostream>

MainWindow::MainWindow()
  : b_menu(Gtk::ORIENTATION_VERTICAL),
    b_view(Gtk::ORIENTATION_VERTICAL),
    f_objects("Objects"),
    f_window_menu("Window"),
    f_view("Viewport"),
    f_log("Log"),
    bt_box(Gtk::ORIENTATION_VERTICAL)
{
  // Main Window Configurations
    set_title("Main Window");
    set_border_width(10);
    set_default_size(800,600);

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
    b_menu.pack_start(f_objects, Gtk::PACK_EXPAND_WIDGET, 10);
    b_menu.pack_start(f_window_menu, Gtk::PACK_EXPAND_WIDGET, 10);

  // Include child widgets in right area
    b_view.pack_start(f_view, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view.pack_start(f_log, Gtk::PACK_EXPAND_WIDGET, 10);

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
    f_window_menu.add(bt_box);
    bt_box.pack_start(*Gtk::manage(
              new WindowMenu(false, "Directionals", 10,
                  Gtk::BUTTONBOX_SPREAD, canvas)),
          Gtk::PACK_EXPAND_WIDGET);
}

void MainWindow::create_objects_viewer() {
  // Objects Viewer Configurations
    w_objects.add(view_objects);
    w_objects.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    f_objects.add(w_objects);

  // Create the Tree model:
    ref_view_objects = Gtk::ListStore::create(m_Columns);
    view_objects.set_model(ref_view_objects);

  // Fill the TreeView's model
    Gtk::TreeModel::Row row = *(ref_view_objects->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "Billy Bob";

  // Add the TreeView's view columns:
  // This number will be shown with the default numeric formatting.
    view_objects.append_column("ID", m_Columns.m_col_id);
    view_objects.append_column("Name", m_Columns.m_col_name);
}

void MainWindow::create_viewport() {
  // Include canvas in viewport
    f_view.add(canvas);
}

void MainWindow::create_log() {
  // Log Configurations
    w_log.add(text_log);
    w_log.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    f_log.add(w_log);

  // Log Buffers
    fill_buffer();
    text_log.set_buffer(buffer_log);
}
