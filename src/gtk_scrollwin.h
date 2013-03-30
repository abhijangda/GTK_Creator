//49 Lines
#include<gtkmm/scrolledwindow.h>
#include"gtk_placeholder.h"

#ifndef GTK_SCROLLWIN_H
#define GTK_SCROLLWIN_H

class gtk_scrollwin : public gtk_container
{
    public:
            gtk_scrollwin();
            virtual ~gtk_scrollwin();
            virtual int set_child_widget(Gtk::Widget& child,int x, int y, int height, int width);
            virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
            void remove_child(Gtk::Widget*);
            
            std::string get_horizontal_policy();
            void set_horizontal_policy(std::string _policy);
            
            std::string get_vertical_policy();
            void set_vertical_policy(std::string _policy);
            
            virtual void draw_around_child(Gtk::Widget& widget);
            Gtk::ScrolledWindow* scroll_win;
            Gtk::Widget* scroll_win_widget;

    protected:
        std::string horizontal_policy;
        std::string vertical_policy;
        
        bool on_mouse_press(GdkEventButton* event);
        bool on_mouse_release(GdkEventButton* event);
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual void on_size_request(Gtk::Requisition* requisition);
        virtual void on_size_allocate(Gtk::Allocation& allocation);
        virtual void on_map();
        virtual void on_unmap();
        virtual void on_realize();
        virtual void on_unrealize();
        virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);
        virtual void on_add(Gtk::Widget* child);
        virtual void on_remove(Gtk::Widget* child);        
       
        virtual GtkType child_type_vfunc() const;
        struct changeDimensions
        {
            bool change_width;
            bool change_height;
            };
        struct changeDimensions change_dimensions;
        //Glib::RefPtr<Gdk::Window> m_refGdkWindow;
        Gtk::Widget* child_widget;
    };

#endif