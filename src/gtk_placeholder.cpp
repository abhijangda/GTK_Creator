//280 lines
#include"gtk_placeholder.h"
#include<iostream>

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;
extern focused_widget current_pressed_placeholder;
gtk_placeholder::gtk_placeholder(Gdk::Color color)
    :bg_color(color),m_child_one(0)
{
    set_flags(Gtk::NO_WINDOW);
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_placeholder::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_placeholder::on_mouse_release));
    at_this_placeholder=false;
    draw_borders = false;
    }
int gtk_placeholder::append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width)
{
    return set_child_widget(widget,x,y,height,width);
    }
void gtk_placeholder::draw_around_borders()
{
    Gtk::Allocation allocation = get_allocation();
    Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
    Gdk::Cairo::set_source_color(cr,Gdk::Color("blue"));
    int i=0,j=0;   
    
    cr->set_line_width(1.0);
    
    cr->move_to(0,0);
    cr->line_to(get_width()-1,0);
    
    cr->move_to(0,0);
    cr->line_to(0,get_height()-1);
    
    cr->move_to(get_width()-1,0);
    cr->line_to(get_width()-1,get_height()-1);
    
    cr->move_to(0,get_height()-1);
    cr->line_to(get_width()-1,get_height()-1);
    
    cr->stroke();
    }

void gtk_placeholder::redraw_placeholder()
{
    if(m_refGdkWindow)
    {
        Gdk::Rectangle rectangle(0,0,m_refGdkWindow->get_width(),m_refGdkWindow->get_height());
        m_refGdkWindow->invalidate_rect(rectangle,true);
        m_refGdkWindow->process_updates(true);
        }
    }

void gtk_placeholder::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    Gtk::Requisition child_requisition_one = {0, 0};

    requisition->height = 200;
    requisition->width = 200;
    
    if(m_child_one && m_child_one->is_visible())
    {
        child_requisition_one = m_child_one->size_request();    
        int max_width = child_requisition_one.width; 
        int total_height = child_requisition_one.height; 
        requisition->height = total_height;
        requisition->width = max_width;   
        }    
    }

Gtk::Widget* gtk_placeholder::get_parent()
{
    Gtk::Widget* _widget  = Gtk::Widget::get_parent();
    if(_widget->get_name()=="gtkmm__GtkNotebook"||_widget->get_name()=="GtkViewport")
        return _widget->get_parent()->get_parent(); //because gtk_notebook is also in a placeholder of gtk_eventbox
    else if(_widget->get_name()=="gtkmm__GtkTable"||_widget->get_name()=="gtkmm__GtkFrame")
        return _widget->get_parent();
    return _widget;
    }

void gtk_placeholder::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);
    Gtk::Allocation child_allocation_one;
    //Place the first child at the top-left,
    child_allocation_one.set_x(1);
    child_allocation_one.set_y(1);
    //Make it take up the full width available:
    child_allocation_one.set_width(allocation.get_width()-2);
    child_allocation_one.set_height(allocation.get_height()-2);
    if(m_child_one && m_child_one->is_visible())
    m_child_one->size_allocate(child_allocation_one);

    if(m_refGdkWindow)
    {
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
        }
    }

void gtk_placeholder::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    if(m_child_one)
        callback(m_child_one->gobj(), callback_data);
    }

void gtk_placeholder::on_add(Gtk::Widget* child)
{
    if(!m_child_one)
    {
        m_child_one = child;
        m_child_one->set_parent(*this);
        }
    }
void gtk_placeholder::on_remove(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == m_child_one)
        {
            m_child_one = 0;
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

GtkType gtk_placeholder::child_type_vfunc() const
{
    if(!m_child_one)
        return Gtk::Widget::get_type();
    else
    {
    //No more widgets may be added.
        return G_TYPE_NONE;
       }
   }

void gtk_placeholder::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_placeholder::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_placeholder::on_realize()
{
    Gtk::Widget::on_realize();
    ensure_style();
    
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

void gtk_placeholder::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_placeholder::on_expose_event(GdkEventExpose* event)
{
    if(m_refGdkWindow)
    {
        Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
        if(event)
        {
            cr->rectangle(event->area.x,event->area.y,event->area.width,event->area.height);
            cr->clip();
            }
        if(m_child_one)
        {
            cr->set_source_rgba(0,0,0,0);
            cr->paint();
            }
        else
        {            
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
        if(draw_borders)
            draw_around_borders();
        }
    Gtk::Container::on_expose_event(event);
    return true;
    }

int gtk_placeholder::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    if(m_child_one)
        return -1;
    m_child_one = &child;
    m_child_one->set_parent(*this);
    return 0;
    }

void gtk_placeholder::remove_child(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(child == m_child_one)
        {
            m_child_one = 0;
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

void gtk_placeholder::set_focussed_widget_as_child_widget()
{
    if(!m_child_one)
        return;
    current_focused_widget.set_value(m_child_one);
    }

bool gtk_placeholder::on_mouse_press(GdkEventButton* event)
{
    return false;    
    }

bool gtk_placeholder::on_mouse_release(GdkEventButton* event)
{
    at_this_placeholder=true;
    if(m_child_one)
         set_focussed_widget_as_child_widget();
    else
        current_focused_widget.set_value(get_parent());
    current_pressed_placeholder.set_value(this);
    return true;
    }

gtk_placeholder::~gtk_placeholder()
{
    }
