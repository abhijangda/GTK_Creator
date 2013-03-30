//1614 Lines

#include"page_general.h"
#include<iostream>
#include"gtk_window.h"
#include"gtk_vbox.h" 
#include"gtk_textview.h"
#include"gtk_hbox.h"
#include"gtk_scrollwin.h"
#include"gtk_notebook.h"
#include"toolbar_editor.h"
#include"gtk_toolbar.h"
#include"gtk_menubar.h"
#include"gtk_offscreenwindow.h"
#include"gtk_eventbox.h"
#include"gtk_table.h"
#include"gtk_button.h"
#include"gtk_menu_item.h" 
#include"gtk_tool_button.h"

PageGeneral::PageGeneral(Frame& _current_frame,ObjectBox& _object_box)
    :Gtk::Table(1,2,false),lblName("Name"),value_widget_vector(10),label_vector(10),label_vector_size(-1),cmdEditToolbar("Edit Toolbar"),
    cmdEditMenubar("Edit Menubar"),current_frame(_current_frame),object_box(_object_box)
{ 
    set_spacings(3);
    attach(lblName,0,1,0,1,Gtk::SHRINK,Gtk::FILL);
    attach(txtName,1,2,0,1,Gtk::EXPAND,Gtk::FILL);
    send_name_change_signal=false;
    txtNameBuffer = txtName.get_buffer();
    txtNameBuffer->signal_deleted_text().connect(sigc::mem_fun(*this,&PageGeneral::on_txtentry_text_deleted));
    txtNameBuffer->signal_inserted_text().connect(sigc::mem_fun(*this,&PageGeneral::on_txtentry_text_inserted));
    cmdEditToolbar.signal_clicked().connect(sigc::mem_fun(*this,&PageGeneral::cmdEditToolbar_clicked));
    cmdEditMenubar.signal_clicked().connect(sigc::mem_fun(*this,&PageGeneral::cmdEditMenubar_clicked));
    
    cb_tree_model_win_type=Gtk::ListStore::create(model_column);
    Gtk::TreeModel::Row row = *(cb_tree_model_win_type->append());
    row[model_win_type.col] = "TOPLEVEL";
    row = *(cb_tree_model_win_type->append());
    row[model_win_type.col] = "POPUP"; 
    
    cb_tree_model_true_false=Gtk::ListStore::create(model_column);
    row = *(cb_tree_model_true_false->append());
    row[model_column.col] = "TRUE";
    row = *(cb_tree_model_true_false->append());
    row[model_column.col] = "FALSE"; 
    
    cb_tree_model_scrollbar_policy=Gtk::ListStore::create(model_column);
    row = *(cb_tree_model_scrollbar_policy->append());
    row[model_column.col] = "ALWAYS";
    row = *(cb_tree_model_scrollbar_policy->append());
    row[model_column.col] = "AUTOMATIC";
    row = *(cb_tree_model_scrollbar_policy->append());
    row[model_column.col] = "NEVER";
    
    cb_tree_model_wrap_mode=Gtk::ListStore::create(model_column);
    row = *(cb_tree_model_wrap_mode->append());
    row[model_column.col] = "NONE";
    row = *(cb_tree_model_wrap_mode->append());
    row[model_column.col] = "CHARACTER";
    row = *(cb_tree_model_wrap_mode->append());
    row[model_column.col] = "WORD";
    row = *(cb_tree_model_wrap_mode->append());
    row[model_column.col] = "WORD CHARACTER";    
    
    cb_tree_model_justification = Gtk::ListStore::create(model_column);
    row = *(cb_tree_model_justification->append());
    row[model_column.col] = "LEFT";
    row = *(cb_tree_model_justification->append());
    row[model_column.col] = "RIGHT";
    row = *(cb_tree_model_justification->append());
    row[model_column.col] = "CENTER";
    row = *(cb_tree_model_justification->append());
    row[model_column.col] = "FILL";    
            
    cb_tree_model_toolbar_style = Gtk::ListStore::create(model_column);
    row = *(cb_tree_model_toolbar_style->append());
    row[model_column.col] = "ICONS ONLY";
    row = *(cb_tree_model_toolbar_style->append());
    row[model_column.col] = "TEXT ONLY";
    row = *(cb_tree_model_toolbar_style->append());
    row[model_column.col] = "TEXT BELOW ICONS";
    row = *(cb_tree_model_toolbar_style->append());
    row[model_column.col] = "TEXT BESIDES ICONS";
        
    cb_tree_model_tab_position = Gtk::ListStore::create(model_column_tab_position);
    row = *(cb_tree_model_tab_position->append());
    row[model_column.col] = "LEFT";
    row = *(cb_tree_model_tab_position->append());
    row[model_column.col] = "RIGHT";
    row = *(cb_tree_model_tab_position->append());
    row[model_column.col] = "BOTTOM";
    row = *(cb_tree_model_tab_position->append());
    row[model_column.col] = "TOP";
    
    cb_tree_model_pack_direction = Gtk::ListStore::create(model_column_pack_direction);
    row = *(cb_tree_model_pack_direction->append());
    row[model_column_pack_direction.col] = "LEFT TO RIGHT";
    row = *(cb_tree_model_pack_direction->append());
    row[model_column_pack_direction.col] = "RIGHT TO LEFT";
    row = *(cb_tree_model_pack_direction->append());
    row[model_column_pack_direction.col] = "TOP TO BOTTOM";
    row = *(cb_tree_model_pack_direction->append());
    row[model_column_pack_direction.col] = "BOTTOM TO TOP";
    }

PageGeneral::~PageGeneral()
{}

void PageGeneral::on_txtentry_text_deleted(guint pos, guint chars)
{
    if(!send_name_change_signal)
       return;
    //current_widget->set_name(txtName.get_buffer()->get_text());
    if(!m_signal_name_changed(txtName.get_buffer()->get_text()))
        txtName.get_buffer()->set_text(current_widget->get_name());
    }

void PageGeneral::on_txtentry_text_inserted(guint pos, const gchar* text, guint chars)
{
    if(!send_name_change_signal)
        return;
    //current_widget->set_name(txtName.get_buffer()->get_text());
    if(!m_signal_name_changed(txtName.get_buffer()->get_text()))
        txtName.get_buffer()->set_text(current_widget->get_name());
    }

