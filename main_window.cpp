//2655 Lines
//auto complete

#include"main_window.h"
#include <iostream>
#include<sstream>
#include<string>
bool event_on_delete = false;

int count_str(std::string& str1, std::string& str2)
{
    int index=0,count=0;
    while((index=str1.find(str2,index))!=-1)
    {
        count++;
        index++;
        }
    return count;
    }

main_window::main_window()
    : recent_filemenu_items(recent_files),recent_filepaths(recent_files),bookmark_menu_item_vector(0),mode("FILE"),hbox(false,2),
        recent_proj_menu_items(recent_projs),recent_proj_paths(recent_projs),creator_main(*this),image_add_bookmark("./bookmarksadd.png"),image_clear_bookmark("./bookmarksclear.png"),
        image_next_bookmark("./bookmarksnext.png"),image_previous_bookmark("./bookmarksprev.png"),image_run("./run.png"),image_compile("./compile.png"),
        image_gdb("./debug_gdb.png"),image_kraken("./debug_gui.png"),image_shell("./shell.png"),image_new_project("./project_new.png"), image_open_project("./project_open.png"),
        image_add_existing_file("./add_existing_file.png"),image_add_new_file("./add_new_file.png"),image_project_close("./project_close.png"),
        image_project_options("./project_options.png"),image_uppercase("./uppercase.png"),image_lowercase("./lowercase.png"),
        tool_button_add_bookmark(image_add_bookmark),tool_button_clear_bookmark(image_clear_bookmark),tool_button_next_bookmark(image_next_bookmark),
        tool_button_previous_bookmark(image_previous_bookmark),tool_button_run(image_run),tool_button_compile(image_compile),tool_button_gdb(image_gdb),
        tool_button_kraken(image_kraken),tool_button_shell(image_shell),tool_button_new_project(image_project_close), tool_button_open_project(image_open_project), 
        tool_button_add_existing_file(image_add_existing_file),tool_button_add_new_file(image_add_new_file),tool_button_project_close(image_new_project),
        tool_button_project_options(image_project_options),tool_button_uppercase(image_uppercase), tool_button_lowercase(image_lowercase)
{    
    set_title("GTK+ Creator");
    set_default_size(600,400);
    set_border_width(5);
    
    lang_manager = gtksourceview::SourceLanguageManager::create();
    action_group = Gtk::ActionGroup::create();

    action_group->add(Gtk::Action::create("FileMenu","File"));
    action_group->add(Gtk::Action::create("FileNew",Gtk::Stock::NEW),sigc::mem_fun(*this,&main_window::filenew_activated));
    action_group->add(Gtk::Action::create("FileNewTab","New Tab"),sigc::mem_fun(*this,&main_window::filenewtab_activated));
    action_group->add(Gtk::Action::create("FileOpen",Gtk::Stock::OPEN),sigc::mem_fun(*this,&main_window::fileopen_activated));
    action_group->add(Gtk::Action::create("FileSave",Gtk::Stock::SAVE),sigc::mem_fun(*this,&main_window::filesave_activated));
    action_group->add(Gtk::Action::create("FileSaveAs",Gtk::Stock::SAVE_AS),sigc::mem_fun(*this,&main_window::filesaveas_activated));
    action_group->add(Gtk::Action::create("FileSaveAll","Save All",""),sigc::mem_fun(*this,&main_window::filesaveall_activated));
    action_group->add(Gtk::Action::create("FileSaveAllAs","Save All As",""),sigc::mem_fun(*this,&main_window::filesaveallas_activated));
    action_group->add(Gtk::Action::create("FileSaveCopyAs","Save Copy As",""),sigc::mem_fun(*this,&main_window::filesavecopyas_activated));
    action_group->add(Gtk::Action::create("FileRemoveTab","Remove Current Tab",""),sigc::mem_fun(*this,&main_window::fileremovetab_activated));
    action_group->add(Gtk::Action::create("FileRemoveAllTab","Remove All Tabs",""),sigc::mem_fun(*this,&main_window::fileremovealltabs_activated));
    action_group->add(Gtk::Action::create("FileQuit",Gtk::Stock::QUIT),sigc::mem_fun(*this,&main_window::filequit_activated));
    
    action_group->add(Gtk::Action::create("EditMenu","Edit"));
    action_group->add(Gtk::Action::create("EditUndo",Gtk::Stock::UNDO),sigc::mem_fun(*this,&main_window::editundo_activated));
    action_group->add(Gtk::Action::create("EditRedo",Gtk::Stock::REDO),sigc::mem_fun(*this,&main_window::editredo_activated));
    action_group->add(Gtk::Action::create("EditCopy",Gtk::Stock::COPY),sigc::mem_fun(*this,&main_window::editcopy_activated));
    action_group->add(Gtk::Action::create("EditCut",Gtk::Stock::CUT),sigc::mem_fun(*this,&main_window::editcut_activated));
    action_group->add(Gtk::Action::create("EditPaste",Gtk::Stock::PASTE),sigc::mem_fun(*this,&main_window::editpaste_activated));
    action_group->add(Gtk::Action::create("EditSelectAll",Gtk::Stock::SELECT_ALL),sigc::mem_fun(*this,&main_window::editselectall_activated));
    action_group->add(Gtk::Action::create("EditFind",Gtk::Stock::FIND),sigc::mem_fun(*this,&main_window::editfind_activated));
    action_group->add(Gtk::Action::create("EditFindAndReplace",Gtk::Stock::FIND_AND_REPLACE),sigc::mem_fun(*this,&main_window::editfindandreplace_activated));
    action_group->add(Gtk::Action::create("EditFindSelectedText","Find Selection"),sigc::mem_fun(*this,&main_window::editfindselectedtext_activated));
    action_group->add(Gtk::Action::create("EditFindInSelectedText","Find in Selection"),sigc::mem_fun(*this,&main_window::editfindinselectedtext_activated));
    action_group->add(Gtk::Action::create("EditFindinFile","Find in File"),sigc::mem_fun(*this,&main_window::editfindinfile_activated));
    action_group->add(Gtk::Action::create("EditRegularExpressionSearch","Regular Expression Search"),sigc::mem_fun(*this,&main_window::editregularexpressionsearch_activated));
    action_group->add(Gtk::Action::create("EditAutoComplete","Auto Complete"),sigc::mem_fun(*this,&main_window::editautocompelete_activated));
    action_group->add(Gtk::Action::create("EditFoldAll","Fold All Functions"),sigc::mem_fun(*this,&main_window::editfoldall_activated));
    action_group->add(Gtk::Action::create("EditUnfoldAll","Unfold All Functions"),sigc::mem_fun(*this,&main_window::editunfoldall_activated));
    action_group->add(Gtk::Action::create("EditFoldCurrent","Fold Current Function"),sigc::mem_fun(*this,&main_window::editfoldcurrent_activated));
    
    action_group->add(Gtk::Action::create("FormatMenu","Format"));
    action_group->add(Gtk::Action::create("FormatIndent",Gtk::Stock::INDENT,"Indent Region"),sigc::mem_fun(*this,&main_window::formatindentregion_activated));
    action_group->add(Gtk::Action::create("FormatDedent",Gtk::Stock::UNINDENT,"Dedent Region",""),sigc::mem_fun(*this,&main_window::formatdedentregion_activated));
    action_group->add(Gtk::Action::create("FormatComment","Multi-Line Comment Out Region",""),sigc::mem_fun(*this,&main_window::formatcommentout_activated));
    action_group->add(Gtk::Action::create("FormatUncomment","Mutli-Line Uncomment Out Region",""),sigc::mem_fun(*this,&main_window::formatuncommentout_activated));
    action_group->add(Gtk::Action::create("FormatSingleComment","Single-Line Comment Out Region",""),sigc::mem_fun(*this,&main_window::formatsinglecommentout_activated));    
    action_group->add(Gtk::Action::create("FormatSingleUnComment","Single-Line Uncomment Out Region",""),sigc::mem_fun(*this,&main_window::formatsingleuncommentout_activated));    
    action_group->add(Gtk::Action::create("FormatUpperCase","Upper Case Selection",""),sigc::mem_fun(*this,&main_window::formatuppercase_activated));
    action_group->add(Gtk::Action::create("FormatLowerCase","Lower Case Selection",""),sigc::mem_fun(*this,&main_window::formatlowercase_activated));
    action_group->add(Gtk::Action::create("FormatTabify","Tabify Region",""),sigc::mem_fun(*this,&main_window::formattabify_activated));
    action_group->add(Gtk::Action::create("FormatUnTabify","UnTabify Region",""),sigc::mem_fun(*this,&main_window::formatuntabify_activated));
    action_group->add(Gtk::Action::create("FormatStripSpaces","Strip Trailing Spaces",""),sigc::mem_fun(*this,&main_window::formatstripspaces_activated));
    action_group->add(Gtk::Action::create("FormatShowParenthesis","Show Surrounding Parenthesis",""),sigc::mem_fun(*this,&main_window::format_show_parenthesis_activated));
    
    action_group->add(Gtk::Action::create("NavigationMenu","Navigation"));
    action_group->add(Gtk::Action::create("NavigationBack",Gtk::Stock::GO_BACK,"Back"),sigc::mem_fun(*this, &main_window::navigation_back_activated));
    action_group->add(Gtk::Action::create("NavigationForward",Gtk::Stock::GO_FORWARD,"Forward",""),sigc::mem_fun(*this, &main_window::navigation_forward_activated));
    action_group->add(Gtk::Action::create("NavigationStart",Gtk::Stock::GO_UP,"Start of file",""),sigc::mem_fun(*this, &main_window::navigation_start_of_file_activated));
    action_group->add(Gtk::Action::create("NavigationEnd",Gtk::Stock::GO_DOWN,"End of file",""),sigc::mem_fun(*this, &main_window::navigation_end_of_file_activated));
    action_group->add(Gtk::Action::create("NavigationGoToLine","Go To Line",""),sigc::mem_fun(*this,&main_window::editgotoline_activated));
    action_group->add(Gtk::Action::create("NavigationGoToMatchingBrace","Go To Maching Brace",""),sigc::mem_fun(*this,&main_window::navigation_go_to_brace_activated));
    action_group->add(Gtk::Action::create("NavigationGoToFunctionDeclaration","Go To Function Declaration",""),sigc::mem_fun(*this,&main_window::navigation_declaration_activated));
    action_group->add(Gtk::Action::create("NavigationGoToFunctionDefinition","Go To Function Definition",""),sigc::mem_fun(*this,&main_window::navigation_definition_activated));
    action_group->add(Gtk::Action::create("NavigationAddBookmark","Add Bookmark",""),sigc::mem_fun(*this,&main_window::navigation_add_bookmark_activated));
    action_group->add(Gtk::Action::create("NavigationClearBookmarks","Clear Bookmarks",""),sigc::mem_fun(*this,&main_window::navigation_clear_bookmark_activated));
    action_group->add(Gtk::Action::create("NavigationPreviousBookmark","Previous Bookmark",""),sigc::mem_fun(*this,&main_window::navigation_next_bookmark_activated));
    action_group->add(Gtk::Action::create("NavigationNextBookmark","Next Bookmark",""),sigc::mem_fun(*this,&main_window::navigation_prev_bookmark_activated));
    
    action_group->add(Gtk::Action::create("ProjectMenu","Project"));
    action_group->add(Gtk::Action::create("ProjectNew","New Project",""),sigc::mem_fun(*this, &main_window::project_new));
    action_group->add(Gtk::Action::create("ProjectOpen","Open Project",""),sigc::mem_fun(*this, &main_window::project_open));
    action_group->add(Gtk::Action::create("ProjectAddNew","Add New File",""),sigc::mem_fun(*this, &main_window::project_add_new));
    action_group->add(Gtk::Action::create("ProjectAddExisting","Add Existing File",""),sigc::mem_fun(*this, &main_window::project_add_existing));
    action_group->add(Gtk::Action::create("ProjectSave","Save Project",""),sigc::mem_fun(*this, &main_window::project_save));
    action_group->add(Gtk::Action::create("ProjectSaveAs","Save Project As",""),sigc::mem_fun(*this, &main_window::project_save_as));
    action_group->add(Gtk::Action::create("ProjectSaveCopyAs","Save Project Copy As",""),sigc::mem_fun(*this, &main_window::project_save_copy_as));
    action_group->add(Gtk::Action::create("ProjectPreferences","Project Preferences",""),sigc::mem_fun(*this, &main_window::project_preferences));
    action_group->add(Gtk::Action::create("ProjectEmpty","Empty Project",""),sigc::mem_fun(*this, &main_window::project_empty));
    action_group->add(Gtk::Action::create("ProjectClose","Close Project",""),sigc::mem_fun(*this, &main_window::project_close));    
    
    action_group->add(Gtk::Action::create("RunMenu","Run"));
    action_group->add(Gtk::Action::create("RunRun","Run"),sigc::mem_fun(*this,&main_window::runrun_activated));
    action_group->add(Gtk::Action::create("RunCompile","Compile"),sigc::mem_fun(*this,&main_window::runcompile_activated));    
    
    action_group->add(Gtk::Action::create("DebugMenu","Debug"));
    action_group->add(Gtk::Action::create("DebugGUI","Debug with GUI Debugger"),sigc::mem_fun(*this,&main_window::debug_gui_activated));
    action_group->add(Gtk::Action::create("DebugGNU","Debug with GNU Debugger"),sigc::mem_fun(*this,&main_window::debug_gnu_activated));
    
    action_group->add(Gtk::Action::create("ToolsMenu","Tools"));
    action_group->add(Gtk::Action::create("ToolsTerminal","Run Terminal"),sigc::mem_fun(*this,&main_window::toolsgnometerminal_activated));
    action_group->add(Gtk::Action::create("ToolsAutoIndent","Auto Indent"),sigc::mem_fun(*this,&main_window::toolsautoindent_activated));
    action_group->add(Gtk::Action::create("ToolsOptions",Gtk::Stock::PREFERENCES,"Options"),sigc::mem_fun(*this,&main_window::toolsoptions_activated));
    
    action_group->add(Gtk::Action::create("WindowMenu","Window"));
    action_group->add(Gtk::ToggleAction::create("WindowMenubar","Menubar","Show/Hide Menubar",true),sigc::mem_fun(*this,&main_window::window_menu_bar_activated));
    action_group->add(Gtk::ToggleAction::create("WindowToolbar","Toolbar","Show/Hide Toolbar",true),sigc::mem_fun(*this,&main_window::window_tool_bar_activated));
    action_group->add(Gtk::ToggleAction::create("WindowStatusbar","Statusbar","Show/Hide Statusbar",true),sigc::mem_fun(*this,&main_window::window_status_bar_activated));
    action_group->add(Gtk::ToggleAction::create("WindowProject","Project"),sigc::mem_fun(*this,&main_window::window_project_activated));
    action_group->add(Gtk::ToggleAction::create("WindowSymbols","Symbols"),sigc::mem_fun(*this,&main_window::window_symbols_activated));
    action_group->add(Gtk::ToggleAction::create("WindowScope","Scope","Show/Hide Scope",true),sigc::mem_fun(*this,&main_window::window_scope_activated));
    action_group->add(Gtk::Action::create("WindowCloseAllDocuments","Close All Documents"),sigc::mem_fun(*this,&main_window::window_close_all_activated));
    action_group->add(Gtk::Action::create("WindowCloseCurrentDocument","Close Current Document"),sigc::mem_fun(*this,&main_window::window_close_current_activated));
    action_group->add(Gtk::Action::create("WindowCloseOtherDocuments","Close Other Documents"),sigc::mem_fun(*this,&main_window::window_close_others_activated));
    
    ui_manager = Gtk::UIManager::create();
    ui_manager->insert_action_group(action_group);
    Glib::ustring ui_info = 
    "<ui>"
    "<menubar name = 'MenuBar'>"
    "<menu action = 'FileMenu'>"
    "<menuitem action = 'FileNew'/>"
    "<menuitem action = 'FileNewTab'/>"
    "<menuitem action = 'FileOpen'/>"
    "<separator/>"
    "<menuitem action = 'FileSave'/>"
    "<menuitem action = 'FileSaveAs'/>"
    "<menuitem action = 'FileSaveAll'/>"
    "<menuitem action = 'FileSaveAllAs'/>"
    "<menuitem action = 'FileSaveCopyAs'/>"
    "<separator/>"
    "<menuitem action = 'FileRemoveTab'/>"
    "<menuitem action = 'FileRemoveAllTab'/>"
    "<menuitem action = 'FileQuit'/>"      
    "<separator/>"
    "</menu>"
    
    "<menu action = 'EditMenu'>"
    "<menuitem action = 'EditUndo'/>"
    "<menuitem action = 'EditRedo'/>"
    "<separator/>"
    "<menuitem action = 'EditCopy'/>"
    "<menuitem action = 'EditCut'/>"
    "<menuitem action = 'EditPaste'/>"
    "<menuitem action = 'EditSelectAll'/>"
    "<separator/>"
    "<menuitem action = 'EditFind'/>"   
    "<menuitem action = 'EditFindSelectedText'/>"
    "<menuitem action = 'EditFindInSelectedText'/>"
    "<menuitem action = 'EditFindinFile'/>"
    "<separator/>"
    "<menuitem action = 'EditFindAndReplace'/>"    
    "<separator/>"
    "<menuitem action = 'EditRegularExpressionSearch'/>"
    "<separator/>"
    "<menuitem action = 'EditAutoComplete'/>"
    "<separator/>"
    "<menuitem action = 'EditFoldAll'/>"
    "<menuitem action = 'EditUnfoldAll'/>"
    "<menuitem action = 'EditFoldCurrent'/>"
    "</menu>"
    
    "<menu action = 'FormatMenu'>"
    "<menuitem action = 'FormatIndent'/>"
    "<menuitem action = 'FormatDedent'/>"
    "<separator/>"
    "<menuitem action = 'FormatComment'/>"
    "<menuitem action = 'FormatUncomment'/>"    
    "<menuitem action = 'FormatSingleComment'/>"
    "<menuitem action = 'FormatSingleUnComment'/>"
    "<separator/>"
    "<menuitem action = 'FormatUpperCase'/>"
    "<menuitem action = 'FormatLowerCase'/>"
     "<separator/>"
    "<menuitem action = 'FormatTabify'/>"
    "<menuitem action = 'FormatUnTabify'/>"
    "<separator/>"
    "<menuitem action = 'FormatShowParenthesis'/>"
    "<separator/>"
    "<menuitem action = 'FormatStripSpaces'/>"
    "</menu>"
    
    "<menu action = 'NavigationMenu'>"
    "<menuitem action = 'NavigationBack'/>"
    "<menuitem action = 'NavigationForward'/>"
    "<separator/>"
    "<menuitem action = 'NavigationStart'/>"
    "<menuitem action = 'NavigationEnd'/>"
    "<separator/>"
    "<menuitem action = 'NavigationGoToLine'/>"
    "<separator/>"
    "<menuitem action = 'NavigationGoToMatchingBrace'/>"
    "<separator/>"
    "<menuitem action = 'NavigationGoToFunctionDeclaration'/>"
    "<menuitem action = 'NavigationGoToFunctionDefinition'/>"
    "<separator/>"
    "<menuitem action = 'NavigationAddBookmark'/>"
    "<menuitem action = 'NavigationClearBookmarks'/>"
    "<menuitem action = 'NavigationPreviousBookmark'/>"
    "<menuitem action = 'NavigationNextBookmark'/>"
    "<separator/>"
    "</menu>"
    
    "<menu action = 'ProjectMenu'>"
    "<menuitem action = 'ProjectNew'/>"
    "<menuitem action = 'ProjectOpen'/>"
    "<separator/>"
    "<menuitem action = 'ProjectAddNew'/>"
    "<menuitem action = 'ProjectAddExisting'/>"
    "<separator/>"
    "<menuitem action = 'ProjectSave'/>"
    "<menuitem action = 'ProjectSaveAs'/>"
    "<menuitem action = 'ProjectSaveCopyAs'/>"
    "<separator/>"
    "<menuitem action = 'ProjectPreferences'/>"
    "<separator/>"
    "<menuitem action = 'ProjectEmpty'/>"
    "<menuitem action = 'ProjectClose'/>"
    "<separator/>"
    "</menu>"
    "<menu action = 'RunMenu'>"
    "<menuitem action = 'RunRun'/>"
    "<menuitem action = 'RunCompile'/>"
    "</menu>"
    "<menu action = 'DebugMenu'>"
    "<menuitem action = 'DebugGUI'/>"
    "<menuitem action = 'DebugGNU'/>"
    "</menu>"
    
    "<menu action = 'ToolsMenu'>"
    "<menuitem action = 'ToolsTerminal'/>"
    "<menuitem action = 'ToolsAutoIndent'/>"
    "<menuitem action = 'ToolsOptions'/>"
    "</menu>"
    
    "<menu action = 'WindowMenu'>"
    "<menuitem action = 'WindowMenubar'/>"
    "<menuitem action = 'WindowToolbar'/>"
    "<menuitem action = 'WindowStatusbar'/>"
    "<menuitem action = 'WindowProject'/>"
    "<menuitem action = 'WindowSymbols'/>"
    "<menuitem action = 'WindowScope'/>"
    "<separator/>"
    "<menuitem action = 'WindowCloseAllDocuments'/>"
    "<menuitem action = 'WindowCloseCurrentDocument'/>"
    "<menuitem action = 'WindowCloseOtherDocuments'/>"
    "</menu>"
    "</menubar>"
    
    "<toolbar name = 'ToolBar'>"
    "<toolitem action = 'FileNew'/>"
    "<toolitem action = 'FileOpen'/>"
    "<toolitem action = 'FileSave'/>"
    "<toolitem action = 'FileSaveAs'/>"
    "<separator/>"
    "<toolitem action = 'EditUndo'/>"
    "<toolitem action = 'EditRedo'/>" 
    "<separator/>"
    "<toolitem action = 'EditCopy'/>" 
    "<toolitem action = 'EditCut'/>" 
    "<toolitem action = 'EditPaste'/>" 
    "<toolitem action = 'EditSelectAll'/>" 
    "<separator/>"
    "<toolitem action = 'EditFind'/>" 
    "<toolitem action = 'EditFindAndReplace'/>"     
    "<separator/>"
    "<toolitem action = 'FormatIndent'/>" 
    "<toolitem action = 'FormatDedent'/>" 
    "<separator/>"
    "<toolitem action = 'NavigationBack'/>" 
    "<toolitem action = 'NavigationForward'/>" 
    "<toolitem action = 'NavigationStart'/>"
    "<toolitem action = 'NavigationEnd'/>"
    "<separator/>"
    "<toolitem action = 'ToolsOptions'/>"
    "<separator/>"
    "<toolitem action = 'FileQuit'/>"
    "</toolbar>"
    "</ui>";
    ui_manager->add_ui_from_string(ui_info);
    Gtk::Widget* menu_bar = ui_manager->get_widget("/MenuBar");
    if(menu_bar)
        vbox.pack_start(*menu_bar,Gtk::PACK_SHRINK);
    Gtk::Toolbar* toolbar = dynamic_cast<Gtk::Toolbar*>(ui_manager->get_widget("/ToolBar"));
    if(toolbar)
        vbox.pack_start(*toolbar,Gtk::PACK_SHRINK);
    
    Gtk::Widget* file_menu_item = ui_manager->get_widget("/MenuBar/FileMenu/");
    if(file_menu_item&&dynamic_cast<Gtk::MenuItem*>(file_menu_item))
        file_menu  = dynamic_cast<Gtk::MenuItem*>(file_menu_item)->get_submenu();
    
    Gtk::Widget* navigation_menu_item = ui_manager->get_widget("/MenuBar/NavigationMenu/");
    if(navigation_menu_item&&dynamic_cast<Gtk::MenuItem*>(navigation_menu_item))
        navigation_menu  = dynamic_cast<Gtk::MenuItem*>(navigation_menu_item)->get_submenu();
        
    Gtk::Widget* project_menu_item = ui_manager->get_widget("/MenuBar/ProjectMenu/");
    if(project_menu_item&&dynamic_cast<Gtk::MenuItem*>(project_menu_item))
        project_menu  = dynamic_cast<Gtk::MenuItem*>(project_menu_item)->get_submenu();
    
    toolbar->insert(tool_button_uppercase,18,sigc::mem_fun(*this,&main_window::formatuppercase_activated));
    toolbar->insert(tool_button_lowercase,19,sigc::mem_fun(*this,&main_window::formatlowercase_activated));
    toolbar->insert(tool_button_run,21,sigc::mem_fun(*this,&main_window::runrun_activated));
    toolbar->insert(tool_button_compile,22,sigc::mem_fun(*this,&main_window::runcompile_activated));
    toolbar->insert(separator_tool_item1,23);
    
    toolbar->insert(tool_button_add_bookmark,24,sigc::mem_fun(*this,&main_window::navigation_add_bookmark_activated));
    toolbar->insert(tool_button_clear_bookmark,25,sigc::mem_fun(*this,&main_window::navigation_clear_bookmark_activated));
    toolbar->insert(tool_button_next_bookmark,26,sigc::mem_fun(*this,&main_window::navigation_next_bookmark_activated));
    toolbar->insert(tool_button_previous_bookmark,27,sigc::mem_fun(*this,&main_window::navigation_prev_bookmark_activated));    
    toolbar->insert(separator_tool_item2,28);
    
    toolbar->insert(tool_button_gdb,29,sigc::mem_fun(*this,&main_window::debug_gnu_activated));
    toolbar->insert(tool_button_kraken,30,sigc::mem_fun(*this,&main_window::debug_gui_activated));
    toolbar->insert(separator_tool_item3,31);
    
    toolbar->set_show_arrow(false);
    
    Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
    settings->property_gtk_toolbar_icon_size()=Gtk::ICON_SIZE_SMALL_TOOLBAR;
    
    tree_model = Gtk::TreeStore::create(model_columns);
    proj_tree_view.set_model(tree_model);
    
    proj_tree_view.append_column("Project", model_columns.col);
    proj_tree_view.signal_row_activated().connect(sigc::mem_fun(*this,&main_window::on_proj_tree_view_row_activated));
    
    symbols_tree_model = Gtk::TreeStore::create(symbols_Columns);
    symbols_icon_view.set_model(symbols_tree_model);
    symbols_icon_view.append_column("Type", symbols_Columns.m_col_icon);
    symbols_icon_view.append_column("Name", symbols_Columns.m_col_sym);
    
    symbols_icon_view.signal_row_activated().connect(sigc::mem_fun(*this,&main_window::on_sym_tree_view_row_activated));
    
    notebook.signal_switch_page().connect(sigc::mem_fun(*this,&main_window::notebook_switch_page));
    
    proj_sym_notebook.append_page(proj_tree_view,"Project");
    proj_sym_notebook.append_page(symbols_icon_view,"Symbols");
    
    hbox.pack_start(proj_sym_notebook,Gtk::PACK_SHRINK);
    
    hbox.pack_start(notebook,Gtk::PACK_EXPAND_WIDGET);
    vbox.pack_start(hbox,Gtk::PACK_EXPAND_WIDGET);
    vbox.pack_start(status_bar, Gtk::PACK_SHRINK);
    add(vbox);
    load_options();
    load_recent_files();
    load_recent_projs();
    show_all_children();
    signal_delete_event().connect(sigc::mem_fun(*this,&main_window::on_delete_event));
    maximize();    
    proj_tree_view.hide();
    proj_sym_notebook.hide();
    source_view::load_gtk_keywords();
    }

