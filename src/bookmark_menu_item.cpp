//10 Lines
#include"bookmark_menu_item.h"

bookmark_menu_item::bookmark_menu_item(Gtk::RadioButtonGroup& _group, int _line, std::string _filename)
: Gtk::RadioMenuItem(_group),filename(_filename)
{
    line = _line;
    set_label(filename+" "+ integer_to_string(line));
    set_active(false);
    }

bookmark_menu_item::~bookmark_menu_item(){}