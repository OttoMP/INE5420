#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

#include "canvas.h"
#include "poligono.h"
#include "dialog_add_object.h"
#include "object_viewer.h"

class MainWindow : public Gtk::Window {

    public:
        MainWindow();
        virtual ~MainWindow();

    protected:
      // Main Window configuration
        Gtk::Paned                          main_pane;
        Gtk::Box                            b_menu, b_view;

     // Application Menu
        void create_application_menu();
        Gtk::Box                            b_application_menu;
        Gtk::Box                            b_window_menu, b_object_menu;

      // Viewport
        void create_viewport();
        Gtk::Frame                          f_view;
        Canvas                              canvas;

      // Log
        void create_log();
        Gtk::Frame                          f_log;
        Gtk::ScrolledWindow                 w_log;
        Gtk::TextView                       text_log;
};

#endif // MAIN_WINDOW_H

