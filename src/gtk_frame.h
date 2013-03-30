//53 Lines
#include"gtk_placeholder.h"
#include<gtkmm/frame.h>
#include<gtkmm/label.h>
#include<iostream>

#ifndef GTK_FRAME_H
#define GTK_FRAME_H

class gtk_frame : public gtk_container
{
    public:
        gtk_frame(Gtk::Label*);
        virtual ~gtk_frame();
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        Gtk::Label* get_label(){return label;}
        void set_label(Gtk::Label* _label);
        Gtk::Widget* get_child(){return child_placeholder->get_child();}
        void remove_child(Gtk::Widget*);
        
    protected:
        Gtk::Frame* frame;
        Gtk::Label* label;
        
        virtual void on_size_request(Gtk::Requisition* requisition);
        virtual void on_size_allocate(Gtk::Allocation& allocation);
        virtual void on_map();
        virtual void on_unmap();
        virtual void on_realize();
        virtual void on_unrealize();
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual bool on_motion_notify_event(GdkEventMotion* event);
        virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);
        virtual void on_add(Gtk::Widget* child);
        virtual void on_remove(Gtk::Widget* child);
        
        virtual GtkType child_type_vfunc() const;
        
        gtk_placeholder* child_placeholder;
        bool on_mouse_press(GdkEventButton* event);
        bool on_mouse_release(GdkEventButton* event);
        struct changeDimensions
        {
            bool change_width;
            bool change_height;
            };
        struct changeDimensions change_dimensions;
        double x_end,y_end;
        Gdk::Color bg_color;
        //Glib::RefPtr<Gdk::Window> m_refGdkWindow;
    };
#endif
