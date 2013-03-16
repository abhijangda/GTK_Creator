//167 Lines
#include"gtk_vbox.h"
#include<iostream>
extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

gtk_vbox::gtk_vbox(bool _homogeneous, float _spacing, int _slots)
    : gtk_box(_homogeneous,_spacing,_slots)
{
    show_all_children();
    }

gtk_vbox::~gtk_vbox()
{
    for(int i = 0;i <slots;i++)
    {
        if(child_placeholder_vector[i])
            delete child_placeholder_vector[i];
        }
    }

void gtk_vbox::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    requisition->height = 200;
    requisition->width = 200;
    Gtk::Requisition child_requisition_one = {0, 0};
    
    if(slots <=0)
        return;
        
    int max_width = child_placeholder_vector[0]->size_request().width;
    int total_height =0;
    for(int i=0;i<slots;i++)
    {
        if(child_placeholder_vector[i])
        {            
            total_height += child_placeholder_vector[i]->size_request().height;
            if(child_placeholder_vector[i]->size_request().width >max_width)
                max_width = child_placeholder_vector[0]->size_request().width;
            }
        else
            total_height += get_height()/slots;
        }
    requisition->height = total_height;
    requisition->width = max_width;   
    }

void gtk_vbox::allocate_size(Gtk::Allocation allocation)
{    
    int child_width = allocation.get_width();
    if(slots==0)
        return;
    int child_height= (float)allocation.get_height()/slots- (slots-1)*spacing/slots;
    if(homogeneous||number_of_widgets<slots)
    {    
        for(int i=0;i<slots;i++)
        {
            Gtk::Allocation child_allocation;                
            child_allocation.set_y(i*(child_height+spacing));
            child_allocation.set_x(0);
            child_allocation.set_width(child_width);
            child_allocation.set_height(child_height);
            if(child_placeholder_vector[i])
                child_placeholder_vector[i]->size_allocate(child_allocation);
            }
        }
    else if(number_of_widgets==slots)
    {
        int i,total_height_of_nonexpand=0,number_of_expands=0;
        for(i=0;i<number_of_widgets;i++)
        {
            if(expand_vector[i])
                number_of_expands++;
            else
                total_height_of_nonexpand+=child_placeholder_vector[i]->size_request().height;
            }        
        int pos_y=0;
        int height_of_expand=0;
        if(number_of_expands)
             height_of_expand = (get_height()-total_height_of_nonexpand-(number_of_widgets-1)*spacing)/number_of_expands;
            
        for(i=0;i<number_of_widgets;i++)
        {            
            if(expand_vector[i])
            {                
                Gtk::Allocation child_allocation;
                child_allocation.set_y(pos_y);
                child_allocation.set_x(0);
                child_allocation.set_width(allocation.get_width());
                child_allocation.set_height(height_of_expand);
                child_placeholder_vector[i]->size_allocate(child_allocation);
                pos_y+=height_of_expand+spacing;
                }
            else
            {
                Gtk::Allocation child_allocation;
                child_allocation.set_y(pos_y);
                child_allocation.set_x(0);
                child_allocation.set_width(allocation.get_width());
                child_allocation.set_height(child_placeholder_vector[i]->size_request().height);
                child_placeholder_vector[i]->size_allocate(child_allocation);
                pos_y+=child_placeholder_vector[i]->size_request().height+spacing;                
                }
            }
        }
    }

void gtk_vbox::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);    
    allocate_size(allocation);
    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

bool gtk_vbox::on_expose_event(GdkEventExpose* event)
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
        
        Gdk::Cairo::set_source_color(cr,Gdk::Color("blue"));
    
        Gdk::Cairo::set_source_color(cr,Gdk::Color("white"));
        cr->set_line_width(0.5);
        int i=0,j=0;
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
        cr->set_line_width(1.0);
        Gdk::Cairo::set_source_color(cr,Gdk::Color("black"));
        if(number_of_widgets!=slots)
        {
            float child_height = (float)get_height()/slots- (slots-1)*spacing/slots;
            for(int i=1;i<slots;i++)
            {
                for(int j = 0;j<=spacing;j++)
                {
                    cr->move_to(0,i*child_height+(i-1)*spacing+j);
                    cr->line_to(get_width(),i*child_height+(i-1)*spacing+j);
                    }                
                }
            }
        cr->stroke();
        }
    if(event)
        Gtk::Container::on_expose_event(event);
    return false;
    }