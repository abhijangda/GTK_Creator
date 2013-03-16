//151 Lines
#include"new_project_dialog.h"
#include<iostream>

new_project_dialog::new_project_dialog(Gtk::Window& _parent)
: parent(_parent), cmd_location("..."),cmd_create("Create"),cmd_cancel("Cancel"),lbl_select_proj(Glib::ustring("Select Project Type")),lbl_proj_info(Glib::ustring(""),Gtk::ALIGN_START,Gtk::ALIGN_START),
   lbl_new_proj(Glib::ustring("Create New Project")),Gtk::Dialog("Create New Project",_parent,false,true),lbl_proj_name(Glib::ustring("Project Name")),lbl_location(Glib::ustring("Location"))
{
    fixed.put(lbl_select_proj,3,0);
    //lbl_select_proj.set_size_request(221,31);
    
    fixed.put(icon_view,3,30);
    icon_view.set_size_request(551,321);
    
    fixed.put(lbl_proj_name,7,370);
    lbl_proj_name.set_size_request(91,21);
    
    fixed.put(lbl_location,8,410);
    lbl_location.set_size_request(67,21);
    
    fixed.put(entry_name,110,370);
    entry_name.set_size_request(601,31);
    
    fixed.put(entry_location,110,410);
    entry_location.set_size_request(531,31);
    
    fixed.put(lbl_proj_info,570,30);
    lbl_proj_info.set_size_request(140,311);
    
    fixed.put(cmd_location,651,410);
    cmd_location.set_size_request(61,31);
    
    get_vbox()->pack_start(fixed,Gtk::PACK_EXPAND_WIDGET);
    
    Gtk::ButtonBox *dialog_button_box = get_action_area();
    
    dialog_button_box->pack_end(cmd_create);
    dialog_button_box->pack_end(cmd_cancel);
    
    cmd_create.signal_clicked().connect(sigc::mem_fun(*this,&new_project_dialog::on_cmd_create_clicked));
    cmd_cancel.signal_clicked().connect(sigc::mem_fun(*this,&new_project_dialog::on_cmd_cancel_clicked));
    
    lbl_proj_info.set_use_markup(true);
    lbl_proj_info.set_line_wrap(true);
    
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    icon_view.set_model(m_refTreeModel);
    icon_view.set_text_column(m_Columns.m_col_proj_type);
    icon_view.set_pixbuf_column(m_Columns.m_col_proj_type_icon);
    icon_view.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_Columns.m_col_proj_type] = "Empty C Project";
    row[m_Columns.m_col_proj_type_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/empty_project.png");
    
    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_proj_type] = "Console C Project";
    row[m_Columns.m_col_proj_type_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/console_project.png");
    
    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_proj_type] = "GTK+ Console Project";
    row[m_Columns.m_col_proj_type_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/console_project.png");
    
    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_proj_type] = "GTK+ GUI Project";
    row[m_Columns.m_col_proj_type_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/gui_project.png");
    
    icon_view.signal_selection_changed().connect(sigc::mem_fun(*this,&new_project_dialog::on_selection_changed));
    
    cmd_location.signal_clicked().connect(sigc::mem_fun(*this,&new_project_dialog::on_cmd_location_clicked));
    
    entry_name.get_buffer()->signal_inserted_text().connect(sigc::mem_fun(*this,&new_project_dialog::on_entry_proj_name_inserted));
    entry_name.get_buffer()->signal_deleted_text().connect(sigc::mem_fun(*this,&new_project_dialog::on_entry_proj_name_deleted));
    folder_selected="";
    proj_type="";
    }

new_project_dialog::~new_project_dialog()
{
    }

void new_project_dialog::on_cmd_create_clicked()
{
    if(entry_location.get_text()=="" || entry_name.get_text()==""|| proj_type=="")
    {
        Gtk::MessageDialog dialog(*this,Glib::ustring("Please enter all the details to create project!"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
        dialog.run();
        return;
        }
    return_val=1;
    hide();
    }

void new_project_dialog::on_cmd_cancel_clicked()
{
    return_val=0;
    hide();
    }

void new_project_dialog::on_entry_proj_name_inserted(guint pos, const gchar* chars, guint n_chars)
{
    entry_location.set_text(folder_selected+"/"+entry_name.get_text());
    }

void new_project_dialog::on_entry_proj_name_deleted(guint pos, guint chars)
{
    entry_location.set_text(folder_selected+"/"+entry_name.get_text());
    }

void new_project_dialog::on_cmd_location_clicked()
{
    Gtk::FileChooserDialog dialog(*this,"Select Folder",Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Open",Gtk::RESPONSE_OK);
    
    dialog.show_all_children();
    if(dialog.run()==Gtk::RESPONSE_OK)
    {
        folder_selected = dialog.get_filename();
        entry_location.set_text(dialog.get_filename());
        }
    }

void new_project_dialog::on_selection_changed()
{
    Gtk::TreePath path;
    if(icon_view.get_cursor(path))
    {
        std::string path_string  = path.to_string();
        std::string info;
        if(path_string=="0")
        {
            info = "<b>Empty C Project</b> \nCreates an empty C project";
            proj_type="Empty C Project";
            }
        else if(path_string=="1")
        {
            info = "<b>Console C Project</b> \nCreates a hello world console project";
            proj_type="Console C Project";
            }
        else if(path_string=="2")
        {
            info="<b>GTK+ Console Project</b> \nCreates a GTK+ hello world console project";
            proj_type="GTK+ Console Project";
            }
        else if(path_string=="3")
        {
            info = "<b>GTK+ GUI Project</b> \nCreates a GTK+ Graphical User Interface project";
            proj_type="GTK+ GUI Project";
            }
        lbl_proj_info.set_label(info);
        }
    }