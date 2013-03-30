//204 Lines
#include<gtkmm.h>
#include<vector>
#include"compiler.h"
#include"code_widget.h"
#include"find_dialog.h"
#include"find_replace_dialog.h"
#include"reg_exp_search_dialog.h"
#include"bookmark_menu_item.h"
#include"new_project_dialog.h"
#include"project_class.h"
#include"project_save_as_dialog.h"
#include"project_preferences_dialog.h"
#include"options_dialog.h"
#include"exit_save_dialog.h"
#include"find_in_file_dialog.h"
#include"creator_main.h"

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
class ProjModelColumns : public Gtk::TreeModel::ColumnRecord
{
    public:
        ProjModelColumns(){add(col);} 
        Gtk::TreeModelColumn<std::string> col;
    };

class SymModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    SymModelColumns()
    { add(m_col_icon);add(m_col_sym);}
    Gtk::TreeModelColumn<std::string> m_col_sym;
    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > m_col_icon;
};

class main_window : public Gtk::Window
{
    public:
        main_window();
        virtual ~main_window();
        static const int recent_files=5;
        
        static const int recent_projs=5;
        
    protected:
        void filenew_activated();
        void filenewtab_activated();
        void fileopen_activated();
        void filesave_activated();
        void filesaveas_activated();
        void filesaveall_activated();
        void filesaveallas_activated();
        void filesavecopyas_activated();
        void fileremovetab_activated();
        void fileremovealltabs_activated();
        void filequit_activated();
        
        void editundo_activated();
        void editredo_activated();
        void editcopy_activated();
        void editcut_activated();
        void editpaste_activated();
        void editselectall_activated();
        void editgotoline_activated();
        void editfind_activated();
        void editfindandreplace_activated();
        void editfindinselectedtext_activated();
        void editfindinfile_activated();
        void editfindselectedtext_activated();
        void editregularexpressionsearch_activated();
        void editautocompelete_activated();
        void editfoldall_activated();
        void editunfoldall_activated();
        void editfoldcurrent_activated();

        void formatindentregion_activated();
        void formatdedentregion_activated();
        void formatcommentout_activated();
        void formatsinglecommentout_activated();
        void formatuncommentout_activated();
        void formatsingleuncommentout_activated();
        void formattabify_activated();
        void formatuntabify_activated();
        void formatuppercase_activated();
        void formatlowercase_activated();
        void formatstripspaces_activated();
        void format_show_parenthesis_activated();
        
        void navigation_back_activated();
        void navigation_forward_activated();
        void navigation_start_of_file_activated();
        void navigation_end_of_file_activated();
        void navigation_go_to_brace_activated();
        void navigation_declaration_activated();
        void navigation_definition_activated();
        void navigation_add_bookmark_activated();
        void navigation_clear_bookmark_activated();
        void navigation_next_bookmark_activated();
        void navigation_prev_bookmark_activated();
        
        void project_new();
        void project_open();
        void project_add_new();
        void project_add_existing();
        void project_save();
        void project_save_as();
        void project_save_copy_as();
        void project_preferences();
        void project_empty();
        void project_close();
        
        void runrun_activated();
        void runcompile_activated();

        void toolsgnometerminal_activated();
        void toolsautoindent_activated();
        void toolsoptions_activated();
        
        void debug_gui_activated();
        void debug_gnu_activated();
        
        void window_menu_bar_activated();
        void window_tool_bar_activated();
        void window_status_bar_activated();
        void window_project_activated();
        void window_symbols_activated();
        void window_scope_activated();
        void window_close_all_activated();
        void window_close_current_activated();
        void window_close_others_activated();
        
        bool is_file_changed(std::string&,Glib::ustring&);
        
        void update_recent_files_menu(std::string&,std::string&);
        void recent_file_menu_item_clicked(Gtk::MenuItem*);
        void save_recent_files();
        void load_recent_files();
        
        void bookmark_menu_item_activated(bookmark_menu_item*);
        
