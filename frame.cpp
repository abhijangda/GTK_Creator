//367 Lines

#include"frame.h"
#include"gtk_window.h"
#include"gtk_vbox.h"
#include"gtk_hbox.h"
#include"gtk_table.h"
#include"gtk_fixed.h"
#include"gtk_scrollwin.h"
#include"gtk_textview.h"
#include"gtk_label.h"
#include"box_dialog.h"
#include"gtk_button.h"
#include"gtk_notebook.h"
#include"gtk_toolbar.h"
#include"gtk_menubar.h"
#include"gtk_eventbox.h"
#include"gtk_offscreenwindow.h"
#include"gtk_frame.h"
#include"gtk_button.h"
#include"gtk_combobox.h"
#include"gtk_entry.h"
#include"gtk_spinbutton.h"
#include"gtk_scale.h"
#include"gtk_hscrollbar.h"
#include"gtk_treeview.h"
#include"gtk_progressbar.h"
#include"gtk_spinner.h"

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

Frame::Frame(std::string name,ToolBox& toolbox)
    :Gtk::EventBox(),_frame(name),fixed(),scrollwin(),number_of_widgets(0),
    tool_box(toolbox),widget_tree()
{
    modify_bg(Gtk::STATE_NORMAL,Gdk::Color("white"));
    modify_fg(Gtk::STATE_NORMAL,Gdk::Color("white"));
    modify_bg(Gtk::STATE_ACTIVE,Gdk::Color("white"));
    modify_fg(Gtk::STATE_ACTIVE,Gdk::Color("white"));
    modify_bg(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
    modify_fg(Gtk::STATE_INSENSITIVE,Gdk::Color("white"));
    modify_bg(Gtk::STATE_SELECTED,Gdk::Color("white"));
    modify_fg(Gtk::STATE_SELECTED,Gdk::Color("white"));
    modify_bg(Gtk::STATE_PRELIGHT,Gdk::Color("white"));
    modify_fg(Gtk::STATE_PRELIGHT,Gdk::Color("white"));
    
    scrollwin.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    //scrollwin.add(fixed);
    _frame.add(fixed);
    //_frame.add(scrollwin);
    add(_frame);
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);   
    //scrollwin.add_events(Gdk::BUTTON_PRESS_MASK);
    //scrollwin.add_events(Gdk::BUTTON_RELEASE_MASK); 
    signal_button_press_event().connect(sigc::mem_fun(*this,&Frame::on_mouse_pressed));
    signal_button_release_event().connect(sigc::mem_fun(*this,&Frame::on_mouse_released)); 
    has_window = false;
    current_item = NULL;
    draw_widget=false;
    type_of_widget="";
    toolbox.signal_can_draw_widget().connect(sigc::mem_fun(*this,&Frame::on_can_draw_widget));
    }

Frame::~Frame(){}

void Frame::on_notebook_page_added(gtk_notebook* notebook, gtk_label* label, int index)
{
    item* notebook_item = widget_tree.get_item_from_widget(notebook);
    item* label_item = new item(*label,std::string("gtk_label"),NULL,NULL,NULL,NULL);
    number_of_widgets++;    
    std::ostringstream oss1;
    oss1<<number_of_widgets;
    label->set_name("WIDGET"+oss1.str());
    notebook_item->insert_child_at(label_item,index);
    current_item=label_item;
    m_signal_widget_added();
    }

bool Frame::if_name_already_exists(std::string name)
{
    return _if_name_already_exists(name, widget_tree.parent_item); 
    }

bool Frame::_if_name_already_exists(std::string name, item* _item)
{
    while(_item)
    {
        if(name==_item->widget->get_name())
            return true;
                    
        if(_item->child)
            if(_if_name_already_exists(name,_item->child))
                return true;
                
        _item=_item->next;        
        }
    return false;
    }

bool Frame::on_mouse_pressed(GdkEventButton *event)
{
    if(draw_widget == true)
    {
        x_start = event->x;
        y_start = event->y;
        }
    return FALSE;
    }

Frame::type_signal_widget_added Frame::signal_widget_added()
{
    return Frame::m_signal_widget_added;
    }

void Frame::on_can_draw_widget(std::string type)
{
    draw_widget=true;
    type_of_widget=type;
    }

