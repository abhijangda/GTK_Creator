//178 Lines
#include<gtksourceviewmm/sourcebuffer.h>
#include<gtksourceviewmm/sourceview.h>
#include<gtksourceviewmm/sourcelanguagemanager.h>
#include<gtkmm.h>
#include"helper_functions.h"
#include<vector>

#ifndef SOURCE_VIEW_H
#define SOURCE_VIEW_H

class fold_text
{
    public:
    fold_text(std::string _tag, int _pos,int __pos): tag_name(_tag)
    {       
        start_pos=_pos;
        end_pos=__pos;
        }
    std::string tag_name;
    int start_pos;
    int end_pos;
    };

class function
{
    public:
    function(std::string func_str,int p)
    {
        parenthesis = func_str.substr(func_str.find("("));
        name = func_str.substr(0,func_str.find("("));
        type = name.substr(0,name.rfind(" "));
        name = name.substr(name.rfind(" ")+1);
        if(type.find(" ")!=std::string::npos)
            type = type.substr(type.find(" ")+1);
        pos=p;
        }
    function(std::string _t, std::string _n, std::string _p, int _pos)
    {
        type=_t;
        name =_n;
        parenthesis=_p;
        pos=_pos;
        }
    
    std::string type;
    std::string name;
    std::string parenthesis;
    int pos;
    
    bool operator==(function _f)
    {
        if(type == _f.type && name == _f.name && parenthesis == _f.parenthesis)
            return true;
        
        return false;
        }
    
    std::string get_func_str() { return type+" " + name + parenthesis + " ";}
    };

class gtk_widget_function
{
    public:
        gtk_widget_function()
        {
            widget_type="";
            }
        gtk_widget_function(std::string _widget_type)
        {
            widget_type = _widget_type;
            }
        std::string widget_type;
        std::vector<function> vector_function;
        void add_function(std::string _f)
        {
            vector_function.insert(vector_function.end(),function(_f,-1));
            }
    };

class c_symbol
{
    public:
        c_symbol(std::string _n, std::string _t,int _p)
        {
            name = _n;
            type = _t;
            pos = _p;
            }
        std::string name;
        std::string type;
        int pos;
        std::vector<c_symbol> child_c_symbols;
    };

class source_view : public gtksourceview::SourceView
{
    public:
        source_view(Gtk::Statusbar&,std::string filename, Gtk::ComboBoxText& cb,Gtk::DrawingArea& ,Gtk::DrawingArea&);
        ~source_view();
        void navigate_back();
        void navigate_forward();
        static int indent_width;
        static bool indentation;
        static bool code_completion;
        void set_filename(std::string _f){filename=_f;}
        void get_curr_file_funcs();
        static int left_margin;
        
        void set_show_line_numbers(bool _b);
        bool get_show_line_numbers();
        Gtk::Frame frame;
        Gtk::ScrolledWindow tree_view_scroll_win;
        Gtk::ListViewText tree_view;
        Gtk::ComboBoxText& combo_box_func;
        Gtk::DrawingArea& code_folding_widget;
        Gtk::DrawingArea& line_numbers_widget;
        Glib::RefPtr<Gtk::TextChildAnchor> child_anchor;
        
        static void load_gtk_keywords();
        static std::vector<gtk_widget_function> vector_gtk_function;
        std::vector<fold_text> vector_fold_text;
        static std::vector<std::string> vector_gtk_structs;
        static std::string gtk_structs_string;
        static std::string gtk_enums_string;
        
        void apply_tag_at_current_line();
        
        bool is_tree_row_activated;
        std::string tree_row_text;        
        std::vector<std::string> stack_tooltip_text;
        int line_number_tooltip;
        
        static std::string fold_str;
        
        void on_combo_box_func_changed();
        sigc::connection connection_combo_box;
        void on_tree_view_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        bool on_mouse_press(GdkEventButton* event);

        void show_auto_complete();
        
        Gtk::TextIter get_line_end_iter(int line);
        void func_include_file_line(std::string line_text);
        void include_file_thread_func(std::string filepath);        
        
        Glib::Thread* include_file_thread;
        
        std::string filename;
        std::vector<int> lines_array;
        
        std::vector<std::string> vector_include_files;
        std::vector<function> vector_include_func;
        std::vector<function> vector_curr_file_func;
        std::vector<c_symbol> vector_c_symbol;
        
        bool can_add_to_history;
        int prev_line;
        Gtk::Statusbar& status_bar;
        Glib::RefPtr<gtksourceview::SourceBuffer> buffer;
        Glib::RefPtr<Gtk::TextBuffer::Mark> current_mark;
        
        virtual bool on_txtinput_key_press(GdkEventKey *event);
        virtual bool on_txtinput_key_release(GdkEventKey *event);
        bool on_tree_view_key_release(GdkEventKey *event);
        
        virtual void on_mark_set(const Gtk::TextBuffer::iterator&,const Glib::RefPtr<Gtk::TextBuffer::Mark>&);
        virtual bool on_expose_event(GdkEventExpose* event);
        sigc::connection connection_mark_set;
        void on_text_insert(const Gtk::TextIter& iter, const Glib::ustring& text, int bytes);
        void on_text_deleted(const Gtk::TextIter& start, const Gtk::TextIter& end);
        void on_text_deleted_after(const Gtk::TextIter& start, const Gtk::TextIter& end);

        void fill_from_include_files();

        std::string open_brace, close_brace;
        int count_str(std::string& str1, std::string& str2);
    };
#endif 