void PageGeneral::set_property_values(Gtk::Widget& widget, std::string type)
{
    if(current_widget_type=="gtk_toolbar")
        remove(cmdEditToolbar);
    else if(current_widget_type=="gtk_menubar")
        remove(cmdEditMenubar);
        
    std::ostringstream ostringstream;
    send_name_change_signal=false;
    current_widget = &widget;
    txtName.get_buffer()->set_text(widget.get_name());
    send_name_change_signal=true;
    current_widget_type=type;
   
    //std::cout<<"LABEL_VECTOR_SIZE"<<label_vector_size<<std::endl;
    for(int i=label_vector_size-1;i>=0;i--)
    {        
        if(label_vector[i]==NULL)
            continue;
        //std::cout<<"LABEL VECTOR I"<<i<<std::endl;
        remove(*label_vector[i]);
        remove(*value_widget_vector[i]);
        delete label_vector[i];
        }
    label_vector_size=-1;
    //std::cout<<"TYPE OF WIDGET IN SET PROPERTY"<<type<<std::endl;
    if(type=="gtk_window")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Window Type"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Window Title"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Default Width"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Default Height"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Resizable"));
        label_vector.insert(label_vector.begin()+5,new Gtk::Label("Modal"));
        label_vector.insert(label_vector.begin()+6,new Gtk::Label("Destroy With Parent"));     
        label_vector_size = 7;               
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_win_type);
        cb->pack_start(model_win_type.col);        
        gtk_window *widget = dynamic_cast<gtk_window*>(current_widget);
        if(widget->get_type()=="TOPLEVEL")
            cb->set_active(0);
        else
            cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_win_type_changed));
        
        Gtk::Entry* entry = new Gtk::Entry();
        entry->get_buffer()->set_text(widget->get_title());
        value_widget_vector.insert(value_widget_vector.begin()+1,entry);
        entry->get_buffer()->signal_deleted_text().connect(sigc::mem_fun(*this,&PageGeneral::txt_win_title_deleted));
        entry->get_buffer()->signal_inserted_text().connect(sigc::mem_fun(*this,&PageGeneral::txt_win_title_inserted));
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(widget->get_default_width());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);        
        sb->set_numeric(true);
        sb->set_adjustment(*adjustment);
        value_widget_vector.insert(value_widget_vector.begin()+2,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_win_default_width_changed));
        
        sb = new Gtk::SpinButton();
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(widget->get_default_height());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);        
        sb->set_numeric(true);
        sb->set_adjustment(*adjustment);
        value_widget_vector.insert(value_widget_vector.begin()+3,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_win_default_height_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(widget->get_resizable())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+4,cb);        
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_win_resizable));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(widget->get_modal())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+5,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_win_modal));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);    
        if(widget->get_destroy_with_parent())
            cb->set_active(0);
        else
           cb->set_active(1);    
        value_widget_vector.insert(value_widget_vector.begin()+6,cb);                   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_win_destroy_with_parent));
        }
    else if(type=="gtk_vbox" || type=="gtk_hbox")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Spacing"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Homogeneous"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Number of items"));
        
        label_vector_size = 3;
        
        if(type=="gtk_vbox")
        {
            gtk_vbox *vbox = dynamic_cast<gtk_vbox *>(current_widget);
            
            Gtk::SpinButton* sb = new Gtk::SpinButton();       
            Gtk::Adjustment* adjustment = sb->get_adjustment();
            adjustment->set_upper(1000);
            adjustment->set_lower(0);
            adjustment->set_value(vbox->get_spacing());   
            adjustment->set_step_increment(1);     
            adjustment->set_page_increment(1);
            value_widget_vector.insert(value_widget_vector.begin(),sb);
            sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_box_spacing_changed));
            
            Gtk::ComboBox* cb = new Gtk::ComboBox();
            cb->set_model(cb_tree_model_true_false);
            cb->pack_start(model_column.col);
            if(vbox->get_homogeneous())
                cb->set_active(0); 
            else
                cb->set_active(1);
            value_widget_vector.insert(value_widget_vector.begin()+1,cb);
            cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_box_homogeneous_changed));
            
            sb = new Gtk::SpinButton();       
            adjustment = sb->get_adjustment();
            adjustment->set_upper(1000);
            adjustment->set_lower(0);
            adjustment->set_value(vbox->get_number_of_widgets());   
            adjustment->set_step_increment(1);     
            adjustment->set_page_increment(1);
            value_widget_vector.insert(value_widget_vector.begin()+2,sb);  
            sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_box_number_of_items_changed));      
            }
        else if(type=="gtk_hbox")
        {
            gtk_hbox *hbox = dynamic_cast<gtk_hbox *>(current_widget);
            
            Gtk::SpinButton* sb = new Gtk::SpinButton();
            Gtk::Adjustment* adjustment = sb->get_adjustment();
            adjustment->set_upper(1000);
            adjustment->set_lower(0);
            adjustment->set_value(hbox->get_spacing());
            adjustment->set_step_increment(1);
            adjustment->set_page_increment(1);
            value_widget_vector.insert(value_widget_vector.begin(),sb);
            sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_box_spacing_changed));
            
            Gtk::ComboBox* cb = new Gtk::ComboBox();
            cb->set_model(cb_tree_model_true_false);
            cb->pack_start(model_column.col);
            if(hbox->get_homogeneous())
                cb->set_active(0); 
            else
                cb->set_active(1);
            value_widget_vector.insert(value_widget_vector.begin()+1,cb);
            cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_box_homogeneous_changed));
            
            sb = new Gtk::SpinButton();       
            adjustment = sb->get_adjustment();
            adjustment->set_upper(1000);
            adjustment->set_lower(0);
            adjustment->set_value(hbox->get_number_of_widgets());   
            adjustment->set_step_increment(1);     
            adjustment->set_page_increment(1);
            value_widget_vector.insert(value_widget_vector.begin()+2,sb);  
            sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_box_number_of_items_changed));      
            }
        }
    else if(type=="gtk_table")
    {
        gtk_table* table = dynamic_cast<gtk_table*>(current_widget);
        
        label_vector.insert(label_vector.begin(),new Gtk::Label("Row Spacing"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Column Spacing"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Homogeneous"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Rows"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Columns"));
        
        label_vector_size = 5;
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();       
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(table->get_row_spacing());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin(),sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_table_row_spacing_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(table->get_col_spacing());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+1,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_table_col_spacing_changed));
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);  
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);
        if(table->get_homogeneous())
            cb->set_active(0);
        else
            cb->set_active(1);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_table_homogeneous_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(table->get_rows());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+3,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_table_rows_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(table->get_cols());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+4,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_table_cols_changed));
        }
    else if(type=="gtk_fixed")
    {        
         label_vector_size = 0;
        }
    else if(type=="gtk_scrollwin")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Horizontal Scrollbar Policy"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Vertical Scrollbar Policy"));        
        
        label_vector_size=2;
        
        gtk_scrollwin* scroll_win = dynamic_cast<gtk_scrollwin*>(current_widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_scrollbar_policy);
        cb->pack_start(model_column_scrollbar_policy.col);
        if(scroll_win->get_horizontal_policy()=="AUTOMATIC")
            cb->set_active(1);
        else if(scroll_win->get_horizontal_policy()=="ALWAYS")
            cb->set_active(0);
        else
            cb->set_active(2);
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scroll_win_horizontal_policy_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_scrollbar_policy);
        cb->pack_start(model_column_scrollbar_policy.col);
        if(scroll_win->get_vertical_policy()=="AUTOMATIC")
            cb->set_active(1);
        else if(scroll_win->get_vertical_policy()=="ALWAYS")
            cb->set_active(0);
        else
            cb->set_active(2);
        value_widget_vector.insert(value_widget_vector.begin()+1,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scroll_win_vertical_policy_changed));
        }
    else if(type=="gtk_textview")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Pixels Above Lines"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Pixels Below Lines"));      
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Pixels Inside Wrap"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Editable"));      
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Wrap Mode"));
        label_vector.insert(label_vector.begin()+5,new Gtk::Label("Justification"));      
        label_vector.insert(label_vector.begin()+6,new Gtk::Label("Cursor Visible"));
        
        label_vector_size = 7;
        
        gtk_textview* textview = dynamic_cast<gtk_textview*>(current_widget);
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();       
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(textview->get_pixels_above_lines());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin(),sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_text_view_pixels_above_lines_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(textview->get_pixels_below_lines());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+1,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_text_view_pixels_below_lines_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(textview->get_pixels_inside_wrap());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+2,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_text_view_pixels_inside_wrap_changed));
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(textview->get_editable())
            cb->set_active(0);
        else
            cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+3,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_text_view_editable_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_wrap_mode);
        cb->pack_start(model_column.col);
        if(textview->get_wrapmode()=="NONE")
            cb->set_active(0);
        else if(textview->get_wrapmode()=="CHARACTER")
            cb->set_active(1);
        else if(textview->get_wrapmode()=="WORD")
            cb->set_active(2);
        else 
            cb->set_active(3);           
        value_widget_vector.insert(value_widget_vector.begin()+4,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_text_view_wrap_mode_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_justification);
        cb->pack_start(model_column.col);        
        value_widget_vector.insert(value_widget_vector.begin()+5,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_text_view_justification_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(textview->get_cursor_visible())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+6,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_text_view_cursor_visible_changed));
        }
    else if(type=="gtk_label")
    {
        label_vector_size = 1;
        label_vector.insert(label_vector.begin(),new Gtk::Label("Text"));
        
        Gtk::Label* label = dynamic_cast<Gtk::Label*>(current_widget);
        Gtk::TextView* textview = new Gtk::TextView();
        value_widget_vector.insert(value_widget_vector.begin(),textview);
        textview->get_buffer()->set_text(label->get_text());
        textview->get_buffer()->signal_erase().connect(sigc::mem_fun(*this,&PageGeneral::on_lbltext_deleted));
        textview->get_buffer()->signal_insert().connect(sigc::mem_fun(*this,&PageGeneral::on_lbltext_inserted));
        }
    else if(type=="gtk_button")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Horizontal \nAlignment"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Vertical \nAlignment"));      
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Focus\nOn Click"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Text"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Stock"));
        
        label_vector_size=5;
        
        gtk_button *button = dynamic_cast<gtk_button*>(current_widget);
        float xalign,yalign;
        button->get_alignment(xalign,yalign);
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();       
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1);
        adjustment->set_lower(0);        
        adjustment->set_value(xalign);   
        adjustment->set_step_increment(0.01);     
        adjustment->set_page_increment(0.01);
        sb->set_digits(2);
        value_widget_vector.insert(value_widget_vector.begin(),sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_button_horizontal_alignment_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1);
        adjustment->set_lower(0);
        adjustment->set_value(yalign);   
        adjustment->set_step_increment(0.01);     
        adjustment->set_page_increment(0.01);
        sb->set_digits(2);
        value_widget_vector.insert(value_widget_vector.begin()+1,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_button_vertical_alignment_changed));
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(button->get_focus_on_click())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_button_focus_on_click_changed));
        
        Gtk::TextView* textview = new Gtk::TextView();
        value_widget_vector.insert(value_widget_vector.begin()+3,textview);
        textview->get_buffer()->set_text(button->get_label());
        textview->get_buffer()->signal_erase().connect(sigc::mem_fun(*this,&PageGeneral::on_buttontext_deleted));
        textview->get_buffer()->signal_insert().connect(sigc::mem_fun(*this,&PageGeneral::on_buttontext_inserted));
        if(button->get_use_stock())
            textview->set_sensitive(false);
            
        cb = get_stock_combo_box(model_column_stock,cb_tree_model_stock);
        value_widget_vector.insert(value_widget_vector.begin()+4,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_stock_changed));
        Gtk::TreeModel::iterator iter = cb->get_model()->children().begin();
        while(iter)
        {
            std::string name = (*iter)[model_column_stock.col];
            if(name == button->get_stock())
            {                
                std::string iter_str = cb->get_model()->get_string(iter);                
                std::istringstream oss(iter_str);
                int index; 
                oss>>index;
                cb->set_active(index);
                break;
                }
            iter++;
            }
        }
    else if(type=="gtk_combobox"||type=="gtk_comboboxtext")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Set Active Item"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Row Span"));      
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Column Span"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Wrap Width"));
        
        Gtk::ComboBox* combobox = dynamic_cast<Gtk::ComboBox*>(current_widget);
        if(!combobox)
            return;
        Gtk::SpinButton* sb = new Gtk::SpinButton();       
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(-1);
        adjustment->set_value(combobox->get_active());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin(),sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_combo_box_set_active_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(-1);
        adjustment->set_value(combobox->get_row_span_column());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+1,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_combo_box_row_span_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(-1);
        adjustment->set_value(combobox->get_column_span_column());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+2,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_combo_box_column_span_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1000);
        adjustment->set_lower(-1);
        adjustment->set_value(combobox->get_wrap_width());   
        adjustment->set_step_increment(1);     
        adjustment->set_page_increment(1);
        value_widget_vector.insert(value_widget_vector.begin()+3,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_combo_box_wrap_width_changed));
        
        label_vector_size  = 4;
        }
    else if(type=="gtk_radiobutton"||type=="gtk_togglebutton"||type=="gtk_checkbutton")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Active"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Inconsistent"));      
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Focus On Click"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Horizontal Alignment for Child"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Vertical Alignment for Child"));      
        label_vector.insert(label_vector.begin()+5,new Gtk::Label("Label"));      
        
        label_vector_size=6;
        
        Gtk::ToggleButton *togglebutton = dynamic_cast<Gtk::ToggleButton*>(current_widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(togglebutton->get_active())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_toggle_button_active_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(togglebutton->get_inconsistent())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+1,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_toggle_button_inconsistent_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        if(togglebutton->get_focus_on_click())
            cb->set_active(0);
        else
           cb->set_active(1);
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_toggle_button_focus_on_click_changed));
        
        float xalign,yalign;
        togglebutton->get_alignment(xalign,yalign);
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();       
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1);
        adjustment->set_lower(0);        
        adjustment->set_value(xalign);   
        adjustment->set_step_increment(0.01);     
        adjustment->set_page_increment(0.01);
        sb->set_digits(2);
        value_widget_vector.insert(value_widget_vector.begin()+3,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_toggle_button_horizontal_alignment_changed));
        
        sb = new Gtk::SpinButton();       
        adjustment = sb->get_adjustment();
        adjustment->set_upper(1);
        adjustment->set_lower(0);        
        adjustment->set_value(xalign);   
        adjustment->set_step_increment(0.01);     
        adjustment->set_page_increment(0.01); 
        sb->set_digits(2);
        value_widget_vector.insert(value_widget_vector.begin()+4,sb);
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_toggle_button_vertical_alignment_changed));
        
        Gtk::TextView* textview = new Gtk::TextView();
        value_widget_vector.insert(value_widget_vector.begin()+5,textview);
        textview->get_buffer()->signal_erase().connect(sigc::mem_fun(*this,&PageGeneral::on_togglebuttontext_deleted));
        textview->get_buffer()->signal_insert().connect(sigc::mem_fun(*this,&PageGeneral::on_togglebuttontext_inserted));
        }
    else if(type=="gtk_toolbar")
    {          
        //label_vector_size = 0; 
        label_vector.insert(label_vector.begin(),new Gtk::Label("Show Arrow"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Icon Size"));      
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Toolbar Style"));
        
        label_vector_size=3;
        
        gtk_toolbar* toolbar = dynamic_cast<gtk_toolbar*>(current_widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_true_false);
        cb->pack_start(model_column.col);
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->set_active(!toolbar->get_show_arrow());
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_toolbar_show_arrow_changed));
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();       
        Gtk::Adjustment* adjustment = sb->get_adjustment();
        adjustment->set_upper(1);
        adjustment->set_lower(0);        
        //adjustment->set_value(xalign);   
        adjustment->set_step_increment(0.01);     
        adjustment->set_page_increment(0.01);
        sb->set_digits(2);
        value_widget_vector.insert(value_widget_vector.begin()+1,sb);
        //sb->set_value(toolbar->get_icon_size());
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_toolbar_icon_size_changed));
        
        cb = new Gtk::ComboBox();
        cb->set_model(cb_tree_model_toolbar_style);
        cb->pack_start(model_column.col);
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);
         if(toolbar->get_toolbarstyle()=="ICONS ONLY")
            cb->set_active(0);
        else if(toolbar->get_toolbarstyle()=="TEXT ONLY")
            cb->set_active(1);
        else if(toolbar->get_toolbarstyle()=="TEXT BELOW ICONS")
            cb->set_active(2);
        else if(toolbar->get_toolbarstyle()=="TEXT BESIDES ICONS")
            cb->set_active(3);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_toolbar_toolbar_style_changed));
        
        attach(cmdEditToolbar,0,2,4,5,Gtk::EXPAND,Gtk::SHRINK);
        }
    else if(type=="gtk_statusbar")
    { 
        label_vector_size = 0;
        }
    else if(type=="gtk_notebook")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Tab Position"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Show Tabs"));       
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Show Border")); 
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Scrollable")); 
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Page Count")) ;
         
        label_vector_size=5;
        
        gtk_notebook* notebook = dynamic_cast<gtk_notebook*>(current_widget);
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_tab_position); 
        cb->pack_start(model_column.col); 
        if(notebook->get_tab_pos()=="LEFT")
            cb->set_active(0);
        else if(notebook->get_tab_pos()=="RIGHT")
            cb->set_active(1);
        else if(notebook->get_tab_pos()=="BOTTOM")
            cb->set_active(2);
        else if(notebook->get_tab_pos()=="TOP")
            cb->set_active(3);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_notebook_tab_pos_changed));
        value_widget_vector.insert(value_widget_vector.begin(),cb); 
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!notebook->get_show_tabs()); 
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_notebook_show_tabs_changed));       
        value_widget_vector.insert(value_widget_vector.begin()+1,cb); 
         
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!notebook->get_show_border());
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_notebook_show_border_changed));
        value_widget_vector.insert(value_widget_vector.begin()+2,cb); 
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!notebook->get_scrollable());
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_notebook_scrollable_changed));
        value_widget_vector.insert(value_widget_vector.begin()+3,cb); 
         
        Gtk::SpinButton* sb = new Gtk::SpinButton();        
        Gtk::Adjustment* adjustment = sb->get_adjustment(); 
        adjustment->set_upper(1000);
        adjustment->set_lower(0);
        adjustment->set_value(notebook->get_n_pages());
        adjustment->set_step_increment(1);      
        adjustment->set_page_increment(1); 
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_notebook_page_count_changed));
        value_widget_vector.insert(value_widget_vector.begin()+4,sb); 
        }
    else if(type=="gtk_menubar")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Pack Direction"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Child Pack Direction"));       
        
        label_vector_size = 2;
        
        gtk_menubar* menubar = dynamic_cast<gtk_menubar*>(current_widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_pack_direction); 
        cb->pack_start(model_column_pack_direction.col); 
        if(menubar->get_packdirection()=="LEFT TO RIGHT")
            cb->set_active(0);
        else if(menubar->get_packdirection()=="RIGHT TO LEFT")
            cb->set_active(1);
        else if(menubar->get_packdirection()=="TOP TO BOTTOM")
            cb->set_active(2);
        else if(menubar->get_packdirection()=="BOTTOM TO TOP")
            cb->set_active(3);                    
        value_widget_vector.insert(value_widget_vector.begin(),cb); 
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_menubar_pack_direction_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_pack_direction); 
        cb->pack_start(model_column_pack_direction.col); 
        if(menubar->get_childpackdirection()=="LEFT TO RIGHT")
            cb->set_active(0);
        else if(menubar->get_childpackdirection()=="RIGHT TO LEFT")
            cb->set_active(1);
        else if(menubar->get_childpackdirection()=="TOP TO BOTTOM")
            cb->set_active(2);
        else if(menubar->get_childpackdirection()=="BOTTOM TO TOP")
            cb->set_active(3);
        value_widget_vector.insert(value_widget_vector.begin()+1,cb); 
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_menubar_child_pack_direction_changed));
        
        attach(cmdEditMenubar,0,2,3,4,Gtk::EXPAND,Gtk::SHRINK);
        }
    else if(type=="gtk_offscreenwindow")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Focus Visible"));
        
        label_vector_size = 1;
        
        gtk_offscreenwindow* offscreen_window = dynamic_cast<gtk_offscreenwindow*>(current_widget);
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!offscreen_window->get_focus_visible());
        value_widget_vector.insert(value_widget_vector.begin(),cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_offscreen_window_focus_visible_changed));
        }
    else if(type=="gtk_eventbox")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Visible Window"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Above Child"));
        
        label_vector_size = 2;
        
        gtk_eventbox* eventbox = dynamic_cast<gtk_eventbox*>(current_widget);
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!eventbox->get_visible_window());
        value_widget_vector.insert(value_widget_vector.begin(),cb);        
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_event_box_visible_window_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!eventbox->get_above_child());
        value_widget_vector.insert(value_widget_vector.begin()+1,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_event_box_above_child_changed));
        }
    else if(type=="gtk_expander")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Expanded"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Use Underline"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Use Markup"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Spacing"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Label Fill"));     
        
        label_vector_size = 5;
        
        Gtk::Expander* expander = dynamic_cast<Gtk::Expander*>(current_widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!expander->get_expanded());
        value_widget_vector.insert(value_widget_vector.begin(),cb);        
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_expander_expanded_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!expander->get_use_underline());
        value_widget_vector.insert(value_widget_vector.begin()+1,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_expander_use_underline_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!expander->get_use_markup());
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_expander_use_markup_changed));
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();        
        Gtk::Adjustment* adjustment = sb->get_adjustment(); 
        adjustment->set_upper(1000); 
        adjustment->set_lower(0); 
        adjustment->set_value(expander->get_spacing());    
        adjustment->set_step_increment(1);      
        adjustment->set_page_increment(1); 
        value_widget_vector.insert(value_widget_vector.begin()+3,sb); 
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_expander_spacing_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!expander->get_label_fill());
        value_widget_vector.insert(value_widget_vector.begin()+4,cb);
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_expander_label_fill_changed));
        }
    else if(type=="gtk_vscale"||type=="gtk_hscale")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Digits"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Draw Value"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Inverted"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Show Fill Level"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Restrict To Fill Level"));
        
        label_vector_size = 5;
        
        Gtk::Scale* scale = dynamic_cast<Gtk::Scale*>(current_widget);
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();        
        Gtk::Adjustment* adjustment = sb->get_adjustment(); 
        adjustment->set_upper(1000); 
        adjustment->set_lower(0); 
        adjustment->set_value(scale->get_digits());    
        adjustment->set_step_increment(1);      
        adjustment->set_page_increment(1); 
        value_widget_vector.insert(value_widget_vector.begin(),sb); 
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_scale_digits_changed));
        
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!scale->get_draw_value());
        value_widget_vector.insert(value_widget_vector.begin()+1,cb);    
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scale_draw_value_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!scale->get_inverted());
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);    
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scale_inverted_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!scale->get_show_fill_level());
        value_widget_vector.insert(value_widget_vector.begin()+3,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scale_show_fill_level_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!scale->get_restrict_to_fill_level());
        value_widget_vector.insert(value_widget_vector.begin()+4,cb); 
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scale_restrict_to_fill_level_changed));
        }
    else if(type=="gtk_spinner")
    {
        label_vector_size = 0;
        }
    else if(type == "gtk_fontbutton"||type=="gtk_filechooserbutton"||type=="gtk_colorbutton")
    {
        label_vector_size = 0;
        }
    else if(type=="gtk_progressbar")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Fractions"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Pulse Step"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Text"));
        
        label_vector_size  = 3;
        
        Gtk::ProgressBar* progress_bar = dynamic_cast<Gtk::ProgressBar*>(current_widget);
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();        
        Gtk::Adjustment* adjustment = sb->get_adjustment(); 
        adjustment->set_upper(1.0); 
        adjustment->set_lower(0); 
        adjustment->set_value(progress_bar->get_fraction());    
        adjustment->set_step_increment(0.01);      
        adjustment->set_page_increment(0.01); 
        sb->set_digits(2);
        value_widget_vector.insert(value_widget_vector.begin(),sb); 
        
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_progress_bar_fractions_changed));
        
        sb = new Gtk::SpinButton();        
        adjustment = sb->get_adjustment(); 
        adjustment->set_upper(1000); 
        adjustment->set_lower(0); 
        adjustment->set_value(progress_bar->get_pulse_step());
        adjustment->set_step_increment(1);      
        adjustment->set_page_increment(1); 
        value_widget_vector.insert(value_widget_vector.begin()+1,sb); 
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_progress_bar_pulse_step_changed));
        
        Gtk::Entry* entry = new Gtk::Entry();
        value_widget_vector.insert(value_widget_vector.begin()+2,entry);    
        }
    else if(type=="gtk_frame")
    {
        
        }    
    else if(type=="gtk_treeview")
    {
        label_vector.insert(label_vector.begin(),new Gtk::Label("Headers Visible"));
        label_vector.insert(label_vector.begin()+1,new Gtk::Label("Headers Clickable"));
        label_vector.insert(label_vector.begin()+2,new Gtk::Label("Reorderable"));
        label_vector.insert(label_vector.begin()+3,new Gtk::Label("Rules Hint"));
        label_vector.insert(label_vector.begin()+4,new Gtk::Label("Enable Search"));
        label_vector.insert(label_vector.begin()+5,new Gtk::Label("Search Column"));
        label_vector.insert(label_vector.begin()+6,new Gtk::Label("Fixed Height Mode"));
        label_vector.insert(label_vector.begin()+7,new Gtk::Label("Hover Selection"));
        label_vector.insert(label_vector.begin()+8,new Gtk::Label("Show Expanders"));
        
        label_vector_size  = 9;
        
        Gtk::TreeView* tree_view = dynamic_cast<Gtk::TreeView*>(current_widget);
        
        Gtk::ComboBox* cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_headers_visible());
        value_widget_vector.insert(value_widget_vector.begin(),cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_headers_visible_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_headers_clickable());
        value_widget_vector.insert(value_widget_vector.begin()+1,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_headers_clickable_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_reorderable());
        value_widget_vector.insert(value_widget_vector.begin()+2,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_reorderable_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_rules_hint());
        value_widget_vector.insert(value_widget_vector.begin()+3,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_rules_hint_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        //cb->set_active(!tree_view->get_enable_search());
        value_widget_vector.insert(value_widget_vector.begin()+4,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_scale_inverted_changed));
        
        Gtk::SpinButton* sb = new Gtk::SpinButton();        
        Gtk::Adjustment* adjustment = sb->get_adjustment(); 
        adjustment->set_upper(1000); 
        adjustment->set_lower(0); 
        adjustment->set_value(tree_view->get_search_column());    
        adjustment->set_step_increment(1);      
        adjustment->set_page_increment(1); 
        value_widget_vector.insert(value_widget_vector.begin()+5,sb);       
        sb->signal_value_changed().connect(sigc::mem_fun(*this,&PageGeneral::sb_tree_view_search_column_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_fixed_height_mode());
        value_widget_vector.insert(value_widget_vector.begin()+6,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_fixed_height_mode_changed));
        
        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_hover_selection());
        value_widget_vector.insert(value_widget_vector.begin()+7,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_hover_selection_changed));

        cb = new Gtk::ComboBox(); 
        cb->set_model(cb_tree_model_true_false); 
        cb->pack_start(model_column.col); 
        cb->set_active(!tree_view->get_show_expanders());
        value_widget_vector.insert(value_widget_vector.begin()+8,cb);   
        cb->signal_changed().connect(sigc::mem_fun(*this,&PageGeneral::cb_tree_view_show_expanders_changed));
        }
    else if(type == "gtk_image_menu_item")
    {
        }
    else if(type == "gtk_separatormenuitem")
    {
        }
    else if(type == "gtk_checkmenuitem")
    {
        }
    int y=1;
    for(int i=1;i<=label_vector_size;i++)
    {        
        if(label_vector[i-1]==NULL)
            break;
        attach(*label_vector[i-1],0,1,y,y+1,Gtk::FILL,Gtk::SHRINK);
        if(dynamic_cast<Gtk::TextView*>(value_widget_vector[i-1])!=NULL)
        {
            attach(*value_widget_vector[i-1],1,2,y,y+15,Gtk::FILL,Gtk::FILL);
            y+=14;
            }
        else
            attach(*value_widget_vector[i-1],1,2,y,y+1,Gtk::FILL,Gtk::SHRINK);
        y++;
        }    
    show_all_children();
    }

