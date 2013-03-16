//29 Lines
#include"page_common.h"
#include"page_general.h"
#include"page_packing.h"

#ifndef PROPERTY_EDITOR_H
#define PROPERTY_EDITOR_H

class PropertyEditor : public Gtk::Notebook
{
    public:
        PropertyEditor(Frame&,ObjectBox&);
        ~PropertyEditor();                
        
        //general
        Gtk::Entry txtname;
        
        void set_property_values_from_widget(Gtk::Widget&,std::string,Gtk::Widget&,std::string);   
        
        PageCommon page_common;
        PageGeneral page_general;
        PagePacking page_packing;
        Gtk::ScrolledWindow page_common_scroll_win; 
        Gtk::ScrolledWindow page_general_scroll_win;      
        Gtk::Table page_specific;
        Gtk::Label lblname;
    
    };
#endif
