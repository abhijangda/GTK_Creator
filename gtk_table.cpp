//285 Lines
#include"gtk_table.h"
#include<iostream>
#include"gtk_placeholder.h"

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;
extern bool can_set_focus;

_gtk_table::_gtk_table(int _row, int _col, bool _h,gtk_table& _parent)
 : Gtk::Table(_row,_col,_h), parent(_parent)
{
    }

_gtk_table::~_gtk_table(){}

bool _gtk_table::on_expose_event(GdkEventExpose* event)
{
    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    if(event)
    {
        cr->rectangle(event->area.x,event->area.y,event->area.width,event->area.height);
        cr->clip();
        }
    Gdk::Cairo::set_source_color(cr,get_style()->get_bg(Gtk::STATE_NORMAL));
    cr->paint();
    Gdk::Cairo::set_source_color(cr,Gdk::Color("black"));
    guint row,col;
    get_size(row,col);
    for(int i = 0;i<row*col;i++)
    {
        Gtk::Allocation allocation;
        allocation = parent.child_placeholder_vector[i]->get_allocation();
        cr->move_to(allocation.get_x(),allocation.get_y());
        cr->line_to(allocation.get_x()+allocation.get_width(),allocation.get_y());
        
        cr->move_to(allocation.get_x(),allocation.get_y());
        cr->line_to(allocation.get_x(),allocation.get_y()+allocation.get_height());
        
        cr->move_to(allocation.get_x(),allocation.get_y()+allocation.get_height());
        cr->line_to(allocation.get_x()+allocation.get_width(),allocation.get_y()+allocation.get_height());
        
        cr->move_to(allocation.get_x()+allocation.get_width(),allocation.get_y());
        cr->line_to(allocation.get_x()+allocation.get_width(),allocation.get_y()+allocation.get_height());
        }
    cr->stroke();       
    Gtk::Table::on_expose_event(event);
    return false;
    }

gtk_table::gtk_table(int _col, int _row,bool _homogeneous,int row_spacing=0,int col_spacing=0)
    :table(_row,_col,_homogeneous,*this),child_placeholder_vector(_row*_col),expand_vector(_row*_col),fill_vector(_row*_col)
{
    change_dimensions.change_width = false;
    change_dimensions.change_height = false;
    set_flags(Gtk::NO_WINDOW);
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&gtk_table::on_mouse_press));
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&gtk_table::on_mouse_release));    
    table.set_parent(*this);
    table.set_row_spacings(row_spacing);
    table.set_col_spacings(col_spacing);
    for(int i = 0; i<_row*_col;i++)
    {
        child_placeholder_vector[i] = new gtk_placeholder(table.get_style()->get_bg(Gtk::STATE_NORMAL));
        expand_vector[i]=true;
        fill_vector[i]=true;
        table.attach(*child_placeholder_vector[i],i%_row,i%_row+1,i/_col,i/_col+1);
        }
    number_of_widgets=0;
    show_all_children();
    }

gtk_table::~gtk_table(){}

/*int get_left_attach(Gtk::Widget& child)
{
    for(int i=0; i< child_placeholder_vector.size();i++)
    {
        if(child_placeholder_vector[i]->get_child()==&child)
        {
            
            }
        }
    }*/
int get_right_attach(Gtk::Widget& child)
{
    }
int get_top_attach(Gtk::Widget& child)
{
    }
int get_bottom_attach(Gtk::Widget& child)
{
    }
        
int gtk_table::set_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    dynamic_cast<gtk_container*>(child_placeholder_vector[number_of_widgets])->set_child_widget(child,x,y,height,width);
    number_of_widgets++;    
    return number_of_widgets-1;
    }
int gtk_table::append_child_widget(Gtk::Widget& child,int x, int y, int height, int width)
{
    return set_child_widget(child,x,y,height,width);
    }
void gtk_table::remove_child(Gtk::Widget* child)
{
    for(int i = 0; i<child_placeholder_vector.size();i++)
    {
        if(child_placeholder_vector[i]->get_child()==child)
        {
            child_placeholder_vector[i]->remove_child(child);
            return;
            }
        }
    }

