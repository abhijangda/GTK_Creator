//284 Lines
#include "gtk_eventbox.h"
#include<iostream>

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;
extern bool can_set_focus;

gtk_eventbox::gtk_eventbox(Gdk::Color color)
    : //Glib::ObjectBase("gtk_eventbox"),
        //Gtk::Container(),
            m_scale(1000),
        bg_color(color),child_placeholder(0)
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    //set_redraw_on_allocate(false);
    add_events(Gdk::BUTTON_PRESS_MASK);
    press_signal=signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_eventbox::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    release_signal=signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_eventbox::on_mouse_release));
    add_events(Gdk::FOCUS_CHANGE_MASK);
    signal_focus_in_event().connect(sigc::mem_fun(*this,&gtk_eventbox::on_focus_in_event));
    signal_focus_out_event().connect(sigc::mem_fun(*this,&gtk_eventbox::on_focus_out_event));
    add_events(Gdk::POINTER_MOTION_MASK);
    signal_motion_notify_event().connect(sigc::mem_fun(*this,&gtk_eventbox::on_motion_notify_event));
    visible_window=true;
    above_child=false;
    child_placeholder = new gtk_placeholder(bg_color);
    child_placeholder->set_parent(*this);
    }

gtk_eventbox::~gtk_eventbox()
{
    delete child_placeholder;
    }

void gtk_eventbox::remove_child(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == dynamic_cast<gtk_placeholder*>(child_placeholder)->get_child())
        {
            dynamic_cast<gtk_placeholder*>(child_placeholder)->remove_child(child);
            found = true;
            }
        if(found)
        {
            child->unparent();
            if(visible)
            queue_resize();
            }
        }
    }

void gtk_eventbox::draw_around_child(Gtk::Widget& widget)
{
    }

int gtk_eventbox::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    if(child_placeholder->set_child_widget(child,x,y,height,width)==-1)
        return -1;
    return 0;
    }
int gtk_eventbox::append_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    return set_child_widget(child,x,y,height,width);
    }
bool gtk_eventbox::on_motion_notify_event(GdkEventMotion* event)
{
    return FALSE;
    }

bool gtk_eventbox::on_focus_out_event(GdkEventFocus* event)
{
    //std::cout<<"FOCUS OUT"<<std::endl;
    return FALSE;
    }

bool gtk_eventbox::on_focus_in_event(GdkEventFocus* event)
{
    //std::cout<<"FOCUS IN"<<std::endl;
    return FALSE;
    }

bool gtk_eventbox::on_mouse_press(GdkEventButton* event)
{
    return FALSE;
    }

bool gtk_eventbox::on_mouse_release(GdkEventButton* event)
{
    //std::cout<<"pressed window"<<std::endl;
    std::cout<<"EVENT BOX release"<<std::endl;
    if(change_dimensions.change_height == true)
    {
        set_size_request(get_width(),event->y);
        }
    
    if(change_dimensions.change_width == true)
    {
        set_size_request(event->x,get_height());
        }
    change_dimensions.change_height = false;
    change_dimensions.change_width = false;
    Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
    Gdk::Cairo::set_source_color(cr,Gdk::Color("blue"));
    int i=0,j=0;
    Gtk::Allocation allocation = get_allocation();
    int x_window = event->x_root - event->x;
    int y_window = event->y_root - event->y;
    //std::cout<<x_window<<std::endl;
    //std::cout<<y_window<<std::endl;
    //std::cout<<"allocationX"<<allocation.get_x()<<std::endl;
    //std::cout<<"allocationY"<<allocation.get_y()<<std::endl;
    cr->set_line_width(1.0);
    
    cr->move_to(0,0);
    cr->line_to(get_width(),0);
    
    cr->move_to(0,0);
    cr->line_to(0,get_height());
    
    cr->move_to(get_width(),0);
    cr->line_to(get_width(),get_height());
    
    cr->move_to(0,get_height());
    cr->line_to(get_width(),get_height());
    
    cr->stroke();
       
    return FALSE;
    }

void gtk_eventbox::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    Gtk::Requisition child_requisition_one = {0, 0};

    if(child_placeholder && child_placeholder->is_visible())
    child_requisition_one = child_placeholder->size_request();
    
    //See which one has the most width:
    int max_width = child_requisition_one.width; 
    //Add the heights together:
    int total_height = child_requisition_one.height; 
    //Request the width for this container based on the sizes requested by its
    //child widgets:
    requisition->height = total_height;
    requisition->width = max_width;   
    }

void gtk_eventbox::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);
    Gtk::Allocation child_allocation_one;
    //Place the first child at the top-left,
    child_allocation_one.set_x(0);
    child_allocation_one.set_y(0);
    //Make it take up the full width available:
    child_allocation_one.set_width(allocation.get_width());
    child_allocation_one.set_height(allocation.get_height());    
    if(child_placeholder && child_placeholder->is_visible())
    child_placeholder->size_allocate(child_allocation_one);

    if(m_refGdkWindow)
    {
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
        }
    }

void gtk_eventbox::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    if(child_placeholder)
        callback(GTK_WIDGET(child_placeholder->gobj()), callback_data);
    }
    
void gtk_eventbox::on_add(Gtk::Widget* child)
{
    if(!child_placeholder)
    {
        if(dynamic_cast<gtk_placeholder*>(child))
        {
            child_placeholder = dynamic_cast<gtk_placeholder*>(child);
            child_placeholder->set_parent(*this);
            }            
        }
    }
void gtk_eventbox::on_remove(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == child_placeholder)
        {
            child_placeholder = 0;
            found = true;
            }
        if(found)
        {
            child->unparent();
            if(visible)
            queue_resize();
            }
        }
    }

GtkType gtk_eventbox::child_type_vfunc() const
{
//If there is still space for one widget, then report the type of widget that
//may be added.
    if(!child_placeholder)
        return Gtk::Widget::get_type();
    else
    {
    //No more widgets may be added.
        return G_TYPE_NONE;
    }
}

void gtk_eventbox::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_eventbox::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_eventbox::on_realize()
{
    Gtk::Widget::on_realize();
    ensure_style();
    //get_style_property("window_scale",m_scale);
    
    if(!m_refGdkWindow)
    {
        GdkWindowAttr attributes;
        memset(&attributes, 0, sizeof(attributes));
        Gtk::Allocation allocation = get_allocation();
        
        attributes.x = allocation.get_x();
        attributes.y = allocation.get_y();
        attributes.width = allocation.get_width();
        attributes.height = allocation.get_height();
        
        attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;
        
        m_refGdkWindow = Gdk::Window::create(get_window(),&attributes,GDK_WA_X|GDK_WA_Y);
        unset_flags(Gtk::NO_WINDOW);
        set_window(m_refGdkWindow);
        
        modify_bg(Gtk::STATE_NORMAL,bg_color);
        modify_fg(Gtk::STATE_NORMAL,bg_color);
        
        m_refGdkWindow->set_user_data(gobj());
        }
    }

void gtk_eventbox::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_eventbox::on_expose_event(GdkEventExpose* event)
{
    if(m_refGdkWindow)
    {
        Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
        if(event)
        {
            cr->rectangle(event->area.x,event->area.y,event->area.width,event->area.height);
            cr->clip();
            }
        Gdk::Cairo::set_source_color(cr,get_style()->get_bg(Gtk::STATE_NORMAL));
        cr->paint();
        Gdk::Cairo::set_source_color(cr,Gdk::Color("white"));
        cr->set_line_width(0.5);
        int i=0,j=0;
        Gtk::Allocation allocation = get_allocation();
        int height = get_height();
        int width = get_width();
        for(i=10;i<height;i+=10)
        {
            cr->move_to(0,i);
            cr->line_to(width,i);
            }
        for(j=10;j<width;j+=10)
        {
            cr->move_to(j,0);
            cr->line_to(j,height);
            }       
        cr->stroke();
        }
    Gtk::Container::on_expose_event(event);
    return true;
    }
