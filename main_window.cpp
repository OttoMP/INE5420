#include "main_window.h"
#include "button_box.h"
#include <iostream>

MainWindow::MainWindow()
    : b_menu(Gtk::ORIENTATION_VERTICAL),
      b_view(Gtk::ORIENTATION_VERTICAL),
      f_objects("Objects"),
      f_window_menu("Window"),
      f_view("Viewport"),
      f_log("Log")
{
    set_title("Main Window");
  // Sets the border width of the window.
    set_border_width(10);

    add(main_pane);

    main_pane.add1(b_menu);
    main_pane.add2(b_view);


  // Box functions
    b_menu.pack_start(f_objects, Gtk::PACK_EXPAND_WIDGET, 10);
    b_menu.pack_start(f_window_menu, Gtk::PACK_EXPAND_WIDGET, 10);

    b_view.pack_start(f_view, Gtk::PACK_EXPAND_WIDGET, 10);
    b_view.pack_start(f_log, Gtk::PACK_EXPAND_WIDGET, 10);

  // The final step is to display this newly created widget...
  show_all_children();

}

MainWindow::~MainWindow() {}
