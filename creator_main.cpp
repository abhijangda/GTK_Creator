//2311 Lines
//gtk_placeholder and gtk::checkbutton, gtk::radiobutton
//add title to gtk::window,remove <child> of window

#include"creator_main.h"
#include<sstream>
#include<string>
#include"gtk_window.h"
#include"gtk_vbox.h"
#include"gtk_hbox.h"
#include"gtk_table.h"
#include"gtk_fixed.h"
#include"gtk_scrollwin.h"
#include"gtk_textview.h"
#include"gtk_label.h"
#include"box_dialog.h"
#include"gtk_button.h"
#include"gtk_notebook.h"
#include"gtk_toolbar.h"
#include"gtk_menubar.h"
#include"gtk_eventbox.h"
#include"gtk_offscreenwindow.h"
#include"gtk_frame.h"
#include"gtk_button.h"
#include"gtk_combobox.h"
#include"gtk_entry.h"
#include"gtk_spinbutton.h"
#include"gtk_scale.h"
#include"gtk_hscrollbar.h"
#include"gtk_treeview.h"
#include"gtk_progressbar.h"
#include"gtk_spinner.h"
#include"gtk_tool_button.h"
#include"focused_widget.h"
#include"copy_function.h"
#include"helper_functions.h"

bool paste_widget,cut_widget,copy_widget;
focused_widget current_focused_widget;
focused_widget current_pressed_placeholder;

float string_to_float(std::string& str)
{
    std::istringstream os(str);
    float x;
    os>>x;
    return x;
    }
std::string float_to_string(float fl)
{
    std::ostringstream oss;
    oss<<fl;
    return oss.str();
    }

std::string add_indentation(int level)
{
    std::string s="";
    for(int i =0;i<level;i++)
        s+=" ";
    return s;

    }
PropertyBox::PropertyBox(Frame& frame)
    :Gtk::VPaned(),object_box(),property_editor(frame,object_box)
{
    pack1(object_box,Gtk::EXPAND);
    pack2(property_editor,Gtk::EXPAND);    
    }

PropertyBox::~PropertyBox(){}

CreatorMain::CreatorMain(Gtk::Window& _parent)
    :hbox(false,2), tool_box(), frame("Working Area",tool_box),property_box(frame),frame_buttons_vbox(false,2),hbox_buttons(false,2),
        cmd_copy("Copy"), cmd_cut("Cut"), cmd_paste("Paste"), cmd_delete("Delete"),scroll_win(),parent_win(_parent)
{   
    signal_button_press_event().connect(sigc::mem_fun(*this,&CreatorMain::on_mouse_pressed));
    signal_button_release_event().connect(sigc::mem_fun(*this,&CreatorMain::on_mouse_released));
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    add(hbox);
    hbox.pack_start(tool_box,FALSE,FALSE,1);
    hbox.pack_start(frame_buttons_vbox,TRUE,TRUE,1);
    hbox.pack_start(property_box,FALSE,FALSE,1);
    set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    frame_buttons_vbox.pack_start(hbox_buttons,FALSE,FALSE,1);
    scroll_win.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    scroll_win.add(frame);
    frame_buttons_vbox.pack_start(scroll_win,TRUE,TRUE,1);    
    
    hbox_buttons.pack_start(cmd_copy,FALSE,FALSE,1);
    hbox_buttons.pack_start(cmd_cut,FALSE,FALSE,1);
    hbox_buttons.pack_start(cmd_paste,FALSE,FALSE,1);
    hbox_buttons.pack_start(cmd_delete,FALSE,FALSE,1);
    
    cmd_copy.signal_clicked().connect(sigc::mem_fun(*this,&CreatorMain::cmd_copy_clicked));
    cmd_cut.signal_clicked().connect(sigc::mem_fun(*this,&CreatorMain::cmd_cut_clicked));
    cmd_paste.signal_clicked().connect(sigc::mem_fun(*this,&CreatorMain::cmd_paste_clicked));
    cmd_delete.signal_clicked().connect(sigc::mem_fun(*this,&CreatorMain::cmd_delete_clicked));
    
    property_box.property_editor.page_general.signal_name_changed().connect(sigc::mem_fun(*this,&CreatorMain::current_widget_name_changed));    
    property_box.object_box.refTreeSelection->signal_changed().connect(sigc::mem_fun(*this,&CreatorMain::on_object_box_tree_selection_changed));
    current_focused_widget.signal_focused_widget_change().connect(sigc::mem_fun(*this,&CreatorMain::on_focused_widget_changed));
    current_pressed_placeholder.signal_focused_widget_change().connect(sigc::mem_fun(*this,&CreatorMain::on_current_pressed_placeholder_changed));
    frame.signal_widget_added().connect(sigc::mem_fun(*this,&CreatorMain::add_child_rows_to_object_box));
    show_all_children(); 
    
    //open_file("/home/abhi/Desktop/project1.glade");
    }

void CreatorMain::cmd_copy_clicked()
{
    clipboard_widget = copy_function(frame.current_item->widget,frame.current_item->type,&frame);
    clipboard_item = frame.current_item;
    cut_widget=false;
    copy_widget=true;
    }

void CreatorMain::cmd_cut_clicked()
{
    clipboard_widget = frame.current_item->widget;
    clipboard_item = frame.current_item;
    Gtk::Widget* __w = current_focused_widget.get_value();
    gtk_container* container = dynamic_cast<gtk_container*>(__w->get_parent()->get_parent());
    if(container)
    {
        container->remove_child(__w);
        item* parent = frame.current_item->get_parent();               
        item* to_delete = frame.current_item;
        current_focused_widget.set_value(container);
        property_box.object_box.remove_child_row(__w->get_name(),parent->widget->get_name());        
        parent->remove_child(to_delete);
        cut_widget=true;
        copy_widget=false;
        }
    }

void CreatorMain::cmd_paste_clicked()
{
    if(clipboard_widget!=NULL)
    {
        paste_widget=true;        
        }
    }

void CreatorMain::cmd_delete_clicked()
{
    Gtk::Widget* __w = current_focused_widget.get_value();
    gtk_container* container = dynamic_cast<gtk_container*>(__w->get_parent()->get_parent());
    if(container)
    {
        container->remove_child(__w);
        item* parent = frame.current_item->get_parent();               
        item* to_delete = frame.current_item;
        current_focused_widget.set_value(container);
        property_box.object_box.remove_child_row(__w->get_name(),parent->widget->get_name());                
        parent->remove_child(to_delete);
        delete __w;
        }
    }

void CreatorMain::on_current_pressed_placeholder_changed(Gtk::Widget* current,Gtk::Widget* previous)
{
    bool added = false;
    if(paste_widget)
    {
        gtk_container* container = NULL;
        if(frame.current_item)
            ;//std::cout<<frame.current_item->widget->get_name()<<std::endl;
        if(frame.current_item && dynamic_cast<gtk_container*>(frame.current_item->widget)!=NULL)
        {
            container = dynamic_cast<gtk_container*>(frame.current_item->widget);
            frame.container_item =frame.current_item;
            }
        int insert_at_pos=-1;
        if(container)
        {
            int width = clipboard_widget->get_width();
            int height = clipboard_widget->get_height();
            if((insert_at_pos=container->set_child_widget(*clipboard_widget,1,1,width,height))!=-1)
            {
                added = true;             
                frame.container_item->insert_child_at(new item(*clipboard_widget,clipboard_item->type,NULL,NULL,NULL,NULL),insert_at_pos);
                frame.current_item = frame.widget_tree.get_item_from_widget(clipboard_widget);
                frame.number_of_widgets++;
                current_focused_widget.set_value(clipboard_widget);
                if(copy_widget)
                     clipboard_widget->set_name(clipboard_widget->get_name()+"1");
                add_child_rows_to_object_box();
                clipboard_widget->show();
                paste_widget = false;        
                clipboard_widget=NULL;
                }
            }          
        }    
    }
   
void CreatorMain::on_focused_widget_changed(Gtk::Widget* prev_widget,Gtk::Widget* current_widget)
{
    if(current_widget->get_parent()&& prev_widget!=current_widget)
    {
        gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(current_widget->get_parent());
        if(_placeholder)
        {
            _placeholder->draw_around_borders();
            _placeholder->set_draw(true);
            }
        if(prev_widget)
        {
            _placeholder = dynamic_cast<gtk_placeholder*>(prev_widget->get_parent());
            if(_placeholder)
                _placeholder->set_draw(false);
            }            
        }
    
    item* _item = frame.widget_tree.get_item_from_widget(current_widget);    
    //std::cout<<"Avvv"<<frame.current_item->widget->get_name()<<std::endl;
    frame.current_item  = frame.widget_tree.get_item_from_name(current_widget->get_name());
    //std::cout<<"Ajjjj"<<frame.current_item->widget->get_name()<<std::endl;
    
    if(frame.draw_widget)
    {
        if(current_widget)
        {
            gtk_placeholder* _placeholder = dynamic_cast<gtk_placeholder*>(current_widget->get_parent());
            if(_placeholder)
                _placeholder->set_draw(false);
            }
        frame.func_draw_widget(0.0,0.0);     
        }
    if(frame.current_item->get_parent())
         property_box.property_editor.set_property_values_from_widget(*(frame.current_item->widget),frame.current_item->type,*(frame.current_item->get_parent()->widget),frame.current_item->get_parent()->type);
    else
        property_box.property_editor.set_property_values_from_widget(*(frame.current_item->widget),frame.current_item->type,*this,"");         
    property_box.object_box.set_selection_from_widget(*(frame.current_item->widget),frame.current_item->type);
    }

int CreatorMain::save_to_file(std::string filepath)
{
    std::string file_contents = "<glade-interface>\n";
    item *_item = frame.widget_tree.parent_item;
    get_gml_string(_item,NULL,file_contents,0);
    file_contents = file_contents + "</glade-interface>";
    file_contents = file_contents.replace(file_contents.find(std::string("<child>")),7,std::string(""));
    file_contents = file_contents.replace(file_contents.rfind(std::string("</child>")),8,std::string(""));
    Glib::file_set_contents(filepath,file_contents);
    }

std::string CreatorMain::get_string()
{
    std::string file_contents = "<glade-interface>\n";
    item *_item = frame.widget_tree.parent_item;
    get_gml_string(_item,NULL,file_contents,0);
    file_contents = file_contents + "</glade-interface>";
    if (file_contents.find("<child>")!=std::string::npos)
    {
        file_contents = file_contents.replace(file_contents.find(std::string("<child>")),7,std::string(""));
        file_contents = file_contents.replace(file_contents.rfind(std::string("</child>")),8,std::string(""));
        }
    return file_contents;
    }

