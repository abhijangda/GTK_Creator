//44 Lines
#include"toolbox.h"
#include"tree.h"
#include<vector>
#include<string>
#include"gtk_notebook.h"
#include"gtk_label.h"

#ifndef FRAME_H
#define FRAME_H

class Frame : public Gtk::EventBox
{
    public:
        Frame(std::string,ToolBox&);
        ~Frame();
        Gtk::Frame _frame;
        Gtk::Fixed fixed;
        Gtk::ScrolledWindow scrollwin;        
        int x_start,y_start,number_of_widgets;
        bool has_window;
        friend Gtk::Widget* copy_function(Gtk::Widget* widget, std::string type,Frame*);
        virtual bool on_mouse_pressed(GdkEventButton* event);
        virtual bool on_mouse_released(GdkEventButton* event);
        
        typedef sigc::signal<void> type_signal_widget_added;
        type_signal_widget_added signal_widget_added();
        
        tree widget_tree;
        ToolBox& tool_box;
        item* container_item;
        item* current_item;
        void on_can_draw_widget(std::string);
        bool draw_widget;
        std::string type_of_widget;
        bool if_name_already_exists(std::string);
        void func_draw_widget(double,double);
        
    private:        
        void on_notebook_page_added(gtk_notebook*,gtk_label*,int);
        bool _if_name_already_exists(std::string,item*);
        type_signal_widget_added m_signal_widget_added;
    };
#endif