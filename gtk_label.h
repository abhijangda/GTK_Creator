//21 Lines
#include<gtkmm/label.h>
#include<gdkmm/drawable.h>
#include<gdkmm/general.h>
#include<gdkmm/cursor.h>
#include"gtk_placeholder.h"

#ifndef GTK_LABEL_H
#define GTK_LABEL_H

class gtk_label : public Gtk::Label
{
    public:
        gtk_label(std::string name);
        virtual ~gtk_label();
        
    protected:
        bool on_mouse_release(GdkEventButton* event);
        virtual bool on_expose_event(GdkEventExpose* event);
    };
#endif