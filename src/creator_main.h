//36 Lines
#include"frame.h"
#include"object_box.h"
#include"property_editor.h"

class PropertyBox : public Gtk::VPaned
{
    public:
        PropertyBox(Frame&);
        ~PropertyBox();
        PropertyEditor property_editor;
        ObjectBox object_box;
    };

class CreatorMain : public Gtk::ScrolledWindow
{
    public:
        CreatorMain(Gtk::Window&);
        ~CreatorMain();
        ToolBox tool_box; 
        Gtk::HBox hbox, hbox_buttons;
        Frame frame;
        Gtk::VBox frame_buttons_vbox;
        Gtk::ScrolledWindow scroll_win;
        Gtk::Button cmd_copy, cmd_cut, cmd_paste,cmd_delete;
        PropertyBox property_box;        
        virtual bool on_mouse_pressed(GdkEventButton *event);
        virtual bool on_mouse_released(GdkEventButton *event); 
        bool current_widget_name_changed(std::string name);  
        void open_file(std::string filepath);
        int save_to_file(std::string filepath);
        std::string get_string();
        int count_str(std::string& str1, std::string& str2);
        void get_full_string(std::string& full_string, std::string& text, std::string opening_str, std::string closing_str);
        void function_widget(std::string text,item*);
        void on_focused_widget_changed(Gtk::Widget*,Gtk::Widget*);
        void on_current_pressed_placeholder_changed(Gtk::Widget*,Gtk::Widget*);
    private:
        Gtk::Window& parent_win;
        void add_child_rows_to_object_box();
        void on_object_box_tree_selection_changed(); 
        void get_gml_string(item* _item, item*, std::string& full_string,int);
        Gtk::Widget* clipboard_widget;
        item* clipboard_item;
        void cmd_copy_clicked();
        void cmd_cut_clicked();
        void cmd_paste_clicked();
        void cmd_delete_clicked();
    };