main_window::~main_window(){}

bool main_window::on_delete_event(GdkEventAny* event)
{
    event_on_delete = true;
    std::vector<int> vector_index_files_changed;
    std::vector<std::string> vector_file_name;
    int glade_index = 0;
    for(int i =0;i<filepathsarray.size();i++)
    {
        Glib::ustring s;
        if(filepathsarray[i].find(".glade")==std::string::npos)
        {
            buffer = vector_code_widget[i-glade_index]->_source_view.get_source_buffer();
            s = buffer->get_text();                        
            }
        else
        {
            s = creator_main.get_string();            
            if(!glade_index)
               glade_index++;
            }
       
        if(is_file_changed(filepathsarray[i],s))
        {
            vector_index_files_changed.insert(vector_index_files_changed.end(),i);  
            if(filepathsarray[i].find(".glade")!=std::string::npos)
                vector_file_name.insert(vector_file_name.end(),notebook.get_tab_label_text(creator_main));
            else
                 vector_file_name.insert(vector_file_name.end(),notebook.get_tab_label_text(*vector_code_widget[i-glade_index]));
            }
        }
    if(vector_index_files_changed.size()==0)
        return false;
        
    exit_save_dialog dialog(*this,vector_file_name);
    dialog.show_all_children();
    int result = dialog.run();
    if(result==2)
    {
        for(int i =0;i<dialog.vector_check_button.size();i++)
        {
            if(dialog.vector_check_button[i]->get_active())
            {
                event_on_delete = true;
                notebook.set_current_page(vector_index_files_changed[i]);                
                filesave_activated();
                }
            }
        }
    else if(result==0)
        return true;
    return false;
    }

