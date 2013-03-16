#include"class_copy.h"

Gtk::Widget* class_copy::get_copy(Gtk::Widget* widget)
{
    copy->set_tooltip_text(widget.get_tooltip_text());    
    copy->set_has_tooltip(widget->get_has_tooltip());        
    copy->set_sensitive(widget->get_sensitive());         
    copy->set_can_focus(widget->get_can_focus());       
    //copy->setwidget->has_focus()    
    copy->set_has_tooltip(widget->get_has_tooltip()); 
    //widget->is_focus()       
    copy->set_can_default(widget->get_can_default());
    //copywidget->has_default()
    copy->set_size_request(widget->get_width(),widget->get_height());
    copy->get_parent()->set_size_request(widget->get_width()+2,widget->get_height()+2);
    }