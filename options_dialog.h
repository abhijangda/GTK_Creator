//64 Lines
#include<gtkmm.h>
#include"helper_functions.h"

#ifndef OPTIONS_DIALOG_H
#define OPTIONS_DIALOG_H

class DirModelColumns : public Gtk::TreeModel::ColumnRecord
{
    public:
    DirModelColumns(){add(m_col);}
    Gtk::TreeModelColumn<Glib::ustring> m_col;
    };

class options_dialog : public Gtk::Dialog
{
    public:
        options_dialog(Gtk::Window& _parent,std::string command);
        ~options_dialog();
        
        Gtk::Notebook notebook;
        Gtk::Fixed fixed_general, fixed_compiler;
        Gtk::CheckButton chk_indentation, chk_auto_save;
        Gtk::CheckButton chk_word_wrap, chk_recent_projects;
        Gtk::CheckButton chk_recent_files, chk_line_numbers;
        Gtk::CheckButton chk_code_completion, chk_highlight_line;
        Gtk::Label lbl_indentation, lbl_auto_save,lbl_tab;
        Gtk::RadioButton rb_current, rb_all;
        Gtk::SpinButton sb_tab_width, sb_indent_width, sb_auto_save_time;
        Gtk::RadioButtonGroup rb_auto_save_group;
        
        Gtk::Label lbl_gcc,lbl_gcc_other_args;
        Gtk::Entry entry_command,entry_symbols,entry_other_args;
        Gtk::TreeView list_view_dir;
        Gtk::CheckButton chk_compile_only, chk_warning, chk_inline;
        Gtk::CheckButton chk_support_89, chk_compile_assemble;
        Gtk::CheckButton chk_optimize, chk_add_dir, chk_symbols;
        Gtk::SpinButton spin_optimize;
        Gtk::Button cmd_add_dir, cmd_rem_dir;
        
        DirModelColumns dir_columns;
         Glib::RefPtr<Gtk::ListStore> dir_tree_model;
    private:
        void on_chk_toggled(Gtk::Widget&);
        
        void cmd_add_dir_clicked();
        void cmd_rem_dir_clicked();
        
        void on_chk_indent_toggled();
        void on_chk_auto_save_toggled();
        
        void on_chk_compile_only_toggled();
        void on_chk_warning_toggled();
        void on_chk_inline_toggled();
        void on_chk_support_89_toggled();
        void on_chk_compile_assemble_toggled();
        void on_chk_add_dir_toggled();
        void on_chk_symbols_toggled();
        void on_chk_optimize_only_toggled();
        void load_options();
    };

#endif