//20 Lines
#include"property_editor.h"

PropertyEditor::PropertyEditor(Frame& _frame,ObjectBox& _object_box)
    : page_common(), page_common_scroll_win(),page_general(_frame,_object_box),page_general_scroll_win(),page_packing(_frame,_object_box)//page_general(2,2), page_specific(2,2),
{
    page_common_scroll_win.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    page_general_scroll_win.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    page_common_scroll_win.add(page_common);
    page_general_scroll_win.add(page_general);
    
    append_page(page_general_scroll_win,"General");     
    append_page(page_common_scroll_win,"Common");       
    append_page(page_packing,"Packing");
    }

PropertyEditor::~PropertyEditor(){}

void PropertyEditor::set_property_values_from_widget(Gtk::Widget& widget,std::string type,Gtk::Widget& parent_widget,std::string parent_type)
{
    page_common.set_property_values(widget,type);
    page_general.set_property_values(widget,type);
    page_packing.set_property_values(parent_widget,parent_type,widget);
    }