//59 Lines
#include"gtk_menubar.h"

gtk_menubar::gtk_menubar()
:Gtk::MenuBar()
{
    }

gtk_menubar::~gtk_menubar()
{
    }

void gtk_menubar::set_packdirection(std::string _direction)
{
    if(_direction == "LEFT TO RIGHT")
        set_pack_direction(Gtk::PACK_DIRECTION_LTR);
    else if(_direction == "RIGHT TO LEFT")
        set_pack_direction(Gtk::PACK_DIRECTION_RTL);
    else if(_direction == "TOP TO BOTTOM")
        set_pack_direction(Gtk::PACK_DIRECTION_TTB);
    else if(_direction == "BOTTOM TO TOP")
        set_pack_direction(Gtk::PACK_DIRECTION_BTT);
    }

std::string gtk_menubar::get_packdirection()
{
    if(get_pack_direction()== Gtk::PACK_DIRECTION_LTR)
        return "LEFT TO RIGHT";
    else if(get_pack_direction()== Gtk::PACK_DIRECTION_RTL)
        return "RIGHT TO LEFT";
    else if(get_pack_direction()== Gtk::PACK_DIRECTION_TTB)
        return "TOP TO BOTTOM";
    else if(get_pack_direction()== Gtk::PACK_DIRECTION_BTT)
        return "BOTTOM TO TOP";
    }

void gtk_menubar::set_childpackdirection(std::string _direction)
{
    if(_direction == "LEFT TO RIGHT")
        set_child_pack_direction(Gtk::PACK_DIRECTION_LTR);
    else if(_direction == "RIGHT TO LEFT")
        set_child_pack_direction(Gtk::PACK_DIRECTION_RTL);
    else if(_direction == "TOP TO BOTTOM")
        set_child_pack_direction(Gtk::PACK_DIRECTION_TTB);
    else if(_direction == "BOTTOM TO TOP")
        set_child_pack_direction(Gtk::PACK_DIRECTION_BTT);
    }

std::string gtk_menubar::get_childpackdirection()
{
    if(get_child_pack_direction()== Gtk::PACK_DIRECTION_LTR)
        return "LEFT TO RIGHT";
    else if(get_child_pack_direction()== Gtk::PACK_DIRECTION_RTL)
        return "RIGHT TO LEFT";
    else if(get_child_pack_direction()== Gtk::PACK_DIRECTION_TTB)
        return "TOP TO BOTTOM";
    else if(get_child_pack_direction()== Gtk::PACK_DIRECTION_BTT)
        return "BOTTOM TO TOP";
    }
