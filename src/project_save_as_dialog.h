//17 Lines
#include<gtkmm/dialog.h>
#include<gtkmm/entry.h>
#include<gtkmm/label.h>

#ifndef PROJECT_SAVE_AS_DIALOG
#define PROJECT_SAVE_AS_DIALOG

class project_save_as_dialog : public Gtk::Dialog
{
    public:
        project_save_as_dialog(Gtk::Window&);
        ~project_save_as_dialog();
        Gtk::HBox hbox_name,hbox_location;
        Gtk::Entry entry_name,entry_location;
        Gtk::Label lbl_name,lbl_location;
    };
#endif