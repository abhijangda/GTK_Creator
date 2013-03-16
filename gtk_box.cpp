//236 Lines
#include"gtk_box.h"
#include<iostream>
#include<string>

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

gtk_box::gtk_box(bool _homogeneous, float _spacing, int _slots)
    : homogeneous(_homogeneous), spacing(_spacing), slots(_slots),child_placeholder_vector(_slots),number_of_widgets(0),
      expand_vector(_slots,false),fill_vector(_slots,false)
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_box::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_box::on_mouse_release));    
    for(int i=0;i<_slots;i++)
    {
        child_placeholder_vector[i] = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
        child_placeholder_vector[i]->set_parent(*this);
        }        
    at_placeholder=-1;
    show_all_children();
    }

gtk_box::~gtk_box(){}
void  gtk_box::set_number_of_widgets(int _number)
{
    if(_number>slots)
    {        
        for(int i =_number-slots-1;i<_number;i++)
        {
            gtk_placeholder* _p  = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
            child_placeholder_vector.insert(child_placeholder_vector.end(),_p);
            _p->set_parent(*this);
            _p->show();
            }
        slots=_number;
        }
    else if(_number<slots)
    {
        for(int i= _number;i<slots;i++)
        {
            gtk_placeholder* _placeholder = child_placeholder_vector[i];
            Gtk::Widget* widget = _placeholder->get_child();
            _placeholder->remove_child(widget);
            delete widget;
            delete _placeholder;
            }
        child_placeholder_vector.resize(_number);
        slots=_number;
        }
    allocate_size(get_allocation());
    if(m_refGdkWindow)
    {
        Gdk::Rectangle rectangle(0,0,m_refGdkWindow->get_width(),m_refGdkWindow->get_height());
        m_refGdkWindow->invalidate_rect(rectangle,true);
        m_refGdkWindow->process_updates(true);
        }
    }

void gtk_box::remove_child(Gtk::Widget* child)
{
    for(int i = 0; i<child_placeholder_vector.size();i++)
    {
        if(child_placeholder_vector[i]->get_child()==child)
        {
            child_placeholder_vector[i]->remove_child(child);
            child_placeholder_vector[i]->show();
            number_of_widgets--;
            allocate_size(get_allocation());
            if(m_refGdkWindow)
            {
                Gdk::Rectangle rectangle(0,0,m_refGdkWindow->get_width(),m_refGdkWindow->get_height());
                m_refGdkWindow->invalidate_rect(rectangle,true);
                m_refGdkWindow->process_updates(true);
                }
            return;
            }
        }
    }

void gtk_box::allocate_size(Gtk::Allocation allocation)
{
    }

void gtk_box::draw_around_child(Gtk::Widget& widget)
{    
    }        

int gtk_box::append_child_widget(Gtk::Widget& child, int x, int y, int height, int width)
{
    slots++;
    gtk_placeholder* placeholder = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    placeholder->set_parent(*this);
    placeholder->set_child_widget(child,x,y,height,width);       
    child_placeholder_vector.insert(child_placeholder_vector.end(), placeholder);
    number_of_widgets++;
    show_all_children();
    return slots-1;
    }

gtk_container* gtk_box::get_current_placeholder()
{
    child_placeholder_vector[at_placeholder];
    }

int gtk_box::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{    
    if(number_of_widgets>=slots)
        return -1;    
    
    for(int i = 0; i<slots;i++)
    {        
        gtk_placeholder* placeholder = child_placeholder_vector[i];
        if(placeholder->at_this_placeholder)
        {
            placeholder->at_this_placeholder=false;
            at_placeholder=i;
            break;
            }             
        }
    if(at_placeholder==-1)
        return -1;
        
    gtk_placeholder* placeholder  = child_placeholder_vector[at_placeholder];
    if(placeholder->set_child_widget(child,x,y,height,width)==-1)
        return -1;    
    number_of_widgets++;
    show_all_children();    
    return at_placeholder;
    }

void gtk_box::set_expand_fill(Gtk::Widget& widget,bool _expand,bool _fill)
{
    for(int i=0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==&widget)
        {
            expand_vector[i] = _expand;
            fill_vector[i]=_fill;
            break;
            }
        }
    allocate_size(get_allocation());
    on_expose_event(NULL);
    }

void gtk_box::set_expand_fill_changes(Gtk::Widget& widget, bool _expand, bool _fill)
{
     for(int i=0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==&widget)
        {
            expand_vector[i] = _expand;
            fill_vector[i]=_fill;
            break;
            }
        }
    }

bool gtk_box::get_expand(Gtk::Widget* widget)
{
    for(int i=0;i<number_of_widgets;i++)
    {
        if(child_placeholder_vector[i]->get_child()==widget)
            return expand_vector[i];            
        }
    }
        
bool gtk_box::on_mouse_press(GdkEventButton* event)
{
    double x_end_new = event->x, y_end_new = event->y;       
    return FALSE;
    }

bool gtk_box::on_mouse_release(GdkEventButton* event)
{    
    return FALSE;
    }

void gtk_box::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    for(int i = 0;i<slots;i++)
    {
        if(child_placeholder_vector[i])
        {
            Gtk::Widget* widget = child_placeholder_vector[i];
            callback(widget->gobj(), callback_data);
            }
        }
    }

void gtk_box::on_add(Gtk::Widget* child)
{
    if(number_of_widgets<slots)
    {
        if(dynamic_cast<gtk_placeholder*>(child))
        {
            child_placeholder_vector[number_of_widgets-1]=dynamic_cast<gtk_placeholder*>(child);
            child_placeholder_vector[number_of_widgets-1]->set_parent(*this);      
            }
        }
    }
void gtk_box::on_remove(Gtk::Widget* child)
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

GtkType gtk_box::child_type_vfunc() const
{
//If there is still space for one widget, then report the type of widget that
//may be added.
    if(number_of_widgets<slots)
        return Gtk::Widget::get_type();
    else
    {
    //No more widgets may be added.
        return G_TYPE_NONE;
    }
}
void gtk_box::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_box::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_box::on_realize()
{
    Gtk::Widget::on_realize();
    ensure_style();
    //std::cout<<"ON REALIZE"<<std::endl;
    if(!m_refGdkWindow)
    {
        //std::cout<<"ON REALIZE m_refGdkWindow TRUE"<<std::endl;
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

void gtk_box::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }