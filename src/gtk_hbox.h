//20 Lines
#include"gtk_box.h"

#ifndef GTK_HBOX_H
#define GTK_HBOX_H
class gtk_hbox : public gtk_box
{
    public:
        gtk_hbox(bool homogeneous, float spacing, int _slots);
        virtual ~gtk_hbox();       
        
    protected:
        void allocate_size(Gtk::Allocation allocation);
        virtual void on_size_request(Gtk::Requisition* requisition);
        virtual void on_size_allocate(Gtk::Allocation& allocation);
 
        virtual bool on_expose_event(GdkEventExpose* event);      
    };
#endif