void main_window::load_options()
{
    int pos_start, pos_end;
    std::string str = Glib::file_get_contents("./settings.ini");    

    pos_start = str.find("<indentation>")+13;
    pos_end=str.find("</indentation>");
    indentation= string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    source_view::indentation=indentation;
    
    pos_start = str.find("<indent_width>")+14;
    pos_end=str.find("</indent_width>");
    indent_width = string_to_integer(str.substr(pos_start,pos_end-pos_start));        
    source_view::indent_width =indent_width;
        
    pos_start = str.find("<auto_save>")+11;
    pos_end=str.find("</auto_save>");
    auto_save =string_to_bool(str.substr(pos_start,pos_end-pos_start));  
    
    pos_start = str.find("<auto_save_time>")+16;
    pos_end=str.find("</auto_save_time>");
    auto_save_time =string_to_integer(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<auto_save_current>")+21;
    pos_end=str.find("</auto_save_current>");
    auto_save_current = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    
    pos_start = str.find("<auto_save_all>")+15;
    pos_end=str.find("</auto_save_all>");
    auto_save_all = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    
    pos_start = str.find("<tab_width>")+11;
    pos_end=str.find("</tab_width>");
    tab_width = string_to_integer(str.substr(pos_start,pos_end-pos_start));    
    
    pos_start = str.find("<word_wrap>")+11;
    pos_end=str.find("</word_wrap>");
    word_wrap = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    
    pos_start = str.find("<recent_projects>")+17;
    pos_end=str.find("</recent_projects>");
    recent_projects = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    
    pos_start = str.find("<recent_files>")+14;
    pos_end=str.find("</recent_files>");
    bool_recent_files = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    
    pos_start = str.find("<code_completion>")+17;
    pos_end=str.find("</code_completion>");
    code_completion = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    source_view::code_completion = code_completion;
    
    pos_start = str.find("<line_numbers>")+14;
    pos_end=str.find("</line_numbers>");
    line_numbers = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    for(int i = 0; i<vector_code_widget.size();i++)
        vector_code_widget[i]->_source_view.set_show_line_numbers(line_numbers);        
        
    pos_start = str.find("<highlight_line>")+16;
    pos_end=str.find("</highlight_line>");
    highlight_line = string_to_bool(str.substr(pos_start,pos_end-pos_start));    
    for(int i = 0; i<vector_code_widget.size();i++)
        vector_code_widget[i]->_source_view.set_highlight_current_line(highlight_line);
        
    pos_start = str.find("<optimize>")+10;
    pos_end=str.find("</optimize>");
    optimize = string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    if(optimize)
    {        
        pos_start = str.find("<optimize_level>")+16;
        pos_end=str.find("</optimize_level>");
        optimize_level =string_to_integer(str.substr(pos_start,pos_end-pos_start));
        }
    
    pos_start = str.find("<compile_assemble>")+18;
    pos_end=str.find("</compile_assemble>");
    compile_assemble =string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<support_c89>")+13;
    pos_end=str.find("</support_c89>");
    support_89=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<warning_as_errors>")+19;
    pos_end=str.find("</warning_as_errors>");
    warning =string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<add_dir>")+9;
    pos_end=str.find("</add_dir>");
    add_dir =string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    if(add_dir)
    {        
        pos_start = 0;
        pos_end = 0;
        while((pos_start=str.find("<dir>",pos_start+1))!=-1 && (pos_end=str.find("</dir>",pos_end+1))!=-1)
            vector_include_dir.insert(vector_include_dir.end(),str.substr(pos_start+5,pos_end-pos_start-5));        
        }
    
    pos_start = str.find("<define_symbols>")+16;
    pos_end=str.find("</define_symbols>");
    define_symbols = string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<symbols>")+9;
    pos_end=str.find("</symbols>");
    symbols = str.substr(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<disable_inline>")+16;
    pos_end=str.find("</disable_inline>");
    disable_inline =string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<compile_only>")+14;
    pos_end=str.find("</compile_only>");
    compile_only = string_to_bool(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<other_args>")+12;
    pos_end=str.find("</other_args>");
    other_args = str.substr(pos_start,pos_end-pos_start);
    }

void main_window::notebook_switch_page(GtkNotebookPage* page,int page_num)
{
    if(!event_on_delete)
        update_symbols();
    event_on_delete = false;
    }

void main_window::update_symbols()
{                    
    if(notebook.get_current_page()==-1)
        return;
    
    symbols_tree_model->clear();
    
    if(filepathsarray[notebook.get_current_page()].find(".glade")!=std::string::npos)
        return;
    
    int i=0;
    for(i=0;i<notebook.get_current_page();i++)
    {
        if(filepathsarray[i].find(".glade")!=std::string::npos)
        {
            i+=1;
            break;
            }
        }    
    
    source_view& __source_view = vector_code_widget[notebook.get_current_page()-i]->_source_view;
    for(int i = 0;i<__source_view.vector_c_symbol.size();i++)
    {
        Gtk::TreeModel::Row parent_row = *(symbols_tree_model->append());
        parent_row[symbols_Columns.m_col_sym] = __source_view.vector_c_symbol[i].name;
        if(__source_view.vector_c_symbol[i].type=="#define")
            parent_row[symbols_Columns.m_col_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/define.png");
        else
        {
            parent_row[symbols_Columns.m_col_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/struct.png");       
            for(int j = 0; j<__source_view.vector_c_symbol[i].child_c_symbols.size();j++)
            {
                Gtk::TreeModel::Row row = *(symbols_tree_model->append(parent_row.children()));
                row[symbols_Columns.m_col_sym] = __source_view.vector_c_symbol[i].child_c_symbols[j].type +" " +__source_view.vector_c_symbol[i].child_c_symbols[j].name;
                row[symbols_Columns.m_col_icon]=Gdk::Pixbuf::create_from_file("/media/sda11/C++/gtkmm/gtk_creator_editor/element.png");       
                }
            }
        }
    }

void main_window::on_sym_tree_view_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column)
{
    Glib::ustring path_str = path.to_string();
    int colon_pos = path_str.find(":");
    if(colon_pos==Glib::ustring::npos)
        colon_pos=path_str.length();
    
    std::string index_str = path_str.substr(0,colon_pos);
    int index = string_to_integer(index_str);
    if(colon_pos==path_str.length())
    {
        Gtk::TextIter navigate_to_iter = buffer->get_iter_at_offset(vector_code_widget[notebook.get_current_page()]->_source_view.vector_c_symbol[index].pos);
        buffer->place_cursor(navigate_to_iter);
        vector_code_widget[notebook.get_current_page()]->_source_view.scroll_to(navigate_to_iter);
        }
    else
    {
        std::string index_str2 = path_str.substr(colon_pos+1);
        int index2 = string_to_integer(index_str2);

        Gtk::TextIter navigate_to_iter = buffer->get_iter_at_offset(vector_code_widget[notebook.get_current_page()]->_source_view.vector_c_symbol[index].child_c_symbols[index2].pos);
        buffer->place_cursor(navigate_to_iter);
        vector_code_widget[notebook.get_current_page()]->_source_view.scroll_to(navigate_to_iter);
        }
    }

bool main_window::is_file_changed(std::string& filename,Glib::ustring& text)
{
    if(filename==""&&text!="")
        return true;
    else if(filename=="" && text=="")
        return false;
    Glib::ustring file_text=Glib::file_get_contents(filename);
    if(file_text==text)
        return false;
    return true;
    }

int main_window::get_notebook_current_page()
{
    int i=0;
    for(i=0;i<notebook.get_current_page();i++)
    {
        if(filepathsarray[i].find(".glade")!=std::string::npos)
        {
            if(i==0)
                i+=1;
            break;
            }
        }    
    return notebook.get_current_page()-i;
    }
    
void main_window::filenew_activated()
{
    if(notebook.get_n_pages()==0)
    {
        filenewtab_activated();
        return;
        }
    buffer = vector_code_widget[notebook.get_current_page()]->_source_view.get_source_buffer();
    buffer->set_text("");
    filepathsarray[notebook.get_current_page()]="";
    vector_code_widget[notebook.get_current_page()]->_source_view.set_filename("");
    notebook.set_tab_label_text(*vector_code_widget[notebook.get_current_page()],"New File");
    notebook.show_all_children();
    }

void main_window::filenewtab_activated()
{
    filepathsarray.resize(filepathsarray.size()+1);
    vector_code_widget.resize(vector_code_widget.size()+1);
    
    vector_code_widget[vector_code_widget.size()-1]=new code_widget(status_bar,"");
    (vector_code_widget[vector_code_widget.size()-1]->_source_view.get_source_buffer())->set_text("");
    filepathsarray[filepathsarray.size()-1]="";
    
    notebook.append_page(*vector_code_widget[vector_code_widget.size()-1],"New File");
    notebook.show_all_children();
    notebook.set_current_page(notebook.get_n_pages()-1);
    for(int i = 0; i<vector_code_widget.size();i++)
    {
        vector_code_widget[i]->_source_view.set_show_line_numbers(line_numbers);        
        vector_code_widget[i]->_source_view.set_highlight_current_line(highlight_line);
        }
    }

void main_window::save_recent_files()
{
    if(!bool_recent_files)
        return;
    
    std::string contents = "";
    for(int i = 0; i <recent_files;i++)
    {
        if(recent_filepaths[i]!="")
             contents+="<file>"+recent_filepaths[i]+"</file>\n";
        }
    Glib::file_set_contents("./recent_files.ini",contents);
    }

void main_window::load_recent_files()
{
    if(!bool_recent_files)
        return;
    std::string str = "";
    try 
    {
         str = Glib::file_get_contents("./recent_files.ini");
        }
    catch(...){}       
    
    int pos_start = -1;
    int pos_end = 0;
    int count = 0;    
    file_menu->append(file_sep);
    while((pos_start=str.find("<file>",pos_start+1))!=-1 && (pos_end=str.find("</file>",pos_end+1))!=-1)
    {
        recent_filepaths[count] = str.substr(pos_start+6,pos_end-pos_start-6);  
        std::string filename = recent_filepaths[count].substr(recent_filepaths[count].rfind("/")+1);
        Gtk::MenuItem* recent_filemenu_item  = new Gtk::MenuItem(filename);
        recent_filemenu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_file_menu_item_clicked),recent_filemenu_item));
        file_menu->append(*recent_filemenu_item);
        recent_filemenu_items[count]=recent_filemenu_item;
        count++;
        }
    }

void main_window::recent_file_menu_item_clicked(Gtk::MenuItem* menu_item)
{
    int i;
    for( i = 0;i<recent_files;i++)
    {
        if(recent_filemenu_items[i]&& recent_filemenu_items[i]==menu_item)
            break;
        }
    buffer = vector_code_widget[notebook.get_current_page()]->_source_view.get_source_buffer();
    Glib::ustring text = buffer->get_text();
    if(notebook.get_n_pages()>=0)
    {
        if(is_file_changed(filepathsarray[notebook.get_current_page()],text))
        {
            Gtk::MessageDialog dialog(*this,Glib::ustring("Current file has been changed, since it was last saved. Do you want to open a new file?"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
            if(dialog.run()==Gtk::RESPONSE_NO)
                return;
            }
        }
    if(notebook.get_n_pages()==0)
        filenewtab_activated();
    
    std::string filepath = recent_filepaths[i];
    
    vector_code_widget[notebook.get_current_page()]->_source_view.set_filename(filepath);
  
    buffer->set_text(Glib::file_get_contents(filepath));
    update_symbols();
    filepathsarray[notebook.get_current_page()] = filepath;
    buffer->set_highlight_syntax(true);
    Glib::RefPtr<gtksourceview::SourceLanguage> lang = lang_manager->guess_language(filepath,Glib::ustring());
    std::string filename;
    for(int i=filepath.rfind("/")+1;i<=filepath.size()-1;i++)
        filename  = filename + filepath[i];
    notebook.set_tab_label_text(*vector_code_widget[notebook.get_current_page()],filename);
    buffer->set_language(lang);
    vector_code_widget[notebook.get_current_page()]->_source_view.get_curr_file_funcs();
    vector_code_widget[notebook.get_current_page()]->_source_view.fill_from_include_files();
    update_recent_files_menu(filename,filepath);    
    }

void main_window::update_recent_files_menu(std::string& filename,std::string& filepath)
{
    if(!bool_recent_files)
        return;
        
    int i=0,j=0;
    for(i =0;i<recent_files;i++)
    {
        if(!recent_filemenu_items[i])
             break;
        }
    
    if(i==recent_files)
       return;
    
    if(i==0)
        file_menu->append(file_sep);
            
    for(j=0;j<i;j++)
    {
        if(Glib::ustring(filename)==recent_filemenu_items[j]->get_label())
            break;
        }
    if(i==0)
    {
        Gtk::MenuItem* recent_file_menu_item  = new Gtk::MenuItem(filename);
        recent_file_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_file_menu_item_clicked),recent_file_menu_item));
        
        recent_filemenu_items[0] = recent_file_menu_item;
        recent_filepaths[0]=filepath;
        file_menu->append(*recent_filemenu_items[0]);
        }
    else if(j==i)
    {
        Gtk::MenuItem* recent_file_menu_item  = new Gtk::MenuItem(filename);
        recent_file_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_file_menu_item_clicked),recent_file_menu_item));

        for(int k = 0;k<i;k++)
           file_menu->remove(*recent_filemenu_items[k]);
        
        for(int k = i;k>0;k--)
        {
            recent_filemenu_items[k]=recent_filemenu_items[k-1];
            recent_filepaths[k] = recent_filepaths[k-1];
            }
            
        recent_filemenu_items[0] = recent_file_menu_item;
        recent_filepaths[0]=filepath;
        for(int k=0;k<i+1;k++)
            file_menu->append(*recent_filemenu_items[k]);
        }
    else
    {
        Gtk::MenuItem* recent_file_menu_item  = new Gtk::MenuItem(filename);
        recent_file_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_file_menu_item_clicked),recent_file_menu_item));
        
        Gtk::MenuItem* item = recent_filemenu_items[i];
        for(int k = 0;k<i;k++)
           file_menu->remove(*recent_filemenu_items[k]);
        
        if(item)
            delete item;
            
        for(int k = j;k>0;k--)
        {
            recent_filemenu_items[k]=recent_filemenu_items[k-1];
            recent_filepaths[k] = recent_filepaths[k-1];
            }
            
        recent_filemenu_items[0] = recent_file_menu_item;
        recent_filepaths[0]=filepath;
        for(int k=0;k<i;k++)
            file_menu->append(*recent_filemenu_items[k]);
        }
    save_recent_files();
    show_all_children();
    proj_tree_view.hide();
    }