PageGeneral::type_signal_name_changed PageGeneral::signal_name_changed()
{
    return m_signal_name_changed;
    }

void PageGeneral::cb_win_type_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active();
    dynamic_cast<gtk_window*>(current_widget)->set_type((*iter)[model_win_type.col]);   
    }
void PageGeneral::txt_win_title_deleted(int pos, int chars)
{
    dynamic_cast<gtk_window*>(current_widget)->set_title(dynamic_cast<Gtk::Entry*>(value_widget_vector[1])->get_buffer()->get_text());
    }
void PageGeneral::txt_win_title_inserted(int pos, const char* text, int chars)
{
    dynamic_cast<gtk_window*>(current_widget)->set_title(dynamic_cast<Gtk::Entry*>(value_widget_vector[1])->get_buffer()->get_text());
    }
void PageGeneral::sb_win_default_height_changed()
{
    dynamic_cast<gtk_window*>(current_widget)->set_default_height(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[2])->get_value());
    }
void PageGeneral::sb_win_default_width_changed()
{
    dynamic_cast<gtk_window*>(current_widget)->set_default_width(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[3])->get_value());
    }
void PageGeneral::cb_win_resizable()
{
    dynamic_cast<gtk_window*>(current_widget)->set_resizable(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::cb_win_modal()
{
    dynamic_cast<gtk_window*>(current_widget)->set_modal(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[5])->get_active_row_number());
    }
void PageGeneral::cb_win_destroy_with_parent()
{
    dynamic_cast<gtk_window*>(current_widget)->set_destroy_with_parent(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[6])->get_active_row_number());
    }

