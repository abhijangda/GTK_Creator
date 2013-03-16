#include"gtk_combobox.h"
#include<iostream>

gtk_combobox::gtk_combobox()
{
    std::cout<<"LLL"<<std::endl;
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_combobox::on_mouse_release),false);    
    }

bool gtk_combobox::on_mouse_release(GdkEventButton* event)
{
    std::cout<<"LLL"<<std::endl;
    return false;
    }

gtk_combobox::~gtk_combobox()
{
    }


gtk_comboboxtext::gtk_comboboxtext(bool _b)
:Gtk::ComboBoxText(_b)
{
    std::cout<<"LLL"<<std::endl;
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_comboboxtext::on_mouse_release),false);    
    }

bool gtk_comboboxtext::on_mouse_release(GdkEventButton* event)
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    return false;
    }

gtk_comboboxtext::~gtk_comboboxtext()
{
    }
