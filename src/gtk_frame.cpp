//249 Lines
#include "gtk_frame.h"

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

gtk_frame::gtk_frame(Gtk::Label* _label)
    :child_placeholder(0),frame(0),label(_label)
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    //set_redraw_on_allocate(false);
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_frame::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_frame::on_mouse_release));
    add_events(Gdk::POINTER_MOTION_MASK);
    signal_motion_notify_event().connect(sigc::mem_fun(*this,&gtk_frame::on_motion_notify_event));   
    frame = new Gtk::Frame("Frame");
    frame->set_parent(*this);
    child_placeholder = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    frame->add(*child_placeholder);
    frame->show();
    if(label)
        frame->set_label_widget(*label);
    else
        frame->set_label("Frame");
    show_all_children();
    }

gtk_frame::~gtk_frame()
{
    delete label;
    delete child_placeholder;
    delete frame;
    }
void gtk_frame::set_label(Gtk::Label* _label)
{
    label=_label;
    frame->set_label_widget(*label);
    }
int gtk_frame::append_child_widget(Gtk::Widget& widget,int x, int y, int height, int width)
{
    return set_child_widget(widget,x,y,height,width);
    }
void gtk_frame::remove_child(Gtk::Widget* child)
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

int gtk_frame::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{       
    if(child_placeholder->set_child_widget(child,x,y,height,width)==-1)
        return -1;
    show_all_children();
    return 0;
    }

bool gtk_frame::on_motion_notify_event(GdkEventMotion* event)
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

bool gtk_frame::on_mouse_press(GdkEventButton* event)
{
    return FALSE;
    }

bool gtk_frame::on_mouse_release(GdkEventButton* event)
{
    return FALSE;
    }

void gtk_frame::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    Gtk::Requisition child_requisition_one = {0, 0};

    if(frame && frame->is_visible())
    child_requisition_one = frame->size_request();
    
    //See which one has the most width:
    int max_width = child_requisition_one.width; 
    //Add the heights together:
    int total_height = child_requisition_one.height; 
    //Request the width for this container based on the sizes requested by its
    //child widgets:
    requisition->height = total_height;
    requisition->width = max_width;   
    }

void gtk_frame::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);
    Gtk::Allocation child_allocation_one;
    //Place the first child at the top-left,
    child_allocation_one.set_x(0);
    child_allocation_one.set_y(0);
    //Make it take up the full width available:
    child_allocation_one.set_width(allocation.get_width());
    child_allocation_one.set_height(allocation.get_height());    
    if(frame && frame->is_visible())
         frame->size_allocate(child_allocation_one);

    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

void gtk_frame::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    if(frame)
        callback(GTK_WIDGET(frame->gobj()), callback_data);
    }

void gtk_frame::on_add(Gtk::Widget* child)
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

void gtk_frame::on_remove(Gtk::Widget* child)
{
    if(child)
    {
        const bool visible = child->is_visible();
        bool found = false;
        if(dynamic_cast<gtk_placeholder*>(child) == child_placeholder)
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

GtkType gtk_frame::child_type_vfunc() const
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

void gtk_frame::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_frame::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_frame::on_realize()
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

void gtk_frame::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_frame::on_expose_event(GdkEventExpose* event)
{
    if(m_refGdkWindow)
    {
        Cairo::RefPtr<Cairo::Context> cr = m_refGdkWindow->create_cairo_context();
        if(event)
        {
            cr->rectangle(event->area.x,event->area.y,event->area.width,event->area.height);
            cr->clip();
            }
        Gdk::Cairo::set_source_color(cr,frame->get_style()->get_bg(Gtk::STATE_NORMAL));
        cr->paint();        
        }
    if(event)
         Gtk::Container::on_expose_event(event);
    return true;
    }
