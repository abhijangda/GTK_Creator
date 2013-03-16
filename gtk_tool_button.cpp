#include"gtk_tool_button.h"
#include<iostream>

gtk_tool_button::gtk_tool_button(std::string label)
: Gtk::ToolButton(label)
{
    use_stock = false;
    }
gtk_tool_button::~gtk_tool_button()
{
    }

void gtk_tool_button::set_stock(std::string _stock)
{
    stock= _stock;
    if(_stock=="NONE" || _stock=="")
    {
        image.clear();
        use_stock=false;
        }
    else
    {
        image.set(get_stock_from_string(_stock),Gtk::ICON_SIZE_SMALL_TOOLBAR);
        set_label(get_stock_label(get_stock_from_string(_stock)));
        use_stock=true;
        }
    set_icon_widget(image);    
    image.show();
    //Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    //settings->property_gtk_button_images()=true;  
    }
std::string gtk_tool_button::get_stock()
{
    return stock;
    }

gtk_separator_tool_item::gtk_separator_tool_item()
{
    }
gtk_separator_tool_item::~gtk_separator_tool_item()
{
    }

gtk_radio_tool_button::gtk_radio_tool_button(Gtk::RadioButtonGroup& group, std::string label)
: Gtk::RadioToolButton(group,label)
{
    use_stock = false;
    }

gtk_radio_tool_button::gtk_radio_tool_button()
{
    }

gtk_radio_tool_button::~gtk_radio_tool_button()
{
    }

void gtk_radio_tool_button::set_stock(std::string _stock)
{
    stock= _stock;
    if(_stock=="NONE" || _stock=="")
    {
        use_stock=false;
        }
    else
    {
        image.set(get_stock_from_string(_stock),Gtk::ICON_SIZE_MENU);
        set_label(get_stock_label(get_stock_from_string(_stock)));
        use_stock=true;
        }
    set_icon_widget(image);    
    //Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    //settings->property_gtk_button_images()=true;  
    }
std::string gtk_radio_tool_button::get_stock()
{
    return stock;
    }