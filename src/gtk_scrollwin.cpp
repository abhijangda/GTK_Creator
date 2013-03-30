//216 Lines
#include"gtk_scrollwin.h"
#include<iostream>
extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;
extern bool can_set_focus;

gtk_scrollwin::gtk_scrollwin()
    : child_widget(0),horizontal_policy("AUTOMATIC"),vertical_policy("AUTOMATIC")
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_scrollwin::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_scrollwin::on_mouse_release));

    scroll_win = new Gtk::ScrolledWindow();
    scroll_win_widget = scroll_win;
    scroll_win->set_policy(Gtk::POLICY_ALWAYS,Gtk::POLICY_ALWAYS);
    child_widget = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    scroll_win->add(*child_widget);
    scroll_win->set_parent(*this);
    show_all_children();
    }

gtk_scrollwin::~gtk_scrollwin()
{
    delete child_widget;
    }

void gtk_scrollwin::draw_around_child(Gtk::Widget& widget)
{
    }

std::string gtk_scrollwin::get_horizontal_policy()
{
    Gtk::PolicyType h,v;
    scroll_win->get_policy(h,v);
    if(h==Gtk::POLICY_ALWAYS)
        return "ALWAYS";
    else if(h==Gtk::POLICY_AUTOMATIC)
         return "AUTOMATIC";
    else
         return "NEVER";
    }
void gtk_scrollwin::set_horizontal_policy(std::string _policy)
{
    Gtk::PolicyType h,v;
    scroll_win->get_policy(h,v);
    if(_policy=="ALWAYS" )
        scroll_win->set_policy(Gtk::POLICY_ALWAYS,v);
    else if(_policy=="AUTOMATIC" )
         scroll_win->set_policy(Gtk::POLICY_AUTOMATIC,v); 
    else
          scroll_win->set_policy(Gtk::POLICY_NEVER,v);
    }

std::string gtk_scrollwin::get_vertical_policy()
{
    Gtk::PolicyType h,v;
    scroll_win->get_policy(h,v);
    if(v==Gtk::POLICY_ALWAYS)
        return "ALWAYS";
    else if(v==Gtk::POLICY_AUTOMATIC)
         return "AUTOMATIC";
    else
         return "NEVER";
    }
void gtk_scrollwin::set_vertical_policy(std::string _policy)
{
    Gtk::PolicyType h,v;
    scroll_win->get_policy(h,v);
    if(_policy=="ALWAYS" )
        scroll_win->set_policy(h,Gtk::POLICY_ALWAYS);
    else if(_policy=="AUTOMATIC" )
         scroll_win->set_policy(h,Gtk::POLICY_AUTOMATIC); 
    else
          scroll_win->set_policy(h,Gtk::POLICY_NEVER);
    }
            
void gtk_scrollwin::remove_child(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == dynamic_cast<gtk_placeholder*>(child_widget)->get_child())
        {
            dynamic_cast<gtk_placeholder*>(child_widget)->remove_child(child);
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

int gtk_scrollwin::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    if(dynamic_cast<gtk_placeholder*>(child_widget)->get_child())
        return -1;
    dynamic_cast<gtk_placeholder*>(child_widget)->set_child_widget(child,x,y,height,width);
    show_all_children();
    return 0;
    }
int gtk_scrollwin::append_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    return set_child_widget(child,x,y,height,width);
    }

bool gtk_scrollwin::on_mouse_press(GdkEventButton* event)
{   
    return FALSE;
    }

bool gtk_scrollwin::on_mouse_release(GdkEventButton* event)
{    
    return FALSE;
    }
void gtk_scrollwin::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    requisition->height = 200;
    requisition->width = 200;
    Gtk::Requisition child_requisition_one = {0, 0};
    
    if (!scroll_win_widget)
        return;     
    int width = scroll_win_widget->size_request().width;
    int height =scroll_win_widget->size_request().height;
    requisition->height = height;
    requisition->width = width;   
    }

void gtk_scrollwin::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);
    
    
    //Place the first child at the top-left,
    if(scroll_win)
    {
        Gtk::Allocation child_allocation;
        child_allocation.set_y(0);
        child_allocation.set_x(0);
        //Make it take up the full width available:
        child_allocation.set_width( allocation.get_width());
        child_allocation.set_height( allocation.get_height());
        scroll_win_widget->size_allocate(child_allocation);
        }       
    
    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

void gtk_scrollwin::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    if(scroll_win_widget)
        callback(scroll_win_widget->gobj(), callback_data);
}

void gtk_scrollwin::on_add(Gtk::Widget* child)
{
     
    if(!scroll_win_widget)
    {
        scroll_win_widget = child;
        scroll_win_widget->set_parent(*this);
        }
    }
void gtk_scrollwin::on_remove(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == scroll_win_widget)
        {
            child_widget = 0;
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

GtkType gtk_scrollwin::child_type_vfunc() const
{
//If there is still space for one widget, then report the type of widget that
//may be added.
    if(!scroll_win_widget)
        return Gtk::Widget::get_type();
    else
    {
    //No more widgets may be added.
        return G_TYPE_NONE;
    }
}

void gtk_scrollwin::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_scrollwin::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_scrollwin::on_realize()
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
        
        //modify_bg(Gtk::STATE_NORMAL,bg_color);
        //modify_fg(Gtk::STATE_NORMAL,bg_color);
        
        m_refGdkWindow->set_user_data(gobj());
        }
    }

void gtk_scrollwin::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_scrollwin::on_expose_event(GdkEventExpose* event)
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
    if(event)
        Gtk::Container::on_expose_event(event);
    return true;
    }
