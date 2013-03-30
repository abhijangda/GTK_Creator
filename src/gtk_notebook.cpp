//128 Lines
#include"gtk_notebook.h"
#include<iostream>
extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;
   
gtk_notebook::gtk_notebook(Gdk::Color color)
    : gtk_eventbox(color),notebook(new Gtk::Notebook),tab_pos("TOP"),child_placeholder_vector(1),number_of_widgets(0),label_vector(1)
{    
    gtk_eventbox::set_child_widget(*notebook,0,0,0,0);
    gtk_placeholder* _placeholder = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    std::fill(child_placeholder_vector.begin(), child_placeholder_vector.begin()+1,_placeholder);
    label_vector[0] = new gtk_label("Page");
    notebook->append_page(*_placeholder,*label_vector[0]);
    notebook->set_current_page(notebook->get_n_pages()-1);  
    show_all_children();
    prev_page_label_set=-1;
    prev_placeholder_set=-1;
    prev_label_set=-1;
    }

gtk_notebook::~gtk_notebook()
{
    for(int i=0;i<get_n_pages();i++)
    {
        delete child_placeholder_vector[i];
        delete label_vector[i];
        }
    delete notebook;
    }

gtk_label* gtk_notebook::get_label_of_page(int page)
{
    return label_vector[page];
    }

void gtk_notebook::set_page_count(int pages)
{
    if(pages>get_n_pages())
    {
        for(int i = 0; i < pages-get_n_pages();i++)
            add_page();
        }
    }
void gtk_notebook::remove_child(Gtk::Widget* widget)
{
    for(int i =0; i<notebook->get_n_pages();i++)
        child_placeholder_vector[i]->remove_child(widget);
    }

void gtk_notebook::add_page()
{
    gtk_placeholder* _placeholder = new gtk_placeholder(get_style()->get_bg(Gtk::STATE_NORMAL));
    child_placeholder_vector.resize(notebook->get_n_pages()+1);
    label_vector.resize(notebook->get_n_pages()+1);
    child_placeholder_vector[notebook->get_n_pages()]=_placeholder;
    label_vector[notebook->get_n_pages()]= new gtk_label("Page");
    notebook->append_page(*_placeholder,*label_vector[notebook->get_n_pages()]);  
    notebook->set_current_page(notebook->get_n_pages()-1);  
    show_all_children();
    m_signal_notebook_page_added(this,label_vector[notebook->get_n_pages()-1],2*notebook->get_n_pages()-1);
    }

void gtk_notebook::set_current_page_label(gtk_label* label)
{
    int current_page = 0;
    if (notebook->get_current_page()!=-1)
         current_page=notebook->get_current_page();
        
    Gtk::Label* _label = label_vector[current_page];
    if(_label)
        delete _label;
    
    label_vector[current_page]=label;
    notebook->set_tab_label(*child_placeholder_vector[current_page],*label);
    }

gtk_notebook::type_signal_notebook_page_added gtk_notebook::signal_notebook_page_added()
{
    return m_signal_notebook_page_added;
    }

void gtk_notebook::set_tab_pos(std::string _tab_pos)
{
    tab_pos=_tab_pos;
    if(_tab_pos== "LEFT")  
        notebook->set_tab_pos(Gtk::POS_LEFT); 
    else if(_tab_pos=="RIGHT") 
        notebook->set_tab_pos(Gtk::POS_RIGHT);     
    else if(_tab_pos=="BOTTOM")  
        notebook->set_tab_pos(Gtk::POS_BOTTOM);      
    else if(_tab_pos=="TOP") 
        notebook->set_tab_pos(Gtk::POS_TOP);
    }

std::string gtk_notebook::get_tab_pos()
{
    if(notebook->get_tab_pos()==Gtk::POS_LEFT)
        tab_pos= "LEFT"; 
    else if(notebook->get_tab_pos()==Gtk::POS_RIGHT) 
        tab_pos="RIGHT"; 
    else if(notebook->get_tab_pos()==Gtk::POS_BOTTOM) 
        tab_pos="BOTTOM"; 
    else if(notebook->get_tab_pos()==Gtk::POS_TOP) 
        tab_pos="TOP";
    
    return tab_pos;        
    }

void gtk_notebook::remove_placeholder_from_vector(int index)
{
    gtk_placeholder* _placeholder = child_placeholder_vector[index];
    
    for(int i = index; i <child_placeholder_vector.size()-1;i++)
        child_placeholder_vector[i] = child_placeholder_vector[i+1];

    child_placeholder_vector.resize(child_placeholder_vector.size()-1);
    delete _placeholder;
    }

void gtk_notebook::set_label_as_tab_label(gtk_label* label)
{
    int label_index=-1;
    Gtk::Widget* widget = label;
    
    for(label_index =0; label_index < notebook->get_n_pages();label_index++)
    {
        if(child_placeholder_vector[label_index]->get_child()==widget)
            break;
        }

    if(label_index==notebook->get_n_pages())
        return;
    
    if(prev_label_set==label_index-1||prev_placeholder_set-1== prev_label_set)
    {
        child_placeholder_vector[label_index]->remove_child(widget);
        notebook->set_tab_label(*child_placeholder_vector[label_index],*label);
        gtk_label* _label = label_vector[label_index];
        label_vector[label_index]=label;
        delete _label;
        prev_label_set=label_index;
        }
    else if(prev_placeholder_set==label_index-2||prev_placeholder_set== prev_label_set-1)
    {
        child_placeholder_vector[label_index]->remove_child(widget);
        notebook->set_tab_label(*child_placeholder_vector[label_index-1],*label);
        notebook->remove_page(label_index);
        remove_placeholder_from_vector(label_index);
        gtk_label* _label = label_vector[label_index-1];
        label_vector[label_index-1]=label;
        delete _label;
        prev_placeholder_set=label_index-1;    
        }
    }

void gtk_notebook::clear_everything()
{
    for(int i=notebook->get_n_pages()-1;i>=0;i--)
        notebook->remove_page(i);
        
    for(int i =0;i<child_placeholder_vector.size();i++)
        delete child_placeholder_vector[i];
    
    for(int i =0;i<label_vector.size();i++)
         delete label_vector[i];
        
    child_placeholder_vector.resize(0);
    label_vector.resize(0);
    number_of_widgets = 0;
    }

int gtk_notebook::append_child_widget(Gtk::Widget& widget, int x, int y, int height, int width)
{
    add_page();
    int n_pages = notebook->get_n_pages();
    gtk_placeholder* _placeholder = child_placeholder_vector[n_pages-1];
    if(_placeholder->set_child_widget(widget,x,y,height,width)==-1)
        return -1;
    
    show_all_children();
    number_of_widgets++;
    }

int gtk_notebook::set_child_widget(Gtk::Widget& widget, int x, int y, int height,int width)
{    
    int current_page = 0;
    if (notebook->get_current_page()!=-1)
         current_page=notebook->get_current_page();
        
    gtk_placeholder* _placeholder = child_placeholder_vector[current_page];
    if(_placeholder->set_child_widget(widget,x,y,height,width)==-1)
        return -1;
    show_all_children();    
    number_of_widgets++;
    return 2*notebook->get_current_page();
    }