void CreatorMain::get_gml_string(item* _item, item* parent, std::string& full_string,int indent_level)
{ 
    std::string property_value="";
    std::string property_string = "";
    std::string type_of_widget="";
    Gtk::Widget *widget;
    while(_item)
    {
        type_of_widget = _item->type;
        full_string += add_indentation(indent_level)+"<child>\n";
        widget=_item->widget;
        property_string="";    
            
        property_string +=add_indentation(indent_level)+"<property name = \"width_request\">"+integer_to_string(widget->size_request().width)+"</property>\n";
        property_string +=add_indentation(indent_level)+"<property name = \"height_request\">"+integer_to_string(widget->size_request().height)+"</property>\n";
        
        if(widget->get_sensitive())
             property_value="True";
        else
            property_value="False";            
        property_string+=add_indentation(indent_level)+"<property name=\"sensitive\">"+property_value+"</property>\n";
        
        property_string+=add_indentation(indent_level)+"<property name=\"tooltip\" translatable=\"yes\">"+widget->get_tooltip_text()+"</property>\n";
        
        if(widget->get_can_default())
            property_value="True";
        else
            property_value="False";
        property_string+=add_indentation(indent_level)+"<property name=\"can_default\">"+property_value+"</property>\n";
        
        if(widget->has_default())
            property_value="True";
        else
            property_value="False";            
        property_string+=add_indentation(indent_level)+"<property name=\"has_default\">"+property_value+"</property>\n";
        
         if(widget->get_can_focus())
            property_value="True";
        else
            property_value="False";
        property_string+=add_indentation(indent_level)+"<property name=\"can_focus\">"+property_value+"</property>\n";
        
        if(widget->has_focus())
            property_value="True";
        else
            property_value="False";
        property_string+=add_indentation(indent_level)+"<property name=\"has_focus\">"+property_value+"</property>\n";
        
        if(type_of_widget=="gtk_window")
        {
            gtk_window *window = dynamic_cast<gtk_window*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkWindow\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            
            if(window->get_type()=="TOPLEVEL")
                property_value="GTK_WINDOW_TOPLEVEL";
            else
                property_value="GTK_WINDOW_POPUP";            
            full_string+=add_indentation(indent_level)+"<property name=\"type\">"+property_value+"</property>\n";
            
            full_string+=add_indentation(indent_level)+"<property name=\"title\" translatable=\"yes\">"+window->get_title()+"</property>\n";
            full_string+=add_indentation(indent_level)+"<property name=\"default_width\">"+integer_to_string(window->get_default_width())+"</property>\n";
            full_string+=add_indentation(indent_level)+"<property name=\"default_height\">"+integer_to_string(window->get_default_height())+"</property>\n";
            
            if(window->get_resizable())
                property_value="True";
            else
               property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"resizable\">"+property_value+"</property>\n";
            
            if(window->get_modal())
                property_value="True";
            else
               property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"modal\">"+property_value+"</property>\n";
      
            if(window->get_destroy_with_parent())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"destroy_with_parent\">"+property_value+"</property>\n";
            
            full_string+=add_indentation(indent_level)+"<property name=\"window_position\">GTK_WIN_POS_NONE</property>\n<property name=\"decorated\">True</property>\n";
            full_string+=add_indentation(indent_level)+"<property name=\"focus_on_map\">True</property>\n<property name=\"urgency_hint\">False</property>\n";
            }
        else if(type_of_widget == "gtk_offscreenwindow")
        {
            gtk_offscreenwindow* window = dynamic_cast<gtk_offscreenwindow*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkOffscreenWindow\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget == "gtk_vbox")
        {
            gtk_vbox* vbox = dynamic_cast<gtk_vbox*>(widget);
            if(vbox->get_homogeneous())
                property_value="True";
            else
                property_value="False";
            full_string += add_indentation(indent_level)+"<widget class=\"GtkVBox\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            full_string+=add_indentation(indent_level)+"<property name=\"homogeneous\">"+property_value+"</property>\n";
            full_string+=add_indentation(indent_level)+"<property name=\"spacing\">"+integer_to_string(vbox->get_spacing())+"</property>\n";
            }
        else if(type_of_widget == "gtk_button")
        {            
            gtk_button* button = dynamic_cast<gtk_button*>(widget);
            full_string+= add_indentation(indent_level)+"<widget class=\"GtkButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            if(button->get_use_stock())
            {
                full_string+= add_indentation(indent_level)+"<property name=\"label\">"+get_gml_string_from_stock_string(button->get_stock())+"</property>\n";
                full_string+= add_indentation(indent_level)+"<property name=\"use_stock\">True</property>\n";
                }
            else
                 full_string+= add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+button->get_label()+"</property>\n";
            float xalign,yalign;
            button->get_alignment(xalign,yalign);
            full_string+= add_indentation(indent_level)+"<property name=\"xalign\">"+float_to_string(xalign)+"</property>\n";
            full_string+= add_indentation(indent_level)+"<property name=\"yalign\">"+float_to_string(yalign)+"</property>\n";
            if(button->get_focus_on_click())
                 property_value="True";
            else
                property_value="False";
            full_string+= add_indentation(indent_level)+"<property name=\"focus_on_click\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_hbox")
        {
            gtk_hbox* box = dynamic_cast<gtk_hbox*>(widget);
            if(box->get_homogeneous())
                property_value="True";
            else
                property_value="False";
            full_string += add_indentation(indent_level)+"<widget class=\"GtkHBox\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            full_string+=add_indentation(indent_level)+"<property name=\"homogeneous\">"+property_value+"</property>\n";
            full_string+=add_indentation(indent_level)+"<property name=\"spacing\">"+integer_to_string(box->get_spacing())+"</property>\n";
            }
        else if(type_of_widget == "gtk_table")
        {            
            gtk_table* table = dynamic_cast<gtk_table*>(widget);
            
            full_string += add_indentation(indent_level)+"<widget class=\"GtkTable\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            full_string += add_indentation(indent_level)+"<property name=\"n_rows\">"+integer_to_string(table->get_rows())+"</property>\n";
            full_string += add_indentation(indent_level)+"<property name=\"n_columns\">"+integer_to_string(table->get_cols())+"</property>\n";
            if(table->get_homogeneous())
                property_value="True";
            else
                property_value="False";
            full_string += add_indentation(indent_level)+"<property name=\"homogeneous\">"+property_value+"</property>\n";
            full_string += add_indentation(indent_level)+"<property name=\"row_spacing\">"+integer_to_string(table->get_row_spacing())+"</property>\n";
            full_string += add_indentation(indent_level)+"<property name=\"column_spacing\">"+integer_to_string(table->get_col_spacing())+"</property>\n";
            }
        else if(type_of_widget == "gtk_fixed")
        {           
            full_string += add_indentation(indent_level)+"<widget class=\"GtkFixed\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }        
        else if(type_of_widget == "gtk_scrollwin")
        {            
            gtk_scrollwin* scrollwin = dynamic_cast<gtk_scrollwin*>(widget);  
            full_string += add_indentation(indent_level)+"<widget class=\"GtkScrolledWindow\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            if(scrollwin->get_horizontal_policy()=="ALWAYS")
                full_string += add_indentation(indent_level)+"<property name=\"hscrollbar_policy\">GTK_POLICY_ALWAYS</property>\n";
            else if(scrollwin->get_horizontal_policy()=="AUTOMATIC")
                full_string += add_indentation(indent_level)+"<property name=\"hscrollbar_policy\">GTK_POLICY_ALWAYS</property>\n";
            else if(scrollwin->get_horizontal_policy()=="NEVER")
                full_string += add_indentation(indent_level)+"<property name=\"hscrollbar_policy\">GTK_POLICY_NEVER</property>\n";
                
            if(scrollwin->get_vertical_policy()=="ALWAYS")
                full_string += add_indentation(indent_level)+"<property name=\"vscrollbar_policy\">GTK_POLICY_ALWAYS</property>\n";
            else if(scrollwin->get_vertical_policy()=="AUTOMATIC")
                full_string += add_indentation(indent_level)+"<property name=\"vscrollbar_policy\">GTK_POLICY_ALWAYS</property>\n";
            else if(scrollwin->get_vertical_policy()=="NEVER")
                full_string += add_indentation(indent_level)+"<property name=\"vscrollbar_policy\">GTK_POLICY_NEVER</property>\n";
            }
        else if(type_of_widget == "gtk_textview")
        {           
            gtk_textview* textview = dynamic_cast<gtk_textview*>(widget);
            full_string += add_indentation(indent_level)+"<widget class=\"GtkTextView\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            full_string+="<property name=\"border_width\">0</property>\n";
            full_string += add_indentation(indent_level);
            if(textview->get_editable())
                property_value="True";
            else
                property_value="False";
            full_string += add_indentation(indent_level)+"<property name=\"editable\">"+property_value+"</property>\n";
            
             if(textview->get_wrapmode()=="NONE")
                property_value="GTK_WRAP_NONE";
            else if(textview->get_wrapmode()=="CHARACTER")
                property_value="CGTK_WRAP_HARACTER";
            else if(textview->get_wrapmode()=="WORD")
                property_value="GTK_WRAP_WORD";
            else 
                property_value="GTK_WRAP_WORD_CHARACTER"; 
            full_string += add_indentation(indent_level)+"<property name=\"wrap_mode\">"+property_value+"</property>\n";
            
            if(textview->get_cursor_visible())
                property_value="True";
            else
                property_value="False";
            full_string += add_indentation(indent_level)+"<property name=\"cursor_visible\">"+property_value+"</property>\n";
            
            full_string += add_indentation(indent_level)+"<property name=\"pixels_above_lines\">"+integer_to_string(textview->get_pixels_above_lines())+"</property>\n";
            full_string += add_indentation(indent_level)+"<property name=\"pixels_below_lines\">"+integer_to_string(textview->get_pixels_below_lines())+"</property>\n";
            full_string += add_indentation(indent_level)+"<property name=\"pixels_inside_wrap\">"+integer_to_string(textview->get_pixels_inside_wrap())+"</property>\n";
            std::string text;
            text=textview->get_buffer()->get_text();
            full_string += add_indentation(indent_level)+"<property name=\"text\" translatable=\"yes\">"+text+"</property>\n";
            }
        else if(type_of_widget == "gtk_entry")
        {            
            gtk_entry* entry = dynamic_cast<gtk_entry*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkEntry\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;     
            }
        else if(type_of_widget == "gtk_label")
        {           
            gtk_label* label =  dynamic_cast<gtk_label*>(widget); 
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkLabel\" id=\""+widget->get_name()+"\">\n";  
            full_string +=add_indentation(indent_level)+property_string;           
            full_string +=add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+label->get_text()+"</property>\n";
            }
        else if(type_of_widget == "gtk_togglebutton")
        {
            gtk_togglebutton* button =  dynamic_cast<gtk_togglebutton*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkToggleButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string+add_indentation(indent_level)+"<property name=\"border_width\">0</property>\n";
            if(button->get_use_stock())
            {
                full_string+= add_indentation(indent_level)+"<property name=\"label\">"+get_gml_string_from_stock_string(button->get_stock())+"</property>\n";
                full_string+= add_indentation(indent_level)+"<property name=\"use_stock\">True</property>\n";
                }
            else
                 full_string+= add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+button->get_label()+"</property>\n";
            
            if(button->get_active())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"active\">"+property_value+"</property>\n";
            
            if(button->get_focus_on_click())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"focus_on_click\">"+property_value+"</property>\n";
            
            if(button->get_inconsistent())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"inconsistent\">"+property_value+"</property>\n";
            
            float xalign,yalign;
            button->get_alignment(xalign,yalign);
            full_string+= add_indentation(indent_level)+"<property name=\"xalign\">"+float_to_string(xalign)+"</property>\n";
            full_string+= add_indentation(indent_level)+"<property name=\"yalign\">"+float_to_string(yalign)+"</property>\n";
            }
        else if(type_of_widget == "gtk_combobox")
        {
            gtk_combobox* combobox =  dynamic_cast<gtk_combobox*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkComboBox\" id=\""+widget->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;
            full_string +=add_indentation(indent_level)+"<property name=\"wrap_width\">"+integer_to_string(combobox->get_active())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"row_span_column\">"+integer_to_string(combobox->get_row_span_column())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"column_span_column\">"+integer_to_string(combobox->get_row_span_column())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"active\">"+integer_to_string(combobox->get_active())+"</property>\n";
            }
        else if(type_of_widget == "gtk_comboboxtext")
        {
            gtk_comboboxtext* combobox =  dynamic_cast<gtk_comboboxtext*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkComboBoxText\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            full_string +=add_indentation(indent_level)+"<property name=\"wrap_width\">"+integer_to_string(combobox->get_active())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"row_span_column\">"+integer_to_string(combobox->get_row_span_column())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"column_span_column\">"+integer_to_string(combobox->get_row_span_column())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"active\">"+integer_to_string(combobox->get_active())+"</property>\n";
            }
        else if(type_of_widget == "gtk_checkbutton")
        {
            gtk_checkbutton* button =  dynamic_cast<gtk_checkbutton*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkCheckButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;        
            if(button->get_use_stock())
            {
                full_string+= add_indentation(indent_level)+"<property name=\"label\">"+get_gml_string_from_stock_string(button->get_stock())+"</property>\n";
                full_string+= add_indentation(indent_level)+"<property name=\"use_stock\">True</property>\n";
                }
            else
                 full_string+= add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+button->get_label()+"</property>\n";
            
            if(button->get_active())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"active\">"+property_value+"</property>\n";
            
            if(button->get_focus_on_click())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"focus_on_click\">"+property_value+"</property>\n";
            
            if(button->get_inconsistent())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"inconsistent\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_radiobutton")
        {
            gtk_radiobutton* button =  dynamic_cast<gtk_radiobutton*>(widget); 
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkRadioButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;        
            if(button->get_use_stock())
            {
                full_string+= add_indentation(indent_level)+"<property name=\"label\">"+get_gml_string_from_stock_string(button->get_stock())+"</property>\n";
                full_string+= add_indentation(indent_level)+"<property name=\"use_stock\">True</property>\n";
                }
            else
                 full_string+= add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+button->get_label()+"</property>\n";
            
            if(button->get_active())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"active\">"+property_value+"</property>\n";
            
            if(button->get_focus_on_click())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"focus_on_click\">"+property_value+"</property>\n";
            
            if(button->get_inconsistent())
                property_value="True";
            else
                property_value="False";
            full_string+=add_indentation(indent_level)+"<property name=\"inconsistent\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_statusbar")
        {
            Gtk::Statusbar* bar=  dynamic_cast<Gtk::Statusbar*>(widget); 
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkStatusbar\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;            
            }
        else if(type_of_widget == "gtk_menubar")
        {
            gtk_menubar* bar =  dynamic_cast<gtk_menubar*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkMenuBar\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget == "gtk_toolbar")
        {
            gtk_toolbar*bar =  dynamic_cast<gtk_toolbar*>(widget); 
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkToolBar\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget=="gtk_notebook")
        {
            gtk_notebook* box=  dynamic_cast<gtk_notebook*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkNotebook\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            full_string +=add_indentation(indent_level)+"<property name=\"border_width\">0</property>\n";
            if(box->get_show_tabs())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"show_tabs\">"+property_value+"</property>\n";
            if(box->get_show_border())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"show_border\">"+property_value+"</property>\n";
            if(box->get_tab_pos()=="LEFT")
                property_value="GTK_POS_LEFT";
            else if(box->get_tab_pos()=="RIGHT")
                property_value="GTK_POS_RIGHT";
            else if(box->get_tab_pos()=="BOTTOM")
                property_value="GTK_POS_BOTTOM";
            else if(box->get_tab_pos()=="TOP")
                property_value="GTK_POS_TOP";
            full_string +=add_indentation(indent_level)+"<property name=\"tab_pos\">"+property_value+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"scrollable\">True</property>\n";
            } 
        else if(type_of_widget == "gtk_eventbox")
        {
            gtk_eventbox* box =  dynamic_cast<gtk_eventbox*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkEventBox\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            if(box->get_visible_window())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"visible_window\">"+property_value+"</property>\n";
            if(box->get_above_child())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"above_child\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_expander")
        {
            Gtk::Expander* expander =  dynamic_cast<Gtk::Expander*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkExpander\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            if(expander->get_expanded())
                property_value="True";
            else
               property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"expanded\">"+property_value+"</property>\n";
            
            if(expander->get_use_markup())
                property_value="True";
            else
               property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"use_markup\">"+property_value+"</property>\n";
            
            full_string +=add_indentation(indent_level)+"<property name=\"spacing\">"+integer_to_string(expander->get_spacing())+"</property>\n";
            
            if(expander->get_label_fill())
                property_value="True";
            else
               property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"label_fill\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_spinbutton")
        {
            gtk_spin_button*  button=  dynamic_cast<gtk_spin_button*>(widget);
            full_string += add_indentation(indent_level)+"<widget class=\"GtkSpinButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }        
        else if(type_of_widget == "gtk_filechooserbutton")
        {
            Gtk::FileChooserButton* button =  dynamic_cast<Gtk::FileChooserButton*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkFileChooserButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;            
            }
        else if(type_of_widget == "gtk_colorchooserbutton")
        {
            Gtk::ColorButton* button =  dynamic_cast<Gtk::ColorButton*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkColorChooserButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget == "gtk_fontbutton")
        {
            Gtk::FontButton* button =  dynamic_cast<Gtk::FontButton*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkFontButton\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }       
        else if(type_of_widget == "gtk_hscale")
        {
            gtk_hscale* scale =  dynamic_cast<gtk_hscale*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkHScale\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            if(scale->get_inverted())
                property_value="True";
            else
                property_value="False";
             full_string +=add_indentation(indent_level)+"<property name=\"inverted\">"+property_value+"</property>\n";
            
            full_string +=add_indentation(indent_level)+"<property name=\"digits\">"+integer_to_string(scale->get_digits())+"</property>\n";
            
            if(scale->get_draw_value())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"draw_value\">"+property_value+"</property>\n";
            
            if(scale->get_show_fill_level())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"show_fill_level\">"+property_value+"</property>\n";
            
            if(scale->get_restrict_to_fill_level())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"restrict_to_fill_level\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_vscale")
        {
            gtk_vscale* scale =  dynamic_cast<gtk_vscale*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkVScale\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            
            if(scale->get_inverted())
                property_value="True";
            else
                property_value="False";
             full_string +=add_indentation(indent_level)+"<property name=\"inverted\">"+property_value+"</property>\n";
            
            full_string +=add_indentation(indent_level)+"<property name=\"digits\">"+integer_to_string(scale->get_digits())+"</property>\n";
            
            if(scale->get_draw_value())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"draw_value\">"+property_value+"</property>\n";
            
            if(scale->get_show_fill_level())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"show_fill_level\">"+property_value+"</property>\n";
            
            if(scale->get_restrict_to_fill_level())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"restrict_to_fill_level\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_hscrollbar")
        {
            gtk_hscrollbar* bar =  dynamic_cast<gtk_hscrollbar*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkHScrollBar\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget == "gtk_progressbar")
        {
            gtk_progressbar* bar =  dynamic_cast<gtk_progressbar*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkProgressBar\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
             
            full_string +=add_indentation(indent_level)+"<property name=\"fraction\">"+float_to_string(bar->get_fraction())+"</property>\n";
            full_string +=add_indentation(indent_level)+"<property name=\"pulse_step\">"+float_to_string(bar->get_pulse_step())+"</property>\n";            
            }
        else if(type_of_widget == "gtk_spinner")
        {
            gtk_spinner* spinner =  dynamic_cast<gtk_spinner*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkSpinner\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget == "gtk_treeview")
        {
            gtk_treeview* tree_view =  dynamic_cast<gtk_treeview*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkTreeView\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            
            if(tree_view->get_headers_visible())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"headers_visible\">"+property_value+"</property>\n";
            
            if(tree_view->get_headers_clickable())
                property_value="True";
            else
                property_value="False";
                   
             if(tree_view->get_show_expanders())
                property_value="True";
            else
                property_value="False";
                
            if(tree_view->get_rules_hint())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"rules_hint\">"+property_value+"</property>\n";
            
            if(tree_view->get_fixed_height_mode())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"fixed_height_mode\">"+property_value+"</property>\n";
            
            if(tree_view->get_hover_selection())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"hover_selection\">"+property_value+"</property>\n";
            }
        else if(type_of_widget == "gtk_frame")
        {
            Gtk::Frame* frame =  dynamic_cast<Gtk::Frame*>(widget);            
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkFrame\" id=\""+widget->get_name()+"\">\n";
            full_string +=property_string;
            }
        else if(type_of_widget=="gtk_menubar")
        {
            gtk_menubar* menubar = dynamic_cast<gtk_menubar*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkMenuBar\" id=\""+menubar->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;        
                    
            if(menubar->get_packdirection()=="LEFT TO RIGHT")
                property_value="GTK_PACK_DIRECTION_LTR";
            else if(menubar->get_packdirection()=="RIGHT TO LEFT")
                property_value="GTK_PACK_DIRECTION_RTL";
            else if(menubar->get_packdirection()=="TOP TO BOTTOM")
                property_value="GTK_PACK_DIRECTION_TTB";
            else if(menubar->get_packdirection()=="BOTTOM TO TOP")
                property_value="GTK_PACK_DIRECTION_BTT";           
             full_string +=add_indentation(indent_level)+"<property name=\"pack_direction\">"+property_value+"</property>\n";
            
            if(menubar->get_childpackdirection()=="LEFT TO RIGHT")
                property_value="GTK_PACK_DIRECTION_LTR";
            else if(menubar->get_childpackdirection()=="RIGHT TO LEFT")
                property_value="GTK_PACK_DIRECTION_RTL";
            else if(menubar->get_childpackdirection()=="TOP TO BOTTOM")
                property_value="GTK_PACK_DIRECTION_TTB";
            else if(menubar->get_childpackdirection()=="BOTTOM TO TOP")
                property_value="GTK_PACK_DIRECTION_BTT";    
            full_string +=add_indentation(indent_level)+"<property name=\"child_pack_direction\">"+property_value+"</property>\n";
            }
        else if(type_of_widget=="gtk_toolbaar")
        {
            gtk_toolbar* toolbar = dynamic_cast<gtk_toolbar*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkToolbar\" id=\""+toolbar->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;        
            
            if(toolbar->get_show_arrow())
                property_value="True";
            else
                property_value="False";
            full_string +=add_indentation(indent_level)+"<property name=\"show_arrow\">"+property_value+"</property>\n";
        
            if(toolbar->get_toolbarstyle()=="ICONS ONLY")
                property_value="GTK_TOOLBAR_ICONS";
            else if(toolbar->get_toolbarstyle()=="TEXT ONLY")
                property_value="GTK_TOOLBAR_TEXT";
            else if(toolbar->get_toolbarstyle()=="TEXT BELOW ICONS")
                property_value="GTK_TOOLBAR_BOTH";
            else if(toolbar->get_toolbarstyle()=="TEXT BESIDES ICONS")
                property_value="GTK_TOOLBAR_BOTH_HORIZ";                
            full_string +=add_indentation(indent_level)+"<property name=\"toolbar_style\">"+property_value+"</property>\n";     
            }
        else if(type_of_widget=="gtk_statusbar")
        {
            Gtk::Statusbar* bar = dynamic_cast<Gtk::Statusbar*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkStatusbar\" id=\""+bar->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;    
            }
        else if(type_of_widget=="gtk_tool_button")
        {
            gtk_tool_button* tool_button = dynamic_cast<gtk_tool_button*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkToolButton\" id=\""+tool_button->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;
            if(tool_button->get_stock() ==""||tool_button->get_stock()=="NONE" )
                full_string +=add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+tool_button->get_label()+"</property>\n";
            else
                full_string +=add_indentation(indent_level)+"<property name=\"stock_id\">"+get_gml_string_from_stock_string(tool_button->get_stock())+"</property>\n";
            }
        else if(type_of_widget=="gtk_radio_tool_button")
        {
            gtk_radio_tool_button* tool_button = dynamic_cast<gtk_radio_tool_button*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkRadioToolButton\" id=\""+tool_button->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;
            full_string +=add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+tool_button->get_label()+"</property>\n";
            }
        else if(type_of_widget=="gtk_separator_item")
        {
            gtk_separator_tool_item* tool_button = dynamic_cast<gtk_separator_tool_item*>(widget);   
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkSeparatorToolItem\" id=\""+tool_button->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string; 
            }
        else if(type_of_widget=="gtk_image_menu_item")
        {            
            gtk_image_menu_item* menu_item = dynamic_cast<gtk_image_menu_item*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkImageMenuItem\" id=\""+menu_item->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;    
            full_string +=add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+menu_item->get_label()+"</property>\n";
            if(menu_item->get_stock() !=""&&menu_item->get_stock()!="NONE" )
            {
                full_string +=add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+get_gml_string_from_stock_string(menu_item->get_stock())+"</property>\n";            
                full_string +=add_indentation(indent_level)+"<property name=\"use_stock\">True</property>\n";
                }
            }
        else if(type_of_widget=="gtk_check_menu_item")
        {            
            gtk_check_menu_item* menu_item = dynamic_cast<gtk_check_menu_item*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkCheckMenuItem\" id=\""+menu_item->get_name()+"\">\n";
            full_string +=add_indentation(indent_level)+property_string;    
            full_string +=add_indentation(indent_level)+"<property name=\"label\" translatable=\"yes\">"+menu_item->get_label()+"</property>\n";
            }
        else if(type_of_widget=="gtk_separator_menu_item")
        {            
            gtk_separator_menu_item* menu_item = dynamic_cast<gtk_separator_menu_item*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkSeparatorMenuItem\" id=\""+menu_item->get_name()+"\">\n";    
            }
        else if(type_of_widget=="gtk_menu")
        {
            Gtk::Menu* menu_item = dynamic_cast<Gtk::Menu*>(widget);
            full_string +=add_indentation(indent_level)+"<widget class=\"GtkMenu\" id=\""+menu_item->get_name()+"\">\n";
            }
        if(_item->child==NULL)
             full_string +=add_indentation(indent_level)+"</widget>\n";
        if(parent && parent->type!="gtk_window")
        {
            type_of_widget=parent->type;            
            
            if(type_of_widget=="gtk_vbox")
            {
                full_string+=add_indentation(indent_level)+"<packing>\n";
                gtk_vbox* vbox = dynamic_cast<gtk_vbox*>(parent->widget);
                full_string+=add_indentation(indent_level)+"<property name=\"padding\">0</property>\n";
                if(vbox->get_expand(_item->widget))
                    property_value="True";
                else
                    property_value="False";
                full_string+=add_indentation(indent_level)+"<property name=\"expand\">"+property_value+"</property>\n";
                full_string+=add_indentation(indent_level)+"<property name=\"fill\">False</property>\n";
                full_string+=add_indentation(indent_level)+"</packing>\n";
                }
            else if(type_of_widget=="gtk_hbox")
            {
                full_string+=add_indentation(indent_level)+"<packing>\n";
                gtk_hbox* vbox = dynamic_cast<gtk_hbox*>(parent->widget);
                full_string+=add_indentation(indent_level)+"<property name=\"padding\">0</property>\n";
                if(vbox->get_expand(_item->widget))
                    property_value="True";
                else
                    property_value="False";
                full_string+=add_indentation(indent_level)+"<property name=\"expand\">"+property_value+"</property>\n";
                full_string+=add_indentation(indent_level)+"<property name=\"fill\">False</property>\n";
                full_string+=add_indentation(indent_level)+"</packing>\n";
                }
            else if(type_of_widget=="gtk_table")
            {
                full_string+=add_indentation(indent_level)+"<packing>\n";
                gtk_table* table = dynamic_cast<gtk_table*>(parent->widget);
                
                }
            else if(type_of_widget=="gtk_fixed")
            {
                full_string+=add_indentation(indent_level)+"<packing>\n";
                gtk_fixed* frame = dynamic_cast<gtk_fixed*>(parent->widget);
                full_string+=add_indentation(indent_level)+"<property name=\"x\">"+integer_to_string(frame->get_x_of_child(*(_item->widget)))+"</property>\n";
                full_string+=add_indentation(indent_level)+"<property name=\"y\">"+integer_to_string(frame->get_y_of_child(*(_item->widget)))+"</property>\n";
                full_string+=add_indentation(indent_level)+"</packing>\n";
                }
            else if(type_of_widget=="gtk_menubar")
            {             
                //Nothing to do   
                }
            else if(type_of_widget=="gtk_menu")
            {
                //Nothing to do
                }
            else if(type_of_widget=="gtk_menuitem")
            {
                //Nothing to do
                }
            else if(type_of_widget=="gtk_frame")
            {
                if(_item->type == "gtk_label")
                {
                    full_string+=add_indentation(indent_level)+"<packing>\n";
                    full_string+=add_indentation(indent_level)+"<property name=\"type\">label_item</property>\n";
                    full_string+=add_indentation(indent_level)+"</packing>\n";
                    }
                }
            else if(type_of_widget=="gtk_notebook")
            {
                full_string+=add_indentation(indent_level)+"<packing>\n";
                if(_item->type=="gtk_label")
                     full_string+=add_indentation(indent_level)+"<property name=\"type\">tab</property>\n";
                else
                {
                    full_string+=add_indentation(indent_level)+"<property name=\"tab_expand\">False</property>\n";
                    full_string+=add_indentation(indent_level)+"<property name=\"tab_fill\">True</property>\n";
                    }
                full_string+=add_indentation(indent_level)+"</packing>\n";
                }            
            else if(type_of_widget=="gtk_toolbar")
            {
                full_string+=add_indentation(indent_level)+"<packing>\n";
                Gtk::ToolItem* tool_item = dynamic_cast<Gtk::ToolItem*>(_item->widget);
                if(tool_item->get_expand())
                    property_value="True";
                else
                    property_value="False";
                full_string+=add_indentation(indent_level)+"<property name=\"expand\">"+property_value+"</property>\n";
                
                if(tool_item->get_homogeneous())
                    property_value="True";
                else
                    property_value="False";
                full_string+=add_indentation(indent_level)+"<property name=\"homogeneous\">"+property_value+"</property>\n";                
                full_string+=add_indentation(indent_level)+"</packing>\n";
                }       
            }
        if(_item->child)
            get_gml_string(_item->child,_item,full_string,indent_level+1);
            
        if(_item->type=="gtk_window")
        {
            if(!_item->child)
            {
                full_string+=add_indentation(indent_level)+"<child>\n";
                full_string+=add_indentation(indent_level)+add_indentation(indent_level)+"<placeholder/>\n";
                full_string+=add_indentation(indent_level)+"</child>\n";                
                }
            }
        else if(_item->type=="gtk_vbox" || _item->type=="gtk_hbox")
        {
            item* __child = _item->child;
            int _index = 0,i=0;
            while(__child!=NULL)
            {
                __child=__child->next;
                i++;
                }
            int total_child = (dynamic_cast<gtk_box*>(_item->widget))->get_number_of_widgets();
            if(i<total_child)
            {
                i=0;                
                while(i<total_child)
                {
                    std::string child_name;
                    if(__child)
                    {
                        child_name = __child->widget->get_name();
                        _index = __child->index;      
                        }              
                    if(_index!=i)
                    {                    
                        int index = full_string.find("id=\""+child_name+"\">");
                        if(index!=std::string::npos)
                        {
                            std::string placeholder="";
                            placeholder+="<child>\n";
                            placeholder+=add_indentation(indent_level)+add_indentation(indent_level)+"<placeholder/>\n";
                            placeholder+=add_indentation(indent_level)+"</child>\n" + add_indentation(indent_level);  
                            index = (full_string.substr(0,index)).rfind("<child>");                       
                            full_string = full_string.insert(index,placeholder);
                            }                    
                        }
                    if(_index==i && __child)
                        __child=__child->next;
                    i++;
                    }
                if(!_item->child)
                     _index=0;
                else
                     _index++;
                while(_index<total_child)
                {
                    full_string+=add_indentation(indent_level)+"<child>\n";
                    full_string+=add_indentation(indent_level)+add_indentation(indent_level)+"<placeholder/>\n";
                    full_string+=add_indentation(indent_level)+"</child>\n";                
                    _index++;
                    }
                }
            }
        else if(_item->type=="gtk_table")
        {
            }
        else if(_item->type=="gtk_frame")
        {
            if(_item->child->index!=0)
            {
                full_string+=add_indentation(indent_level)+"<child>\n";
                full_string+=add_indentation(indent_level)+add_indentation(indent_level)+"<placeholder/>\n";
                full_string+=add_indentation(indent_level)+"</child>\n";                
                }
            }        
        if(_item->child!=NULL)
             full_string +=add_indentation(indent_level)+"</widget>\n";
        full_string +=add_indentation(indent_level)+"</child>\n";
        _item=_item->next;
        }    
    }

int CreatorMain::count_str(std::string& str1, std::string& str2)
{
    int index=0,count=0;
    while((index=str1.find(str2,index))!=-1)
    {
        count++;
        index++;
        }
    return count;
    }

void CreatorMain::get_full_string(std::string& full_string, std::string& text, std::string opening_str, std::string closing_str)
{
    std::string regex_str = "(?<="+closing_str+")+.+?(?="+closing_str+")";
    Glib::RefPtr<Glib::Regex> regex;
    Glib::MatchInfo match_info;
    regex = Glib::Regex::create(regex_str,static_cast<Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    //std::cout<<"FINDING FROM TEXT "<<text<<"/PPPPPPPPPPP FINDING FROM TEXT"<<std::endl;
    if(regex->match(text,match_info))
    {
        do
        {
            //std::cout<<"FULL_STRING"<<full_string<<"/FULL_STRING"<<std::endl;
            int count_open = count_str(full_string,opening_str);
            int count_close = count_str(full_string,closing_str);
            //std::cout<<"OPEN"<<count_open<<"CLOSE"<<count_close<<std::endl;
            if(count_open==count_close)
                break;
            
            full_string += match_info.fetch(0)+closing_str;            
            }
        while(match_info.next());
        }    
    }

void CreatorMain::function_widget(std::string text,item* container_item)
{
    Glib::RefPtr<Glib::Regex> regex_widget;
    Glib::MatchInfo match_info_widget;
    //std::cout<<"TEXT"<<text<<"/TEXT"<<std::endl;
    //regex = Glib::Regex::create("<glade-interface>+.+</glade-interface>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    if(container_item!=NULL)
    {
        std::string text2 = text;
        if(text2.find("<placeholder/>")!=std::string::npos)
        {
            text2 = text2.replace(0,text2.find("<placeholder/>"),"");
            text2 = text2.replace(std::string("<placeholder/>").length(),text2.length(),"");
            }
        if(text2=="<placeholder/>")
        {            
            if(container_item->type=="gtk_vbox")
            {
                gtk_vbox* vbox = dynamic_cast<gtk_vbox*>(container_item->widget);
                vbox->set_number_of_widgets(vbox->get_number_of_widgets()+1);
                return;
                }           
            else if(container_item->type=="gtk_hbox")
            {
                gtk_hbox* vbox = dynamic_cast<gtk_hbox*>(container_item->widget);
                vbox->set_number_of_widgets(vbox->get_number_of_widgets()+1);
                return;
                }
            else if(container_item->type=="gtk_frame")
            {
                return;
                }   
            else if(container_item->type=="gtk_window")
            {
                return;
                }
            else if(container_item->type=="gtk_table")
            {
                return;
                }
            else if(container_item->type=="gtk_notebook")
            {
                return;
                }
            else if(container_item->type=="gtk_eventbox")
            {
                return;
                }
            }
        }
    
    regex_widget = Glib::Regex::create("<widget+.+>");
    std::string widget_str;
    std::string widget_type;
    std::string widget_name;
    item* current_item=NULL;
    bool added = false;
    
    if(regex_widget->match(text,match_info_widget))
    {
        widget_str = match_info_widget.fetch(0);
        regex_widget = Glib::Regex::create("id=+.+");
        
        if(regex_widget->match(widget_str,match_info_widget))
        {
             widget_name = match_info_widget.fetch(0);
             widget_name = match_info_widget.fetch(0);
             regex_widget = Glib::Regex::create("\"+.+\"");
             if(regex_widget->match(widget_name,match_info_widget))
             {
                 widget_name=match_info_widget.fetch(0);
                 widget_name.erase(0,1);
                 widget_name.erase(widget_name.length()-1,1);
                 }
            }
        regex_widget = Glib::Regex::create("class=+.+id");
        
        if(regex_widget->match(widget_str,match_info_widget))
        {
            widget_type = match_info_widget.fetch(0);
            regex_widget = Glib::Regex::create("\"+.+\"");
            if(regex_widget->match(widget_type,match_info_widget))
            {
                widget_type=match_info_widget.fetch(0);
                widget_type.erase(0,1);
                widget_type.erase(widget_type.length()-1,1);
                }
            }
        
        gtk_container* container = NULL;        
        gtk_notebook* container_notebook=NULL;
        gboolean added = false;
        
        try
        {                
            if(container_item!=NULL && dynamic_cast<gtk_notebook*>(container_item->widget)!=NULL)
                 container_notebook= dynamic_cast< gtk_notebook*>(container_item->widget);
                
            else if(container_item!=NULL && dynamic_cast<gtk_container*>(container_item->widget)!=NULL)
            {
                //std::cout<<"CONTAINER WIDGET IS NOTEBOOK"<<std::endl;
                container= dynamic_cast<gtk_container*>(container_item->widget);
                
                }
            else{//std::cout<<"CONTAINER WIDGET IS NOTHING"<<std::endl;
                //container_item = frame.widget_tree.parent_item;
                }
            }
        catch(...){}   
        
        if(container_item == NULL && widget_type=="GtkWindow")
        {            
            gtk_window* window = new gtk_window(get_style()->get_bg(Gtk::STATE_NORMAL));
            frame.number_of_widgets++;
            window->set_size_request(100,100);
            frame.fixed.put(*window,0,0);            
            frame.fixed.show_all_children();
            window->set_name(widget_name);
            current_item = new item(*dynamic_cast<Gtk::Widget*>(window),std::string("gtk_window"),NULL,NULL,NULL,NULL);
            frame.widget_tree.parent_item = current_item;    
            }
        else if(container_item != NULL && widget_type=="GtkVBox")
        {            
            gtk_vbox* widget = new gtk_vbox(true,0.0,0); // Remember to add dialog box quering about these three values
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_vbox"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);
                widget->set_name(widget_name);
                widget->show();
                //std::cout<<"successfully addedd"<<std::endl;
                }
            }   
        else if(container_item != NULL && widget_type=="GtkHBox")
        {
            gtk_hbox* widget = new gtk_hbox(true,0.0,0); // Remember to add dialog box quering about these three values
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_hbox"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);
                widget->set_name(widget_name);
                widget->show();
                //std::cout<<"successfully addedd"<<std::endl;
                }
            }
        else if(container_item != NULL && widget_type=="GtkButton")
        {  
            gtk_button* widget = new gtk_button("Button");
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;            
                
            if(added)
            {                
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_button"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();                
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkFixed")
        {
            gtk_fixed* widget = new gtk_fixed();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_fixed"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->set_name(widget_name);
                widget->show();                
                }
            }
        else if(container_item != NULL && widget_type=="GtkScrolledWindow")
        {
            gtk_scrollwin* widget = new gtk_scrollwin(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_scrollwin"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkTextView")
        {
            gtk_textview* widget = new gtk_textview(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_textview"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkEntry")
        {
            gtk_entry* widget = new gtk_entry(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_entry"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkLabel")
        {           
            gtk_label* widget = new gtk_label("Label"); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added||container_item->type=="gtk_frame"||container_item->type == "gtk_notebook")
            {
                current_item=new item(*widget,std::string("gtk_label"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);       
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkToggleButton")
        {
            gtk_togglebutton* widget = new gtk_togglebutton("Toggle Button"); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_togglebutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkComboBox")
        {
            gtk_combobox* widget = new gtk_combobox(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_combobox"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkComboBoxText")
        {
            gtk_comboboxtext* widget = new gtk_comboboxtext(true); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_comboboxtext"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkCheckButton")
        {
            gtk_checkbutton* widget = new gtk_checkbutton("Check Button"); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_checkbutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkRadioButton")
        {
            gtk_radiobutton* widget = new gtk_radiobutton("Radio Button"); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_radiobutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkStatusbar")
        {
            Gtk::Statusbar* widget = new Gtk::Statusbar(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_statusbar"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkMenuBar")
        {
            gtk_menubar* widget = new gtk_menubar(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_menubar"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkToolbar")
        {
            gtk_toolbar* widget = new gtk_toolbar(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_toolbar"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkNotebook")
        {
            gtk_notebook* widget = new gtk_notebook(get_style()->get_bg(Gtk::STATE_NORMAL));
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_notebook"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                widget->clear_everything();
                }
            }
        else if(container_item != NULL && widget_type=="GtkEventBox")
        {
            gtk_eventbox* widget = new gtk_eventbox(get_style()->get_bg(Gtk::STATE_NORMAL));
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_eventbox"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkExpander")
        {
            Gtk::Expander* widget = new Gtk::Expander("Expander");
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_expander"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkSpinButton")
        {
            gtk_menubar* widget = new gtk_menubar(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_spinbutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkFileChooserButton")
        {
            Gtk::FileChooserButton* widget = new Gtk::FileChooserButton("File Chooser Button");
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_filechooserbutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkColorChooserButton")
        {
            Gtk::ColorButton* widget = new Gtk::ColorButton();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_colorchooserbutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkFontButton")
        {
            Gtk::FontButton* widget = new Gtk::FontButton("Font Button");
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_fontbutton"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkHScale")
        {
            gtk_hscale* widget = new gtk_hscale();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_hscale"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkVScale")
        {
            gtk_vscale* widget = new gtk_vscale();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_vscale"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkHScrollbar")
        {
            gtk_hscrollbar* widget = new gtk_hscrollbar();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_hscrollbar"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkProgressBar")
        {
            gtk_progressbar* widget = new gtk_progressbar(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_progressbar"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkSpinner")
        {
            gtk_spinner* widget = new gtk_spinner();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_spinner"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkTreeView")
        {
            gtk_treeview* widget = new gtk_treeview();
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_treeview"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
        else if(container_item != NULL && widget_type=="GtkIconView")
        {
            Gtk::IconView* widget = new Gtk::IconView(); 
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_iconview"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                widget->show();
                widget->set_name(widget_name);
                }
            }
         else if(container_item != NULL && widget_type=="GtkFrame")
        {
            gtk_frame* widget = new gtk_frame(NULL);
            if(container)  
                if(container->append_child_widget(*widget,0,0,0,0)!=-1)
                    added = true;
            
            if(container_notebook)
                if(container_notebook->append_child_widget(*widget,0,0,0,0))
                    added=true;
            
            if(added)
            {
                current_item=new item(*dynamic_cast<Gtk::Widget*>(widget),std::string("gtk_frame"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);
                widget->show();      
                widget->set_name(widget_name);
                }                
            }
        else if(container_item != NULL && widget_type=="GtkToolButton")
        {
            gtk_tool_button* tool_button = new gtk_tool_button("ToolButton");
            
            gtk_toolbar* container_toolbar  = dynamic_cast<gtk_toolbar*>(container_item->widget);
            if(container_toolbar)
            {
                container_toolbar->append(*tool_button);
                current_item=new item(*dynamic_cast<Gtk::Widget*>(tool_button),std::string("gtk_tool_button"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                tool_button->show();
                tool_button->set_name(widget_name);
                }                
            }
        else if(container_item != NULL && widget_type=="GtkRadioToolButton")
        {
            gtk_radio_tool_button* tool_button = new gtk_radio_tool_button();            
            gtk_toolbar* container_toolbar  = dynamic_cast<gtk_toolbar*>(container_item->widget);
            if(container_toolbar)
            {
                container_toolbar->append(*tool_button);
                current_item=new item(*dynamic_cast<Gtk::Widget*>(tool_button),std::string("gtk_radio_tool_button"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);
                tool_button->show();
                tool_button->set_name(widget_name);
                }                
            }
        else if(container_item != NULL && widget_type=="GtkSeparatorToolItem")
        {
            gtk_separator_tool_item* tool_button = new gtk_separator_tool_item();
            gtk_toolbar* container_toolbar  = dynamic_cast<gtk_toolbar*>(container_item->widget);
            if(container_toolbar)
            {
                container_toolbar->append(*tool_button);
                current_item=new item(*dynamic_cast<Gtk::Widget*>(tool_button),std::string("gtk_separator_item"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);               
                tool_button->show();            
                tool_button->set_name(widget_name);
                }                
            }
        else if(container_item!=NULL && widget_type=="GtkMenu")
        {            
            Gtk::MenuItem* menu_item = dynamic_cast<Gtk::MenuItem*>(container_item->widget);
            if(menu_item)
            {
                Gtk::Menu* menu = new Gtk::Menu();
                current_item=new item(*dynamic_cast<Gtk::Widget*>(menu),std::string("gtk_menu"),NULL,NULL,NULL,NULL);
                container_item->add_next_child(current_item);
                menu->set_name(widget_name);               
                menu_item->set_submenu(*menu);                
                }
            }
        else if(container_item!=NULL && (widget_type=="GtkImageMenuItem"||widget_type=="GtkMenuItem"))
        {
            gtk_image_menu_item* menu_item = new gtk_image_menu_item("");
            current_item=new item(*dynamic_cast<Gtk::Widget*>(menu_item),std::string("gtk_image_menu_item"),NULL,NULL,NULL,NULL);
            container_item->add_next_child(current_item);
            menu_item->show();
            menu_item->set_name(widget_name);
            
            gtk_menubar* container_menubar = dynamic_cast<gtk_menubar*>(container_item->widget);
            Gtk::Menu* container_menu = dynamic_cast<Gtk::Menu*>(container_item->widget);
            if(container_menubar)
                container_menubar->append(*menu_item);
            else if(container_menu)
                container_menu->append(*menu_item);
            }        
        
        std::string _name= property_box.object_box.parent_row[property_box.object_box.model_columns.col_object];
        if(_name=="" )
           property_box.object_box.add_parent_row(current_item->widget->get_name(),current_item->type);
        else 
        {            
            std::string parent_name = container_item->widget->get_name();
            
            if(!current_item)
            {
                std::cout<<"current null"<<std::endl;
                return;
                }
            frame.number_of_widgets++;
            std::string child_name = current_item->widget->get_name();
            std::string child_type = current_item->type;
            property_box.object_box.add_child_row(parent_name,child_name,child_type);
            }
        }            
    
    Glib::RefPtr<Glib::Regex> regex_child;
    Glib::MatchInfo match_info_child;
    regex_child = Glib::Regex::create("<child>+.+?</child>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    int child_pos = text.length();
    if(regex_child->match(text,match_info_child))
    {
        int x;
        match_info_child.fetch_pos(0,child_pos,x);        
        }
    
    Glib::RefPtr<Glib::Regex> regex_property;
    Glib::MatchInfo match_info_property,match_info_property_str;    
    regex_property =Glib::Regex::create("<property+.+?<child>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    std::string property;
    if(regex_property->match(text,match_info_property))
        property = match_info_property.fetch(0);
    else
    {
        regex_property =Glib::Regex::create("<property+.+?<packing>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
        if(regex_property->match(text,match_info_property))
             property=match_info_property.fetch(0);
        else 
        {
            regex_property =Glib::Regex::create("<property+.+",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
            if(regex_property->match(text,match_info_property))
                 property=match_info_property.fetch(0);
            }
        }
    //std::cout<<property<<std::endl;
    regex_property = Glib::Regex::create("<property+.+?</property>");
    Gtk::Widget* current_widget = NULL;
    if(current_item)
         current_widget = current_item->widget;
    
    if(regex_property->match(property,match_info_property))
    {
        do
        {
            int s,e;
            match_info_property.fetch_pos(0,s,e);
            //if(s>child_pos)
                //break;
            std::string property_str = match_info_property.fetch(0);
            std::string property_name;
            regex_property = Glib::Regex::create("name+.+<");
            if(regex_property->match(property_str,match_info_property_str))
                property_name = match_info_property_str.fetch(0);
            regex_property = Glib::Regex::create("\"+.+?\"");
            if(regex_property->match(property_str,match_info_property_str))
                property_name = match_info_property_str.fetch(0);
            property_name.erase(0,1);
            property_name.erase(property_name.length()-1,1);
            
            regex_property = Glib::Regex::create(">+.+<");
            std::string property_value;
            if(regex_property->match(property_str,match_info_property_str))
                property_value = match_info_property_str.fetch(0);
            property_value.erase(0,1);            
            if(property_value.length()!=0)
                 property_value.erase(property_value.length()-1,1);
            //std::cout<<property_str<<std::endl;
            //std::cout<<"Property NAME "<<property_name<<" VALUE "<<property_value<<std::endl;

            if(property_name=="width_request")
            {
                int width,height;
                current_widget->get_size_request(width,height);
                current_widget->set_size_request(string_to_integer(property_value),height);
                }
            if(property_name=="height_request")
            {
                int width,height;
                current_widget->get_size_request(width,height);
                current_widget->set_size_request(width,string_to_integer(property_value));
                }
            if(property_name=="sensitive")
                current_widget->set_sensitive(string_to_bool(property_value));
            if(property_name=="tooltip")
                 ;//current_widget->set_tooltip(property_value);
            if(property_name=="can_default")
                 current_widget->set_can_default(string_to_bool(property_value));
            if(property_name=="has_default")
                 current_widget->property_has_default()=string_to_bool(property_value);
            if(property_name=="can_focus")
                 current_widget->set_can_focus(string_to_bool(property_value));
            if(property_name=="has_focus")
                 current_widget->property_has_focus()=string_to_bool(property_value);
            if(widget_type=="GtkWindow")
            {
                if(property_name=="type")
                {                    
                    if(property_value=="GTK_WINDOW_TOPLEVEL")
                    {
                         dynamic_cast<gtk_window*>(current_widget)->set_type("TOPLEVEL"); }
                    else
                         dynamic_cast<gtk_window*>(current_widget)->set_type("POPUP"); 
                    }
                if(property_name == "default_width")
                    dynamic_cast<gtk_window*>(current_widget)->set_default_width(string_to_integer(property_value)); 
                    
                else if(property_name == "default_height")
                    dynamic_cast<gtk_window*>(current_widget)->set_default_height(string_to_integer(property_value));
                    
                else if(property_name == "destroy_with_parent")
                    dynamic_cast<gtk_window*>(current_widget)->set_destroy_with_parent(string_to_bool(property_value)); 
                    
                else if(property_name == "accept_focus")
                    dynamic_cast<gtk_window*>(current_widget)->set_accept_focus(string_to_bool(property_value));
                    
                else if(property_name == "focus_on_map")
                    dynamic_cast<gtk_window*>(current_widget)->set_focus_on_map(string_to_bool(property_value));
                    
                else if(property_name == "decorated")
                    dynamic_cast<gtk_window*>(current_widget)->set_decorated(string_to_bool(property_value));
                    
                else if(property_name == "deletable")
                    dynamic_cast<gtk_window*>(current_widget)->set_deletable(string_to_bool(property_value));
                    
                else if(property_name == "mnemonics_visible")
                    dynamic_cast<gtk_window*>(current_widget)->set_mnemonics_visible(string_to_bool(property_value));
                    
                else if(property_name == "focus_visible")
                    dynamic_cast<gtk_window*>(current_widget)->set_focus_visible(string_to_bool(property_value));
                    
                 else if(property_name == "modal")
                    dynamic_cast<gtk_window*>(current_widget)->set_modal(string_to_bool(property_value));
 
                else if(property_name == "opacity")
                    dynamic_cast<gtk_window*>(current_widget)->set_opacity(string_to_float(property_value));
 
                else if(property_name == "title")
                    dynamic_cast<gtk_window*>(current_widget)->set_title(property_value);
                    
                else if(property_name == "resizable")
                    dynamic_cast<gtk_window*>(current_widget)->set_resizable(string_to_bool(property_value)); 
                }
            else if(widget_type=="GtkVBox")
            {
                if(property_name == "spacing")
                    dynamic_cast<gtk_vbox*>(current_widget)->set_spacing(string_to_integer(property_value));
 
                else if(property_name == "homogeneous")
                    dynamic_cast<gtk_vbox*>(current_widget)->set_homogeneous(string_to_bool(property_value));
 
                }
            else if(widget_type=="GtkHBox")
            {
                if(property_name == "spacing")
                    dynamic_cast<gtk_hbox*>(current_widget)->set_spacing(string_to_integer(property_value));
 
                else if(property_name == "homogeneous")
                    dynamic_cast<gtk_hbox*>(current_widget)->set_homogeneous(string_to_bool(property_value));
 
                }
            else if(widget_type=="GtkButton")
            {      
                //std::cout<<property_name<<std::endl;          
                if(property_name == "xalign")
                {
                    float xalign,yalign;
                    dynamic_cast<gtk_button*>(current_widget)->get_alignment(xalign,yalign);
                    dynamic_cast<gtk_button*>(current_widget)->set_alignment(string_to_float(property_value),yalign);
                    }
                else if(property_name == "yalign")
                {
                    float xalign,yalign;
                    dynamic_cast<gtk_button*>(current_widget)->get_alignment(xalign,yalign);
                    dynamic_cast<gtk_button*>(current_widget)->set_alignment(xalign,string_to_float(property_value));
                    }
                else if(property_name == "focus_on_click")
                    dynamic_cast<gtk_button*>(current_widget)->set_focus_on_click(string_to_bool(property_value));
                else if(property_name=="label")
                    dynamic_cast<gtk_button*>(current_widget)->set_label(property_value);                
                else if(property_name=="use_stock")
                {
                    if(property_value=="True")
                    {
                        dynamic_cast<gtk_button*>(current_widget)->set_use_stock(true);
                        dynamic_cast<gtk_button*>(current_widget)->set_stock(get_stock_string_from_gml_string(dynamic_cast<gtk_button*>(current_widget)->get_label()));
                        }
                    }
                }
            else if(widget_type=="GtkFixed")
            {
                //no explicit property
                }
            else if(widget_type=="GtkScrolledWindow")
            {
                if(property_name == "hscrollbar_policy")
                {
                    if(property_value=="GTK_POLICY_AUTOMATIC")
                         property_value="AUTOMATIC";
                    else if(property_value=="GTK_POLICY_ALWAYS")
                         property_value="ALWAYS";
                    else if (property_value=="GTK_POLICY_NEVER")
                          property_value="NEVER";                    
                        
                    dynamic_cast<gtk_scrollwin*>(current_widget)->set_horizontal_policy(property_value);
                    }
                else if(property_name == "vscrollbar_policy")
                {
                    if(property_value=="GTK_POLICY_AUTOMATIC")
                         property_value="AUTOMATIC";
                    else if(property_value=="GTK_POLICY_ALWAYS")
                         property_value="ALWAYS";
                    else if (property_value=="GTK_POLICY_NEVER")
                          property_value="NEVER";
                        
                    dynamic_cast<gtk_scrollwin*>(current_widget)->set_horizontal_policy(property_value);
                    }
                }
            else if(widget_type=="GtkTextView")
            {
                if(property_name == "pixels_above_lines")
                    dynamic_cast<gtk_textview*>(current_widget)->set_pixels_above_lines(string_to_float(property_value));
 
                else if(property_name == "pixels_below_lines")
                    dynamic_cast<gtk_textview*>(current_widget)->set_pixels_below_lines(string_to_float(property_value));
 
                else if(property_name == "pixels_inside_wrap")
                    dynamic_cast<gtk_textview*>(current_widget)->set_pixels_inside_wrap(string_to_float(property_value));
 
                else if(property_name == "editable")
                    dynamic_cast<gtk_textview*>(current_widget)->set_editable(string_to_bool(property_value));
 
                else if(property_name == "wrap_mode")
                {
                    if(property_value=="GTK_WRAP_NONE")
                         property_value="NONE";
                    else if(property_value=="GTK_WRAP_CHARACTER")
                         property_value="CHARACTER";
                    else if (property_value=="GTK_WRAP_WORD")
                          property_value="WORD";
                    
                    dynamic_cast<gtk_textview*>(current_widget)->set_wrapmode(property_value);
                    }
                else if(property_name == "justification")
                {
                    //dynamic_cast<gtk_textview*>(current_widget)->set_pixels_above_lines(
                    }
                else if(property_name == "cursor_visible")
                {
                    dynamic_cast<gtk_textview*>(current_widget)->set_cursor_visible(string_to_bool(property_value));
                    }
                }
            else if(widget_type=="GtkEntry")
            {
                //nothing
                }
            else if(widget_type=="GtkLabel")
            {
                if(property_name=="label")
                    dynamic_cast<Gtk::Label*>(current_widget)->set_text(property_value);
                }
            else if(widget_type=="GtkToggleButton" || widget_type=="GtkRadioButton"||widget_type=="GtkCheckButton")
            {
                if(property_name == "active")
                    dynamic_cast<gtk_togglebutton*>(current_widget)->set_active(string_to_integer(property_value));
 
                else if(property_name == "inconsistent")
                    dynamic_cast<gtk_togglebutton*>(current_widget)->set_active(string_to_bool(property_value));
 
                else if(property_name == "xalign")
                {
                    float xalign,yalign;
                    dynamic_cast<gtk_togglebutton*>(current_widget)->get_alignment(xalign,yalign);
                    dynamic_cast<gtk_togglebutton*>(current_widget)->set_alignment(string_to_float(property_value),yalign);
                    }
                else if(property_name == "yalign")
                {
                    float xalign,yalign;
                    dynamic_cast<gtk_togglebutton*>(current_widget)->get_alignment(xalign,yalign);
                    dynamic_cast<gtk_togglebutton*>(current_widget)->set_alignment(xalign,string_to_float(property_value));
                    }
                else if(property_name == "focus_on_click")
                    dynamic_cast<gtk_togglebutton*>(current_widget)->set_focus_on_click(string_to_bool(property_value));
                else if(property_name=="label")
                    dynamic_cast<gtk_togglebutton*>(current_widget)->set_label(property_value);                
                else if(property_name=="use_stock")
                {
                    if(property_value=="True")
                    {
                        dynamic_cast<gtk_togglebutton*>(current_widget)->set_use_stock(true);
                        dynamic_cast<gtk_togglebutton*>(current_widget)->set_stock(get_stock_string_from_gml_string(dynamic_cast<gtk_togglebutton*>(current_widget)->get_label()));
                        }
                    }
 
                }
            else if(widget_type=="GtkComboBox"||widget_type=="GtkComboBoxText")
            {
                if(property_name == "active")
                    dynamic_cast<gtk_combobox*>(current_widget)->set_active(string_to_integer(property_value));
 
                else if(property_name == "row_span_column")
                    dynamic_cast<gtk_combobox*>(current_widget)->set_row_span_column(string_to_float(property_value));
 
                else if(property_name == "column_span_column")
                    dynamic_cast<gtk_combobox*>(current_widget)->set_column_span_column(string_to_float(property_value));
 
                else if(property_name == "wrap_width")
                    dynamic_cast<gtk_combobox*>(current_widget)->set_wrap_width(string_to_float(property_value));
 
                }
            else if(widget_type=="GtkStatusBar")
            {
                //nothing
                }
            else if(widget_type=="GtkMenuBar")
            {                
                if(property_name == "pack_direction")
                {
                    if(property_value=="GTK_PACK_DIRECTION_LTR")
                         property_value="LEFT TO RIGHT";
                    else if(property_value=="GTK_PACK_DIRECTION_RTL")
                         property_value="RIGHT TO LEFT";
                    else if (property_value=="GTK_PACK_DIRECTION_TTB")
                          property_value="TOP TO BOTTOM";
                    else if (property_value=="GTK_PACK_DIRECTION_BTT")
                          property_value="BOTTOM TO TOP";
                        
                     dynamic_cast<gtk_menubar*>(current_widget)->set_packdirection(property_value);
                    }
                else if(property_name == "child_pack_direction")
                {
                    if(property_value=="GTK_PACK_DIRECTION_LTR")
                         property_value="LEFT TO RIGHT";
                    else if(property_value=="GTK_PACK_DIRECTION_RTL")
                         property_value="RIGHT TO LEFT";
                    else if (property_value=="GTK_PACK_DIRECTION_TTB")
                          property_value="TOP TO BOTTOM";
                    else if (property_value=="GTK_PACK_DIRECTION_BTT")
                          property_value="BOTTOM TO TOP";
                        
                     dynamic_cast<gtk_menubar*>(current_widget)->set_childpackdirection(property_value);
                    }
                }
            else if(widget_type=="GtkToolBar")
            {
                 if(property_name == "show_arrow")
                    dynamic_cast<gtk_toolbar*>(current_widget)->set_show_arrow(string_to_bool(property_value));
 
                else if(property_name == "toolbar_style")
                {
                     if(property_value=="GTK_TOOLBAR_ICONS")
                         property_value="ICONS ONLY";
                    else if(property_value=="GTK_TOOLBAR_TEXT")
                         property_value="TEXT ONLY";
                    else if (property_value=="GTK_TOOLBAR_BOTH")
                          property_value="TEXT BELOW ICONS";
                    else if (property_value=="GTK_TOOLBAR_BOTH_HORIZ")
                          property_value="TEXT BESIDES ICONS";
                        
                    dynamic_cast<gtk_toolbar*>(current_widget)->set_toolbarstyle(property_value);
                    }
                else if(property_name == "icon_size")
                {
                    
                    }
                }
            else if(widget_type=="GtkNotebook")
            {
                if(property_name == "tab_pos")
                {
                    if(property_value=="GTK_POS_LEFT")
                         property_value="LEFT";
                    else if(property_value=="GTK_POS_RIGHT")
                         property_value="RIGHT";
                    else if (property_value=="GTK_POS_BOTTOM")
                          property_value="BOTTOM";
                    else if (property_value=="GTK_POS_TOP")
                          property_value="TOP";
                        
                    dynamic_cast<gtk_notebook*>(current_widget)->set_tab_pos(property_value);
                    }
                else if(property_name == "show_tabs")
                    dynamic_cast<gtk_notebook*>(current_widget)->set_show_tabs(string_to_bool(property_value));
 
                else if(property_name == "show_border")
                    dynamic_cast<gtk_notebook*>(current_widget)->set_show_border(string_to_bool(property_value));
 
                else if(property_name == "scrollable")
                    dynamic_cast<gtk_notebook*>(current_widget)->set_scrollable(string_to_bool(property_value));
 
                }
            else if(widget_type=="GtkEventBox")
            {
                if(property_name == "visible_window")
                    dynamic_cast<gtk_eventbox*>(current_widget)->set_visible_window(string_to_bool(property_value));
 
                else if(property_name == "above_child")
                    dynamic_cast<gtk_eventbox*>(current_widget)->set_above_child(string_to_bool(property_value));
 
                }
            else if(widget_type=="GtkExpander")
            {
                if(property_name == "expanded")
                    dynamic_cast<Gtk::Expander*>(current_widget)->set_expanded(string_to_bool(property_value));
 
                else if(property_name == "use_underline")
                    dynamic_cast<Gtk::Expander*>(current_widget)->set_use_underline(string_to_bool(property_value));
 
                else if(property_name == "use_markup")
                    dynamic_cast<Gtk::Expander*>(current_widget)->set_use_markup(string_to_bool(property_value));
 
                else if(property_name == "spacing")
                    dynamic_cast<Gtk::Expander*>(current_widget)->set_spacing(string_to_integer(property_value));
 
                else if(property_name == "label_fill")
                    dynamic_cast<Gtk::Expander*>(current_widget)->set_label_fill(string_to_bool(property_value));
 
                }
            else if(widget_type=="GtkSpinner")
            {
                //nothing
                }
            else if(widget_type=="GtkFileChooserButton")
            {
                //nothing
                }
            else if(widget_type=="GtkColorChooserButton")
            {
                //nothing
                }
            else if(widget_type=="GtkFontButton")
            {
                //nothing
                }
            else if(widget_type=="GtkHScale"||widget_type=="GtkVScale")
            {
                if(property_name == "digits")
                    dynamic_cast<Gtk::Scale*>(current_widget)->set_digits(string_to_float(property_value));
                
                else if(property_name == "draw_value")
                    dynamic_cast<Gtk::Scale*>(current_widget)->set_draw_value(string_to_float(property_value));
 
                else if(property_name == "inverted")
                    dynamic_cast<Gtk::Scale*>(current_widget)->set_inverted(string_to_bool(property_value));
 
                }
            else if(widget_type=="GtkHScrollbar")
            {
                //
                }
            else if(widget_type=="GtkProgressBar")
            {
                if(property_name == "fraction")
                    dynamic_cast<gtk_progressbar*>(current_widget)->set_fraction(string_to_float(property_value));
 
                else if(property_name == "text")
                    dynamic_cast<gtk_progressbar*>(current_widget)->set_fraction(string_to_float(property_value));
 
                else if(property_name == "pulse_step")
                    dynamic_cast<gtk_progressbar*>(current_widget)->set_fraction(string_to_float(property_value));
 
                }
            else if(widget_type=="GtkTreeView")
            {
                if(property_name == "headers_visible")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_headers_visible(string_to_bool(property_value));
 
                else if(property_name == "headers_clickable")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_headers_clickable(string_to_bool(property_value));
 
                else if(property_name == "reorderable")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_reorderable(string_to_bool(property_value));
 
                else if(property_name == "search_column")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_search_column(string_to_float(property_value));
 
                else if(property_name == "fixed_height_mode")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_fixed_height_mode(string_to_bool(property_value));
 
                else if(property_name == "hover_selection")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_hover_selection(string_to_bool(property_value));
 
                else if(property_name == "show_expanders")
                    dynamic_cast<gtk_treeview*>(current_widget)->set_show_expanders(string_to_bool(property_value)); 
                }
            else if(widget_type=="GtkFrame")
            {
                //Nothing
                }
            else if(widget_type=="GtkImageMenuItem" || widget_type=="GtkMenuItem")
            {
                if(property_name=="label")
                    dynamic_cast<gtk_image_menu_item*>(current_widget)->set_label(property_value);
                else if(property_name=="use_stock")
                {
                    if(property_value=="True")
                    {
                        dynamic_cast<gtk_image_menu_item*>(current_widget)->set_use_stock(true);
                        dynamic_cast<gtk_image_menu_item*>(current_widget)->set_stock(get_stock_string_from_gml_string(dynamic_cast<gtk_image_menu_item*>(current_widget)->get_label()));
                        }
                    }
                }
            else if(widget_type=="GtkRadioToolButton")
            {
                if(property_name=="label")
                     dynamic_cast<gtk_radio_tool_button*>(current_widget)->set_label(property_value);
                else if(property_name=="stock_id")
                {
                    dynamic_cast<gtk_radio_tool_button*>(current_widget)->set_stock(get_stock_string_from_gml_string(property_value));
                    }
                }
            else if(widget_type=="GtkToolButton")
            {
                if(property_name=="label")
                     dynamic_cast<gtk_tool_button*>(current_widget)->set_label(property_value);
                else if(property_name=="stock_id")
                {
                    dynamic_cast<gtk_tool_button*>(current_widget)->set_stock(get_stock_string_from_gml_string(property_value));
                    }
                }
            }
        while(match_info_property.next());        
        }    
    
    if(child_pos!=text.length())
    {
        std::string str="";
        do
        {            
            std::string str1 = match_info_child.fetch(0);        
            get_full_string(str1,text,"<child>","</child>");
            if(text.find(str1)==std::string::npos)
                 continue;
            if(str1.find("<child>")!=std::string::npos)
                str1.erase(str1.find("<child>"),strlen("<child>"));
            if(str1.find("</child>")!=std::string::npos)
                str1.erase(str1.rfind("</child>"),strlen("</child>"));
           // std::cout<<"BEFORE ERASE"<<str1<<"TEXT END"<<std::endl;
            if(text.find(str1)!=std::string::npos)
            {
                text.erase(text.find(str1),str1.length());           
                text.erase(text.find("<child></child>"),std::string("<child></child>").length());
                }
            //std::cout<<"TEXT AFTER ERASE"<<text<<"TEXT END"<<std::endl;
            function_widget(str1,current_item);
            }
        while(match_info_child.next());
        }
    
    Glib::RefPtr<Glib::Regex> regex_packing;
    Glib::MatchInfo match_info_packing;
    //std::cout<<"TEXT"<<text<<"/TEXT"<<std::endl;
    //regex = Glib::Regex::create("<glade-interface>+.+</glade-interface>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    regex_packing = Glib::Regex::create("<packing>+.+?</packing>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    std::string packing_str="";
    if(regex_packing->match(text,match_info_packing))
    {        
        std::string packing_str = match_info_packing.fetch(0);        
        get_full_string(packing_str,text,"<packing>","</packing>");
        text.erase(text.find(packing_str),packing_str.length());         
        regex_property = Glib::Regex::create("<property+.+?</property>");
        Gtk::Widget* container_widget = container_item->widget;
        if(regex_property->match(packing_str,match_info_property))
        {
            do
            {
                int s,e;
                match_info_property.fetch_pos(0,s,e);
                //if(s>child_pos)
                    //break;
                std::string property_str = match_info_property.fetch(0);
                std::string property_name;
                regex_property = Glib::Regex::create("name+.+<");
                if(regex_property->match(property_str,match_info_property_str))
                    property_name = match_info_property_str.fetch(0);
                regex_property = Glib::Regex::create("\"+.+\"");
                if(regex_property->match(property_str,match_info_property_str))
                    property_name = match_info_property_str.fetch(0);
                property_name.erase(0,1);
                property_name.erase(property_name.length()-1,1);
                
                regex_property = Glib::Regex::create(">+.+<");
                std::string property_value;
                if(regex_property->match(property_str,match_info_property_str))
                    property_value = match_info_property_str.fetch(0);
                property_value.erase(0,1);
                property_value.erase(property_value.length()-1,1);
                
                if(container_item->type=="gtk_vbox")
                {                    
                    if(property_name=="expand")
                        dynamic_cast<gtk_vbox*>(container_widget)->set_expand_fill_changes(*current_widget,string_to_bool(property_value),false);
 
                    //else if(property_name=="fill")
                    //else if(property_name=="padding")
                    }
                else if(container_item->type=="gtk_fixed")
                {
                    if(property_name=="x")
                        dynamic_cast<gtk_fixed*>(container_widget)->set_x_of_child(*current_widget,string_to_integer(property_value));
                    if(property_name=="y")
                        dynamic_cast<gtk_fixed*>(container_widget)->set_y_of_child(*current_widget,string_to_integer(property_value));
                    }
                else if(container_item->type=="gtk_hbox")
                {
                    if(property_name=="expand")
                        dynamic_cast<gtk_hbox*>(container_widget)->set_expand_fill_changes(*current_widget,string_to_bool(property_value),false);
 
                    //else if(property_name=="fill")
                    //else if(property_name=="padding")
                    }
                else if(current_item->type=="gtk_label")
                {                    
                    if(container_item->type =="gtk_frame"&&property_name=="type"&&property_value=="label_item")
                    {
                        //std::cout<<"LABEL TYPE LABEL ITEM WITH FRAME PARENT"<<std::endl;
                        if(dynamic_cast<gtk_frame*>(container_widget)->get_child())
                            dynamic_cast<gtk_frame*>(container_widget)->remove_child(current_widget);
                            
                        dynamic_cast<gtk_frame*>(container_widget)->set_label(dynamic_cast<gtk_label*>(current_widget));
                        }
                    }
                if(container_item->type =="gtk_notebook"&&property_name=="type"&&property_value=="tab")
                {
                    gtk_notebook* _notebook = dynamic_cast<gtk_notebook*>(container_item->widget);
                    //std::cout<<"LLLLLLLLLL"<<std::endl;
                    //_notebook->remove_child(current_item->widget);
                    _notebook->set_label_as_tab_label(dynamic_cast<gtk_label*>(current_item->widget));
                    }
                }
            while(match_info_property.next());
            }
        }
    }

void CreatorMain::open_file(std::string filepath)
{
    std::string glade_text = Glib::file_get_contents(filepath);
    Glib::RefPtr<Glib::Regex> regex;
    Glib::MatchInfo match_info;
    regex = Glib::Regex::create("<widget+.+</widget>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    std::string str;
     //std::cout<<"SEARCHING"<<std::endl;
    if(regex->match(glade_text,match_info))
    {
        str = match_info.fetch(0);
        //std::cout<<str<<std::endl;
        function_widget(str,NULL);        
        }
    }

void CreatorMain::on_object_box_tree_selection_changed()
{    
    std::string name = property_box.object_box.get_current_name();   
    frame.current_item = frame.widget_tree.get_item_from_name(name);    
    //std::cout<<name<<std::endl;
    current_focused_widget.set_value(frame.current_item->widget);
    item* parent = frame.current_item->get_parent();
    if(parent)
        property_box.property_editor.set_property_values_from_widget(*(frame.current_item->widget),frame.current_item->type,*(parent->widget),parent->type);
    else
        property_box.property_editor.set_property_values_from_widget(*(frame.current_item->widget),frame.current_item->type,*this,"");
    }

bool CreatorMain::current_widget_name_changed(std::string name)
{
    if(name == frame.current_item->widget->get_name())
        return false;
        
    if(frame.if_name_already_exists(name))
    {
        Gtk::MessageDialog msg_dialog(parent_win,name+" already exists, choose another name!");
        msg_dialog.run();
        return false;
        }
    else
    {
        property_box.object_box.change_name(name,frame.current_item->widget->get_name());
        frame.current_item->widget->set_name(name);
        return true;
        }
    }

bool CreatorMain::on_mouse_pressed(GdkEventButton *event)
{    
    return FALSE;
    }

void CreatorMain::add_child_rows_to_object_box()
{
    if(frame.current_item)
    {
        //std::cout<<"current name"<<frame.current_item->widget->get_name()<<std::endl;
        std::string _name= property_box.object_box.parent_row[property_box.object_box.model_columns.col_object];
        ///std::cout<<"current _name"<<_name<<std::endl;
        if(_name=="")
           property_box.object_box.add_parent_row(frame.current_item->widget->get_name(),frame.current_item->type);
        else
        {
            property_box.object_box.add_child_row(frame.current_item->get_parent()->widget->get_name(),frame.current_item->widget->get_name(),frame.current_item->type);
            if(frame.current_item->child)
                property_box.object_box.add_child_row(frame.current_item->widget->get_name(),frame.current_item->child->widget->get_name(),frame.current_item->child->type);
            }
         }
    frame.draw_widget=false;
    frame.type_of_widget="";
    }

bool CreatorMain::on_mouse_released(GdkEventButton *event)
{        
    if(frame.current_item)
    {        
        if(frame.current_item->get_parent())
             property_box.property_editor.set_property_values_from_widget(*(frame.current_item->widget),frame.current_item->type,*(frame.current_item->get_parent()->widget),frame.current_item->get_parent()->type);
        else
            property_box.property_editor.set_property_values_from_widget(*(frame.current_item->widget),frame.current_item->type,*this,"");         
        property_box.object_box.set_selection_from_widget(*(frame.current_item->widget),frame.current_item->type);
        }
    return FALSE;
    }

CreatorMain::~CreatorMain(){}
