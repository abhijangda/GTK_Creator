//20 Lines
#include<gtkmm.h>

#ifndef FILE_RUN_DIALOG_H
#define FILE_RUN_DIALOG_H

class file_run_dialog : public Gtk::Dialog
{
    public:
        file_run_dialog(Gtk::Window& _parent);
        ~file_run_dialog();
        
        Gtk::Fixed fixed;
        Gtk::Label lbl_curr_dir,lbl_args,lbl_envs;
        Gtk::Entry entry_curr_dir,entry_args;
        Gtk::TextView txt_envs;
        Gtk::CheckButton chk_run_on_ext_console;
        Gtk::Button cmd_curr_dir;
    };

#endif