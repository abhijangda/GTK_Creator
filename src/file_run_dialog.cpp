//40 Lines
#include"file_run_dialog.h"

file_run_dialog::file_run_dialog(Gtk::Window& _parent)
: Gtk::Dialog("Run Program",_parent,false,true),lbl_curr_dir("Current Directory"),lbl_args("Arguments"),lbl_envs("Environment Variables"),
chk_run_on_ext_console("Run on console"),cmd_curr_dir("...")
{
    fixed.put(lbl_curr_dir,11,10);
    lbl_curr_dir.set_size_request(121,21);
    
    fixed.put(entry_curr_dir,164,10);
    entry_curr_dir.set_size_request(360,31);
    
    fixed.put(cmd_curr_dir,530,10);
    cmd_curr_dir.set_size_request(49,29);
    
    fixed.put(lbl_args,11,50);
    lbl_args.set_size_request(101,21);
    
    fixed.put(entry_args,165,50);
    entry_args.set_size_request(405,31);
    
    fixed.put(lbl_envs,11,86);
    lbl_envs.set_size_request(151,21);
    
    fixed.put(txt_envs,165,90);
    txt_envs.set_size_request(404,131);
    
    fixed.put(chk_run_on_ext_console,11,229);
    chk_run_on_ext_console.set_size_request(131,26);
    chk_run_on_ext_console.set_active(true);
    
    Gtk::Button* cmd_run  = add_button("Run",1);
    Gtk::Button* cmd_cancel = add_button("Cancel",0);
    
    Gtk::VBox *dialog_vbox = get_vbox();
    dialog_vbox->pack_start(fixed);
    }
file_run_dialog::~file_run_dialog()
{
    }