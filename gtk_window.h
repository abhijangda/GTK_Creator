//94 Lines
#include"gtk_container.h"
#include"gtk_placeholder.h"

#ifndef GTK_WINDOW_H
#define GTK_WINDOW_H
#define container_spacing 1
class gtk_window : public gtk_container
{
    public:
        gtk_window(Gdk::Color color);
        virtual ~gtk_window();
        virtual int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        virtual int append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        void draw_around_child(Gtk::Widget& widget);
        virtual void remove_child(Gtk::Widget*);
        
        void set_type(std::string _type){type=_type;}
        std::string get_type(){return type;}
        
        void set_default_width(int _width){default_width=_width;}
        int get_default_width(){return default_width;}
        void set_default_height(int _height){default_height=_height;}
        int get_default_height(){return default_height;}
        
        bool get_destroy_with_parent(){return destroy_with_parent;}
        void set_destroy_with_parent(bool _destroy){destroy_with_parent=_destroy;}
        bool get_accept_focus(){return accept_focus;}
        void set_accept_focus(bool _accept){accept_focus=_accept;}
        bool get_focus_on_map(){return focus_on_map;}
        void set_focus_on_map(bool _focus){focus_on_map=_focus;}
        bool get_decorated(){return decorated;}
        void set_decorated(bool _decorated){decorated=_decorated;}
        bool get_deletable(){return deletable;}
        void set_deletable(bool _deletable){deletable=_deletable;}
        bool get_mnemonics_visible(){return mnemonics_visible;}
        void set_mnemonics_visible(bool _mnemonics){mnemonics_visible=_mnemonics;}
        bool get_focus_visible(){return focus_visible;}
        void set_focus_visible(bool _focus){focus_visible=_focus;}
        bool get_modal(){return modal;}
        void set_modal(bool _modal){modal=_modal;}
        
        float get_opacity(){return opacity;}
        void set_opacity(float _opacity){opacity=_opacity;}        
        std::string get_title(){return title;}
        void set_title(std::string _title){title=_title;}
        bool get_resizable(){return resizable;}
        void set_resizable(bool _resizable){resizable=_resizable;}
            
    protected:
        std::string type;
        int default_width;
        int default_height;
        bool destroy_with_parent;
        bool accept_focus;
        bool focus_on_map;
        bool decorated;
        bool deletable;        
        bool mnemonics_visible;
        bool focus_visible;
        float opacity;       
        std::string title;
        bool modal;
        bool resizable;
        
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
        
        gtk_placeholder* placeholder_child;
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
        Glib::RefPtr<Gdk::Window> m_refGdkWindow;
        int m_scale;
    };
#endif