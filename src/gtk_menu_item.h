#include<gtkmm/radiomenuitem.h>
#include<gtkmm/imagemenuitem.h>
#include<gtkmm/image.h>
#include<gtkmm/separatormenuitem.h>
#include<gtkmm/radiobuttongroup.h>

#ifndef GTK_MENU_ITEM_H
#define GTK_MENU_ITEM_H

class gtk_image_menu_item : public Gtk::ImageMenuItem
{
   public:
        gtk_image_menu_item(std::string);
        gtk_image_menu_item();
         ~gtk_image_menu_item();
         void set_stock(std::string _stock);
        std::string get_stock();        
    private:
        bool use_stock;
        std::string stock;
        Gtk::Image image;
   };

class gtk_separator_menu_item : public Gtk::SeparatorMenuItem
{
   public:
        gtk_separator_menu_item();
         ~gtk_separator_menu_item();        
   };

class gtk_check_menu_item : public Gtk::CheckMenuItem
{
   public:
        gtk_check_menu_item(std::string);
         ~gtk_check_menu_item();
   };

class gtk_radio_menu_item : public Gtk::RadioMenuItem
{
   public:
        gtk_radio_menu_item(Gtk::RadioButtonGroup&,std::string);
         ~gtk_radio_menu_item();
   };
#endif