        void save_recent_projs();
        void load_recent_projs();
        
        void on_compile_dialog_tree_view_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column,compiler_win&);
        bool on_delete_event(GdkEventAny* event);
        
        void update_recent_project_menu(std::string filename,std::string filepath);
        void recent_proj_menu_item_clicked(Gtk::MenuItem* menu_item);
        
        int get_notebook_current_page();
        
        Gtk::VBox vbox;
        Gtk::HBox hbox;
        Gtk::Notebook notebook; 
        void notebook_switch_page(GtkNotebookPage*,int);
        CreatorMain creator_main;
        Glib::RefPtr<Gtk::UIManager> ui_manager;
        Glib::RefPtr<Gtk::ActionGroup> action_group;
        Glib::RefPtr<gtksourceview::SourceBuffer> buffer;
        Glib::RefPtr<gtksourceview::SourceLanguageManager> lang_manager;
        Gtk::Statusbar status_bar;
        std::vector<code_widget*> vector_code_widget;
        
        std::vector<std::string> filepathsarray;
        std::vector<Gtk::MenuItem*> recent_filemenu_items;
        std::vector<std::string> recent_filepaths;
        
        std::vector<Gtk::MenuItem*> recent_proj_menu_items;
        std::vector<std::string> recent_proj_paths;
        
        Gtk::Menu* file_menu,*navigation_menu,*project_menu;
        Gtk::SeparatorMenuItem file_sep,navigation_sep,project_sep;
        std::vector<bookmark_menu_item*> bookmark_menu_item_vector;
        
        Gtk::RadioButtonGroup bookmark_menu_item_group;        
        bool indentation,auto_save,optimize,auto_save_all,recent_projects,word_wrap;
        bool auto_save_current,disable_inline,bool_recent_files,warning,support_89,line_numbers;
        bool compile_only,code_completion,compile_assemble,add_dir,highlight_line,define_symbols;
        int indent_width, auto_save_time,tab_width, optimize_level;
        std::string symbols,other_args;
        std::vector<std::string> vector_include_dir;
        void load_options();
        Glib::ustring get_gcc_command();
        
        Gtk::Notebook proj_sym_notebook;
        Gtk::TreeView proj_tree_view; 
        Glib::RefPtr<Gtk::TreeStore> tree_model;
        Gtk::TreeModel::Row parent_row;
        Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
        ProjModelColumns model_columns;  
        project_class current_proj;
        std::string mode;
        
        void on_proj_tree_view_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        
        SymModelColumns symbols_Columns;
        Gtk::TreeView symbols_icon_view;
        Glib::RefPtr<Gtk::TreeStore> symbols_tree_model;
        
        void on_sym_tree_view_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
        
        void update_symbols();        
        Gtk::SeparatorToolItem separator_tool_item1,separator_tool_item2,separator_tool_item3,separator_tool_item4;
        Gtk::Image image_add_bookmark,image_clear_bookmark,image_next_bookmark,image_previous_bookmark;
        Gtk::Image image_run,image_compile;
        Gtk::Image image_gdb,image_kraken;
        Gtk::Image image_shell;
        Gtk::Image image_new_project, image_open_project,image_add_existing_file;
        Gtk::Image image_add_new_file,image_project_close,image_project_options;
        Gtk::Image image_uppercase, image_lowercase;
        Gtk::ToolButton tool_button_add_bookmark,tool_button_clear_bookmark;
        Gtk::ToolButton tool_button_next_bookmark,tool_button_previous_bookmark;
        Gtk::ToolButton tool_button_run,tool_button_compile;
        Gtk::ToolButton tool_button_gdb,tool_button_kraken;
        Gtk::ToolButton tool_button_shell;
        Gtk::ToolButton tool_button_new_project, tool_button_open_project, tool_button_add_existing_file;
        Gtk::ToolButton tool_button_add_new_file,tool_button_project_close,tool_button_project_options;
        Gtk::ToolButton tool_button_uppercase, tool_button_lowercase;
    };
#endif