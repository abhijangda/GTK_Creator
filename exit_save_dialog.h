//15 Lines
#include<gtkmm.h>

#ifndef EXIT_SAVE_DIALOG_H
#define EXIT_SAVE_DIALOG_H

class exit_save_dialog : public Gtk::Dialog
{
    public:
        exit_save_dialog(Gtk::Window& _parent,std::vector<std::string>&);
        ~exit_save_dialog();
        
        Gtk::Label lbl_not_saved;
        std::vector<Gtk::CheckButton*> vector_check_button;
    };
#endif