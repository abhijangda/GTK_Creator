//46 lines
#include<gtkmm/button.h>
#include<gtkmm/checkbutton.h>
#include<gtkmm/radiobutton.h>
#include"gtk_placeholder.h"
#include<gtkmm/image.h>

#ifndef GTK_BUTTON_H
#define GTK_BUTTON_H

class gtk_button : public Gtk::Button
{
    public:
        gtk_button(std::string label);
        virtual ~gtk_button();
        std::string get_stock();
        void set_stock(std::string);
        bool get_use_stock(){return use_stock;}
        void set_use_stock(bool _b){use_stock=true;}
    private:
        bool use_stock;
        Gtk::Image image;
        std::string stock;
        gtk_placeholder* container;
        void on_mouse_press();
    };

class gtk_togglebutton : public Gtk::ToggleButton
{
    public:
        gtk_togglebutton(std::string label);
        virtual ~gtk_togglebutton();
        std::string get_stock();
        void set_stock(std::string);
        bool get_use_stock(){return use_stock;}
        void set_use_stock(bool _b){use_stock=true;}
    private:
        bool use_stock;
        Gtk::Image image;
        std::string stock;
        void on_mouse_press();
    };

class gtk_checkbutton : public Gtk::CheckButton
{
    public:
        gtk_checkbutton(std::string label);
        virtual ~gtk_checkbutton();
        std::string get_stock();
        void set_stock(std::string);
        bool get_use_stock(){return use_stock;}
        void set_use_stock(bool _b){use_stock=true;}
    private:
        bool use_stock;
        Gtk::Image image;
        std::string stock;
        void on_mouse_press();
    };

class gtk_radiobutton : public Gtk::RadioButton
{
    public:
        gtk_radiobutton(std::string label);
        virtual ~gtk_radiobutton();
        std::string get_stock();
        void set_stock(std::string);
        bool get_use_stock(){return use_stock;}
        void set_use_stock(bool _b){use_stock=true;}
    private:
        bool use_stock;
        Gtk::Image image;
        std::string stock;
        void on_mouse_press();
    };
#endif