//gtk_vbox and gtk_hbox
void PageGeneral::sb_box_spacing_changed()
{
    if (current_widget_type=="gtk_vbox")
        dynamic_cast<gtk_vbox*>(current_widget)->set_spacing(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    else if(current_widget_type=="gtk_hbox")
        dynamic_cast<gtk_hbox*>(current_widget)->set_spacing(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }
void PageGeneral::sb_box_number_of_items_changed()
{
    if (current_widget_type=="gtk_vbox")
        dynamic_cast<gtk_vbox*>(current_widget)->set_number_of_widgets(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[2])->get_value());
    else if(current_widget_type=="gtk_hbox")
        dynamic_cast<gtk_hbox*>(current_widget)->set_number_of_widgets(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[2])->get_value());
    }
void PageGeneral::cb_box_homogeneous_changed()
{
    if (current_widget_type=="gtk_vbox")
        dynamic_cast<gtk_vbox*>(current_widget)->set_homogeneous(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    else if(current_widget_type=="gtk_hbox")
        dynamic_cast<gtk_hbox*>(current_widget)->set_homogeneous(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }

//gtk_table
void PageGeneral::sb_table_row_spacing_changed()
{
    dynamic_cast<gtk_table*>(current_widget)->set_row_spacing(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }
void PageGeneral::sb_table_col_spacing_changed()
{
    dynamic_cast<gtk_table*>(current_widget)->set_col_spacing(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }
void PageGeneral::cb_table_homogeneous_changed()
{
    dynamic_cast<gtk_table*>(current_widget)->set_homogeneous(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active_row_number());
    }
void PageGeneral::sb_table_rows_changed()
{
    dynamic_cast<gtk_table*>(current_widget)->set_rows(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[3])->get_value());
    }
void PageGeneral::sb_table_cols_changed()
{
    dynamic_cast<gtk_table*>(current_widget)->set_cols(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[4])->get_value());
    }
        
//gtk_scrollwin
void PageGeneral::cb_scroll_win_horizontal_policy_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active();
    dynamic_cast<gtk_scrollwin*>(current_widget)->set_horizontal_policy((*iter)[model_column_scrollbar_policy.col]);   
    }

void PageGeneral::cb_scroll_win_vertical_policy_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active();
    dynamic_cast<gtk_scrollwin*>(current_widget)->set_vertical_policy((*iter)[model_column_scrollbar_policy.col]);   
    }

