//27 Lines
#include<gtkmm/textview.h>
#include<gdkmm/drawable.h>
#include<gdkmm/general.h>
#include<gdkmm/cursor.h>
#include<gtkmm/eventbox.h>

#include"gtk_placeholder.h"

#ifndef GTK_TEXTVIEW_H
#define GTK_TEXTVIEW_H

class gtk_textview : public Gtk::TextView
{
    public:
        gtk_textview();
        virtual ~gtk_textview();
        std::string get_wrapmode();
        void set_wrapmode(std::string _wrapmode);
        std::string get_justifi();
        void set_justifi(std::string _j);
        Gtk::EventBox event_box;
        
    protected:
        std::string wrap_mode;
        std::string justification;
        bool on_mouse_release(GdkEventButton* event);
        virtual bool on_expose_event(GdkEventExpose* event);
    };
#endif