void main_window::fileopen_activated()
{
    std::string filepath;
    int result;
    if(mode=="FILE" && notebook.get_current_page()!=-1)
    {
        buffer = vector_code_widget[notebook.get_current_page()]->_source_view.get_source_buffer();
        Glib::ustring text = buffer->get_text();
        if(notebook.get_n_pages()>=0)
       {
            if(is_file_changed(filepathsarray[notebook.get_current_page()],text))
            {
                Gtk::MessageDialog dialog(*this,Glib::ustring("Current file has been changed, since it was last saved. Do you want to open a new file?"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
                if(dialog.run()==Gtk::RESPONSE_NO)
                    return;
                }
            }
        }
    Gtk::FileChooserDialog dialog("Open File",Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Open",Gtk::RESPONSE_OK);
    
    Gtk::FileFilter file_filter_c,file_filter_all,file_filter_h;
    file_filter_c.add_pattern("*.c");
    file_filter_all.add_pattern("*.*");
    file_filter_h.add_pattern("*.h");
    
    file_filter_c.set_name("C Files(*.c)");
    file_filter_all.set_name("All Files(*.*)");
    file_filter_h.set_name("C Header Files(*.h)");
    
    dialog.add_filter(file_filter_c);
    dialog.add_filter(file_filter_h);
    dialog.add_filter(file_filter_all);
    
    result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
    {
        mode="FILE";
        if(notebook.get_n_pages()==0)
            filenewtab_activated();

        filepath = dialog.get_filename();
        vector_code_widget[notebook.get_current_page()]->_source_view.set_filename(filepath);
        buffer = vector_code_widget[notebook.get_current_page()]->_source_view.get_source_buffer();
        buffer->set_text(Glib::file_get_contents(filepath));
        filepathsarray[notebook.get_current_page()] = filepath;
        buffer->set_highlight_syntax(true);
        Glib::RefPtr<gtksourceview::SourceLanguage> lang = lang_manager->guess_language(filepath,Glib::ustring());
        std::string filename;
        for(int i=filepath.rfind("/")+1;i<=filepath.size()-1;i++)
            filename  = filename + filepath[i];

        notebook.set_tab_label_text(*vector_code_widget[notebook.get_current_page()],filename);
        buffer->set_language(lang);
        vector_code_widget[notebook.get_current_page()]->_source_view.get_curr_file_funcs();
        vector_code_widget[notebook.get_current_page()]->_source_view.fill_from_include_files();
        update_recent_files_menu(filename,filepath);
        update_symbols();
        }
    }

void main_window::filesave_activated()
{       
    //std::cout<<notebook.get_current_page()<<std::endl;
    //std::cout<<filepathsarray[notebook.get_current_page()]<<std::endl;
    if(filepathsarray[notebook.get_current_page()].find(".glade")!=std::string::npos)
    {    
        creator_main.save_to_file(filepathsarray[notebook.get_current_page()]);
        }
    else
    {                
        int i=0;
        for(i=0;i<notebook.get_current_page();i++)
        {
            if(filepathsarray[i].find(".glade")!=std::string::npos)
            {
                i+=1;
                break;
                }
            }    
        
        if(filepathsarray[notebook.get_current_page()]=="")
            filesaveas_activated();
        else
        {
            buffer = vector_code_widget[notebook.get_current_page()-i]->_source_view.get_source_buffer();
            Glib::file_set_contents(filepathsarray[notebook.get_current_page()],buffer->get_text());
            update_symbols();
            vector_code_widget[notebook.get_current_page()-i]->_source_view.get_curr_file_funcs();
            vector_code_widget[notebook.get_current_page()-i]->_source_view.fill_from_include_files();            
            }
        }
    }

void main_window::filesaveas_activated()
{
    std::string filepath;
    int result;
    
    Gtk::FileChooserDialog dialog("Save As",Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Save As",Gtk::RESPONSE_OK);
    Gtk::FileFilter file_filter_c,file_filter_all,file_filter_h,file_filter_glade;
    
    if(filepathsarray[notebook.get_current_page()].find(".glade")==std::string::npos)
    {           
        file_filter_c.add_pattern("*.c");
        file_filter_all.add_pattern("*.*");
        file_filter_h.add_pattern("*.h");
        
        file_filter_c.set_name("C Files(*.c)");
        file_filter_all.set_name("All Files(*.*)");
        file_filter_h.set_name("C Header Files(*.h)");
        
        dialog.add_filter(file_filter_c);
        dialog.add_filter(file_filter_h);
        dialog.add_filter(file_filter_all);
        }
    else
    {
        file_filter_glade.add_pattern(".glade");
        file_filter_glade.set_name("Glade GUI File(*.glade)");
        dialog.add_filter(file_filter_glade);
        }
    
    result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
    {
        filepath = dialog.get_filename();
        std::string filename;
        for(int i=filepath.rfind("/")+1;i<=filepath.size()-1;i++)
        {
            filename  = filename + filepath[i];
            }
        if(filepathsarray[notebook.get_current_page()].find(".glade")==std::string::npos)
       {
            vector_code_widget[get_notebook_current_page()]->_source_view.set_filename(filepath);
            buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
            Glib::file_set_contents(filepath,buffer->get_text());
            filepathsarray[notebook.get_current_page()] = filepath;
            buffer->set_highlight_syntax(true);
            Glib::RefPtr<gtksourceview::SourceLanguage> lang = lang_manager->guess_language(filepath,Glib::ustring());
            notebook.set_tab_label_text(*vector_code_widget[get_notebook_current_page()],filename);
            vector_code_widget[get_notebook_current_page()]->_source_view.get_curr_file_funcs();
            vector_code_widget[get_notebook_current_page()]->_source_view.fill_from_include_files();
            buffer->set_language(lang);
            update_symbols();
            }
        else
        {
            creator_main.save_to_file(filepath);
            filepathsarray[notebook.get_current_page()] = filepath;
            notebook.set_tab_label_text(*vector_code_widget[notebook.get_current_page()],filename);
            }
        }
    }

void main_window::filesaveall_activated()
{
    int current_page = notebook.get_current_page();
    for (int i =0; i<notebook.get_n_pages();i++)
    {
        notebook.set_current_page(i);
        filesave_activated();
        }
    notebook.set_current_page(current_page);
    }

void main_window::filesaveallas_activated()
{
    int current_page = notebook.get_current_page();
    for (int i =0; i<notebook.get_n_pages();i++)
    {
        notebook.set_current_page(i);
        filesaveas_activated();
        }
    notebook.set_current_page(current_page);
    }

void main_window::filesavecopyas_activated()
{
    std::string filepath;
    int result;
    
    Gtk::FileChooserDialog dialog("Save As",Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Save As",Gtk::RESPONSE_OK);
    result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
    {
        filepath = dialog.get_filename();
        buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
        Glib::file_set_contents(filepath,buffer->get_text());
        }
    }

void main_window::fileremovetab_activated()
{
    int current_page = notebook.get_current_page();
    code_widget* txt= vector_code_widget[current_page];
    
    filepathsarray[current_page]="";    
    
    for(int i=current_page;i<notebook.get_n_pages()-1;i++)
    {
        vector_code_widget[i] = vector_code_widget[i+1];
        vector_code_widget[i] = vector_code_widget[i+1];
        filepathsarray[i] = filepathsarray[i+1];
        }
    notebook.remove_page(notebook.get_current_page());
    vector_code_widget.resize(vector_code_widget.size()-1);
    vector_code_widget.resize(vector_code_widget.size()-1);
    filepathsarray.resize(filepathsarray.size()-1);
    delete txt;
    show_all_children();
    }

void main_window::fileremovealltabs_activated()
{
    for(int i =notebook.get_n_pages()-1;i>=0;i--)
    {
        notebook.set_current_page(i);
        fileremovetab_activated();
        }
    }

void main_window::filequit_activated()
{
    destroy_();
    }

void main_window::editundo_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    if (buffer->can_undo() == TRUE)
        buffer->undo();
    }

void main_window::editredo_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    if (buffer->can_undo() == FALSE)
        buffer->redo();
    }

void main_window::editcopy_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    const Glib::RefPtr<Gtk::Clipboard> clipboard = Gtk::Clipboard::get();
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->copy_clipboard(clipboard);
    }

void main_window::editcut_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    const Glib::RefPtr<Gtk::Clipboard> clipboard = Gtk::Clipboard::get();
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->cut_clipboard(clipboard);
    }

void main_window::editpaste_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    const Glib::RefPtr<Gtk::Clipboard> clipboard = Gtk::Clipboard::get();
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->paste_clipboard(clipboard);
    }

void main_window::editselectall_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator start_iter,end_iter;
    start_iter = buffer->begin();
    end_iter = buffer->end();
    buffer->select_range(start_iter,end_iter);
    }

void main_window::editgotoline_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::Dialog dialog("Go To Line",*this,true,true);
    dialog.add_button(Gtk::Stock::OK,Gtk::RESPONSE_OK);
    dialog.add_button(Gtk::Stock::CANCEL,Gtk::RESPONSE_CANCEL);
    Gtk::VBox* dialog_vbox = dialog.get_vbox();
    Gtk::Label label;
    label.set_text("Go To Line");
    Gtk::Entry entry;
    dialog_vbox->pack_start(label);
    dialog_vbox->pack_start(entry);
    
    dialog.show_all_children();
    int ans = dialog.run();
    
    if (ans = Gtk::RESPONSE_OK)
    {
        buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
        Gtk::TextBuffer::iterator goto_iter;
        std::istringstream stream_line(entry.get_text());
        int line;
        stream_line>>line;
        goto_iter = buffer->get_iter_at_line(line);
        vector_code_widget[get_notebook_current_page()]->_source_view.scroll_to(goto_iter);
        }
    }


void main_window::editfind_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    find_dialog dialog(vector_code_widget[get_notebook_current_page()]->_source_view,*this);
    dialog.show_all_children();
    dialog.run();
    }

void main_window::editfindandreplace_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    find_replace_dialog dialog(vector_code_widget[get_notebook_current_page()]->_source_view,*this);
    dialog.show_all_children();
    dialog.run();
    }
void main_window::editfindinfile_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    find_in_file_dialog dialog(*this);
    dialog.show_all_children();
    dialog.run();
    }

void main_window::editfindinselectedtext_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    find_dialog dialog(vector_code_widget[get_notebook_current_page()]->_source_view,*this,true);
    dialog.show_all_children();
    dialog.run();
    }

void main_window::editfindselectedtext_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextIter start_iter,end_iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    if(buffer->get_selection_bounds(start_iter,end_iter))
    {
        std::string selected_text = buffer->get_text(start_iter,end_iter);
        start_iter = buffer->get_iter_at_mark(buffer->get_insert());
        if(start_iter.forward_search(selected_text,Gtk::TEXT_SEARCH_TEXT_ONLY,start_iter,end_iter))
        {
            buffer->select_range(start_iter,end_iter);
            vector_code_widget[get_notebook_current_page()]->_source_view.scroll_to(end_iter);
            }
        }
    }

void main_window::editregularexpressionsearch_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    reg_exp_search_dialog dialog(vector_code_widget[get_notebook_current_page()]->_source_view);
    dialog.show_all_children();
    dialog.run();
    }

void main_window::editautocompelete_activated()
{
    //vector_code_widget[get_notebook_current_page()]->_source_view;
    }

void main_window::editfoldall_activated()
{
    editunfoldall_activated();
    
    code_widget *cw = vector_code_widget[get_notebook_current_page()];
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    
    cw->_source_view.vector_fold_text.erase(cw->_source_view.vector_fold_text.begin(),cw->_source_view.vector_fold_text.end());
    std::vector<function>& vector_curr_file_func = cw->_source_view.vector_curr_file_func;
    
    for(int i = 1; i<vector_curr_file_func.size();i++)
    {
        Gtk::TextIter iter = buffer->get_iter_at_offset(vector_curr_file_func[i].pos);
        int brace_count  = 0;
        int line;
        line = iter.get_line();
        std::string line_text;
        int open_brace_offset;
        do
        {
            iter = buffer->get_iter_at_line(line);
            Gtk::TextIter line_end_iter=cw->_source_view.get_line_end_iter(line);
            line_text = buffer->get_text(iter,line_end_iter);
            line++;
            }
        while(line_text.find("{")==std::string::npos);
        open_brace_offset = iter.get_offset() + line_text.find("{");
        brace_count  = 1;
        do
        {                
            iter = buffer->get_iter_at_line(line);
            Gtk::TextIter line_end_iter=cw->_source_view.get_line_end_iter(line);
            line_text = buffer->get_text(iter,line_end_iter);
            brace_count = brace_count + cw->_source_view.count_str(line_text,cw->_source_view.open_brace)-cw->_source_view.count_str(line_text,cw->_source_view.close_brace);
            line++;
            }
        while(brace_count!=0);        
        
        int close_brace_offset = iter.get_offset()+line_text.find("}");   
        
        open_brace_offset++;
        
        Gtk::TextIter start = buffer->get_iter_at_offset(open_brace_offset);
        Gtk::TextIter end = buffer->get_iter_at_offset(close_brace_offset);
        int end_pos = end.get_offset();
        
        std::string tag_name = "TAG " + integer_to_string(cw->_source_view.vector_fold_text.size());
        Glib::RefPtr<Gtk::TextBuffer::Tag> tag = buffer->create_tag(tag_name);
        tag->property_invisible()=true;
        
        buffer->apply_tag(tag,start,end);
        start = buffer->get_iter_at_offset(open_brace_offset);
        buffer->insert(start,cw->_source_view.fold_str);
        cw->_source_view.vector_fold_text.insert(cw->_source_view.vector_fold_text.end(),fold_text(tag_name,open_brace_offset-1,end_pos));
        }
    }

