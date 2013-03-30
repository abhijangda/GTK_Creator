//57 Lines
#include<gtkmm/button.h>
#include<gtkmm/dialog.h>
#include<gtkmm/box.h>
#include<gtkmm/toolbar.h>
#include<gtkmm/entry.h>
#include<gtkmm/frame.h>
#include<gtkmm/table.h>
#include<gtkmm/treeview.h>
#include<gtkmm/liststore.h>
#include<gtkmm/treeiter.h>
#include<gtkmm/separatortoolitem.h>
#include<gtkmm/radiotoolbutton.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/fixed.h>
#include<gtkmm/scrolledwindow.h>
#include<gtkmm/combobox.h>

#include"tree.h"
#include"stock_functions.h"

#ifndef TOOLBAR_EDITOR_H
#define TOOLBAR_EDITOR_H

class ModelColumnToolbarEditor : public Gtk::TreeModel::ColumnRecord
{
    public:
        ModelColumnToolbarEditor()
        {add(col_name);add(col_text);add(col_type);add(col_stock);}
        
        Gtk::TreeModelColumn<std::string> col_name;
        Gtk::TreeModelColumn<std::string> col_text;
        Gtk::TreeModelColumn<std::string> col_type;
        Gtk::TreeModelColumn<std::string> col_stock;
    };

class toolbar_editor : public Gtk::Dialog
{
    public:
        toolbar_editor(item*);
        item* toolbar_item;
        
        Glib::RefPtr<Gtk::TreeSelection> tree_selection;
        Gtk::Button cmdAdd, cmdRemove;
        Gtk::Button* cmdSave;
        Gtk::Button* cmdCancel;
        Gtk::TreeView tree_view;
        ModelColumnToolbarEditor columns;
        Glib::RefPtr<Gtk::ListStore> treemodel;
        Glib::RefPtr<Gtk::ListStore> tree_model_stock;
        
        Gtk::Fixed fixed,fixed_type;
        Gtk::Label lblName, lblText,lblStock;
        Gtk::Entry entry_name, entry_text;
        Gtk::ComboBox* combo_stock;
        Gtk::Frame type_frame;
        Gtk::RadioButton type_item,type_separator, type_radio,type_check;
        Gtk::RadioButtonGroup type_group;
        Gtk::CheckButton chk_active;
        Gtk::Toolbar* toolbar;
        Gtk::ScrolledWindow scrollwin;
        Model_Column_Stock model_column_stock;
        
        void cmdAdd_clicked();
        void cmdRemove_clicked();
        void combo_stock_active_changed();
        void cmdSave_clicked();
        void cmdCancel_clicked();
        void item_type_changed(Gtk::RadioButton&);
        void on_tree_selection_changed();
        
        void update_treeview(item* _item,Gtk::TreeModel::Children::iterator,Gtk::TreeModel::Children::iterator);
    };
#endif