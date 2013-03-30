//51 Lines
#include"gtk_label.h"
#include"focused_widget.h"
#include<iostream>

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

gtk_label::gtk_label(std::string str)
    : Gtk::Label(str)
{
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_label::on_mouse_release));
    }

gtk_label::~gtk_label()
{}

bool gtk_label::on_expose_event(GdkEventExpose* event)
{
    //std::cout<<"inside on expose event label"<<std::endl;    
    /*Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    Gdk::Cairo::set_source_color(cr,Gdk::Color("blue"));
    
    cr->set_line_width(1.0);
    
    cr->move_to(0,0);
    cr->line_to(get_width(),0);
    
    cr->move_to(0,0);
    cr->line_to(0,get_height());
    
    cr->move_to(get_width(),0);
    cr->line_to(get_width(),get_height());
    
    cr->move_to(0,get_height());
    cr->line_to(get_width(),get_height());
    
    cr->stroke();*/
    
    Gtk::Label::on_expose_event(event);
    return FALSE;
    }

bool gtk_label::on_mouse_release(GdkEventButton* event)
{   
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    
    return FALSE;
    }