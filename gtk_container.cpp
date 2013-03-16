//17 Lines
#include"gtk_container.h"

extern bool can_set_focus;

gtk_container::gtk_container()           
{    
    focused = false;
    }

void gtk_container::draw_around_child(Gtk::Widget& widget)
{
    }

void gtk_container::remove_child(Gtk::Widget* widget)
{
    }