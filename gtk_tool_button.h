#include<gtkmm/radiotoolbutton.h>
#include<gtkmm/separatortoolitem.h>
#include<gtkmm/image.h>
#include"stock_functions.h"

#ifndef GTK_TOOL_BUTTON_H
#define GTK_TOOL_BUTTON_H

class gtk_tool_button : public Gtk::ToolButton
{
    public:
        gtk_tool_button(std::string label);
        ~gtk_tool_button();
        
        void set_stock(std::string);
        std::string get_stock();
    private:
        Gtk::Image image;
        std::string stock;
        bool use_stock;
    };

class gtk_radio_tool_button : public Gtk::RadioToolButton
{
    public:
        gtk_radio_tool_button(Gtk::RadioButtonGroup&, std::string label);
        gtk_radio_tool_button();
        ~gtk_radio_tool_button();
        void set_stock(std::string);
        std::string get_stock();
        bool get_use_stock(){return use_stock;}
        void set_use_stock(bool _b){use_stock=_b;}
    private:
        Gtk::Image image;
        std::string stock;
        bool use_stock;       
    };

class gtk_separator_tool_item : public Gtk::SeparatorToolItem
{
    public:
        gtk_separator_tool_item();
        ~gtk_separator_tool_item();
    };

#endif