//gtk_textview
void PageGeneral::sb_text_view_pixels_above_lines_changed()
{
    dynamic_cast<gtk_textview*>(current_widget)->set_pixels_above_lines(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }
void PageGeneral::sb_text_view_pixels_below_lines_changed()
{
    dynamic_cast<gtk_textview*>(current_widget)->set_pixels_below_lines(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }
void PageGeneral::sb_text_view_pixels_inside_wrap_changed()
{
    dynamic_cast<gtk_textview*>(current_widget)->set_pixels_inside_wrap(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[2])->get_value());
    }
void PageGeneral::cb_text_view_editable_changed()
{
    dynamic_cast<gtk_textview*>(current_widget)->set_editable(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[3])->get_active_row_number());
    }
void PageGeneral::cb_text_view_wrap_mode_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active();
    dynamic_cast<gtk_textview*>(current_widget)->set_wrapmode((*iter)[model_column.col]);   
    }
void PageGeneral::cb_text_view_justification_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[5])->get_active();
    dynamic_cast<gtk_textview*>(current_widget)->set_justifi((*iter)[model_column.col]);   
    }
void PageGeneral::cb_text_view_cursor_visible_changed()
{
    dynamic_cast<gtk_textview*>(current_widget)->set_cursor_visible(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[6])->get_active_row_number());
    }

