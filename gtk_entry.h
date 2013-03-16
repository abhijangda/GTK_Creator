#include<gtkmm/entry.h>

#ifndef GTK_ENTRY_H
#define GTK_ENTRY_H

class gtk_entry : public Gtk::Entry
{
    public:
        gtk_entry();
        virtual ~gtk_entry();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif