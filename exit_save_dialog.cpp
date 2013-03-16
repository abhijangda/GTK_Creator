//26 Lines
#include"exit_save_dialog.h"

exit_save_dialog::exit_save_dialog(Gtk::Window& _parent,std::vector<std::string>& file_name_vector)
:vector_check_button(0),Gtk::Dialog("",_parent)
{
    lbl_not_saved.set_label("Following files are not saved. Select files you want to save before closing.");
    
    Gtk::VBox* dialog_vbox = get_vbox();
    dialog_vbox->pack_start(lbl_not_saved);
    
    for(int i = 0;i<file_name_vector.size();i++)
    {
        Gtk::CheckButton* chk = new Gtk::CheckButton(file_name_vector[i]);
        vector_check_button.insert(vector_check_button.end(),chk);
        dialog_vbox->pack_start(*chk);
        }
    Gtk::Button* cmd_close_without_saving = add_button("Close without saving",1);
    Gtk::Button* cmd_cancel = add_button("Cancel",0);
    Gtk::Button* cmd_save = add_button("Save",2);
    }

exit_save_dialog::~exit_save_dialog()
{
    for(int i = 0;i <vector_check_button.size();i++)
        delete vector_check_button[i];
    }