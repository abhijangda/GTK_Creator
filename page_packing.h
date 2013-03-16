//48 Lines
#include<gtkmm.h>
#include"frame.h"
#include"object_box.h"

#ifndef PAGE_PACKING_H
#define PAGE_PACKING_H

class Model__Column : public Gtk::TreeModel::ColumnRecord
{
    public:
        Model__Column(){add(col);} 
        Gtk::TreeModelColumn<std::string> col;
    };

class PagePacking : public Gtk::Table
{
    public:
        PagePacking(Frame&,ObjectBox&);
        ~PagePacking();
        void set_property_values(Gtk::Widget&, std::string, Gtk::Widget&);
        
    private:        
        Glib::RefPtr<Gtk::ListStore> cb_tree_model_expand;
        Model__Column model_column;
        
        Frame& frame;
        ObjectBox& object_box;
        std::vector<Gtk::Widget*>value_widget_vector;
        std::vector<Gtk::Widget*>label_vector;
        int label_vector_size;
        std::string type_of_parent;
        Gtk::Widget* parent;
        Gtk::Widget* current_widget;
        
        //gtk_vbox or gtk_hbox
        void cb_box_expand_changed();
        
        //gtk_fixed
        void sb_fixed_x_changed();
        void sb_fixed_y_changed();
        
        //gtk_table
        void cb_table_expand_changed();
        void cb_table_fill_changed();
    };
#endif
