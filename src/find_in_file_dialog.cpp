//43 lines
#include"find_in_file_dialog.h"

find_in_file_dialog::find_in_file_dialog(Gtk::Window& _parent)
: Gtk::Dialog("Find In File",_parent),lbl_file("File  "),lbl_find("Find"),cmd_close("Close"),cmd_search("Search"),hbox_file(false,5),hbox_find(false,5)
{
    hbox_file.pack_start(lbl_file,Gtk::PACK_SHRINK);
    hbox_file.pack_start(entry_file,Gtk::PACK_EXPAND_WIDGET);
    
    hbox_find.pack_start(lbl_find,Gtk::PACK_SHRINK);
    hbox_find.pack_start(entry_find,Gtk::PACK_EXPAND_WIDGET);
    
    Gtk::VBox *dialog_vbox = get_vbox();
    dialog_vbox->pack_start(hbox_file);
    dialog_vbox->pack_start(hbox_find);
    dialog_vbox->pack_start(lbl_status);
    
    Gtk::ButtonBox *dialog_button_box = get_action_area();
    dialog_button_box->pack_start(cmd_close);
    dialog_button_box->pack_start(cmd_search);
    
    cmd_search.signal_clicked().connect(sigc::mem_fun(*this,&find_in_file_dialog::cmd_search_clicked));
    cmd_close.signal_clicked().connect(sigc::mem_fun(*this,&find_in_file_dialog::cmd_close_clicked));
    
    set_size_request(400,125);
    }

void find_in_file_dialog::cmd_search_clicked()
{
    Glib::ustring str = Glib::file_get_contents(entry_file.get_text());
    if(str.find(entry_find.get_text())!=Glib::ustring::npos)
         lbl_status.set_label("Found");
    else
        lbl_status.set_label("Not Found");
    }

void find_in_file_dialog::cmd_close_clicked()
{
    destroy_();
    }

find_in_file_dialog::~find_in_file_dialog()
{
    }