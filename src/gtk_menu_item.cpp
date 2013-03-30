#include"gtk_menu_item.h"
#include"stock_functions.h"
#include<iostream>

gtk_image_menu_item::gtk_image_menu_item(std::string label)
: Gtk::ImageMenuItem(label,true)
{
    use_stock = false;
    }
gtk_image_menu_item::~gtk_image_menu_item()
{
    }

void gtk_image_menu_item::set_stock(std::string _stock)
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
    set_image(image);    
    set_always_show_image(true);
 
    //Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    //settings->property_gtk_button_images()=true;  
    }
std::string gtk_image_menu_item::get_stock()
{
    return stock;
    }

gtk_image_menu_item::gtk_image_menu_item()
{
    }

gtk_separator_menu_item::gtk_separator_menu_item()
{
    }
gtk_separator_menu_item::~gtk_separator_menu_item()
{
    }

gtk_check_menu_item::gtk_check_menu_item(std::string label)
:Gtk::CheckMenuItem(label,true)
{
    }
gtk_check_menu_item::~gtk_check_menu_item()
{
    }


gtk_radio_menu_item::gtk_radio_menu_item(Gtk::RadioButtonGroup& group,std::string label)
:Gtk::RadioMenuItem(group,label)
{
    }
gtk_radio_menu_item::~gtk_radio_menu_item()
{
    }