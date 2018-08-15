#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

#include "window_menu.h"
#include "canvas.h"
#include "poligono.h"
#include "dialog_add_object.h"

class MainWindow : public Gtk::Window {

    public:
        MainWindow();
        virtual ~MainWindow();

    protected:
      // Main Window configuration
        Gtk::Paned                          main_pane;
        Gtk::Box                            b_menu, b_view;

      // Object Viewer Widgets
        void create_objects_viewer();
        void on_add_objects_clicked();
        void on_rm_objects_clicked(int ID);
        Gtk::Button                         add_objects;
        Gtk::Button                         rm_objects;
        Gtk::ButtonBox                      b_add_rm_objects;
        Gtk::Box                            b_objects;
        Gtk::ScrolledWindow                 w_objects;
        Gtk::ListBox                        object_viewer;

        // Button Menu
        void create_window_menu();
        Gtk::Box                            bt_box;
        Gtk::Frame                          f_window_menu;

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

