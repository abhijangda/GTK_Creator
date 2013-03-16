//56 Lines
#include<gtkmm/notebook.h>
#include"gtk_placeholder.h"
#include"gtk_eventbox.h"
#include"gtk_label.h"

#ifndef GTK_NOTEBOOK_H
#define GTK_NOTEBOOK_H

class gtk_notebook : public gtk_eventbox
{
    public:
        gtk_notebook(Gdk::Color);
        virtual ~gtk_notebook();
        int set_child_widget(Gtk::Widget& widget,int x, int y, int height, int width);
        void remove_child(Gtk::Widget* widget);
        int append_child_widget(Gtk::Widget& widget, int x, int y, int height, int width);
        void set_label_as_tab_label(gtk_label* label);
        void clear_everything();
        
        void set_current_page_label(gtk_label* label);        
        void set_tab_pos(std::string _tab_pos);
        std::string get_tab_pos(); 
        int get_n_pages(){return notebook->get_n_pages();} 
        bool get_scrollable(){return notebook->get_scrollable();} 
        bool get_show_border(){return notebook->get_show_border();} 
        bool get_show_tabs(){return notebook->get_show_tabs();}
        
        void set_scrollable(bool value){return notebook->set_scrollable(value);} 
        void set_show_border(bool value){return notebook->set_show_border(value);} 
        void set_show_tabs(bool value){return notebook->set_show_tabs(value);}
        
        void set_page_count(int pages);
        void add_page();
        
        typedef sigc::signal<void,gtk_notebook*,gtk_label*,int> type_signal_notebook_page_added;
        type_signal_notebook_page_added signal_notebook_page_added();
        
        gtk_label* get_label_of_page(int page);
        
    private:
        type_signal_notebook_page_added m_signal_notebook_page_added;
        std::string tab_pos;
        Gtk::Notebook* notebook;
        std::vector<gtk_placeholder*> child_placeholder_vector;
        std::vector<gtk_label*> label_vector;
        int number_of_widgets,prev_page_label_set,prev_placeholder_set,prev_label_set;
        void remove_placeholder_from_vector(int index);
    };
#endif
