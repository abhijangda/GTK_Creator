#include<gtkmm/scale.h>

#ifndef GTK_SCALE_H
#define GTK_SCALE_H

class gtk_vscale : public Gtk::VScale
{
    public:
        gtk_vscale();
        virtual ~gtk_vscale();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };

class gtk_hscale : public Gtk::HScale
{
    public:
        gtk_hscale();
        virtual ~gtk_hscale();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif