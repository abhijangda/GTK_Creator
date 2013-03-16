//20 Lines
#include"gtk_window.h"

#ifndef GTK_OFFSCREENWINDOW_H
#define GTK_OFFSCREENWINDOW_H

class gtk_offscreenwindow : public gtk_window
{
    public:
        gtk_offscreenwindow(Gdk::Color color);
        virtual ~gtk_offscreenwindow();
        
        bool get_focus_visible(){return focus_visible;}
        void set_focus_visible(bool _focus_visible){focus_visible = _focus_visible;}
            
    protected:
        bool focus_visible;
    };
#endif