void main_window::editunfoldall_activated()
{
    code_widget *cw = vector_code_widget[get_notebook_current_page()];
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    
    std::vector<fold_text>& vector_fold_text = cw->_source_view.vector_fold_text;
    for(int i = 0;i<vector_fold_text.size();i++)
    {
        Gtk::TextIter start = buffer->get_iter_at_offset(vector_fold_text[i].start_pos+1);
        Gtk::TextIter end = buffer->get_iter_at_offset(vector_fold_text[i].start_pos+1+cw->_source_view.fold_str.length());
        buffer->erase(start,end);
        Glib::RefPtr<Gtk::TextBuffer::Tag> tag = buffer->get_tag_table()->lookup(vector_fold_text[i].tag_name);
        
        tag->property_invisible()=false;   
        
        buffer->get_tag_table()->remove(tag);
        }
    vector_fold_text.erase(vector_fold_text.begin(),vector_fold_text.end());
    }

void main_window::editfoldcurrent_activated()
{
    code_widget *cw = vector_code_widget[get_notebook_current_page()];
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    
    cw->_source_view.vector_fold_text.erase(cw->_source_view.vector_fold_text.begin(),cw->_source_view.vector_fold_text.end());
    std::vector<function>& vector_curr_file_func = cw->_source_view.vector_curr_file_func;
    
    int i = cw->combo_box_func.get_active_row_number();
    Gtk::TextIter iter = buffer->get_iter_at_offset(vector_curr_file_func[i].pos);
    int brace_count  = 0;
    int line;
    line = iter.get_line();
    std::string line_text;
    int open_brace_offset;
    do
    {
        iter = buffer->get_iter_at_line(line);
        Gtk::TextIter line_end_iter=cw->_source_view.get_line_end_iter(line);
        line_text = buffer->get_text(iter,line_end_iter);
        line++;
        }
    while(line_text.find("{")==std::string::npos);
    open_brace_offset = iter.get_offset() + line_text.find("{");
    brace_count  = 1;
    do
    {                
        iter = buffer->get_iter_at_line(line);
        Gtk::TextIter line_end_iter=cw->_source_view.get_line_end_iter(line);
        line_text = buffer->get_text(iter,line_end_iter);
        brace_count = brace_count + cw->_source_view.count_str(line_text,cw->_source_view.open_brace)-cw->_source_view.count_str(line_text,cw->_source_view.close_brace);
        line++;
        }
    while(brace_count!=0);        
    
    int close_brace_offset = iter.get_offset()+line_text.find("}");   
    
    open_brace_offset++;
    
    Gtk::TextIter start = buffer->get_iter_at_offset(open_brace_offset);
    Gtk::TextIter end = buffer->get_iter_at_offset(close_brace_offset);
    int end_pos = end.get_offset();
    
    std::string tag_name = "TAG " + integer_to_string(cw->_source_view.vector_fold_text.size());
    Glib::RefPtr<Gtk::TextBuffer::Tag> tag = buffer->create_tag(tag_name);
    tag->property_invisible()=true;
    
    buffer->apply_tag(tag,start,end);
    start = buffer->get_iter_at_offset(open_brace_offset);
    buffer->insert(start,cw->_source_view.fold_str);
    cw->_source_view.vector_fold_text.insert(cw->_source_view.vector_fold_text.end(),fold_text(tag_name,open_brace_offset-1,end_pos));        
    }
   
void main_window::formatindentregion_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextBuffer::iterator start_iter,end_iter,iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_iter_line =  start_iter.get_line(),end_iter_line = end_iter.get_line(),start_iter_offset = start_iter.get_line_offset(), i;
    int indent_width = 4; //Remember to add indent width
    for (i=0;i<indent_width;i++)
    {
        buffer->insert(start_iter," ");
        start_iter = buffer->get_iter_at_line_offset(start_iter_line,start_iter_offset);
        } 
    for(i=start_iter_line+1;i<=end_iter_line;i++)
    {
        iter = buffer->get_iter_at_line_offset(i,0);
        for (int j=0;j<indent_width;j++)
        {
            iter = buffer->get_iter_at_line_offset(i,0);
            buffer->insert(iter," ");
            }
        }
    }

void main_window::formatdedentregion_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextBuffer::iterator start_iter,end_iter,line_start_iter,line_indent_width_iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_iter_line =  start_iter.get_line(),end_iter_line = end_iter.get_line(),start_iter_offset = start_iter.get_line_offset(), i;
    int indent_width = 4; //Remember to add indent width
    if (start_iter.get_line_offset()>=indent_width)
        buffer->erase(start_iter,buffer->get_iter_at_offset(start_iter.get_offset()-indent_width));
    else
        buffer->erase(start_iter,buffer->get_iter_at_offset(start_iter.get_offset()+indent_width));
    for(i=start_iter_line+1;i<=end_iter_line;i++)
    {
        buffer->erase(buffer->get_iter_at_line_offset(i,0),buffer->get_iter_at_line_offset(i,indent_width));
        }
    }

void main_window::formatcommentout_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextBuffer::iterator start_iter,end_iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_offset = start_iter.get_offset();
    buffer->insert(end_iter,"*/");
    buffer->insert(buffer->get_iter_at_offset(start_offset),"/*");
    }

void main_window::formatsinglecommentout_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextBuffer::iterator start_iter,end_iter,iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_iter_line =  start_iter.get_line(),end_iter_line = end_iter.get_line(),start_iter_offset = start_iter.get_line_offset(), i;
    int indent_width = 2; //Remember to add indent width
    for (i=0;i<indent_width;i++)
    {
        buffer->insert(start_iter,"/");
        start_iter = buffer->get_iter_at_line_offset(start_iter_line,start_iter_offset);
        } 
    for(i=start_iter_line+1;i<=end_iter_line;i++)
    {
        iter = buffer->get_iter_at_line_offset(i,0);
        for (int j=0;j<indent_width;j++)
        {
            iter = buffer->get_iter_at_line_offset(i,0);
            buffer->insert(iter,"/");
            }
        }
    }

void main_window::formatsingleuncommentout_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextBuffer::iterator start_iter,end_iter,line_start_iter,line_indent_width_iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_iter_line =  start_iter.get_line(),end_iter_line = end_iter.get_line(),start_iter_offset = start_iter.get_line_offset(), i;
    int indent_width = 2; //Remember to add indent width
    if (start_iter.get_line_offset()>=indent_width)
        buffer->erase(start_iter,buffer->get_iter_at_offset(start_iter.get_offset()-indent_width));
    else
        buffer->erase(start_iter,buffer->get_iter_at_offset(start_iter.get_offset()+indent_width));
    for(i=start_iter_line+1;i<=end_iter_line;i++)
    {
        buffer->erase(buffer->get_iter_at_line_offset(i,0),buffer->get_iter_at_line_offset(i,indent_width));
        }
    }

void main_window::formatuncommentout_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextBuffer::iterator start_iter,end_iter;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_offset = start_iter.get_offset(), end_offset = end_iter.get_offset();
    std::string start_text = buffer->get_text(start_iter,buffer->get_iter_at_offset(start_iter.get_offset()+2));
    std::string end_text = buffer->get_text(end_iter,buffer->get_iter_at_offset(end_iter.get_offset()-2));
    if(start_text == "/*" && end_text == "*/")
    {
        buffer->erase(end_iter,buffer->get_iter_at_offset(end_iter.get_offset()-2));
        buffer->erase(buffer->get_iter_at_offset(start_offset),buffer->get_iter_at_offset((start_offset)+2));
        }
    }

void main_window::formatstripspaces_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator start_iter,end_iter;
    for(int i =0;i<buffer->get_line_count()-1;i++)
    {
        start_iter = buffer->get_iter_at_line(i);
        end_iter = buffer->get_iter_at_line(i+1);
        end_iter = buffer->get_iter_at_offset(end_iter.get_offset()-1);
        std::string line_string = buffer->get_text(start_iter,end_iter,false);
        std::string::const_iterator str_iter = line_string.end();
        int j = line_string.length()-1;
        str_iter--;
        while(*str_iter==' ')
        {
            j--;
            str_iter--;
            }
        start_iter = buffer->get_iter_at_line_offset(i,j+1);
        buffer->erase(start_iter,end_iter);
        }
    start_iter = buffer->get_iter_at_line(buffer->get_line_count()-1);
    end_iter= buffer->end();
    std::string line_string = buffer->get_text(start_iter,end_iter,false);
    std::string::const_iterator str_iter = line_string.end();
    int j = line_string.length()-1;
    str_iter--;
    while(*str_iter==' ')
    {
        j--;
        str_iter--;
        }
    start_iter = buffer->get_iter_at_line_offset(buffer->get_line_count()-1,j+1);
    buffer->erase(start_iter,end_iter);
    }

void main_window::formattabify_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter start_iter, end_iter;
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_line = start_iter.get_line(), end_line = end_iter.get_line();
    for(int i = start_line;i<=end_line;i++)
    {
        start_iter = buffer->get_iter_at_line(i);
        end_iter =buffer->get_iter_at_line(i+1);
        std::string line_text = buffer->get_text(start_iter, end_iter,false);
        std::string::const_iterator str_iter = line_text.begin();
        int count_spaces=0;
        str_iter  = line_text.begin();
        while(*str_iter++==' ')
            count_spaces++;
        end_iter = buffer->get_iter_at_line_offset(i,count_spaces);
        buffer->erase_interactive(start_iter,end_iter);
        for(int j = 0;j<count_spaces/tab_width;j++)
             buffer->insert(buffer->get_iter_at_line(i),"\t");
        }
    }

void main_window::formatuntabify_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter start_iter, end_iter;
    buffer->get_selection_bounds(start_iter,end_iter);
    int start_line = start_iter.get_line(), end_line = end_iter.get_line();
    for(int i = start_line;i<=end_line;i++)
    {
        start_iter = buffer->get_iter_at_line(i);
        end_iter =buffer->get_iter_at_line(i+1);
        std::string line_text = buffer->get_text(start_iter, end_iter,false);
        std::string::const_iterator str_iter = line_text.begin();
        int count_tabs=0;
        str_iter  = line_text.begin();
        while(*str_iter++=='\t')
            count_tabs++;
        end_iter = buffer->get_iter_at_line_offset(i,count_tabs);
        buffer->erase_interactive(start_iter,end_iter);
        for(int j = 0;j<count_tabs*tab_width;j++)
             buffer->insert(buffer->get_iter_at_line(i)," ");
        }
    }

void main_window::formatuppercase_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextIter start_iter,end_iter;
    Glib::RefPtr<Gtk::TextBuffer> txtbuffer  = vector_code_widget[get_notebook_current_page()]->_source_view.get_buffer();
    if(!txtbuffer->get_selection_bounds(start_iter,end_iter))
        return;
    
    Glib::ustring selected_text = txtbuffer->get_text(start_iter,end_iter);
    selected_text = selected_text.uppercase();
    int start_offset = start_iter.get_offset();
    txtbuffer->erase_selection();
    txtbuffer->insert(txtbuffer->get_iter_at_offset(start_offset),selected_text);
    }

void main_window::formatlowercase_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    Gtk::TextIter start_iter,end_iter;
    Glib::RefPtr<Gtk::TextBuffer> txtbuffer  = vector_code_widget[get_notebook_current_page()]->_source_view.get_buffer();
    if(!txtbuffer->get_selection_bounds(start_iter,end_iter))
        return;
    
    Glib::ustring selected_text = txtbuffer->get_text(start_iter,end_iter);
    selected_text = selected_text.lowercase();
    int start_offset = start_iter.get_offset();
    txtbuffer->erase_selection();
    txtbuffer->insert(txtbuffer->get_iter_at_offset(start_offset),selected_text);
    }

void main_window::format_show_parenthesis_activated()
{
    buffer  = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter iter;
    iter = buffer->get_iter_at_mark(buffer->get_insert());
    Gtk::TextIter line_start_iter,line_end_iter;
    line_start_iter = buffer->get_iter_at_line(iter.get_line());
    line_end_iter = buffer->get_iter_at_line(iter.get_line()+1);
    line_end_iter=buffer->get_iter_at_offset(line_end_iter.get_offset()-1);
    std::string line_text = buffer->get_text(line_start_iter,line_end_iter);
    int current_line_offset = iter.get_line_offset();
    int i,open_bracket_count=0,close_bracket_count=0;
    for (i=0;i<line_text.size();i++)
    {
        if(line_text[i]=='(')
            open_bracket_count++;
        if (line_text[i]==')')
            close_bracket_count++;
        }
    int open_array[open_bracket_count],close_array[close_bracket_count];
    int j=0,k=0;
    int open_bracket_before=0,open_bracket_after=0,close_bracket_after=0,close_bracket_before=0,closest_open_bracket=0;
    for (i=0;i<line_text.length();i++)
    {
        if(line_text[i]=='(')
        {
            open_array[j++] = i;
            if (i<current_line_offset)
            {
                closest_open_bracket = i;
                open_bracket_before++;
                }
            else
                open_bracket_after++;
            }
        if (line_text[i]==')')
        {
            close_array[k++] = i;
            if (i>current_line_offset)
                close_bracket_after++;
            }
        }
    for (i=0;i<close_bracket_count;i++)
    {
        if(close_array[i]>closest_open_bracket&&close_array[i]<current_line_offset)
            close_bracket_before++;
        }
    Gtk::TextIter bracket_start_iter,bracket_close_iter;
    bracket_start_iter = buffer->get_iter_at_line_offset(iter.get_line(),open_array[open_bracket_before-close_bracket_before-1]);
    bracket_close_iter = buffer->get_iter_at_line_offset(iter.get_line(),close_array[close_bracket_count-close_bracket_after+open_bracket_after]);
    buffer->select_range(bracket_start_iter,bracket_close_iter);
    }

