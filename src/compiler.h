//41 Lines
#include<string>
#include<iostream>
#include"project_class.h"
#include"file_run_dialog.h"

#ifndef COMPILER_WIN_H
#define COMPILER_WIN_H

class OutputModelColumn : public Gtk::TreeModel::ColumnRecord
{
    public:
    OutputModelColumn(){add(m_col);}
    Gtk::TreeModelColumn<Glib::ustring> m_col;
    };
class compiler_win : public Gtk::Dialog
{
    public:
        compiler_win(Gtk::Window& _parent, std::string _command,std::string _mode,project_class& );
        ~compiler_win();        
        
        void compile(std::string source_path);
        void run_and_compile(std::string source_path,std::string);
        void run_and_compile(project_class& _proj,std::string);
        Gtk::TreeView list_view_output;
        OutputModelColumn out_columns;
    private:
        std::string compiled_path,command,mode;
        project_class& current_proj;
        void cmdRun_clicked();
        void cmdCancel_clicked();
        Gtk::Label lbl_compiler,lbl_compiler_name,lbl_source,lbl_source_name,lbl_destination,lbl_destination_name;
        
        Gtk::ScrolledWindow scrollwin;
        Glib::RefPtr<Gtk::ListStore> tree_model_output;
        Gtk::Frame frame;
        Gtk::Button cmdRun,cmdCancel;
        Gtk::HBox hbox_compiler,hbox_source,hbox_destination;
        Gtk::VBox vbox;
    }; 
#endif