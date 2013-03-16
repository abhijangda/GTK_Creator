//33 Lines
#include"gtk_toolbar.h"

gtk_toolbar::gtk_toolbar()
:Gtk::Toolbar(),toolbar_style("")
{
    toolbar_style = get_toolbarstyle();
    }

gtk_toolbar::~gtk_toolbar(){}

std::string gtk_toolbar::get_toolbarstyle()
{
    if (get_toolbar_style() == Gtk::TOOLBAR_ICONS)
         return "ICONS ONLY";
    else if (get_toolbar_style() == Gtk::TOOLBAR_TEXT)
         return "TEXT ONLY";
    else if (get_toolbar_style() == Gtk::TOOLBAR_BOTH)
         return "TEXT BELOW ICONS";
    else if (get_toolbar_style() == Gtk::TOOLBAR_BOTH_HORIZ)
         return "TEXT BESIDES ICONS";
    }

void gtk_toolbar::set_toolbarstyle(std::string _toolbar_style)
{
    if (_toolbar_style ==  "ICONS ONLY")
         set_toolbar_style(Gtk::TOOLBAR_ICONS);
    else if (_toolbar_style =="TEXT ONLY" )
         set_toolbar_style(Gtk::TOOLBAR_TEXT);
    else if (_toolbar_style =="TEXT BELOW ICONS" )
        set_toolbar_style(Gtk::TOOLBAR_BOTH);
    else if (_toolbar_style == "TEXT BESIDES ICONS")
        set_toolbar_style(Gtk::TOOLBAR_BOTH_HORIZ);
    }