void main_window::navigation_back_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    vector_code_widget[get_notebook_current_page()]->_source_view.navigate_back();
    }

void main_window::navigation_forward_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    vector_code_widget[get_notebook_current_page()]->_source_view.navigate_forward();
    }

void main_window::navigation_start_of_file_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer= vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter it = buffer->begin();
    vector_code_widget[get_notebook_current_page()]->_source_view.scroll_to(it);
    }

void main_window::navigation_end_of_file_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    buffer= vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter it = buffer->end();
    vector_code_widget[get_notebook_current_page()]->_source_view.scroll_to(it);
    }

void main_window::navigation_go_to_brace_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    
    buffer= vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter iter = buffer->get_iter_at_mark(buffer->get_insert());
    int brace_count;
    std::string text = buffer->get_text();
    if(iter.get_char()=='{')
    {
        brace_count=1;
        int offset = iter.get_offset()+1;
        while(brace_count!=0)
        {
            if(text[offset]=='{')
                brace_count++;
            else if(text[offset]=='}')
                brace_count--;
            offset++;
            }
        
        iter = buffer->get_iter_at_offset(offset);
        buffer->place_cursor(iter);
        }
    else if(iter.get_char()=='}')
    {
        brace_count=-1;
        int offset = iter.get_offset()-1;
        while(brace_count!=0)
        {
            if(text[offset]=='{')
                brace_count++;
            else if(text[offset]=='}')
                brace_count--;
            offset--;
            }
        
        iter = buffer->get_iter_at_offset(offset+1);
        buffer->place_cursor(iter);
        }
    }

void main_window::navigation_declaration_activated()
{
    int active = vector_code_widget[get_notebook_current_page()]->combo_box_func.get_active_row_number();
    if(active==-1)
       return;
    int i;
    code_widget *cw = vector_code_widget[get_notebook_current_page()];
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    std::string text = buffer->get_text();
    
    Glib::RefPtr<Glib::Regex> regex_func_dec;
    Glib::MatchInfo match_info_func_dec;    
    regex_func_dec = Glib::Regex::create("[\\w*]+[\\s*]+[\\w*]+\\(+.+\\)\\s*;");
    if(!regex_func_dec->match(text,match_info_func_dec))
    {
        std::cout<<"Not Found Any Function Declartion"<<std::endl;
        return;
        }
    do
    {
        std::string func_dec = match_info_func_dec.fetch(0);
        if (func_dec.find("\n")!=std::string::npos || func_dec.find("\"")!=std::string::npos)
            continue;
        
        func_dec = func_dec.substr(0,func_dec.find(";"));
        if(function(func_dec,0)==cw->_source_view.vector_curr_file_func[active])
        {
            int start,end;
            match_info_func_dec.fetch_pos(0,start,end);
            Gtk::TextIter iter = buffer->get_iter_at_offset(start);
            buffer->select_range(iter,cw->_source_view.get_line_end_iter(iter.get_line()));
            return;
            }
        }
    while(match_info_func_dec.next());    
    }

void main_window::navigation_definition_activated()
{
    int active = vector_code_widget[get_notebook_current_page()]->combo_box_func.get_active_row_number();
    if(active==-1)
       return;
    int i;
    code_widget *cw = vector_code_widget[get_notebook_current_page()];
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    
    Gtk::TextIter iter = buffer->get_iter_at_mark(buffer->get_insert());
    std::string line_text = buffer->get_text(iter,cw->_source_view.get_line_end_iter(iter.get_line()));
    
    Glib::RefPtr<Glib::Regex> regex_func_dec;
    Glib::MatchInfo match_info_func_dec;    
    regex_func_dec = Glib::Regex::create("[\\w*]+[\\s*]+[\\w*]+\\(+.+\\)\\s*;");
    if(!regex_func_dec->match(line_text,match_info_func_dec))
         return;
    
    function func_def = function(match_info_func_dec.fetch(0),0);
    for(int i =0;i<cw->_source_view.vector_curr_file_func.size();i++)
    {
        if(cw->_source_view.vector_curr_file_func[i]==func_def)
        {
            Gtk::TextIter iter = buffer->get_iter_at_offset(cw->_source_view.vector_curr_file_func[i].pos);
            buffer->select_range(iter,cw->_source_view.get_line_end_iter(iter.get_line()));
            break;
            }
        }
    }

void main_window::navigation_add_bookmark_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    bookmark_menu_item_vector.resize(bookmark_menu_item_vector.size()+1);
    buffer = vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Gtk::TextIter iter = buffer->get_iter_at_mark(buffer->get_insert());
    std::string filename = notebook.get_tab_label_text(*vector_code_widget[get_notebook_current_page()]);
    bookmark_menu_item* _b = new bookmark_menu_item(bookmark_menu_item_group,iter.get_line(),filename);
    bookmark_menu_item_vector[bookmark_menu_item_vector.size()-1] = _b;
    _b->signal_activate().connect(sigc::bind<bookmark_menu_item*>(sigc::mem_fun(*this,&main_window::bookmark_menu_item_activated),_b));
    navigation_menu->append(*_b);
    show_all_children();
    }

void main_window::navigation_clear_bookmark_activated()
{    
    if(notebook.get_n_pages()==0)
         return;
    for(int i =0;i<bookmark_menu_item_vector.size();i++)
    {
        navigation_menu->remove(*bookmark_menu_item_vector[i]);
        delete bookmark_menu_item_vector[i];
        }
    bookmark_menu_item_vector.resize(0);
    }

void main_window::navigation_next_bookmark_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    int i;
    for(i =0;i<bookmark_menu_item_vector.size();i++)
        if(bookmark_menu_item_vector[i]->get_active())
             break;
    
    if(i==bookmark_menu_item_vector.size())
        return;
    
    bookmark_menu_item_vector[i+1]->activate();
    }

void main_window::navigation_prev_bookmark_activated()
{
    if(notebook.get_n_pages()==0)
         return;
    int i;
    for(i =0;i<bookmark_menu_item_vector.size();i++)
        if(bookmark_menu_item_vector[i]->get_active())
             break;
    
    if(i==bookmark_menu_item_vector.size())
        return;
    
    bookmark_menu_item_vector[i-1]->activate();
    }        

void main_window::bookmark_menu_item_activated(bookmark_menu_item* _item)    
{
    int line = _item->line;
    std::string filename = _item->filename;
    for(int i = 0;i<notebook.get_n_pages();i++)
        if(filename==notebook.get_tab_label_text(*vector_code_widget[i]))
        {
            buffer = vector_code_widget[i]->_source_view.get_source_buffer();
            Gtk::TextIter iter = buffer->get_iter_at_line(line);
            buffer->place_cursor(iter);
            vector_code_widget[i]->_source_view.scroll_to(iter);
            break;
            }
    }

void main_window::on_proj_tree_view_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
    Glib::ustring path_str = path.to_string();
    std::string str_index = path_str.substr(path_str.find(':')+1);
    int index = string_to_integer(str_index);    
    
    std::string filepath = current_proj.file_path_vector[index];    
    std::string filename;
    for(int i=filepath.rfind("/")+1;i<=filepath.size()-1;i++)
        filename  = filename + filepath[i];
        
    for(int i =0;i<filepathsarray.size();i++)
    {
        std::string path = filepathsarray[i];
        std::string name;
        for(int j=path.rfind("/")+1;j<=path.size()-1;j++)
            name  = name + path[j];
        if(filename==name)
        {
            notebook.set_current_page(i);
            return;
            }
        }
    std::string text;
    try
    {
        text = Glib::file_get_contents(filepath);
        }
    catch(Glib::FileError e)
    {
        Gtk::MessageDialog msg_dialog("Cannot find the specified file.");
        msg_dialog.run();
        return;
        }
    if(filepath.find(".glade")!=std::string::npos)
    {
        creator_main.open_file(filepath);
        filepathsarray.resize(filepathsarray.size()+1);        
        filepathsarray[notebook.get_n_pages()] = filepath;
        notebook.append_page(creator_main,filename);
        notebook.show_all_children();
        notebook.set_current_page(notebook.get_n_pages()-1);
        }
    else
    {    
        filenewtab_activated();    
        int i=0;
        for(i=0;i<notebook.get_current_page();i++)
        {
            if(filepathsarray[i].find(".glade")!=std::string::npos)
            {
                i+=1;
                break;
                }
            }    
        buffer=vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
        buffer->set_text(text);
        vector_code_widget[get_notebook_current_page()]->_source_view.get_curr_file_funcs();
        vector_code_widget[notebook.get_current_page()]->_source_view.fill_from_include_files();
        update_symbols();
        filepathsarray[notebook.get_n_pages()-1] = filepath;
        buffer->set_highlight_syntax(true);
        Glib::RefPtr<gtksourceview::SourceLanguage> lang = lang_manager->guess_language(filepath,Glib::ustring());
        notebook.set_tab_label_text(*vector_code_widget[get_notebook_current_page()],filename);
        buffer->set_language(lang);
        }   
    }

void main_window::save_recent_projs()
{
    if(!recent_projects)
        return;
    
    std::string contents = "";
    for(int i = 0; i <recent_projs;i++)
    {
        if(recent_proj_paths[i]!="")
             contents+="<proj>"+recent_proj_paths[i]+"</proj>\n";
        }
    Glib::file_set_contents("./recent_projs.ini",contents);
    }

void main_window::load_recent_projs()
{
    if(!recent_projects)
        return;
    std::string str="";
    try 
    {
         str = Glib::file_get_contents("./recent_projs.ini");
        }
    catch(...){}       
    
    int pos_start = -1;
    int pos_end = 0;
    int count = 0;    
    project_menu->append(project_sep);
    while((pos_start=str.find("<proj>",pos_start+1))!=-1 && (pos_end=str.find("</proj>",pos_end+1))!=-1)
    {
        recent_proj_paths[count] = str.substr(pos_start+6,pos_end-pos_start-6);  
        std::string filename;
        for(int i=recent_proj_paths[count].rfind("/")+1;i<=recent_proj_paths[count].size()-1;i++)
            filename  = filename + recent_proj_paths[count][i];
        Gtk::MenuItem* recent_proj_menu_item  = new Gtk::MenuItem(filename);
        recent_proj_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_proj_menu_item_clicked),recent_proj_menu_item));
        project_menu->append(*recent_proj_menu_item);
        recent_proj_menu_items[count]=recent_proj_menu_item;
        count++;
        }
    }

void main_window::update_recent_project_menu(std::string proj_name,std::string proj_path)
{
    int i=0,j=0;
    for(i =0;i<recent_projs;i++)
    {
        if(!recent_proj_menu_items[i])
             break;
        }
        
    if(i==recent_projs)
       return;
    if(i==0)
        project_menu->append(project_sep);
        
    for(j=0;j<i;j++)
    {
        if(Glib::ustring(proj_name)==recent_proj_menu_items[j]->get_label())
            break;
        }
    if(i==0)
    {
        Gtk::MenuItem* recent_proj_menu_item  = new Gtk::MenuItem(proj_name);
        recent_proj_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_proj_menu_item_clicked),recent_proj_menu_item));
        
        recent_proj_menu_items[0] = recent_proj_menu_item;
        recent_proj_paths[0]=proj_path;
        project_menu->append(*recent_proj_menu_items[0]);
        }
    else if(j==i)
    {
        Gtk::MenuItem* recent_proj_menu_item  = new Gtk::MenuItem(proj_name);
        recent_proj_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_proj_menu_item_clicked),recent_proj_menu_item));

        for(int k = 0;k<i;k++)
           project_menu->remove(*recent_proj_menu_items[k]);
        
        for(int k = i;k>0;k--)
        {
            recent_proj_menu_items[k]=recent_proj_menu_items[k-1];
            recent_proj_paths[k] = recent_proj_paths[k-1];
            }
            
        recent_proj_menu_items[0] = recent_proj_menu_item;
        recent_proj_paths[0]=proj_path;
        for(int k=0;k<i+1;k++)
            project_menu->append(*recent_proj_menu_items[k]);
        }
    else
    {
        Gtk::MenuItem* recent_proj_menu_item  = new Gtk::MenuItem(proj_name);
        recent_proj_menu_item->signal_activate().connect(sigc::bind<Gtk::MenuItem*>(sigc::mem_fun(*this,&main_window::recent_proj_menu_item_clicked),recent_proj_menu_item));
        
        Gtk::MenuItem* item = recent_proj_menu_items[i];
        for(int k = 0;k<i;k++)
           project_menu->remove(*recent_proj_menu_items[k]);
        
        if(item)
            delete item;
            
        for(int k = j;k>0;k--)
        {
            recent_proj_menu_items[k]=recent_proj_menu_items[k-1];
            recent_proj_paths[k] = recent_proj_paths[k-1];
            }
            
        recent_proj_menu_items[0] = recent_proj_menu_item;
        recent_proj_paths[0]=proj_path;
        for(int k=0;k<i;k++)
            project_menu->append(*recent_proj_menu_items[k]);
        }
    show_all_children();
    save_recent_projs();
    }

