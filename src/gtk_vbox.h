//21 Lines
#include"gtk_box.h"

#ifndef GTK_VBOX_H
#define GTK_VBOX_H

class gtk_vbox : public gtk_box
{
    public:
        gtk_vbox(bool _homogeneous, float spacing, int _slots);
        virtual ~gtk_vbox();
        
    protected:
        void allocate_size(Gtk::Allocation allocation);
        virtual void on_size_request(Gtk::Requisition* requisition);
        virtual void on_size_allocate(Gtk::Allocation& allocation);
 
        virtual bool on_expose_event(GdkEventExpose* event);      
    };
#endif
