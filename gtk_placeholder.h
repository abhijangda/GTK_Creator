//46 lines
#include"gtk_container.h"

#ifndef GTK_PLACEHOLDER_H
#define GTK_PLACEHOLDER_H

class gtk_placeholder : public gtk_container
{
    public:
        gtk_placeholder(Gdk::Color);
        virtual ~gtk_placeholder();
        Gtk::Widget* get_child(){return m_child_one;}
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        
        void set_at_this_placeholder(bool _b){at_this_placeholder=_b;}
        bool get_at_this_placeholder(){return at_this_placeholder;}
        bool at_this_placeholder;
        void set_focussed_widget_as_child_widget();
        void remove_child(Gtk::Widget*);
        void set_draw(bool _b){draw_borders=_b;redraw_placeholder();}
        void redraw_placeholder();
        
        void draw_around_borders();
        Gtk::Widget* get_parent();
        
    protected:
        virtual void on_size_request(Gtk::Requisition* requisition);
        virtual void on_size_allocate(Gtk::Allocation& allocation);
        virtual void on_map();
        virtual void on_unmap();
        virtual void on_realize();
        virtual void on_unrealize();
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);
        virtual void on_add(Gtk::Widget* child);
        virtual void on_remove(Gtk::Widget* child);
        
        virtual GtkType child_type_vfunc() const;
        
        Gtk::Widget* m_child_one;
        Gdk::Color bg_color;
        bool on_mouse_press(GdkEventButton* event);
        bool on_mouse_release(GdkEventButton* event);        
        bool draw_borders;
    };
#endif