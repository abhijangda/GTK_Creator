//74 lines
#include"gtk_button.h"
#include<iostream>
#include"stock_functions.h"

gtk_button::gtk_button(std::string label)
:Gtk::Button(label)
{       
    stock="NONE";
    signal_clicked().connect(sigc::mem_fun(*this,&gtk_button::on_mouse_press));
    use_stock=false;
    }

gtk_button::~gtk_button()
{
    }

std::string gtk_button::get_stock()
{
    return stock;
    }

void gtk_button::set_stock(std::string _stock)
{
    if(_stock=="NONE")
    {
        image.clear();
        use_stock=false;
        }
    else
    {
        image.set(get_stock_from_string(_stock),Gtk::ICON_SIZE_BUTTON);
        set_label(get_stock_label(get_stock_from_string(_stock)));
        use_stock=true;
        }
    stock=_stock;
    set_image(image);    
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    settings->property_gtk_button_images()=true;  
    }

void gtk_button::on_mouse_press()
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    }

//gtk_togglebutton
gtk_togglebutton::gtk_togglebutton(std::string label)
:Gtk::ToggleButton(label)
{       
    signal_clicked().connect(sigc::mem_fun(*this,&gtk_togglebutton::on_mouse_press));
    }

gtk_togglebutton::~gtk_togglebutton()
{
    }

void gtk_togglebutton::on_mouse_press()
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    }

std::string gtk_togglebutton::get_stock()
{
    return stock;
    }

void gtk_togglebutton::set_stock(std::string _stock)
{
    if(_stock=="NONE")
    {
        image.clear();
        use_stock=false;
        }
    else
    {
        image.set(get_stock_from_string(_stock),Gtk::ICON_SIZE_BUTTON);
        set_label(get_stock_label(get_stock_from_string(_stock)));
        use_stock=true;
        }
    stock=_stock;
    set_image(image);    
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    settings->property_gtk_button_images()=true;  
    }

//gtk_checkbutton
gtk_checkbutton::gtk_checkbutton(std::string label)
:Gtk::CheckButton(label)
{       
    signal_clicked().connect(sigc::mem_fun(*this,&gtk_checkbutton::on_mouse_press));
    }

gtk_checkbutton::~gtk_checkbutton()
{
    }

void gtk_checkbutton::on_mouse_press()
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    }

std::string gtk_checkbutton::get_stock()
{
    return stock;
    }

void gtk_checkbutton::set_stock(std::string _stock)
{
    if(_stock=="NONE")
    {
        image.clear();
        use_stock=false;
        }
    else
    {
        image.set(get_stock_from_string(_stock),Gtk::ICON_SIZE_BUTTON);
        set_label(get_stock_label(get_stock_from_string(_stock)));
        use_stock=true;
        }
    stock=_stock;
    set_image(image);    
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    settings->property_gtk_button_images()=true;  
    }

//gtk_radiobutton
gtk_radiobutton::gtk_radiobutton(std::string label)
:Gtk::RadioButton(label)
{       
    signal_clicked().connect(sigc::mem_fun(*this,&gtk_radiobutton::on_mouse_press));
    }

gtk_radiobutton::~gtk_radiobutton()
{
    }

void gtk_radiobutton::on_mouse_press()
{
    gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(get_parent());
    _placeholder->set_focussed_widget_as_child_widget();
    }

std::string gtk_radiobutton::get_stock()
{
    return stock;
    }

void gtk_radiobutton::set_stock(std::string _stock)
{
    if(_stock=="NONE")
    {
        image.clear();
        use_stock=false;
        }
    else
    {
        image.set(get_stock_from_string(_stock),Gtk::ICON_SIZE_BUTTON);
        set_label(get_stock_label(get_stock_from_string(_stock)));
        use_stock=true;
        }
    stock=_stock;
    set_image(image);    
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    settings->property_gtk_button_images()=true;  
    }