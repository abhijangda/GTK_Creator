//74 Lines
#include"gtk_placeholder.h"
#include<gtkmm/table.h>

#ifndef GTK_TABLE_H
#define GTK_TABLE_H

class gtk_table;
class _gtk_table : public Gtk::Table
{
    public:
        _gtk_table(int _row, int _col, bool _h,gtk_table& _parent);
        virtual ~_gtk_table();
    
    protected:
        gtk_table& parent;
        virtual bool on_expose_event(GdkEventExpose* event);
    };

class gtk_table : public gtk_container
{
    public:
        gtk_table(int, int, bool,int,int);
        virtual ~gtk_table();
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        void remove_child(Gtk::Widget*);
        
        void set_expand_fill(Gtk::Widget& widget,bool _expand,bool _fill);
        bool get_expand(Gtk::Widget& widget);
        bool get_fill(Gtk::Widget& widget);
        
        void set_row_spacing(int _spacing){table.set_row_spacings(_spacing);}
        void set_col_spacing(int _spacing){table.set_col_spacings(_spacing);}
        int get_row_spacing(){return table.get_row_spacing(0);}
        int get_col_spacing(){return table.get_col_spacing(0);}
        
        void set_rows(int _number);
        void set_cols(int _number);
        int get_rows();
        int get_cols();
        
        void set_homogeneous(bool _homogeneous){table.set_homogeneous(_homogeneous);}
        bool get_homogeneous(){return table.get_homogeneous();}
        _gtk_table table;
        int number_of_widgets;
        std::vector<gtk_placeholder*> child_placeholder_vector;
        int get_left_attach(Gtk::Widget&);
        int get_right_attach(Gtk::Widget&);
        int get_top_attach(Gtk::Widget&);
        int get_bottom_attach(Gtk::Widget&);
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
        double x_end,y_end;
        struct changeDimensions change_dimensions;
        
        std::vector<bool> expand_vector;
        std::vector<bool> fill_vector;
        
    };
#endif