//gtk_button
void PageGeneral::sb_button_horizontal_alignment_changed()
{
    dynamic_cast<gtk_button*>(current_widget)->set_alignment(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value(),dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }
void PageGeneral::sb_button_vertical_alignment_changed()
{
    dynamic_cast<gtk_button*>(current_widget)->set_alignment(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value(),dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }
void PageGeneral::cb_button_focus_on_click_changed()
{
    dynamic_cast<gtk_button*>(current_widget)->set_focus_on_click(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active_row_number());
    }
void PageGeneral::on_buttontext_deleted(const Gtk::TextIter&,const Gtk::TextIter&)
{
    dynamic_cast<gtk_button*>(current_widget)->set_label((dynamic_cast<Gtk::TextView*>(value_widget_vector[3]))->get_buffer()->get_text());
    }
void PageGeneral::on_buttontext_inserted(const Gtk::TextIter&,const std::string&,int)
{
    dynamic_cast<gtk_button*>(current_widget)->set_label((dynamic_cast<Gtk::TextView*>(value_widget_vector[3]))->get_buffer()->get_text());
    }

void PageGeneral::cb_stock_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active();
    //std::cout<<"FFF"<<dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_model()->get_string(iter)<<std::endl;
    dynamic_cast<gtk_button*>(current_widget)->set_stock((*iter)[model_column.col]);
    if(dynamic_cast<gtk_button*>(current_widget)->get_use_stock())
    {
         value_widget_vector[3]->set_sensitive(false);
         dynamic_cast<Gtk::TextView*>(value_widget_vector[3])->get_buffer()->set_text(dynamic_cast<gtk_button*>(current_widget)->get_label());
        }
    else
    {
        value_widget_vector[3]->set_sensitive(true);
        dynamic_cast<Gtk::TextView*>(value_widget_vector[3])->get_buffer()->set_text(dynamic_cast<gtk_button*>(current_widget)->get_label());
        }
    }

//gtk_combobox and gtk_comboboxtext
void PageGeneral::sb_combo_box_set_active_changed()
{
    dynamic_cast<Gtk::ComboBox*>(current_widget)->set_active(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }
void PageGeneral::sb_combo_box_row_span_changed()
{
    dynamic_cast<Gtk::ComboBox*>(current_widget)->set_row_span_column(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }
void PageGeneral::sb_combo_box_column_span_changed()
{
    dynamic_cast<Gtk::ComboBox*>(current_widget)->set_column_span_column(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[2])->get_value());
    }
void PageGeneral::sb_combo_box_wrap_width_changed()
{
    dynamic_cast<Gtk::ComboBox*>(current_widget)->set_wrap_width(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[3])->get_value());
    }

//gtk_togglebutton and gtk_radiobutton
void PageGeneral::cb_toggle_button_active_changed()
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_active(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number());
    }
