//72 lines 
#include"gtk_container.h"
#include"gtk_placeholder.h"

#ifndef GTK_BOX_H
#define GTK_BOX_H

class gtk_box : public gtk_container
{
    public:
        gtk_box(bool _homogeneous, float spacing, int _slots);
        virtual ~gtk_box();
        
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        virtual int append_child_widget(Gtk::Widget&, int x, int y, int height, int width);
        
        virtual void remove_child(Gtk::Widget*);
        
        void set_expand_fill(Gtk::Widget& widget,bool _expand,bool _fill);
        void set_expand_fill_changes(Gtk::Widget& widget, bool _expand, bool _fill);
        void set_spacing(int _spacing)
        {
            spacing=_spacing;
            allocate_size(get_allocation());
            //on_expose_event(NULL);
            }
        int get_spacing(){return spacing;}
        void set_number_of_widgets(int _number);
        int get_number_of_widgets(){return slots;}
        void set_homogeneous(bool _homogeneous)
        {
            homogeneous=_homogeneous;
            allocate_size(get_allocation());
            on_expose_event(NULL);
            }
        bool get_homogeneous(){return homogeneous;}
        bool get_expand(Gtk::Widget* widget);
        void draw_around_child(Gtk::Widget& widget);
        
        gtk_container* get_current_placeholder();
        
    protected:
        bool on_mouse_press(GdkEventButton* event);
        bool on_mouse_release(GdkEventButton* event);  
        
        virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);
        virtual void on_add(Gtk::Widget* child);
        virtual void on_remove(Gtk::Widget* child);
        virtual GtkType child_type_vfunc() const;
        virtual void on_map();
        virtual void on_unmap();
        virtual void on_realize();
        virtual void on_unrealize();
        virtual void allocate_size(Gtk::Allocation);
        
        struct changeDimensions
        {
            bool change_width;
            bool change_height;
            };
        //Glib::RefPtr<Gdk::Window> m_refGdkWindow;
        bool homogeneous;
        int slots,spacing,number_of_widgets,at_placeholder;
        double x_end,y_end;
        struct changeDimensions change_dimensions;
        std::vector<gtk_placeholder*> child_placeholder_vector;
        std::vector<bool> expand_vector;
        std::vector<bool> fill_vector;
    };

#endif