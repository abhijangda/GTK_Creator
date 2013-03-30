//303 Lines
#include"gtk_fixed.h"
#include<iostream>
extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

gtk_fixed::gtk_fixed()
    :child_placeholder_vector(1),x_vector(1),y_vector(1),width_vector(1),height_vector(1),number_of_widgets(0)//,Glib::ObjectBase("gtk_fixed")
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_fixed::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_fixed::on_mouse_release));
    }

gtk_fixed::~gtk_fixed()
{
    for(int i = 0;i <number_of_widgets;i++)
    {
        if(child_placeholder_vector[i])
            delete child_placeholder_vector[i];
        }
    }

void gtk_fixed::remove_child(Gtk::Widget* child)
{
    for(int i = 0; i<child_placeholder_vector.size();i++)
    {
        if(child_placeholder_vector[i]->get_child()==child)
        {
            child_placeholder_vector[i]->remove_child(child);
            gtk_placeholder *p = child_placeholder_vector[i];
            for(int j=i;j<child_placeholder_vector.size()-1;j++)
            {
                child_placeholder_vector[j]=child_placeholder_vector[j+1];
                y_vector[j]=y_vector[j+1];
                x_vector[j]=x_vector[j+1];
                width_vector[j] =width_vector[j+1];
                height_vector[j]=height_vector[j+1];
                number_of_widgets--;
                }
            child_placeholder_vector.resize(child_placeholder_vector.size()-1);
            delete p;
            return;
            }
        }
    }

void gtk_fixed::draw_around_child(Gtk::Widget& widget)
{
    }

int gtk_fixed::get_x_of_child(Gtk::Widget& widget)
{
    for (int i =0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==&widget)
             return x_vector[i];
        }
    }

int gtk_fixed::get_y_of_child(Gtk::Widget& widget)
{
    for (int i =0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==&widget)
            return y_vector[i];
        }
    }

void gtk_fixed::set_x_of_child(Gtk::Widget& widget,int x)
{
    for (int i =0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==&widget)
        {            
            x_vector[i]=x;            
            Gtk::Allocation child_allocation = child_placeholder_vector[i]->get_allocation();
            child_allocation.set_y(y_vector[i]); 
            child_allocation.set_x(x_vector[i]); 
            //std::cout<<"set x"<<x_vector[i]<<std::endl;
            child_placeholder_vector[i]->size_allocate(child_allocation);                
            }
         }
    }

void gtk_fixed::set_y_of_child(Gtk::Widget& widget, int y)
{
    for (int i =0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==&widget)   
        {         
            y_vector[i]=y;
            Gtk::Allocation child_allocation = child_placeholder_vector[i]->get_allocation();
            child_allocation.set_y(y_vector[i]); 
            child_allocation.set_x(x_vector[i]); 
            //std::cout<<"set y"<<y_vector[i]<<std::endl;
            child_placeholder_vector[i]->size_allocate(child_allocation);
            }
        }
    }
int gtk_fixed::append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width)
{
    return set_child_widget(widget,x,y,height,width);
    }
int gtk_fixed::set_child_widget(Gtk::Widget& child,int x, int y, int _width, int _height)
{    
    if(_height<0 || _width <0)
        return -1;        
        
    
    gtk_placeholder* _placeholder = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    if(_placeholder->set_child_widget(child,x,y,width,height)==-1)
        return -1;
    
    Gtk::Allocation child_allocation;     
    child_allocation.set_y(y);         
    child_allocation.set_x(x); 
    
    /*std::cout<<_width<<"KK"<<width<<"KKKK"<<_height<<"FFFFF"<<height<<std::endl;
    if(x==1 && y==1)
    {
        child_allocation.set_width(width);
        child_allocation.set_height(height);
        }
    else
    {*/
        child_allocation.set_width(child.size_request().width);
        child_allocation.set_height(child.size_request().height);
    _placeholder->size_allocate(child_allocation);
    child_placeholder_vector[number_of_widgets]=_placeholder;

    x_vector[number_of_widgets]=x_new;
    y_vector[number_of_widgets]=y_new;

    _placeholder->set_parent(*this);
    number_of_widgets++;
    
    child_placeholder_vector.resize(number_of_widgets+1);
    x_vector.resize(number_of_widgets+1);
    y_vector.resize(number_of_widgets+1);
    show_all_children();
    return number_of_widgets-1;
    }

bool gtk_fixed::on_mouse_press(GdkEventButton* event)
{
    x_new = event->x;
    y_new = event->y;           
    return false;
    }

bool gtk_fixed::on_mouse_release(GdkEventButton* event)
{
    width= event->x - x_new;
    height = event->y- y_new;
    return false;
    }

void gtk_fixed::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    if(number_of_widgets==0)
    {
        requisition->height = 200;
        requisition->width = 200;
        return;
        }
    
    int height_max = get_height();
    int width_max= get_width();
     for(int i=0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->size_request().height+y_vector[i]>=height_max)
            height_max=child_placeholder_vector[i]->size_request().height+y_vector[i];
        if(child_placeholder_vector[i]->size_request().width+x_vector[i]>=width_max)
            width_max=child_placeholder_vector[i]->size_request().width+x_vector[i];
        }
    
    requisition->width  = width_max;
    requisition->height= height_max;
    if(number_of_widgets <=0)
        return;
    }

void gtk_fixed::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);
    int width,height;
    for(int i=0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->size_request().height>child_placeholder_vector[i]->get_height())
            height=child_placeholder_vector[i]->size_request().height;
        else
            height =child_placeholder_vector[i]->get_height();
        if(child_placeholder_vector[i]->size_request().width>child_placeholder_vector[i]->get_width())
            width=child_placeholder_vector[i]->size_request().width;
        else
            width =child_placeholder_vector[i]->get_width();
        Gtk::Allocation child_allocation;
        child_allocation.set_y(y_vector[i]); 
        child_allocation.set_x(x_vector[i]); 
        child_allocation.set_width(width);
        child_allocation.set_height(height);
        child_placeholder_vector[i]->size_allocate(child_allocation);
        }

    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

void gtk_fixed::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    for(int i = 0;i<number_of_widgets;i++)
       callback(GTK_WIDGET(child_placeholder_vector[i]->gobj()), callback_data);
}

void gtk_fixed::on_add(Gtk::Widget* child)
{
    if(!child_placeholder_vector[number_of_widgets])
    {
        if(dynamic_cast<gtk_placeholder*>(child))
        {
            child_placeholder_vector[number_of_widgets]=dynamic_cast<gtk_placeholder*>(child);
            child_placeholder_vector[number_of_widgets]->set_parent(*this);
            }
        }
    }

void gtk_fixed::on_remove(Gtk::Widget* child)
{
    /*if(child)
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
        }*/
    }

GtkType gtk_fixed::child_type_vfunc() const
{
//If there is still space for one widget, then report the type of widget that
//may be added.
        return Gtk::Widget::get_type();
        }
    
void gtk_fixed::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_fixed::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_fixed::on_realize()
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
    
        m_refGdkWindow->set_user_data(gobj());
        }
    }

void gtk_fixed::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_fixed::on_expose_event(GdkEventExpose* event)
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
        Gdk::Cairo::set_source_color(cr,Gdk::Color("black"));
        int i=0,j=0;
        for(i=0;i<=get_height();i=i+10)
        {
            for(j=0;j<=get_width();j=j+10)
            {
                cr->move_to(j,i);
                cr->line_to(j+1,i+1);
                }
            }
        cr->stroke();
        }
    if(event)
        Gtk::Container::on_expose_event(event);
    return false;
    }
