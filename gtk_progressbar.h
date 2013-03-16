#include<gtkmm/progressbar.h>

#ifndef GTK_PROGRESSBAR_H
#define GTK_PROGRESSBAR_H

class gtk_progressbar : public Gtk::ProgressBar
{
    public:
        gtk_progressbar();
        virtual ~gtk_progressbar();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif