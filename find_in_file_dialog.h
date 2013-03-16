//24 lines
#include<gtkmm/dialog.h>
#include<gtkmm/entry.h>
#include<gtkmm/label.h>
#include<gtkmm/button.h>

#ifndef FIND_IN_FILE_DIALOG_H
#define FIND_IN_FILE_DIALOG_H

class find_in_file_dialog : public Gtk::Dialog
{
    public:
        find_in_file_dialog(Gtk::Window&);
        ~find_in_file_dialog();
    
    private:
        void cmd_search_clicked();
        void cmd_close_clicked();
        Gtk::Label lbl_file,lbl_status,lbl_find;
        Gtk::Entry entry_file,entry_find;
        Gtk::Button cmd_close,cmd_search;
        Gtk::HBox hbox_file, hbox_find;
    };

#endif