//54 Lines
#include"gtk_placeholder.h"

#ifndef GTK_EVENTBOX_H
#define GTK_EVENTBOX_H

class gtk_eventbox : public gtk_container
{
    public:
        gtk_eventbox(Gdk::Color color);
        virtual ~gtk_eventbox();
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        void remove_child(Gtk::Widget*);
        
        bool get_above_child(){return above_child;}
        void set_above_child(bool _above_child){above_child=_above_child;}
        
        bool get_visible_window(){return visible_window;}
        void set_visible_window(bool _visible_window){visible_window = _visible_window;}
        
        void draw_around_child(Gtk::Widget& widget);
    protected:
        bool visible_window;
        bool above_child;    
        
        virtual void on_size_request(Gtk::Requisition* requisition);
        virtual void on_size_allocate(Gtk::Allocation& allocation);
        virtual void on_map();
        virtual void on_unmap();
        virtual void on_realize();
        virtual void on_unrealize();
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual bool on_focus_in_event(GdkEventFocus* event);
        virtual bool on_focus_out_event(GdkEventFocus* event);
        virtual bool on_motion_notify_event(GdkEventMotion* event);
        virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);
        virtual void on_add(Gtk::Widget* child);
        virtual void on_remove(Gtk::Widget* child);
        
        virtual GtkType child_type_vfunc() const;
        
        gtk_placeholder* child_placeholder;
        virtual bool on_mouse_press(GdkEventButton* event);
        virtual bool on_mouse_release(GdkEventButton* event);
        struct changeDimensions
        {
            bool change_width;
            bool change_height;
            };
        struct changeDimensions change_dimensions;
        double x_end,y_end;
        Gdk::Color bg_color;
        //Glib::RefPtr<Gdk::Window> m_refGdkWindow;
        sigc::connection press_signal,release_signal;
        int m_scale;
    };
#endif