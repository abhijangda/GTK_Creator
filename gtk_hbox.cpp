//172 Lines
#include"gtk_hbox.h"
#include<iostream>
extern Gtk::Widget* focussed_widget;

gtk_hbox::gtk_hbox(bool _homogeneous, float _spacing, int _slots)
    : gtk_box(_homogeneous,_spacing,_slots)
{
    show_all_children();
    }

gtk_hbox::~gtk_hbox()
{
    for(int i = 0;i <slots;i++)
    {
        if(child_placeholder_vector[i])
            delete child_placeholder_vector[i];
        }
    }

void gtk_hbox::on_size_request(Gtk::Requisition* requisition)
{
    *requisition = Gtk::Requisition();
    requisition->height = 200;
    requisition->width = 200;
    Gtk::Requisition child_requisition_one = {0, 0};
    
    if(slots <=0)
        return;
        
    int total_width = 0;
    int max_height =child_placeholder_vector[0]->size_request().height;
    for(int i=0;i<slots;i++)
    {
        if(child_placeholder_vector[i])
        {            
            total_width += child_placeholder_vector[i]->size_request().width;
            if(child_placeholder_vector[i]->size_request().width >total_width)
                max_height = child_placeholder_vector[0]->size_request().height;
            }
        else
            total_width += get_width()/slots;
        }    
    requisition->height = max_height;
    requisition->width = total_width;   
    }

void gtk_hbox::allocate_size(Gtk::Allocation allocation)
{
    if(slots==0)
        return;
    int child_width = (float)allocation.get_width()/slots- (slots-1)*spacing/slots;
    int child_height= allocation.get_height();
    if(homogeneous||number_of_widgets<slots)
    {    
        //Place the first child at the top-left,
        
        for(int i=0;i<slots;i++)
        {
            Gtk::Allocation child_allocation;
            child_allocation.set_x(i*(child_width+spacing));
            child_allocation.set_y(0);
            //Make it take up the full width available:
            child_allocation.set_width(child_width);
            child_allocation.set_height( child_height);
            if(child_placeholder_vector[i])
                child_placeholder_vector[i]->size_allocate(child_allocation);
            }
        }
    else if(number_of_widgets==slots)
    {
        int i,total_width_of_nonexpand=0,number_of_expands=0;
        for(i=0;i<number_of_widgets;i++)
        {
            if(expand_vector[i])
                number_of_expands++;
            else
                total_width_of_nonexpand+=child_placeholder_vector[i]->get_width();
            }        
        int pos_x=0;
        int width_of_expand=0;
        if(number_of_expands)
             width_of_expand = (get_width()-total_width_of_nonexpand-(number_of_widgets-1)*spacing)/number_of_expands;
        
        for(i=0;i<number_of_widgets;i++)
        {            
            if(expand_vector[i])
            {
                Gtk::Allocation child_allocation;
                child_allocation.set_x(pos_x);
                child_allocation.set_y(0);
                //Make it take up the full width available:
                child_allocation.set_height(child_height);
                child_allocation.set_width(width_of_expand);
                child_placeholder_vector[i]->size_allocate(child_allocation);
                pos_x+=width_of_expand+spacing;
                }
            else
            {
                Gtk::Allocation child_allocation;
                child_allocation.set_x(pos_x);
                child_allocation.set_y(0);
                //Make it take up the full width available:
                child_allocation.set_height(child_height);
                child_allocation.set_width(child_placeholder_vector[i]->size_request().width);
                child_placeholder_vector[i]->size_allocate(child_allocation);
                pos_x+=child_placeholder_vector[i]->size_request().width+spacing;                
                }   
            }
        }
    }

void gtk_hbox::on_size_allocate(Gtk::Allocation& allocation)
{
    set_allocation(allocation);    
    allocate_size(allocation);
    if(m_refGdkWindow)
        m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),allocation.get_width(),allocation.get_height());
    }

bool gtk_hbox::on_expose_event(GdkEventExpose* event)
{
    //std::cout<<"Widget_expose_event"<<std::endl;
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
        cr->set_line_width(1.0);
        if(number_of_widgets!=slots)
        {
            float child_width = (float)get_width()/slots- (slots-1)*spacing/slots;
            //std::cout<<"slots"<<slots<<"heightofslot"<<width_of_slot<<std::endl;
            for(int i=1;i<slots;i++)
            {
               for(int j = 0;j<=spacing;j++)
                {
                    cr->move_to(i*child_width+(i-1)*spacing+j,0);
                    cr->line_to(i*child_width+(i-1)*spacing+j,get_height());
                    }  
                }        
            }
        cr->stroke();
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
        }
    if(event)
        Gtk::Container::on_expose_event(event);
    return false;
    }
