//64 Lines
#include<gtkmm/button.h>
#include<gtkmm/dialog.h>
#include<gtkmm/box.h>
#include<gtkmm/toolbar.h>
#include<gtkmm/entry.h>
#include<gtkmm/frame.h>
#include<gtkmm/table.h>
#include<gtkmm/treeview.h>
#include<gtkmm/treestore.h>
#include<gtkmm/treeiter.h>
#include<gtkmm/separatormenuitem.h>
#include<gtkmm/radiomenuitem.h>
#include<gtkmm/scrolledwindow.h>
#include<gtkmm/fixed.h>
#include<gtkmm/combobox.h>

#include"gtk_menu_item.h"
#include"tree.h"
#include"stock_functions.h"

#ifndef MENUBAR_EDITOR_H
#define MENUBAR_EDITOR_H

class ModelColumnMenuBarEditor : public Gtk::TreeModel::ColumnRecord
{
    public:
        ModelColumnMenuBarEditor()
        {add(col_name);add(col_text);add(col_type);add(col_stock);}
        
        Gtk::TreeModelColumn<std::string> col_name;
        Gtk::TreeModelColumn<std::string> col_text;
        Gtk::TreeModelColumn<std::string> col_type;
        Gtk::TreeModelColumn<std::string> col_stock;
    };

class menu_item_info
{
    public:
        menu_item_info(std::string _name, std::string _t, std::string _text, std::string _stock)
        {
            type=_t;
            text = _text;
            stock=_stock;
            name = _name;
            }
        //~menu_item_info(){}
        std::string type, text, stock, name;
        std::vector<menu_item_info> vector_child_menu_item_info;  
    };

class  menubar_editor : public Gtk::Dialog
{
    public:
        menubar_editor(item*);
        item* menubar_item;
        Glib::RefPtr<Gtk::TreeSelection> tree_selection;
        Gtk::Button cmdAddItem, cmdRemove, cmdAddMenu;
        Gtk::Button cmdRemoveMenu;
        Gtk::Button* cmdSave;
        Gtk::Button* cmdCancel;
        Gtk::TreeView tree_view;
        ModelColumnMenuBarEditor columns;
        Glib::RefPtr<Gtk::TreeStore> treemodel;
        
        Gtk::Fixed fixed,fixed_type;
        Gtk::Label lblName, lblText,lblStock;
        Gtk::Entry entry_name, entry_text;
        Gtk::ComboBox* combo_stock;
        Gtk::Frame type_frame;
        Gtk::RadioButton type_item, type_separator, type_radio,type_check;
        Gtk::RadioButtonGroup type_group;
        Gtk::CheckButton chk_active;
        Gtk::HBox hbox_dialog,hbox_type,hbox_add_remove;
        Gtk::VBox vbox_item;
        Gtk::Toolbar* toolbar;
        Gtk::ScrolledWindow scrollwin;

        Model_Column_Stock model_column_stock;
        Glib::RefPtr<Gtk::ListStore> tree_model_stock;
        
        void cmdAddItem_clicked();
        void cmdRemove_clicked();
        void cmdAddMenu_clicked();
        void cmdRemoveMenu_clicked();
        void combo_stock_active_changed();
        void cmdSave_clicked();
        void cmdCancel_clicked();
        void item_type_changed(Gtk::RadioButton&);
        void on_tree_selection_changed();
        
        void update_treeview(item* _item,Gtk::TreeModel::Children::iterator,Gtk::TreeModel::Children::iterator);
        bool create_menu;
        std::vector<menu_item_info> vector_menu_item_info;
    };
#endif