#include<gtkmm/scrollbar.h>

#ifndef GTK_HSCROLLBAR_H
#define GTK_HSCROLLBAR_H

class gtk_hscrollbar : public Gtk::HScrollbar
{
    public:
        gtk_hscrollbar();
        virtual ~gtk_hscrollbar();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif