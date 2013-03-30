//51 Lines
#include<gtkmm/dialog.h>
#include<gtkmm/entry.h>
#include<gtkmm/label.h>
#include<gtkmm/fixed.h>
#include<gtkmm/iconview.h>
#include<gtkmm/liststore.h>
#include<gtkmm.h>

#ifndef NEW_PROJECT_DIALOG_H
#define NEW_PROJECT_DIALOG_H

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    ModelColumns()
    { add(m_col_proj_type_icon);add(m_col_proj_type);}
    Gtk::TreeModelColumn<std::string> m_col_proj_type;
    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > m_col_proj_type_icon;
};

class new_project_dialog : public Gtk::Dialog
{
    public:
        new_project_dialog(Gtk::Window&);
        ~new_project_dialog();
        std::string get_proj_type(){return proj_type;}
        std::string get_proj_name(){return entry_name.get_text();}
        std::string get_proj_location(){return entry_location.get_text();}
        int return_val;
    private:
        void on_selection_changed();
        void on_cmd_location_clicked();
        void on_entry_proj_name_inserted(guint pos, const gchar* chars, guint n_chars);
        void on_entry_proj_name_deleted(guint pos, guint chars);
        void on_cmd_create_clicked();
        void on_cmd_cancel_clicked();
        
        std::string folder_selected;
        std::string proj_type;
        Gtk::Window& parent;
        Gtk::Fixed fixed;
        Gtk::Label lbl_select_proj,lbl_proj_info,lbl_new_proj;
        Gtk::Label lbl_proj_name,lbl_location;
        ModelColumns m_Columns;
        Gtk::IconView icon_view;
        Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
        Gtk::Button cmd_location,cmd_create,cmd_cancel;
        Gtk::Entry entry_name,entry_location;
    };

#endif