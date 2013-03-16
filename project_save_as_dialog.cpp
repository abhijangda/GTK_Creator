//23 Lines
#include"project_save_as_dialog.h"

project_save_as_dialog::project_save_as_dialog(Gtk::Window& _parent)
: Gtk::Dialog("Save Project As", _parent,false,true),lbl_name("Project Name"),lbl_location("Location"),hbox_name(false,2),hbox_location(false,2)
{
    hbox_name.pack_start(lbl_name,Gtk::PACK_SHRINK,5);
    hbox_name.pack_start(entry_name,Gtk::PACK_EXPAND_WIDGET,5);
    
    hbox_location.pack_start(lbl_location,Gtk::PACK_SHRINK,5);
    hbox_location.pack_start(entry_location,Gtk::PACK_EXPAND_WIDGET,5);
    
    Gtk::VBox *dialog_vbox = get_vbox();
    dialog_vbox->pack_start(hbox_name);
    dialog_vbox->pack_start(hbox_location);
    
    Gtk::Button* cmd_save_as = add_button("Save As",1);
    Gtk::Button* cmd_cancel = add_button("Cancel",0);
    }

project_save_as_dialog::~project_save_as_dialog()
{
    }