void main_window::recent_proj_menu_item_clicked(Gtk::MenuItem* menu_item)
{    
    int i;
    for( i = 0;i<recent_projs;i++)
    {
        if(recent_proj_menu_items[i]&& recent_proj_menu_items[i]==menu_item)
            break;
        }
    filepathsarray.erase(filepathsarray.begin(),filepathsarray.end());
    
    std::string filepath = recent_proj_paths[i];
    std::string str;
    try
    {
        str = Glib::file_get_contents(filepath);
        }
    catch(Glib::FileError e)
    {
        Gtk::MessageDialog message_dialog(*this,"Cannot find "+filepath);
        message_dialog.run();
        return;
        }
    
    for(int i =notebook.get_n_pages()-1;i>=0;i--)
    {
        notebook.remove_page(*vector_code_widget[i]);
        delete vector_code_widget[i];
        }
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    current_proj.clear();
    
    current_proj.set_path(filepath);
    current_proj.set_data_from_string(str);
    tree_model->clear();
    Gtk::TreeModel::Row row = *(tree_model->append());
    parent_row=row;
    row[model_columns.col]=current_proj.get_name();
    Gtk::TreeModel::Row child_row;
    for(int i = 0;i<current_proj.file_path_vector.size();i++)
    {
        child_row = *(tree_model->append(row.children()));
        std::string filename = current_proj.file_path_vector[i].substr(current_proj.file_path_vector[i].rfind("/")+1);
        child_row[model_columns.col]= filename;
        }        
    
    vector_code_widget[get_notebook_current_page()]->_source_view.set_filename(filepath);
    vector_code_widget[get_notebook_current_page()]->_source_view.get_curr_file_funcs();
    vector_code_widget[get_notebook_current_page()]->_source_view.fill_from_include_files();
    
    mode="PROJECT";    
    window_project_activated();
    proj_tree_view.show_all_children();
    update_recent_project_menu(current_proj.get_name(),current_proj.get_path());
    }

void main_window::project_new()
{
    new_project_dialog dialog(*this);
    dialog.show_all_children();
    dialog.run();
    if(dialog.return_val == 0)
        return;
    
    filepathsarray.erase(filepathsarray.begin(),filepathsarray.end());
    
    for(int i =notebook.get_n_pages()-1;i>=0;i--)
    {
        notebook.remove_page(*vector_code_widget[i]);
        delete vector_code_widget[i];
        }
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    current_proj.clear();
    
    std::string proj_name = dialog.get_proj_name();
    std::string proj_location = dialog.get_proj_location();
    std::string proj_type = dialog.get_proj_type();
    std::string proj_file_str = "<name>"+proj_name+"</name>\n"+"<type>"+proj_type+"</type>\n"+"<location>"+proj_location+"</location>\n";
    std::string proj_file_path = proj_location + "/" + proj_name+".gtk_proj";
    
    current_proj.set_name(proj_name);
    current_proj.set_location(proj_location);
    current_proj.set_type(proj_type);
    current_proj.set_path(proj_file_path);
    
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(proj_location+"/");
    if(!file->make_directory_with_parents())
        return;
    Glib::file_set_contents(proj_file_path,proj_file_str);    
    tree_model->clear();
    Gtk::TreeModel::Row row = *(tree_model->append());
    row[model_columns.col]=proj_name;
    parent_row=row;
    
    if(proj_type == "Console C Project")
    {
        Glib::file_set_contents(proj_file_path,proj_file_str);    
        Glib::file_set_contents(proj_location+"/main.c","");    
        row = *(tree_model->append(row.children()));
        row[model_columns.col]="main.c";
        current_proj.append_file(proj_location+"/main.c");
        }
    else if(proj_type=="GTK+ Console Project")
    {
        Glib::file_set_contents(proj_file_path,proj_file_str);    
        std::string contents;
        contents = Glib::file_get_contents("./gtk_console_main.c");
        Glib::file_set_contents(proj_location+"/main.c",contents);    
        row = *(tree_model->append(row.children()));
        row[model_columns.col]="main.c";
        current_proj.append_file(proj_location+"/main.c");
        current_proj.set_other_args("-o `pkg-config --cflags --libs gtk+-2.0 gtksourceview-2.0 vte`");
        }
    else if(proj_type=="GTK+ GUI Project")
    {        
        std::string contents;
        contents = Glib::file_get_contents("./gtk_gui_main.c");
        Glib::file_set_contents(proj_location+"/main.c",contents);
        contents = Glib::file_get_contents("./gtk_gui_glade.glade");
        Glib::file_set_contents(proj_location+"/interface.glade",contents);
        Gtk::TreeModel::Row child_row = *(tree_model->append(row.children()));
        child_row[model_columns.col]="main.c";
        child_row = *(tree_model->append(row.children()));
        child_row[model_columns.col]="interface.glade";
        current_proj.append_file(proj_location+"/main.c");
        current_proj.append_file(proj_location+"/interface.glade");
        current_proj.set_other_args("-o `pkg-config --cflags --libs gtk+-2.0 gtksourceview-2.0 vte` `pkg-config --cflags --libs libglade-2.0`");
        }
    Glib::file_set_contents(proj_file_path,current_proj.get_project_str());    
    
    mode="PROJECT";    
    window_project_activated();
    proj_tree_view.show_all_children();
    update_recent_project_menu(current_proj.get_name(),current_proj.get_path());
    }

void main_window::project_open()
{    
    Gtk::FileChooserDialog dialog("Open File",Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Open",Gtk::RESPONSE_OK);
    
    Gtk::FileFilter file_filter_c,file_filter_all,file_filter_h;
    file_filter_c.add_pattern("*.gtk_proj");
    file_filter_all.add_pattern("*.*");
    
    file_filter_c.set_name("GTK+ Project(*.gtk_proj)");
    file_filter_all.set_name("All Files(*.*)");
    
    dialog.add_filter(file_filter_c);
    dialog.add_filter(file_filter_all);
    
    int result = dialog.run();
    std::string filename;
    if(result == Gtk::RESPONSE_OK)
    {
        filepathsarray.erase(filepathsarray.begin(),filepathsarray.end());
        
        //std::cout<<notebook.get_n_pages()<<std::endl;
        for(int i =notebook.get_n_pages()-1;i>=0;i--)
        {
            notebook.remove_page(*vector_code_widget[i]);
            delete vector_code_widget[i];
            }
        vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
        vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
        current_proj.clear();
        
        std::string filepath = dialog.get_filename();
        current_proj.set_path(filepath);
        std::string str = Glib::file_get_contents(filepath);
        current_proj.set_data_from_string(str);
        tree_model->clear();
        Gtk::TreeModel::Row row = *(tree_model->append());
        parent_row=row;
        row[model_columns.col]=current_proj.get_name();
        Gtk::TreeModel::Row child_row;
        for(int i = 0;i<current_proj.file_path_vector.size();i++)
        {
            child_row = *(tree_model->append(row.children()));
            filename = current_proj.file_path_vector[i].substr(current_proj.file_path_vector[i].rfind("/")+1);
            child_row[model_columns.col]= filename;
            }        
        mode="PROJECT";    
        window_project_activated();
        proj_tree_view.show_all_children();
        update_recent_project_menu(current_proj.get_name(),current_proj.get_path());
        }        
    }

void main_window::project_add_new()
{
     if(mode=="FILE")
        return;
        
    Glib::ustring filepath;
    int result;
    
    Gtk::FileChooserDialog dialog("Save As",Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_current_folder(current_proj.get_location());
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Save As",Gtk::RESPONSE_OK);
    Gtk::FileFilter file_filter_c,file_filter_all,file_filter_h;
    file_filter_c.add_pattern("*.c");
    file_filter_all.add_pattern("*.*");
    file_filter_h.add_pattern("*.h");
    
    file_filter_c.set_name("C Files(*.c)");
    file_filter_all.set_name("All Files(*.*)");
    file_filter_h.set_name("C Header Files(*.h)");
    
    dialog.add_filter(file_filter_c);
    dialog.add_filter(file_filter_h);
    dialog.add_filter(file_filter_all);
    
    result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
    {
        filepath = dialog.get_filename();
        Gtk::TreeModel::Row child_row;
        child_row = *(tree_model->append(parent_row.children()));
        std::string filename = filepath.substr(filepath.rfind("/")+1);
        child_row[model_columns.col]=filename;
        current_proj.append_file(filepath);
        Glib::file_set_contents(filepath,"");
        }
    }

void main_window::project_add_existing()
{
    if(mode=="FILE")
        return;
        
    Glib::ustring filepath;
    int result;
    
    Gtk::FileChooserDialog dialog("Open File",Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_current_folder(current_proj.get_location());
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Open",Gtk::RESPONSE_OK);
    
    Gtk::FileFilter file_filter_c,file_filter_all,file_filter_h;
    file_filter_c.add_pattern("*.c");
    file_filter_all.add_pattern("*.*");
    file_filter_h.add_pattern("*.h");
    
    file_filter_c.set_name("C Files(*.c)");
    file_filter_all.set_name("All Files(*.*)");
    file_filter_h.set_name("C Header Files(*.h)");
    
    dialog.add_filter(file_filter_c);
    dialog.add_filter(file_filter_h);
    dialog.add_filter(file_filter_all);
    
    result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
    {
        filepath = dialog.get_filename();
        Gtk::TreeModel::Row child_row;
        child_row = *(tree_model->append(parent_row.children()));
        std::string filename = filepath.substr(filepath.rfind("/")+1);
        child_row[model_columns.col]=filename;
        current_proj.append_file(filepath);
        }
    }

void main_window::project_save()
{
    if(mode=="FILE")
        return;
        
    for(int i = 0; i<notebook.get_n_pages();i++)
    {
        buffer = vector_code_widget[i]->_source_view.get_source_buffer();
        Glib::file_set_contents(filepathsarray[i],buffer->get_text());        
        }
    }

void main_window::project_save_as()
{
    if(mode=="FILE")
        return;
        
    project_save_as_dialog dialog(*this);
    dialog.show_all_children();
    if(dialog.run()==1)
    {
        current_proj.set_name(dialog.entry_name.get_text());
        current_proj.set_location(dialog.entry_location.get_text());
        current_proj.set_path(current_proj.get_location()+"/"+current_proj.get_name()+".gtk_proj");
        current_proj.set_files_to_location();
        Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(current_proj.get_location()+"/");
        if(!file->make_directory_with_parents())
            return;
        filesaveall_activated();
        for(int i = 0;i<current_proj.file_path_vector.size();i++)
        {
            Glib::ustring filepath = current_proj.file_path_vector[i];
            std::string filename = filepath.substr(filepath.rfind("/")+1);
            std::string new_filepath = current_proj.get_location()+"/"+filename;
            std::string contents = Glib::file_get_contents(filepath);
            Glib::file_set_contents(new_filepath,contents);
            }
        std::string proj_str = current_proj.get_project_str();
        current_proj.write_to_file();
        parent_row[model_columns.col] = current_proj.get_name();
        }
    }

void main_window::project_save_copy_as()
{
    if(mode=="FILE")
        return;
    
    
    }

void main_window::project_preferences()
{
    if(mode=="FILE")
        return;
        
    proj_pref_dialog dialog(*this,current_proj);
    dialog.show_all_children();
    if(dialog.run()==1)
    {
        std::string location = current_proj.get_location();
        std::string prev_path = current_proj.get_path();
        //Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(prev_path);
        ///file->remove();
        current_proj.clear();
        tree_model->clear();
        
        current_proj.set_location(location);
        current_proj.set_name(dialog.entry_name.get_text());
        current_proj.set_type(dialog.lbl_proj_type.get_label());
        current_proj.set_path(prev_path);
        
        parent_row = *(tree_model->append());
        parent_row[model_columns.col]=current_proj.get_name();
        
        Gtk::TreeIter iter = dialog.file_tree_model->children().begin();
        while(iter)
        {
            Gtk::TreeModel::Row row = *(tree_model->append(parent_row.children()));
            std::string filepath = (*iter).get_value(dialog.file_columns.m_col);
            std::string filename = filepath.substr(filepath.rfind("/")+1);
            row[model_columns.col] = filename;
            current_proj.append_file((*iter).get_value(dialog.file_columns.m_col));
            iter++;
            }
        current_proj.set_compile_only(dialog.chk_compile_only.get_active());
        current_proj.set_compile_only(dialog.chk_warning.get_active());
        current_proj.set_disable_inline(dialog.chk_inline.get_active());
        current_proj.set_support_c89(dialog.chk_support_89.get_active());
        current_proj.set_compile_assemble(dialog.chk_compile_assemble.get_active());
        current_proj.set_optimize(dialog.chk_optimize.get_active());
        current_proj.set_add_dir(dialog.chk_add_dir.get_active());
        if(current_proj.get_add_dir())
        {
            iter = dialog.dir_tree_model->children().begin();
            while(iter)
            {                
                current_proj.vector_dir.insert(current_proj.vector_dir.end(),(*iter).get_value(dialog.dir_columns.m_col));
                iter++;
                }
            }
        current_proj.set_define_symbols(dialog.chk_symbols.get_active());
        if(current_proj.get_define_symbols())
            current_proj.symbols = dialog.entry_symbols.get_text();
            
        current_proj.set_run_on_ext_console(dialog.chk_ext_console.get_active());
        current_proj.set_optimize_level(dialog.spin_optimize.get_value());
        current_proj.set_out_dir(dialog.entry_out_dir.get_text());
        current_proj.set_params(dialog.entry_param.get_text());
        current_proj.set_curr_dir(dialog.entry_curr_dir.get_text());
        current_proj.set_other_args(dialog.entry_other_args.get_text());
        iter = dialog.env_tree_model->children().begin();
        while(iter)
        {
            current_proj.env_var_vector.insert(current_proj.env_var_vector.end(),env_var((*iter).get_value(dialog.env_columns.m_col_name),(*iter).get_value(dialog.env_columns.m_col_value)));
            iter++;
            }
        current_proj.write_to_file();
        }    
    }

void main_window::project_empty()
{
    if(mode=="FILE")
        return;
    
    Gtk::MessageDialog dialog(*this,Glib::ustring("Are you sure you want to empty the current project?"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
    if(dialog.run()==Gtk::RESPONSE_NO)
        return;
    
    for(int i = 0;i<current_proj.file_path_vector.size();i++)
    {
        std::string file_path = current_proj.file_path_vector[i];
        Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(file_path);
        file->remove();
        }
    current_proj.file_path_vector.erase(current_proj.file_path_vector.begin(),current_proj.file_path_vector.end());
    for(int i =notebook.get_n_pages()-1;i>=0;i--)
    {
        notebook.remove_page(*vector_code_widget[i]);
        delete vector_code_widget[i];
        }
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    tree_model->clear();    
    }

void main_window::project_close()
{
    if(mode=="FILE")
        return;
    
    Gtk::MessageDialog dialog(*this,Glib::ustring("Are you sure you want to close the current project?"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
    if(dialog.run()==Gtk::RESPONSE_NO)
        return;
    
    for(int i =notebook.get_n_pages()-1;i>=0;i--)
    {
        notebook.remove_page(*vector_code_widget[i]);
        delete vector_code_widget[i];
        }
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    vector_code_widget.erase(vector_code_widget.begin(),vector_code_widget.end());
    tree_model->clear();
    current_proj.clear();
    }   

Glib::ustring main_window::get_gcc_command()
{
    Glib::ustring command = "gcc <input> ";
    if(other_args!="")
    {        
        int i = other_args.find("-o ");
        if (i!=std::string::npos)
        {
            std::string other1 = other_args;
            command += "-o <output> "+ other1.replace(i,3,"");
            }
        else
             command +=other_args;
        }
    
    if(compile_only)
        command += "-S ";
    if(disable_inline)
        command += "-fno-asm ";
    if(define_symbols)
         command += "-D "+ symbols;
    if(add_dir) // Remember to do it
        command +="";
    if(warning)
         command += "-Werror ";
    if(support_89)
         command += "-ansi ";
    if(compile_assemble)
         command += "-c ";
    if(optimize)
    {
         command += "-O";
        if(optimize_level!=-1)
            command += integer_to_string(optimize_level)+ " ";
        else
            command +=" ";
        }
    return command;
    }

void main_window::on_compile_dialog_tree_view_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column,compiler_win& dialog)
{
    Gtk::TreeModel::Row row = *(dialog.list_view_output.get_selection()->get_selected());
    Glib::ustring err_string = row.get_value(dialog.out_columns.m_col);
    int pos_start,pos_end;
    pos_start = err_string.find(":");
    std::string file_path = err_string.substr(0,pos_start);
    std::string line_str = "";
    std::string col_str="";
    pos_end = err_string.find(":",pos_start+1);
    if(pos_end!=-1  && pos_end != err_string.length()-1)
        line_str = err_string.substr(pos_start+1,pos_end-pos_start-1);
    pos_start = pos_end;
    pos_end = err_string.find(":",pos_start+1);
    if(pos_end!=-1  && pos_end != err_string.length())
        col_str = err_string.substr(pos_start+1,pos_end-pos_start-1);
    
    int i;
    for(i = 0; i<filepathsarray.size();i++)
        if(filepathsarray[i] == file_path)
             break;
    
    if(i!=filepathsarray.size())
    {
        buffer = vector_code_widget[i]->_source_view.get_source_buffer();
        Gtk::TextBuffer::iterator goto_iter,end_iter;
        int line=string_to_integer(line_str);
        goto_iter = buffer->get_iter_at_line(line);
        if(line == buffer->get_line_count())
            end_iter  = buffer->end();
        else
           end_iter = buffer->get_iter_at_line(line+1);
        buffer->select_range(goto_iter,end_iter);
        vector_code_widget[i]->_source_view.scroll_to(goto_iter);
        }
    }

void main_window::runrun_activated()
{
    Glib::ustring command;
    std::string output_filename;
    if(mode=="FILE")
    {
        if(notebook.get_n_pages()==0)
              return;
        command = get_gcc_command();
        std::string source_filename = filepathsarray[notebook.get_current_page()];
        if(source_filename == "")
        {
            Gtk::MessageDialog dialog(*this,Glib::ustring("You must save the file before compiling!"),false);
            dialog.run();
            return;
            }
        output_filename = source_filename.substr(0,source_filename.rfind(".c"));
        command = command.replace(command.find("<input>"),7,source_filename);
        command = command.replace(command.find("<output>"),8,output_filename);
        
        compiler_win* ptrgcc_win = new compiler_win(*this,command,mode,current_proj);
        ptrgcc_win->list_view_output.signal_row_activated().connect(sigc::bind<compiler_win&>(sigc::mem_fun(*this,&main_window::on_compile_dialog_tree_view_row_activated),*ptrgcc_win));
        ptrgcc_win->run_and_compile(filepathsarray[notebook.get_current_page()],output_filename);
        ptrgcc_win->show();
        ptrgcc_win->show_all_children();
        }
    else if(mode=="PROJECT")
    {
        command = current_proj.get_command();
        std::string files = "";
        for(int i = 0; i<current_proj.file_path_vector.size();i++)
        {
            if(current_proj.file_path_vector[i].find(".glade")!=Glib::ustring::npos)
                continue;
            files += current_proj.file_path_vector[i]+" ";
            }
        command = command.replace(command.find("<input>"),7,files);
        output_filename = current_proj.get_out_dir()+"/"+current_proj.get_name();
        Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(current_proj.get_out_dir()+"/");
        if(!file->query_exists())
            if(!file->make_directory_with_parents())
                return;
        command = command.replace(command.find("<output>"),8,output_filename);
        
        compiler_win* ptrgcc_win = new compiler_win(*this,command,mode,current_proj);
        ptrgcc_win->list_view_output.signal_row_activated().connect(sigc::bind<compiler_win&>(sigc::mem_fun(*this,&main_window::on_compile_dialog_tree_view_row_activated),*ptrgcc_win));
        ptrgcc_win->run_and_compile(current_proj.get_path(),output_filename);
        ptrgcc_win->show();
        ptrgcc_win->show_all_children();
        }
    else
        return;
    }

void main_window::runcompile_activated()
{
    Glib::ustring command;
    std::string output_filename;
    Gtk::FileChooserDialog dialog("Save File",Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Save",Gtk::RESPONSE_OK);
    
    int result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
        output_filename = dialog.get_filename();
    else
        return;
        
    if(mode=="FILE")
    {
        if(notebook.get_n_pages()==0)
             return;
        command = get_gcc_command();
        std::string source_filename = filepathsarray[notebook.get_current_page()];
        if(source_filename == "")
        {
            Gtk::MessageDialog dialog(*this,Glib::ustring("You must save the file before compiling!"),false);
            dialog.run();
            return;
            }
        command = command.replace(command.find("<input>"),7,source_filename);
        command = command.replace(command.find("<output>"),8,output_filename);
        
        compiler_win* ptrgcc_win = new compiler_win(*this,command,mode,current_proj);
        ptrgcc_win->list_view_output.signal_row_activated().connect(sigc::bind<compiler_win&>(sigc::mem_fun(*this,&main_window::on_compile_dialog_tree_view_row_activated),*ptrgcc_win));
        ptrgcc_win->run_and_compile(filepathsarray[notebook.get_current_page()],output_filename);
        ptrgcc_win->show();
        ptrgcc_win->show_all_children();
        }
    else if(mode=="PROJECT")
    {
        command = current_proj.get_command();
        std::string files = "";
        for(int i = 0; i<current_proj.file_path_vector.size();i++)
        {
            if(current_proj.file_path_vector[i].find(".glade")!=Glib::ustring::npos)
                continue;
            files += current_proj.file_path_vector[i]+" ";
            }
        command = command.replace(command.find("<input>"),7,files);
        command = command.replace(command.find("<output>"),8,output_filename);
        
        compiler_win* ptrgcc_win = new compiler_win(*this,command,mode,current_proj);
        ptrgcc_win->list_view_output.signal_row_activated().connect(sigc::bind<compiler_win&>(sigc::mem_fun(*this,&main_window::on_compile_dialog_tree_view_row_activated),*ptrgcc_win));
        ptrgcc_win->run_and_compile(current_proj,output_filename);
        ptrgcc_win->show();
        ptrgcc_win->show_all_children();
        }
    else
        return;
    }

void main_window::toolsgnometerminal_activated()
{
    Glib::spawn_command_line_sync("./shell");
    }

void main_window::toolsautoindent_activated()
{
    buffer= vector_code_widget[get_notebook_current_page()]->_source_view.get_source_buffer();
    Glib::ustring text = "",emp="";
    text = buffer->get_text();
    
    std::string indent_text = "";
    for(int  i = 0; i<source_view::indent_width;i++)
        indent_text+=" ";
        
    int pos=-1;
    while((pos=text.find("  ",pos+1))!=std::string::npos)
        text.replace(pos,2,emp);
    
    int indent=0;
    buffer->set_text(text);
    
    Gtk::TextBuffer::iterator start_iter,end_iter;
    for(int i =0;i<buffer->get_line_count()-1;i++)
    {
        std::cout<<indent<<std::endl;
        start_iter = buffer->get_iter_at_line(i);
        end_iter = buffer->get_iter_at_line(i+1);
        end_iter = buffer->get_iter_at_offset(end_iter.get_offset()-1);
        std::string line_string = buffer->get_text(start_iter,end_iter,false);
        std::string indent_text2 = "";
        for(int i =0;i<indent;i++)
             indent_text2+=indent_text;
        buffer->insert(start_iter,indent_text2);
        if(line_string.find("{")!=std::string::npos)
            indent++;
        if(line_string.find("}")!=std::string::npos)
            indent--;
        }
    start_iter = buffer->get_iter_at_line(buffer->get_line_count()-1);
    end_iter = buffer->end();
    std::string indent_text2 = "";
    for(int i =0;i<indent;i++)
          indent_text2+=indent_text;
    buffer->insert(start_iter,indent_text2);
    }

void main_window::toolsoptions_activated()
{
    options_dialog dialog(*this,get_gcc_command());
    dialog.show_all_children();
    if(dialog.run()==1)
    {
        std::string opt_str = "";
        opt_str += "<indentation>"+bool_to_string(dialog.chk_indentation.get_active())+"</indentation>\n";
        if(dialog.chk_indentation.get_active())
                opt_str += "<indent_width>"+integer_to_string(dialog.sb_indent_width.get_value())+"</indent_width>\n";
        else
               opt_str += "<indent_width>-1</indent_width>\n";
        opt_str += "<auto_save>"+bool_to_string(dialog.chk_auto_save.get_active())+"</auto_save>\n";
        if(dialog.chk_auto_save.get_active())
        {
            opt_str += "<auto_save_time>"+integer_to_string(dialog.sb_auto_save_time.get_value())+"</auto_save_time>\n";
            opt_str += "<auto_save_current>"+bool_to_string(dialog.rb_current.get_active())+"</auto_save_current>\n";
            opt_str += "<auto_save_all>"+bool_to_string(dialog.rb_all.get_active())+"</auto_save_all>\n";
            }
        
        opt_str += "<tab_width>"+integer_to_string(dialog.sb_tab_width.get_value())+"</tab_width>\n";
        opt_str += "<word_wrap>"+bool_to_string(dialog.chk_word_wrap.get_active())+"</word_wrap>\n";
        opt_str += "<recent_projects>"+bool_to_string(dialog.chk_recent_projects.get_active())+"</recent_projects>\n";
        opt_str += "<recent_files>"+bool_to_string(dialog.chk_recent_files.get_active())+"</recent_files>\n";
        opt_str += "<code_completion>"+bool_to_string(dialog.chk_code_completion.get_active())+"</code_completion>\n";
        opt_str += "<highlight_line>"+bool_to_string(dialog.chk_highlight_line.get_active())+"</highlight_line>\n";
        opt_str += "<line_numbers>"+bool_to_string(dialog.chk_line_numbers.get_active())+"</line_numbers>\n";
        
        opt_str += "<compile_only>" + bool_to_string(dialog.chk_compile_only.get_active())+"</compile_only>\n";
        opt_str += "<warning>" + bool_to_string(dialog.chk_warning.get_active())+"</warning>\n";
        opt_str += "<inline>" + bool_to_string(dialog.chk_inline.get_active())+"</inline>\n";
        opt_str += "<support_89>" + bool_to_string(dialog.chk_support_89.get_active())+"</support_89>\n";
        opt_str += "<compile_assemble>" + bool_to_string(dialog.chk_compile_assemble.get_active())+"</compile_assemble>\n";
        opt_str += "<optimize>" + bool_to_string(dialog.chk_optimize.get_active())+"</optimize>\n";
        opt_str += "<optimize_level>" + integer_to_string(dialog.spin_optimize.get_value())+"</optimize_level>\n";
        opt_str += "<add_dir>" + bool_to_string(dialog.chk_add_dir.get_active())+"</add_dir>\n";
        if(dialog.chk_add_dir.get_active())
        {
            Gtk::TreeIter iter = dialog.dir_tree_model->children().begin();
            while(iter)
            {
                opt_str+="<dir>"+(*iter).get_value(dialog.dir_columns.m_col)+"</dir>\n";
                iter++;
                }
            }
        opt_str += "<define_symbols>" + bool_to_string(dialog.chk_symbols.get_active())+"</define_symbols>\n";
        opt_str += "<symbols>" + dialog.entry_symbols.get_text()+"</symbols>\n";
        opt_str += "<other_args>" + dialog.entry_other_args.get_text()+"</other_args>\n";

        Glib::file_set_contents("./settings.ini",opt_str);
        load_options();
        }
    }

void main_window::debug_gui_activated()
{
    }

void main_window::debug_gnu_activated()
{
    }

void main_window::window_menu_bar_activated()
{           
   Gtk::Widget* menu_bar = ui_manager->get_widget("/MenuBar");
   menu_bar->set_visible(!menu_bar->get_visible());
    }
void main_window::window_tool_bar_activated()
{
    Gtk::Widget* menu_bar = ui_manager->get_widget("/ToolBar");
    menu_bar->set_visible(!menu_bar->get_visible());
    }
void main_window::window_status_bar_activated()
{
   status_bar.set_visible(!status_bar.get_visible());
    }
void main_window::window_project_activated()
{
    proj_sym_notebook.show();
    proj_tree_view.set_visible(!proj_tree_view.get_visible());
    }

void main_window::window_symbols_activated()
{
    update_symbols();
    symbols_icon_view.set_visible(!symbols_icon_view.get_visible());
    proj_sym_notebook.show();
    }

void main_window::window_scope_activated()
{
    code_widget::show_scope=false;
    for(int i = 0; i < vector_code_widget.size();i++)
         vector_code_widget[i]->combo_box_func.set_visible(false);
    }
void main_window::window_close_all_activated()
{
    fileremovealltabs_activated();
    }

void main_window::window_close_current_activated()
{
    fileremovetab_activated();
    }

void main_window::window_close_others_activated()
{
    int current_page = notebook.get_current_page();
    for(int i =notebook.get_n_pages()-1;i>=0;i--)
    {
        if(current_page==i)
            continue;
        notebook.set_current_page(i);
        fileremovetab_activated();
        }
    }