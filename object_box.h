//52 Lines
#include<gtkmm/treeview.h>
#include<gtkmm/box.h>
#include<gtkmm/treeiter.h>
#include<gtkmm/treemodel.h>
#include<gtkmm/treestore.h>
#include<gtkmm/scrolledwindow.h>
#include<gtkmm/frame.h>

#include<string>
//#include<iostream>

#ifndef OBJECT_BOX_H
#define OBJECT_BOX_H

typedef Gtk::TreeModel::Children::iterator  GtkTreeChildIter;
class ModelColumns1 : public Gtk::TreeModel::ColumnRecord
{
    public:
        ModelColumns1(){add(col_object);add(col_class);} 
        Gtk::TreeModelColumn<std::string> col_object;
        Gtk::TreeModelColumn<std::string> col_class;
    };

class ObjectBox : public Gtk::VBox
{
    public:
        ObjectBox();
        ~ObjectBox();
        
        void add_parent_row(std::string,std::string);
        void add_child_row(std::string,std::string,std::string);    
        
        std::string get_name(std::string);
        Gtk::TreeView tree_view;
        Glib::RefPtr<Gtk::TreeStore> tree_model;
        Gtk::TreeModel::Row parent_row;
        Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
        
        GtkTreeChildIter get_iter_from_string(GtkTreeChildIter iter, std::string);        
        
        ModelColumns1 model_columns;      
        void set_selection_from_widget(Gtk::Widget&,std::string);  
        void change_name(std::string,std::string);
        std::string get_current_name();
        void delete_child_rows(std::string parent_name);
        void remove_child_row(std::string child_name, std::string parent_name);
        protected:
            virtual bool on_mouse_released(GdkEventButton *event){return true;}
        private:            
            Gtk::Widget* current_widget;
            GtkTreeChildIter iter_found;
            Gtk::Frame frame;
            Gtk::ScrolledWindow scroll_win;
    };
#endif