void gtk_table::set_expand_fill(Gtk::Widget& widget,bool _expand,bool _fill)
{
    guint _row,_col;
    table.get_size(_row,_col);
    
    for(int i=0;i<number_of_widgets;i++)
    {
        gtk_placeholder* _ph = dynamic_cast<gtk_placeholder*>(child_placeholder_vector[i]);
        if(_ph->get_child()==&widget)
        {
            expand_vector[i] = _expand;
            fill_vector[i]=_fill;
            table.remove(*child_placeholder_vector[i]);
            Gtk::AttachOptions attach_opt;
            if(expand_vector[i])
               attach_opt |= Gtk::EXPAND;
            if(fill_vector[i])
              attach_opt|=Gtk::FILL;
            
            _ph->remove(widget);
            if(_ph)
                delete _ph;
            child_placeholder_vector[i]  = new gtk_placeholder(table.get_style()->get_bg(Gtk::STATE_NORMAL));            
            dynamic_cast<gtk_placeholder*>(child_placeholder_vector[i])->set_child_widget(widget,0,0,0,0);
            table.attach(*child_placeholder_vector[i],i%_row,i%_row+1,i/_col,i/_col+1,attach_opt,attach_opt);
            table.show_all_children();
            break; 
            }
        }
    }

bool gtk_table::get_expand(Gtk::Widget& widget)
{
    for(int i = 0; i< number_of_widgets;i++)
         if(dynamic_cast<gtk_placeholder*>(child_placeholder_vector[i])->get_child()==&widget && expand_vector[i])
            return false;
    }

bool gtk_table::get_fill(Gtk::Widget& widget)
{
    for(int i = 0; i< number_of_widgets;i++)
         if(dynamic_cast<gtk_placeholder*>(child_placeholder_vector[i])->get_child()==&widget && fill_vector[i])
            return false;
    }
void gtk_table::set_rows(int _number)
{
    guint row, col;
    table.get_size(row,col);
    table.resize(_number,col);
    }
void gtk_table::set_cols(int _number)
{
    guint row, col;
    table.get_size(row,col);
    table.resize(row,_number);
    }
int gtk_table::get_rows()
{
    guint row, col;
    table.get_size(row,col);
    return row;
    }
int gtk_table::get_cols()
{
    guint row, col;
    table.get_size(row,col);
    return col;
    }
        
bool gtk_table::on_mouse_press(GdkEventButton* event)
{
    return false;
    }

bool gtk_table::on_mouse_release(GdkEventButton* event)
{
    return FALSE;
    }

void gtk_table::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    requisition->height = 200;
    requisition->width = 200;
    Gtk::Requisition child_requisition_one = {0, 0};
    
    int width = table.size_request().width;
    int height =table.size_request().height;
    requisition->height = height;
    requisition->width = width;  
    }

void gtk_table::on_size_allocate(Gtk::Allocation& allocation)
{
    Gtk::Allocation child_allocation;
    child_allocation.set_y(0);
    child_allocation.set_x(0);
    child_allocation.set_width( allocation.get_width());
    child_allocation.set_height( allocation.get_height());
    table.size_allocate(child_allocation);
    
    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

void gtk_table::forall_vfunc(gboolean include_internals,GtkCallback callback, gpointer callback_data)
{
    callback(GTK_WIDGET(table.gobj()),callback_data);
    }

void gtk_table::on_add(Gtk::Widget* child)
{
    table.set_parent(*this);
    }

void gtk_table::on_remove(Gtk::Widget* child)
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

GtkType gtk_table::child_type_vfunc() const
{
    return Gtk::Widget::get_type();
    }

void gtk_table::on_map()
{
    Gtk::Widget::on_map();
    }

void gtk_table::on_unmap()
{
    Gtk::Widget::on_unmap();
    }

void gtk_table::on_realize()
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

void gtk_table::on_unrealize()
{
    m_refGdkWindow.clear();
    Gtk::Widget::on_unrealize();
    }

bool gtk_table::on_expose_event(GdkEventExpose* event)
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
        cr->stroke();
        }
    Gtk::Container::on_expose_event(event);
    return false;
    }
