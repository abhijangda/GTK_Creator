//185 Lines
#include"page_packing.h"
#include"gtk_fixed.h"
#include"gtk_vbox.h"
#include"gtk_hbox.h"
#include"gtk_table.h"
    
PagePacking::PagePacking(Frame& _frame, ObjectBox& _object_box)
    : Gtk::Table(1,2,false),frame(_frame), object_box(_object_box),label_vector_size(0), label_vector(10),value_widget_vector(10),type_of_parent("")
{
    cb_tree_model_expand=Gtk::ListStore::create(model_column);
    Gtk::TreeModel::Row row = *(cb_tree_model_expand->append());
    row[model_column.col] = "TRUE";
    row = *(cb_tree_model_expand->append());
    row[model_column.col] = "FALSE"; 
    } 

void PagePacking::set_property_values(Gtk::Widget& _parent, std::string type,Gtk::Widget& widget)
{
    parent = &_parent;
    current_widget = &widget;
    type_of_parent = type;
    //std::cout<<"PARENT TYPE IS"<<type<<std::endl;
    for(int i=label_vector_size-1;i>=0;i--)
    {        
        if(label_vector[i]==NULL)
            continue;
        //std::cout<<"LABEL VECTOR I"<<i<<std::endl;
        remove(*label_vector[i]);
        remove(*value_widget_vector[i]);
        delete label_vector[i];
        }
    label_vector_size=-1;
    if(type=="gtk_window")
    {
        label_vector_size=0;
        }
    else if(type=="gtk_vbox"||type=="gtk_hbox")
    {
        label_vector_size = 0;
        label_vector.insert(label_vector.begin(),new Gtk::Label("Expand"));
        
        label_vector_size = 1;
        bool is_expand = false;
        if(type=="gtk_vbox")
             is_expand = dynamic_cast<gtk_vbox*>(parent)->get_expand(&widget);
        else if(type=="gtk_hbox")
             is_expand = dynamic_cast<gtk_hbox*>(parent)->get_expand(&widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_expand);
        cb->pack_start(model_column.col);        
        cb->set_active(!is_expand);        
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PagePacking::cb_box_expand_changed));
        }
    else if(type=="gtk_fixed")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("X Position"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Y Position"));
        
        label_vector_size = 2;
        
        gtk_fixed* fixed = dynamic_cast<gtk_fixed*>(parent);
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);       
        adjustment->set_value(fixed->get_x_of_child(*current_widget));   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);        
        sb->set_numeric(true);
        sb->set_adjustment(*adjustment);
        value_widget_vector.insert(value_widget_vector.begin(),sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PagePacking::sb_fixed_x_changed));
        
        sb = new Gtk::SpinButton();
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(fixed->get_y_of_child(*current_widget));   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);        
        sb->set_numeric(true);
        sb->set_adjustment(*adjustment);
        value_widget_vector.insert(value_widget_vector.begin()+1,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PagePacking::sb_fixed_y_changed));
        }
    else if(type=="gtk_eventbox")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_menubar")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_toolbar")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_offscreenwindow")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_notebook")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_scrollwin")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_table")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Expand"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Fill"));
        
        label_vector_size = 2;
        
        gtk_table* fixed = dynamic_cast<gtk_table*>(parent);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_expand);
        cb->pack_start(model_column.col);        
        cb->set_active(!fixed->get_expand(widget));        
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PagePacking::cb_table_expand_changed));

        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_expand);
        cb->pack_start(model_column.col);        
        cb->set_active(!fixed->get_fill(widget));        
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PagePacking::cb_table_fill_changed));
        }
    else if(type=="gtk_frame")
    {
        label_vector_size = 0;
        }
    for(int i=0;i<label_vector_size;i++)
    {        
        if(label_vector[i]==NULL)
            break;
        attach(*label_vector[i],0,1,i,i+1,Gtk::SHRINK,Gtk::FILL);
        attach(*value_widget_vector[i],1,2,i,i+1,Gtk::SHRINK,Gtk::FILL);
        }    
    show_all_children();
    }

//gtk_vbox or gtk_hbox
void PagePacking::cb_box_expand_changed()
{
    if(type_of_parent=="gtk_vbox")
        dynamic_cast<gtk_vbox*>(parent)->set_expand_fill(*current_widget,!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number(),false);
    else if(type_of_parent=="gtk_hbox")
        dynamic_cast<gtk_hbox*>(parent)->set_expand_fill(*current_widget,!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number(),false);
    }

//gtk_fixed
void PagePacking::sb_fixed_x_changed()
{
    gtk_fixed* fixed = dynamic_cast<gtk_fixed*>(parent);
    fixed->set_x_of_child(*current_widget,dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }

void PagePacking::sb_fixed_y_changed()
{
    gtk_fixed* fixed = dynamic_cast<gtk_fixed*>(parent);
    fixed->set_y_of_child(*current_widget,dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());    
    }

//gtk_table
void PagePacking::cb_table_expand_changed()
{
    dynamic_cast<gtk_table*>(parent)->set_expand_fill(*current_widget,!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number(),!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }

void PagePacking::cb_table_fill_changed()
{
    dynamic_cast<gtk_table*>(parent)->set_expand_fill(*current_widget,!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number(),!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }
        
PagePacking::~PagePacking(){}
