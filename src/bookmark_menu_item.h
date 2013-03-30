//17 Lines
#include<gtkmm/radiomenuitem.h>
#include<string>
#include"source_view.h"
#include"helper_functions.h"

#ifndef BOOKMARK_MENU_ITEM_H
#define BOOKMARK_MENU_ITEM_H

class bookmark_menu_item : public Gtk::RadioMenuItem
{
    public:
        bookmark_menu_item(Gtk::RadioButtonGroup&, int _line, std::string _filename);
        ~bookmark_menu_item();
        int line;
        std::string filename;
    };
#endif