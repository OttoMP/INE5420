#include "main_window.h"
#include "window_menu.h"
#include "object_menu.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

MainWindow::MainWindow()
  : b_menu(Gtk::ORIENTATION_VERTICAL),
    b_view(Gtk::ORIENTATION_VERTICAL),
    b_application_menu(Gtk::ORIENTATION_VERTICAL),
    f_view("Viewport"),
    b_view_changes(Gtk::ORIENTATION_HORIZONTAL),
    view_rb_parallel("Parallel"),
    view_rb_perspective("Perspective"),
    slider_adjustment(Gtk::Adjustment::create(120.0, 60.0, 151.0,
                                                0.1,  1.0,   1.0)),
    slider_angle(slider_adjustment, Gtk::ORIENTATION_HORIZONTAL),
    f_log("Log"),
    b_window_menu(Gtk::ORIENTATION_VERTICAL)
{
  // Main Window Configurations
    set_title("Main Window");
    set_border_width(5);
    set_default_size(1024,768);

  // Divide Main Window in two areas
    add(main_pane);

  // Populate Main Window
    create_viewport();
    create_application_menu();
    create_log();

  // Left area contains object viewer and application menu
  // Right area contains viewport and log
    main_pane.add1(b_menu);
    main_pane.add2(b_view);

  // Include child widgets in left area
    b_menu.pack_start(b_application_menu, Gtk::PACK_EXPAND_WIDGET, 10);

  // Include child widgets in right area
    b_view.pack_start(f_view, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view.pack_start(b_view_changes, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view.pack_start(f_log, Gtk::PACK_EXPAND_WIDGET, 10);

  // Button functions

  // The final step is to display this newly created widget
    show_all_children();

}

MainWindow::~MainWindow() {}

void MainWindow::create_application_menu() {
    auto object_viewer = Gtk::manage(new ObjectViewer(canvas, text_log));
    b_menu.pack_start(*object_viewer, Gtk::PACK_EXPAND_WIDGET, 10);

    b_application_menu.set_border_width(10);

  // Include Move buttons
    b_application_menu.pack_start(b_window_menu);
    b_window_menu.pack_start(*Gtk::manage(
              new WindowMenu("Window Menu", 5, canvas)),
          Gtk::PACK_EXPAND_WIDGET);

  // Include Object Functions
    b_application_menu.pack_start(b_object_menu);
    b_object_menu.pack_start(*Gtk::manage(
              new ObjectMenu(
                  "Object Menu", 5, canvas, text_log, *object_viewer)),
          Gtk::PACK_EXPAND_WIDGET);
}

void MainWindow::create_viewport() {
  // Include canvas in viewport
    f_view.set_border_width(10);
    f_view.add(canvas);

    view_rb_perspective.join_group(view_rb_parallel);

    view_rb_parallel.set_active();

    b_view_changes.set_spacing(5);
    b_view_changes.pack_start(view_rb_parallel, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view_changes.pack_start(view_rb_perspective, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view_changes.pack_start(slider_angle, Gtk::PACK_EXPAND_WIDGET, 10);
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

