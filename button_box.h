#ifndef GTKMM_BUTTONBOX_H
#define GTKMM_BUTTONBOX_H

#include <gtkmm.h>

class ButtonBox : public Gtk::Frame {
    public:
        ButtonBox(bool horizontal,
             const Glib::ustring& title,
             gint spacing,
             Gtk::ButtonBoxStyle layout);

    protected:
        Gtk::Button button_up, button_down, button_left, button_right;

        //Signal handlers:
        void on_button_clicked(Glib::ustring data);
};

#endif //GTKMM_BUTTONBOX_H
