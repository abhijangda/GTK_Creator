#include<gtkmm/comboboxtext.h>
#include<gtkmm/eventbox.h>
#include"gtk_placeholder.h"

#ifndef GTK_COMBOBOX_H
#define GTK_COMBOBOX_H

class gtk_combobox : public Gtk::ComboBox
{
    public:
        gtk_combobox();
        virtual ~gtk_combobox();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };

class gtk_comboboxtext : public Gtk::ComboBoxText
{
    public:
        gtk_comboboxtext(bool);
        virtual ~gtk_comboboxtext();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };

#endif