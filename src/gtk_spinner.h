#include<gtkmm/spinner.h>

#ifndef GTK_SPINNER_H
#define GTK_SPINNER_H

class gtk_spinner : public Gtk::Spinner
{
    public:
        gtk_spinner();
        virtual ~gtk_spinner();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif