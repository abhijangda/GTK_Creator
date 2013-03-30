//352 Lines
#include "gtk_window.h"
#include<iostream>

extern focused_widget current_focused_widget;
extern Gtk::Widget* focussed_widget;

gtk_window::gtk_window(Gdk::Color color)
    : //Glib::ObjectBase("gtk_window"),
        //Gtk::Container(),
            m_scale(1000),
        bg_color(color),placeholder_child(0) 
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    //set_redraw_on_allocate(false);
    add_events(Gdk::BUTTON_PRESS_MASK);
    //signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_window::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    //signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_window::on_mouse_release));
    add_events(Gdk::FOCUS_CHANGE_MASK);
    signal_focus_in_event().connect(sigc::mem_fun(*this,&gtk_window::on_focus_in_event));
    signal_focus_out_event().connect(sigc::mem_fun(*this,&gtk_window::on_focus_out_event));
    add_events(Gdk::POINTER_MOTION_MASK);
    signal_motion_notify_event().connect(sigc::mem_fun(*this,&gtk_window::on_motion_notify_event));
    placeholder_child = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    placeholder_child->set_parent(*this);
    
    type="TOPLEVEL";
    title="Window";
    default_width=600;
    default_height=400;
    destroy_with_parent=FALSE;
    accept_focus=TRUE;
    focus_on_map=TRUE;
    decorated=TRUE;
    deletable=TRUE;
    mnemonics_visible=TRUE;
    focus_visible=TRUE;
    modal=FALSE;
    opacity=1.00;
    }

gtk_window::~gtk_window()
{
    if(placeholder_child)
         delete placeholder_child;
    }

int gtk_window::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{    
    if(placeholder_child->set_child_widget(child,x,y,height,width)==-1)
        return -1;
    return 0;
    }
int gtk_window::append_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    return set_child_widget(child,x,y,height,width);
    }

void gtk_window::remove_child(Gtk::Widget* child)
{
    if(placeholder_child->get_child()==child)
         placeholder_child->remove_child(child);
    }

void gtk_window::draw_around_child(Gtk::Widget& widget)
{
    Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
    Gdk::Cairo::set_source_color(cr,Gdk::Color("blue"));
    int i=0,j=0;
    Gtk::Allocation allocation = widget.get_allocation();
    int x1=allocation.get_x()-container_spacing;
    int y1=allocation.get_y()-container_spacing;
    int x2=x1+allocation.get_width()+container_spacing*2;
    int y2=y1+allocation.get_height()+container_spacing*2;
    //std::cout<<"X1"<<x1<<"Y1"<<y1<<"X2"<<x2<<"Y2"<<y2<<std::endl;
    cr->set_line_width(1.0);
    
    cr->move_to(x1,y1);
    cr->line_to(x2,y1);
    
    cr->move_to(x1,y1);
    cr->line_to(x1,y2);
    
    cr->move_to(x2,y1);
    cr->line_to(x2,y2);
    
    cr->move_to(x1,y2);
    cr->line_to(x2,y2);
    
    cr->stroke();
    }

bool gtk_window::on_motion_notify_event(GdkEventMotion* event)
{
    //std::cout<<"MOUSE MOVING INSIDE"<<std::endl;
    double x_end_new = event->x, y_end_new = event->y;        
    if(x_end_new<=get_width() && x_end_new>=get_width()-5)
    {
        Gdk::Cursor cursor(Gdk::CROSS);        
        m_refGdkWindow->set_cursor(cursor);
        }
    if(y_end_new <=get_height() && y_end_new >=get_height()-5)
    {
        Gdk::Cursor cursor(Gdk::CROSS);        
        m_refGdkWindow->set_cursor(cursor);
        }
    return FALSE;
    }

bool gtk_window::on_focus_out_event(GdkEventFocus* event)
{
    //std::cout<<"FOCUS OUT"<<std::endl;
    return FALSE;
    }

bool gtk_window::on_focus_in_event(GdkEventFocus* event)
{
    //std::cout<<"FOCUS IN"<<std::endl;
    return FALSE;
    }

bool gtk_window::on_mouse_press(GdkEventButton* event)
{
    double x_end_new = event->x, y_end_new = event->y;        
    if(x_end_new<=get_width() && x_end_new>=get_width()-10)
    {
        change_dimensions.change_width = true;
        }
    if(y_end_new <=get_height() && y_end_new >=get_height()-10)
    {
        change_dimensions.change_height = true;
        }

    //std::cout<<"x"<<x_end_new<<"y"<<y_end_new<<std::endl;
    double x_root = event->x_root, y_root=event->y_root;
    //std::cout<<"x_root"<<x_root<<"y_root"<<y_root<<std::endl;
   
    return FALSE;
    }

bool gtk_window::on_mouse_release(GdkEventButton* event)
{
    //std::cout<<"pressed window"<<std::endl;
    if(change_dimensions.change_height == true)
        set_size_request(get_width(),event->y);
    
    if(change_dimensions.change_width == true)
        set_size_request(event->x,get_height());

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

void gtk_window::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    Gtk::Requisition child_requisition_one = {0, 0};

    requisition->height = 200;
    requisition->width = 200;
    
    if(placeholder_child && placeholder_child->is_visible())
    {        
        child_requisition_one = placeholder_child->size_request();        
        int max_width = child_requisition_one.width;
        int total_height = child_requisition_one.height; 
        requisition->height = total_height;
        requisition->width = max_width;
        }
    }

void gtk_window::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);
    Gtk::Allocation child_allocation_one;  
    child_allocation_one.set_x(container_spacing);
    child_allocation_one.set_y(container_spacing);
    child_allocation_one.set_width(allocation.get_width()-container_spacing*2);
    child_allocation_one.set_height(allocation.get_height()-container_spacing*2);    
    if(placeholder_child && placeholder_child->is_visible())
        placeholder_child->size_allocate(child_allocation_one);

    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

void gtk_window::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    if(placeholder_child)
        callback(GTK_WIDGET(placeholder_child->gobj()), callback_data);
    }
    
void gtk_window::on_add(Gtk::Widget* child)
{
    if(!placeholder_child)
    {
        if(dynamic_cast<gtk_placeholder*>(child))
        {
            placeholder_child = dynamic_cast<gtk_placeholder*>(child);
            placeholder_child->set_parent(*this);
            }
        }
    }
void gtk_window::on_remove(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == placeholder_child)
        {
            placeholder_child = 0;
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

GtkType gtk_window::child_type_vfunc() const
{
//If there is still space for one widget, then report the type of widget that
//may be added.
    if(!placeholder_child)
        return Gtk::Widget::get_type();
    else
    {
    //No more widgets may be added.
        return G_TYPE_NONE;
    }
}

void gtk_window::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_window::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_window::on_realize()
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

void gtk_window::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_window::on_expose_event(GdkEventExpose* event)
{
    if(m_refGdkWindow)
    {
        double scale_x = (double)get_allocation().get_width()/m_scale;    
        double scale_y = (double)get_allocation().get_height()/m_scale;    
        Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
        if(event)
        {
            cr->rectangle(event->area.x,event->area.y,event->area.width,event->area.height);
            cr->clip();
            }
        Gdk::Cairo::set_source_color(cr,get_style()->get_bg(Gtk::STATE_NORMAL));
        cr->paint();
        /*Gdk::Cairo::set_source_color(cr,Gdk::Color("black"));
        int i=0,j=0;
        Gtk::Allocation allocation = get_allocation();
        for(i=0;i<=get_height();i=i+10)
        {
            for(j=0;j<=get_width();j=j+10)
            {
                cr->move_to(j,i);
                cr->line_to(j+1,i+1);
                }
            }*/
        Gdk::Cairo::set_source_color(cr,Gdk::Color("white"));
        cr->set_line_width(0.5);
        int i=0, j =0;
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
