#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/paned.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/window.h>

#include "window_menu.h"
#include "canvas.h"

class MainWindow : public Gtk::Window {

    public:
        MainWindow();
        virtual ~MainWindow();

    protected:
      // Main Window configuration
        Gtk::Paned                          main_pane;
        Gtk::Box                            b_menu, b_view;

      // Objects selection
        Gtk::Frame                          f_objects;
        Gtk::ScrolledWindow                 w_objects;
        Gtk::TreeView                       view_objects;
        Glib::RefPtr<Gtk::ListStore>        ref_view_objects;
      // TreeView
      //// Tree model columns:
      class ModelColumns : public Gtk::TreeModel::ColumnRecord {
          public:

            ModelColumns()
            { add(m_col_id); add(m_col_name);;}

            Gtk::TreeModelColumn<unsigned int> m_col_id;
            Gtk::TreeModelColumn<Glib::ustring> m_col_name;
      };

      ModelColumns m_Columns;

      // Button Menu
        Gtk::Box                            bt_box;
        Gtk::Frame                          f_window_menu;

      // Viewport
        Gtk::Frame                          f_view;
        Canvas                              canvas;

      // Log
        void fill_buffer();
        Gtk::Frame                          f_log;
        Gtk::ScrolledWindow                 w_log;
        Gtk::TextView                       text_log;
        Glib::RefPtr<Gtk::TextBuffer>       buffer_log;
};

#endif // MAIN_WINDOW_H
