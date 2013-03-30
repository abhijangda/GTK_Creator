//79 Lines
#include<gtkmm.h>
#include"project_class.h"

#ifndef PROJ_PREF_DIALOG_H	
#define PROJ_PREF_DIALOG_H

class FileModelColumns : public Gtk::TreeModel::ColumnRecord
{
    public:
    FileModelColumns(){add(m_col);}
    Gtk::TreeModelColumn<Glib::ustring> m_col;
    };

class EnvModelColumns : public Gtk::TreeModel::ColumnRecord
{
    public:
    EnvModelColumns(){add(m_col_name);add(m_col_value);}
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_value;
    };

class proj_pref_dialog : public Gtk::Dialog
{
    public:
        proj_pref_dialog(Gtk::Window& _parent,project_class&);
        ~proj_pref_dialog();
        
        project_class& current_proj;
        Gtk::Fixed fixed_general,fixed_compiler;
        Gtk::Fixed fixed_execution;
        Gtk::Notebook notebook;
        Gtk::Label lbl_name,lbl_type,lbl_files,lbl_proj_type;
        Gtk::Label lbl_gcc,lbl_gcc_other_args;
        Gtk::Entry entry_name,entry_command,entry_symbols;
        Gtk::Entry entry_other_args;
        Gtk::TreeView list_view_file,list_view_dir,list_view_env_var;
        FileModelColumns file_columns,dir_columns;
        EnvModelColumns env_columns;
        Glib::RefPtr<Gtk::ListStore> file_tree_model, dir_tree_model,env_tree_model;      
          
        Gtk::CheckButton chk_compile_only, chk_warning, chk_inline;
        Gtk::CheckButton chk_support_89, chk_compile_assemble;
        Gtk::CheckButton chk_optimize, chk_add_dir, chk_symbols;
        Gtk::SpinButton spin_optimize;
        Gtk::Button cmd_add_file, cmd_rem_file, cmd_ren_file;
        Gtk::Button cmd_rem_all;
        Gtk::Button cmd_add_dir, cmd_rem_dir;
        Gtk::Button cmd_add_env, cmd_rem_env;
        Gtk::Label lbl_out_dir, lbl_param,lbl_curr_dir;
        Gtk::Label lbl_env_var;
        Gtk::Entry entry_out_dir,entry_param,entry_curr_dir;
        Gtk::CheckButton chk_ext_console;
        Gtk::Button* cmd_cancel, *cmd_ok;
        
    private:
        void load_preferences();
        void on_chk_toggled(Gtk::Widget&);
        void cmd_add_file_clicked();
        void cmd_rem_file_clicked();
        void cmd_ren_file_clicked();
        void cmd_rem_all_clicked();
        
        void cmd_add_dir_clicked();
        void cmd_rem_dir_clicked();
        
        void cmd_add_env_clicked();
        void cmd_rem_env_clicked();
        
        void on_chk_compile_only_toggled();
        void on_chk_warning_toggled();
        void on_chk_inline_toggled();
        void on_chk_support_89_toggled();
        void on_chk_compile_assemble_toggled();
        void on_chk_add_dir_toggled();
        void on_chk_symbols_toggled();
        void on_chk_optimize_only_toggled();
    };

#endif