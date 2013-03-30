#include<gtkmm/treeview.h>

#ifndef GTK_TREE_VIEW_H
#define GTK_TREE_VIEW_H

class gtk_treeview : public Gtk::TreeView
{
    public:
        gtk_treeview();
        virtual ~gtk_treeview();
    protected:
        bool on_mouse_release(GdkEventButton* event);
    };
#endif