void PageGeneral::cb_toggle_button_inconsistent_changed()
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_inconsistent(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }
void PageGeneral::cb_toggle_button_focus_on_click_changed()
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_focus_on_click(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active_row_number());
    }
void PageGeneral::sb_toggle_button_horizontal_alignment_changed()
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_alignment(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[3])->get_value(),dynamic_cast<Gtk::SpinButton*>(value_widget_vector[4])->get_value());
    }
void PageGeneral::sb_toggle_button_vertical_alignment_changed()
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_alignment(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[3])->get_value(),dynamic_cast<Gtk::SpinButton*>(value_widget_vector[4])->get_value());
    }
void PageGeneral::on_togglebuttontext_deleted(const Gtk::TextIter&,const Gtk::TextIter&)
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_label((dynamic_cast<Gtk::TextView*>(value_widget_vector[5]))->get_buffer()->get_text());
    }
void PageGeneral::on_togglebuttontext_inserted(const Gtk::TextIter&,const std::string&,int)
{
    dynamic_cast<Gtk::ToggleButton*>(current_widget)->set_label((dynamic_cast<Gtk::TextView*>(value_widget_vector[5]))->get_buffer()->get_text());
    }

//gtk_toolbar
void PageGeneral::cb_toolbar_show_arrow_changed()
{
    gtk_toolbar* toolbar = dynamic_cast<gtk_toolbar*>(current_widget);
    toolbar->set_show_arrow(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number());
    }
void PageGeneral::sb_toolbar_icon_size_changed()
{  
    gtk_toolbar* toolbar = dynamic_cast<gtk_toolbar*>(current_widget);
    //toolbar->set_icon_size(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }
void PageGeneral::cb_toolbar_toolbar_style_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active();
    dynamic_cast<gtk_toolbar*>(current_widget)->set_toolbarstyle((*iter)[model_column_toolbar_style.col]);   
    }

void PageGeneral::cmdEditToolbar_clicked()
{
    if(dynamic_cast<gtk_toolbar*>(current_widget)==NULL)
        return;
    
    gtk_toolbar* toolbar = dynamic_cast<gtk_toolbar*>(current_widget);
    item* toolbar_item = current_frame.widget_tree.get_item_from_widget(current_widget);
    toolbar_editor te(toolbar_item);    
    te.show_all();
    if (te.run()==1)
    {
        item* toolbar_child = toolbar_item->child;
        while(toolbar_child)
        {
            toolbar->remove(*(toolbar_child->widget));            
            toolbar_child=toolbar_child->next;
            }
        object_box.delete_child_rows(current_widget->get_name());
        std::string type; 
        delete toolbar_item->child;
        toolbar_item->child=NULL;
        Gtk::TreeModel::Children::iterator iter = te.treemodel->children().begin();
        while(iter)
        {
            std::string col_type = (*iter)[te.columns.col_type];
            Gtk::Widget* widget;
            std::string text = (*iter)[te.columns.col_text];
            std::string stock = (*iter)[te.columns.col_stock];
            std::string name = (*iter)[te.columns.col_name];
            
            if(name=="")
                break;

            if(col_type=="Button")
            {
                type="gtk_tool_button";
                gtk_tool_button* tb = new gtk_tool_button(text);
                tb->set_stock(stock);
                toolbar->append(*tb);
                widget=(Gtk::Widget*) tb;
                }
            else if(col_type=="Separator")
            {
                type="gtk_separator_item";
                Gtk::SeparatorToolItem* st = new Gtk::SeparatorToolItem();
                toolbar->append(*st);
                widget=(Gtk::Widget*)st;
                }
            else if(col_type== "Radio")
            {
                type="gtk_radio_tool_button";
                gtk_radio_tool_button* rb = new gtk_radio_tool_button();
                rb->set_stock(stock);
                rb->set_label(text);
                toolbar->append(*rb);
                widget=(Gtk::Widget*)rb;
                }
            widget->set_name(name);        
            toolbar_item->add_next_child(new item(*widget,type,NULL,NULL,NULL,NULL));            
            object_box.add_child_row(toolbar->get_name(),widget->get_name(),type);
            iter++;
            }
        }
    toolbar->show_all_children();    
    }

//gtk_notebook
void PageGeneral::cb_notebook_tab_pos_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active();
    dynamic_cast<gtk_notebook*>(current_widget)->set_tab_pos((*iter)[model_column_tab_position.col]);   
    }
void PageGeneral::cb_notebook_show_tabs_changed()
{
    dynamic_cast<gtk_notebook*>(current_widget)->set_show_tabs(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }
void PageGeneral::cb_notebook_show_border_changed()
{
    dynamic_cast<gtk_notebook*>(current_widget)->set_show_border(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active_row_number());
    }
void PageGeneral::cb_notebook_scrollable_changed()
{
    dynamic_cast<gtk_notebook*>(current_widget)->set_scrollable(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[3])->get_active_row_number());
    }
void PageGeneral::sb_notebook_page_count_changed()
{
    dynamic_cast<gtk_notebook*>(current_widget)->set_page_count(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[4])->get_value());
    }

//gtk_menubar
void PageGeneral::cb_menubar_pack_direction_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active();
    dynamic_cast<gtk_menubar*>(current_widget)->set_packdirection((*iter)[model_column_pack_direction.col]);   
    }
void PageGeneral::cb_menubar_child_pack_direction_changed()
{
    Gtk::TreeModel::iterator iter = dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active();
    dynamic_cast<gtk_menubar*>(current_widget)->set_childpackdirection((*iter)[model_column_pack_direction.col]);   
    }

