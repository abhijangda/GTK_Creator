//41 Lines
#include<gtkmm/container.h>
#include<gdkmm/drawable.h>
#include<gdkmm/general.h>
#include<gdkmm/cursor.h>
#include"focused_widget.h"

//#include<iostream>

#ifndef GTK_CONTAINER_H
#define GTK_CONTAINER_H
#define container_spacing 1

class gtk_container : public Gtk::Container
{
    public:
        bool focused;
        gtk_container();
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width)=0;
        virtual void draw_around_child(Gtk::Widget& widget);
        virtual void remove_child(Gtk::Widget*);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width)=0;
    protected:        
        Glib::RefPtr<Gdk::Window> m_refGdkWindow;    
    };
#endif