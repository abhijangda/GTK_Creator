//94 Lines
#include"gtk_textview.h"
#include<iostream>
#include"focused_widget.h"

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

gtk_textview::gtk_textview()
    : Gtk::TextView(),wrap_mode("NONE"),event_box()
{
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_textview::on_mouse_release),false);
    //add_child_in_window(event_box,Gtk::TEXT_WINDOW_TEXT,0,0);
    event_box.set_size_request(get_width(),get_height());    
    }

gtk_textview::~gtk_textview()
{}

std::string gtk_textview::get_wrapmode()
{
    if(get_wrap_mode()==Gtk::WRAP_NONE)
        return "NONE";
    else if(get_wrap_mode()==Gtk::WRAP_CHAR)
        return "CHARACTER";
    else if(get_wrap_mode()==Gtk::WRAP_WORD)
        return "WORD";
    }

void gtk_textview::set_wrapmode(std::string _wrapmode)
{
    if(_wrapmode == "NONE")
        set_wrap_mode(Gtk::WRAP_NONE); 
    else if(_wrapmode=="CHARACTER")
        set_wrap_mode(Gtk::WRAP_CHAR);
    else if(_wrapmode=="WORD")
        set_wrap_mode(Gtk::WRAP_WORD);
    }

std::string gtk_textview::get_justifi()
{
    if(get_justification()==Gtk::JUSTIFY_FILL)
        return "FILL";
    else if(get_justification()==Gtk::JUSTIFY_RIGHT)
        return "RIGHT";
    else if(get_justification()==Gtk::JUSTIFY_LEFT)
        return "LEFT";
    else if(get_justification()==Gtk::JUSTIFY_CENTER)
        return "CENTER";
    }

void gtk_textview::set_justifi(std::string _j)
{
    if(_j=="FILL")
         set_justification(Gtk::JUSTIFY_FILL);
    else if(_j=="RIGHT")
        set_justification(Gtk::JUSTIFY_RIGHT);
    else if(_j=="LEFT")
        set_justification(Gtk::JUSTIFY_LEFT);
    else if(_j=="CENTER")
        set_justification(Gtk::JUSTIFY_CENTER);
    }

bool gtk_textview::on_expose_event(GdkEventExpose* event)
{
    //std::cout<<"inside on expose event text view"<<std::endl;
    Gtk::TextView::on_expose_event(event);
    /*Cairo::RefPtr<Cairo::Context> cr = get_window(Gtk::TEXT_WINDOW_TEXT)->create_cairo_context();
    Gdk::Cairo::set_source_color(cr,Gdk::Color("black"));
    
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
    
    return FALSE;
    }

bool gtk_textview::on_mouse_release(GdkEventButton* event)
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    return FALSE;
    }