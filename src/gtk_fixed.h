//50Lines
#include"gtk_placeholder.h"

#ifndef GTK_FIXED_H
#define GTK_FIXED_H

class gtk_fixed : public gtk_container
{
    public:
        gtk_fixed();
        virtual ~gtk_fixed();
        virtual int set_child_widget(Gtk::Widget& child,int x, int y, int width, int height);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        void remove_child(Gtk::Widget*);
        
        int get_x_of_child(Gtk::Widget& widget);
        int get_y_of_child(Gtk::Widget& widget);
        void set_x_of_child(Gtk::Widget& widget,int x);
        void set_y_of_child(Gtk::Widget& widget, int y);
        virtual void draw_around_child(Gtk::Widget& widget);
        
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
        bool on_mouse_press(GdkEventButton* event);
        bool on_mouse_release(GdkEventButton* event);
        
        struct changeDimensions
        {
            bool change_width;
            bool change_height;
            };
        //Glib::RefPtr<Gdk::Window> m_refGdkWindow;
        int number_of_widgets;
        int x_new,y_new,height,width;
        struct changeDimensions change_dimensions;
        std::vector<int> x_vector;
        std::vector<int> y_vector;
        std::vector<int> width_vector;
        std::vector<int> height_vector;
        std::vector<gtk_placeholder*> child_placeholder_vector;
        //void allocate_size();
    };
#endif