#include"gtk_treeview.h"
#include"gtk_placeholder.h"
#include<iostream>

gtk_treeview::gtk_treeview()
{
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_treeview::on_mouse_release),false);    
    }

bool gtk_treeview::on_mouse_release(GdkEventButton* event)
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    return false;
    }

gtk_treeview::~gtk_treeview()
{
    }