void Frame::func_draw_widget(double width, double height)
{
    bool added = false;
    int insert_at_pos=-1;
    
    if(!draw_widget)
        return;
           
    gtk_container* container = NULL;        
    Gtk::Widget* widget = NULL;
    Gtk::Widget* focussed_widget=NULL;
    try
    {                
        if(current_item && dynamic_cast<gtk_container*>(current_item->widget)!=NULL)
        {            
            container= dynamic_cast<gtk_container*>(current_item->widget);
            container_item = widget_tree.get_item_from_widget(current_item->widget);
            if(container_item == NULL)
                container_item = widget_tree.parent_item;
            }
        else
            container_item = widget_tree.parent_item;
        }
    
    catch(...){}            
    if(container)
        std::cout<<"CONTAINER NOT NULL"<<std::endl;
    else
        std::cout<<"CONTAINER NULL"<<std::endl;
    if(type_of_widget == "gtk_window")
    {
        gtk_window* window = new gtk_window(scrollwin.get_style()->get_bg(Gtk::STATE_NORMAL));
        number_of_widgets++;
        window->set_size_request(x_start,y_start);
        fixed.put(*window,0,0);            
        fixed.show_all_children();
        window->set_name("");
        widget_tree.parent_item = new item(*window,std::string("gtk_window"),NULL,NULL,NULL,NULL);    
        focussed_widget = window;
        added=true;
        }
    else if(type_of_widget == "gtk_offscreenwindow")
    {
        gtk_offscreenwindow* window = new gtk_offscreenwindow(scrollwin.get_style()->get_bg(Gtk::STATE_NORMAL));
        number_of_widgets++;
        window->set_size_request(x_start,y_start);
        fixed.put(*window,0,0);
        fixed.show_all_children();
        window->set_name("");
        widget_tree.parent_item = new item(*window,std::string("gtk_offscreenwindow"),NULL,NULL,NULL,NULL);    
        focussed_widget = window;
        added=true;
        }
    else if(type_of_widget == "gtk_vbox")
    {
        BoxDialog vbox_dialog("Add VBox");
        vbox_dialog.show_all_children();
        bool homogeneous;
        int slots;
        float spacing;
        
        if(vbox_dialog.run())
        {
            homogeneous = vbox_dialog.rbTrue.get_active();
            std::istringstream str_slots(vbox_dialog.entrySlots.get_text()), str_spacing(vbox_dialog.entrySpacing.get_text());
            str_slots>>slots;
            str_spacing>>spacing;
            widget = new gtk_vbox(homogeneous,spacing,slots);                 
            }            
        }
    else if(type_of_widget == "gtk_button")       
        widget = new gtk_button("Button");            
        
    else if(type_of_widget == "gtk_hbox")
    {
        BoxDialog vbox_dialog("Add HBox");
        vbox_dialog.show_all_children();
        bool homogeneous;
        int slots;
        float spacing;
        
        if(vbox_dialog.run())
        {
            homogeneous = vbox_dialog.rbTrue.get_active();
            std::istringstream str_slots(vbox_dialog.entrySlots.get_text()), str_spacing(vbox_dialog.entrySpacing.get_text());
            str_slots>>slots;
            str_spacing>>spacing;                
            widget = new gtk_hbox(homogeneous,spacing,slots);                
            }            
        }
    else if(type_of_widget == "gtk_table")
    {         
        TableDialog tb("Add Table");
        tb.show_all_children();
        
        bool homogeneous=false;
        int rows,cols;
        float row_spacing,col_spacing;
        
        if(tb.run())
        {
            homogeneous = tb.rbTrue.get_active();
            std::istringstream  str_rows(tb.entryRows.get_text()), str_cols(tb.entryColumns.get_text()), str_row_spacing(tb.entryRowSpacing.get_text()), str_col_spacing(tb.entryColumnSpacing.get_text());
            str_rows>>rows;
            str_cols>>cols;
            str_row_spacing>>row_spacing;
            str_col_spacing>>col_spacing;
            
            widget = new gtk_table(rows,cols,homogeneous,row_spacing,col_spacing);
            }
        }
    else if(type_of_widget == "gtk_fixed")
        widget = new gtk_fixed(); 
    else if(type_of_widget == "gtk_scrollwin")
        widget = new gtk_scrollwin(); 
    else if(type_of_widget == "gtk_textview")
        widget = new gtk_textview(); 
    else if(type_of_widget == "gtk_entry")
        widget = new gtk_entry(); 
    else if(type_of_widget == "gtk_label")
        widget = new gtk_label("Label"); 
    else if(type_of_widget == "gtk_togglebutton")
        widget = new gtk_togglebutton("Toggle Button");           
    else if(type_of_widget == "gtk_combobox")
        widget = new gtk_combobox(); 
    else if(type_of_widget == "gtk_comboboxtext")
        widget = new gtk_comboboxtext(true); 
    else if(type_of_widget == "gtk_checkbutton")
        widget = new gtk_checkbutton("Check Button"); 
    else if(type_of_widget == "gtk_radiobutton")
        widget = new gtk_radiobutton("Radio Button");        
    else if(type_of_widget == "gtk_statusbar")
        widget = new Gtk::Statusbar(); 
    else if(type_of_widget == "gtk_menubar")
        widget = new gtk_menubar(); 
    else if(type_of_widget == "gtk_toolbar")
        widget = new gtk_toolbar();         
    else if(type_of_widget == "gtk_eventbox")
        widget = new gtk_eventbox(scrollwin.get_style()->get_bg(Gtk::STATE_NORMAL));
    else if(type_of_widget == "gtk_expander")
         widget = new Gtk::Expander("Expander");        
    else if(type_of_widget == "gtk_spinbutton")
        widget = new gtk_spin_button();
    else if(type_of_widget == "gtk_filechooserbutton")
        widget = new Gtk::FileChooserButton("File Chooser Button");
    else if(type_of_widget == "gtk_colorchooserbutton")
        widget = new Gtk::ColorButton();        
    else if(type_of_widget == "gtk_fontbutton")
        widget = new Gtk::FontButton("Font Button");   
    else if(type_of_widget == "gtk_hscale")
        widget = new gtk_hscale();
    else if(type_of_widget == "gtk_vscale")
        widget = new gtk_vscale();
    else if(type_of_widget == "gtk_hscrollbar")
        widget = new gtk_hscrollbar();
    else if(type_of_widget == "gtk_progressbar")
        widget = new gtk_progressbar();
    else if(type_of_widget == "gtk_spinner")
        widget = new gtk_spinner();
    else if(type_of_widget == "gtk_treeview")
        widget = new gtk_treeview();
    else if(type_of_widget == "gtk_iconview")
        widget = new Gtk::IconView();            
    else if(type_of_widget == "gtk_frame")
    {
        gtk_label* label = new gtk_label("Frame");
        gtk_frame* frame = new gtk_frame(label);
        
        if(container)  
            if((insert_at_pos=container->set_child_widget(*frame,0,0,width,height))!=-1)
                added = true;
        
        if(added)
        {
            item* __item = new item(*dynamic_cast<Gtk::Widget*>(frame),type_of_widget,NULL,NULL,NULL,NULL);
            container_item->insert_child_at(__item,insert_at_pos);
            __item->insert_child_at(new item (*(frame->get_label()),"gtk_label",NULL,NULL,NULL,NULL),1);
            number_of_widgets++;
            std::ostringstream oss1;
            oss1<<number_of_widgets;
            frame->get_label()->set_name("WIDGET "+oss1.str());
            number_of_widgets++;
            frame->set_name("");
            focussed_widget = frame;
            frame->show();
            }
        }
    else if(type_of_widget=="gtk_notebook")
    {
        gtk_notebook* notebook = new gtk_notebook(scrollwin.get_style()->get_bg(Gtk::STATE_NORMAL));        
        notebook->signal_notebook_page_added().connect(sigc::mem_fun(*this,&Frame::on_notebook_page_added));            
        if(container)  
            if((insert_at_pos=container->set_child_widget(*notebook,0,0,width,height))!=-1)
                added = true;
        
        if(added)
        {
            item* __item = new item(*notebook,type_of_widget,NULL,NULL,NULL,NULL);
            container_item->insert_child_at(__item,insert_at_pos);
            __item->insert_child_at(new item (*(notebook->get_label_of_page(0)),"gtk_label",NULL,NULL,NULL,NULL),1);
            number_of_widgets++;
            std::ostringstream oss1;
            oss1<<number_of_widgets;
            notebook->get_label_of_page(0)->set_name("WIDGET "+oss1.str());
            number_of_widgets++;
            notebook->set_name("");
            focussed_widget = notebook; 
            notebook->show();
            }
        }
    if(widget != NULL)
    {
        if(container)
        {
            if((insert_at_pos=container->set_child_widget(*widget,1,1,width,height))!=-1)
                added = true;
            }
        if(added)
        {
            container_item->insert_child_at(new item(*widget,type_of_widget,NULL,NULL,NULL,NULL),insert_at_pos);
            number_of_widgets++;
            widget->set_name("");
            widget->show();
            focussed_widget = widget;
            
            }
        }        
    tool_box.set_active_false();
    
    if(added)
    {
        std::string name;
        do
        {
            std::ostringstream oss;
            oss<<number_of_widgets;
            name = "WIDGET"+oss.str();
            number_of_widgets++;
            }
        while(if_name_already_exists(name));
        focussed_widget->set_name(name);
        if(dynamic_cast<Gtk::Container*>(focussed_widget)!=NULL)
              (dynamic_cast<Gtk::Container*>(focussed_widget))->show_all_children();
        current_item=NULL;
        current_item = widget_tree.get_item_from_widget(focussed_widget);
        draw_widget=false;
        //std::cout<<"ADDED"<<number_of_widgets<<current_item->widget->get_name()<<std::endl;
        current_focused_widget.set_value(focussed_widget);
        //std::cout<<"ADDED"<<number_of_widgets<<current_item->widget->get_name()<<std::endl;
        m_signal_widget_added();        
        }
    }

bool Frame::on_mouse_released(GdkEventButton *event)
{
    //std::cout<<"one mouse released"<<std::endl;
    func_draw_widget(event->x-x_start,event->y-y_start);    
    //current_item = widget_tree.get_item_from_widget(current_focused_widget.get_value());    
    return false;
    }