void PageGeneral::update_menubar(Gtk::TreeModel::Children::iterator iter,item* parent,ModelColumnMenuBarEditor& col)
{
    while(iter)
    {
        std::string _name = (*iter)[col.col_name];
        std::string _type = (*iter)[col.col_type];
        std::string _text = (*iter)[col.col_text];
        std::string _stock =(*iter)[col.col_stock];
         
        if(_type=="Menu")
        {
            gtk_image_menu_item* menuitem = new gtk_image_menu_item(_text);            
            item* _item = new item(*menuitem,"gtk_image_menu_item",NULL,NULL,NULL,NULL);
            menuitem->set_stock(_stock);
            parent->add_next_child(_item);
            menuitem->set_name(_name);
            object_box.add_child_row(parent->widget->get_name(),menuitem->get_name(),_type);
            if (dynamic_cast<Gtk::MenuShell*>(parent->widget) !=NULL)
                dynamic_cast<Gtk::MenuShell*>(parent->widget)->append(*menuitem);
                
            Gtk::Menu* menu = new Gtk::Menu();
            item* __item = new item(*menu,"gtk_menu",NULL,NULL,NULL,NULL);
            _item->add_next_child(__item);            
            menu->set_name(_name+"_menu");          
            object_box.add_child_row(_name,menu->get_name(),"gtk_menu");
            menuitem->set_submenu(*menu);
            
            if(((*iter).children()).begin())
                update_menubar(((*iter).children()).begin(),__item,col);
            }
        else if(_type=="Menu Item")
        {
            gtk_image_menu_item* menuitem = new gtk_image_menu_item(_text);            
            menuitem->set_label(_text);
            menuitem->set_stock(_stock);            
            parent->add_next_child(new item(*menuitem,"gtk_image_menu_item",NULL,NULL,NULL,NULL));
            menuitem->set_name(_name);            
            object_box.add_child_row(parent->widget->get_name(),menuitem->get_name(),"gtk_image_menu_item");
            if (dynamic_cast<Gtk::MenuShell*>(parent->widget) !=NULL)
                dynamic_cast<Gtk::MenuShell*>(parent->widget)->append(*menuitem);
            }
        else if(_type=="Separator")
        {
            gtk_separator_menu_item* separator = new gtk_separator_menu_item();
            parent->add_next_child(new item(*separator,"gtk_separatormenuitem",NULL,NULL,NULL,NULL));
            separator->set_name(_name);
            object_box.add_child_row(parent->widget->get_name(),separator->get_name(),"gtk_separatormenuitem");
            if (dynamic_cast<Gtk::MenuShell*>(parent->widget) !=NULL)
                dynamic_cast<Gtk::MenuShell*>(parent->widget)->append(*separator);
            }
        else if(_type=="Radio")
        {
            /*gtl_radio_menu_item* radio = new gtl_radio_menu_item();
            parent->add_next_child(new item(*radio,"gtk_radiomenuitem",NULL,NULL,NULL,NULL));
            radio->set_name(_name);
            object_box.add_child_row(parent->widget->get_name(),radio->get_name(),_type);*/
            }
        else if(_type=="Check")
        {
            gtk_check_menu_item* check = new gtk_check_menu_item(_text);
            parent->add_next_child(new item(*check,"gtk_checkmenuitem",NULL,NULL,NULL,NULL));
            check->set_name(_name);
            object_box.add_child_row(parent->widget->get_name(),check->get_name(),"gtk_checkmenuitem");
            if (dynamic_cast<Gtk::MenuShell*>(parent->widget) !=NULL)
                dynamic_cast<Gtk::MenuShell*>(parent->widget)->append(*check);
            }
        //std::cout<<"NAME "<<_name<<std::endl;        
        iter++;
        }
    }

void PageGeneral::cmdEditMenubar_clicked()
{
    if(dynamic_cast<gtk_menubar*>(current_widget)==NULL)
        return;
    
    gtk_menubar* menubar = dynamic_cast<gtk_menubar*>(current_widget);
    item* menubar_item = current_frame.widget_tree.get_item_from_widget(current_widget);    
    
    menubar_editor me(menubar_item);
    me.show_all_children();
    if(me.run()==1)
    {
        item* _item = menubar_item->child;
        object_box.delete_child_rows(menubar->get_name());
        while(_item!=NULL)
        {
            menubar->remove(*(_item->widget));
            _item=_item->next;
            }
        delete menubar_item->child;
        menubar_item->child = NULL;
        update_menubar(me.treemodel->children().begin(),menubar_item,me.columns);
        menubar->show_all_children();
        }    
    }
//gtk_offscreenwindow
void PageGeneral::cb_offscreen_window_focus_visible_changed()
{
     dynamic_cast<gtk_offscreenwindow*>(current_widget)->set_focus_visible(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number());
    }

//gtk_eventbox
void PageGeneral::cb_event_box_above_child_changed()
{
    dynamic_cast<gtk_eventbox*>(current_widget)->set_above_child(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number());
    }
void PageGeneral::cb_event_box_visible_window_changed()
{
    dynamic_cast<gtk_eventbox*>(current_widget)->set_visible_window(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }

//gtk_expander
void PageGeneral::cb_expander_expanded_changed()
{
    dynamic_cast<Gtk::Expander*>(current_widget)->set_expanded(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[0])->get_active_row_number());
    }
void PageGeneral::cb_expander_use_underline_changed()
{
    dynamic_cast<Gtk::Expander*>(current_widget)->set_use_underline(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }
void PageGeneral::cb_expander_use_markup_changed()
{
    dynamic_cast<Gtk::Expander*>(current_widget)->set_use_markup(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active_row_number());
    }
void PageGeneral::sb_expander_spacing_changed()
{
    dynamic_cast<Gtk::Expander*>(current_widget)->set_spacing(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[3])->get_value());
    }
void PageGeneral::cb_expander_label_fill_changed()
{
    dynamic_cast<Gtk::Expander*>(current_widget)->set_label_fill(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }

//gtk_vscale or gtk_hscale
void PageGeneral::sb_scale_digits_changed()
{
    dynamic_cast<Gtk::Scale*>(current_widget)->set_digits(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }
void PageGeneral::cb_scale_draw_value_changed()
{
     dynamic_cast<Gtk::Scale*>(current_widget)->set_draw_value(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[1])->get_active_row_number());
    }
void PageGeneral::cb_scale_inverted_changed()
{
    dynamic_cast<Gtk::Scale*>(current_widget)->set_inverted(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[2])->get_active_row_number());
    }
void PageGeneral::cb_scale_show_fill_level_changed()
{
    dynamic_cast<Gtk::Scale*>(current_widget)->set_show_fill_level(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[3])->get_active_row_number());
    }
void PageGeneral::cb_scale_restrict_to_fill_level_changed()
{
    dynamic_cast<Gtk::Scale*>(current_widget)->set_restrict_to_fill_level(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }

//gtk_progressbar
void PageGeneral::sb_progress_bar_fractions_changed()
{
    dynamic_cast<Gtk::ProgressBar*>(current_widget)->set_fraction(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[0])->get_value());
    }
void PageGeneral::sb_progress_bar_pulse_step_changed()
{
    dynamic_cast<Gtk::ProgressBar*>(current_widget)->set_pulse_step(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[1])->get_value());
    }

//gtk_treeview
void PageGeneral::cb_tree_view_headers_visible_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_headers_visible (!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::cb_tree_view_headers_clickable_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_headers_clickable(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::cb_tree_view_reorderable_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_reorderable(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::cb_tree_view_rules_hint_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_rules_hint(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::sb_tree_view_search_column_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_search_column(dynamic_cast<Gtk::SpinButton*>(value_widget_vector[4])->get_value());
    }
void PageGeneral::cb_tree_view_fixed_height_mode_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_fixed_height_mode(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::cb_tree_view_hover_selection_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_hover_selection(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }
void PageGeneral::cb_tree_view_show_expanders_changed()
{
    dynamic_cast<Gtk::TreeView*>(current_widget)->set_show_expanders(!dynamic_cast<Gtk::ComboBox*>(value_widget_vector[4])->get_active_row_number());
    }

//gtk_label
void PageGeneral::on_lbltext_deleted(const Gtk::TextIter& s,const Gtk::TextIter& e)
{
    Gtk::Label* lbl = dynamic_cast<Gtk::Label*>(current_widget);
    lbl->set_text(dynamic_cast<Gtk::TextView*>(value_widget_vector[0])->get_buffer()->get_text());
    }
void PageGeneral::on_lbltext_inserted(const Gtk::TextIter& iter,const std::string& s,int i)
{
    Gtk::Label* lbl = dynamic_cast<Gtk::Label*>(current_widget);
    lbl->set_text(dynamic_cast<Gtk::TextView*>(value_widget_vector[0])->get_buffer()->get_text());
    }