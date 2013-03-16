#include<gtkmm/spinbutton.h>

#ifndef GTK_SPIN_BUTTON_H
#define GTK_SPIN_BUTTON_H

class gtk_spin_button : public Gtk::SpinButton
{
    public:
        gtk_spin_button();
        virtual ~gtk_spin_button();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif