//979 Lines
#include"source_view.h"
#include<iostream>
#include<algorithm>
#include<cstdlib>

bool source_view::indentation = false;
int source_view::indent_width = 0;
bool source_view::code_completion = false;
int source_view::left_margin = 20;
std::string source_view::fold_str = "\n.....";
std::vector<std::string> source_view::vector_gtk_structs(0);
std::vector<gtk_widget_function> source_view::vector_gtk_function(0);
std::string source_view::gtk_structs_string = "";
std::string source_view::gtk_enums_string = "";

int source_view::count_str(std::string& str1, std::string& str2)
{
    int index=0,count=0;
    while((index=str1.find(str2,index))!=-1)
    {
        count++;
        index++;
        }
    return count;
    }

void source_view::load_gtk_keywords()
{
    std::string text;
    try
    {
        text  = Glib::file_get_contents("./gtk_keywords");
        }
    catch(Glib::FileError e)
    {
        Gtk::MessageDialog msg_dialog("Cannot find gtk_keywords file in the main directory. Cannot load Gtk+ Keywords.");
        msg_dialog.run();
        return;
        }
    
    int start=0,end=0;
       
    Glib::RefPtr<Glib::Regex> regex_all_gtk_func;
    Glib::MatchInfo match_info_gtk_func;
    regex_all_gtk_func = Glib::Regex::create("<functions>+.+</functions>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    if(!regex_all_gtk_func->match(text,match_info_gtk_func))
    {
        std::cout<<"Not Found Any Function"<<std::endl;
        return;
        }
    
    std::string func_def = match_info_gtk_func.fetch(0);
    func_def= func_def.replace(0,11,"");
    Glib::RefPtr<Glib::Regex> regex_gtk_func = Glib::Regex::create("\\w+.+");
    if(!regex_gtk_func->match(func_def,match_info_gtk_func))
    {
        std::cout<<"No Function"<<std::endl;
        return;
        }
    do
    {
        std::string func = match_info_gtk_func.fetch(0);
        //std::cout<<func<<std::endl;
        std::string widget_type;
        if(func.find("gtk_")!=std::string::npos)
            widget_type = func.substr(func.find("gtk"),func.find("_",func.find("_")+1) - func.find("gtk"));
        else
        {
            if(match_info_gtk_func.next())
                continue;
            else
                break;
            }         
        //std::string widget_type  = func.substr(0,func.find("_",func.find("_")+1));
        int i;
        for(i = 0;i<vector_gtk_function.size();i++)
             if(vector_gtk_function[i].widget_type==widget_type)
                 break;
        
        if(i==vector_gtk_function.size())
        {
            vector_gtk_function.insert(vector_gtk_function.end(),gtk_widget_function(widget_type));
            if(func.find("(")!=std::string::npos)
            {
               // std::cout<<func<<std::endl;
                vector_gtk_function[vector_gtk_function.size()-1].add_function(func);
                }
            }
        else
        {
            if(func.find("(")!=std::string::npos)
            vector_gtk_function[i].add_function(func);
            }
        }
    while(match_info_gtk_func.next()); 
    
    Glib::RefPtr<Glib::Regex> regex_all_gtk_structs;
    Glib::MatchInfo match_info_gtk_structs;
    regex_all_gtk_structs = Glib::Regex::create("<structs>+.+</structs>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    if(!regex_all_gtk_structs->match(text,match_info_gtk_structs))
    {
        std::cout<<"Not Found any Gtk Keywords"<<std::endl;
        return;
        }
    std::string structs = match_info_gtk_structs.fetch(0);
    Glib::RefPtr<Glib::Regex> regex_gtk_structs;
    regex_gtk_structs = Glib::Regex::create("\\w+.+");
    if(!regex_gtk_structs->match(structs,match_info_gtk_structs))
    {
        std::cout<<"Not Found any Gtk Structs"<<std::endl;
        return;
        }
    
    do
    {
        std::string gtk_struct = match_info_gtk_structs.fetch(0);
        gtk_structs_string += gtk_struct + " ";
        }
    while(match_info_gtk_structs.next()); 
    
    Glib::RefPtr<Glib::Regex> regex_all_gtk_enums;
    Glib::MatchInfo match_info_gtk_enums;
    regex_all_gtk_enums = Glib::Regex::create("<enums>+.+</enums>",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    if(!regex_all_gtk_enums->match(text,match_info_gtk_enums))
    {
        std::cout<<"Not Found any Gtk enums"<<std::endl;
        return;
        }
    structs = match_info_gtk_enums.fetch(0);
    Glib::RefPtr<Glib::Regex> regex_gtk_enums;
    regex_gtk_enums = Glib::Regex::create("\\w+.+");
    if(!regex_gtk_enums->match(structs,match_info_gtk_enums))
    {
        std::cout<<"Not Found any Gtk enums"<<std::endl;
        return;
        }
    
    do
    {
        std::string gtk_enums = match_info_gtk_enums.fetch(0);
        gtk_enums_string += gtk_enums + " ";
        }
    while(match_info_gtk_enums.next()); 
    //std::cout<<gtk_enums_string<<std::endl;
    }

source_view::source_view(Gtk::Statusbar& _status_bar,std::string _f, Gtk::ComboBoxText& cb,Gtk::DrawingArea& _c,Gtk::DrawingArea& _l)
:    status_bar(_status_bar),lines_array(0),vector_include_files(0),filename(_f),frame(""),tree_view(1),combo_box_func(cb),current_mark(0),
     code_folding_widget(_c),line_numbers_widget(_l)
{
    set_events(Gdk::KEY_PRESS_MASK);
    set_events(Gdk::KEY_RELEASE_MASK);
    signal_key_press_event().connect(sigc::mem_fun(*this,&source_view::on_txtinput_key_press),false);  
    signal_key_release_event().connect(sigc::mem_fun(*this,&source_view::on_txtinput_key_release),false);  
    buffer = get_source_buffer();
    Glib::RefPtr<Gtk::TextBuffer> text_buffer = get_buffer();
    connection_mark_set = text_buffer->signal_mark_set().connect(sigc::mem_fun(*this,&source_view::on_mark_set));
    open_brace="{";
    close_brace="}";
    prev_line = -1;
    can_add_to_history=true;
    tree_view_scroll_win.set_policy(Gtk::POLICY_ALWAYS,Gtk::POLICY_ALWAYS);    
    tree_view.set_column_title(0,"Functions");
    tree_view_scroll_win.add(tree_view);
    frame.add(tree_view_scroll_win);
    frame.set_size_request(300,200);
    
    tree_view.signal_row_activated().connect(sigc::mem_fun(*this,&source_view::on_tree_view_row_activated));
    tree_view.set_events(Gdk::KEY_RELEASE_MASK);
    tree_view.signal_key_release_event().connect(sigc::mem_fun(*this,&source_view::on_tree_view_key_release));
    tree_view.set_enable_search(false);
    
    vector_curr_file_func.insert(vector_curr_file_func.end(),function("","Global Scope","",0));
    combo_box_func.append_text("Global Scope");
    connection_combo_box= combo_box_func.signal_changed().connect(sigc::mem_fun(*this,&source_view::on_combo_box_func_changed));

    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this,&source_view::on_mouse_press));
    
    buffer->signal_insert().connect(sigc::mem_fun(*this,&source_view::on_text_insert));
    text_buffer->signal_erase().connect(sigc::mem_fun(*this,&source_view::on_text_deleted),false);
    text_buffer->signal_erase().connect(sigc::mem_fun(*this,&source_view::on_text_deleted_after),false);
    
    frame.set_border_width(0);
    }

source_view::~source_view()
{
    }

void source_view::apply_tag_at_current_line()
{
    Glib::RefPtr<Gtk::TextTagTable> tag_table = buffer->get_tag_table();
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = get_source_buffer();
    Gtk::TextBuffer::iterator current_iter;
    current_iter = buffer->get_iter_at_mark(buffer->get_insert());
    current_iter = buffer->get_iter_at_line(current_iter.get_line());
    
    buffer->remove_all_tags(current_iter,get_line_end_iter(current_iter.get_line()));
    
    std::string line_str = buffer->get_text(current_iter,get_line_end_iter(current_iter.get_line()));
    //std::cout<<"line"<<line_str<<std::endl;
    Glib::RefPtr<Glib::Regex> regex_word;
    Glib::MatchInfo match_info_word;
    regex_word = Glib::Regex::create("\\b\\w+\\b");
    
    if(!regex_word->match(line_str,match_info_word))
    {
        //std::cout<<"LL"<<std::endl;
        return;
        }
    int first_start, first_end;
    match_info_word.fetch_pos(0,first_start,first_end);
    do
    {
        std::string word = match_info_word.fetch(0);
        int start_pos,end_pos;
        match_info_word.fetch_pos(0,start_pos,end_pos);
        Gtk::TextIter start = buffer->get_iter_at_offset(start_pos+current_iter.get_offset());
        Gtk::TextIter end = buffer->get_iter_at_offset(end_pos+current_iter.get_offset());
        //std::cout<<"start_pos"<<start.get_offset()<<" "<<start.get_line_offset()<<"end_pos"<<end.get_offset()<<" "<<end.get_line_offset()<<std::endl;
        Glib::RefPtr<Glib::Regex> regex_gtk_struct;
        Glib::MatchInfo match_info_gtk_struct;
        regex_gtk_struct = Glib::Regex::create("\\s+"+word+"\\s");
        if(regex_gtk_struct->match(gtk_structs_string,match_info_gtk_struct))
        {
            do
            {
                Glib::RefPtr<Gtk::TextBuffer::Tag> tag = tag_table->lookup(word);
                if(tag==0)
                    tag = buffer->create_tag(word);                
    
                tag->property_foreground()="darkgreen";                          
                buffer->apply_tag(tag,start,end);
                }
            while(match_info_gtk_struct.next());
            }        
        else if(regex_gtk_struct->match(gtk_enums_string,match_info_gtk_struct))
        {
            do
            {
                Glib::RefPtr<Gtk::TextBuffer::Tag> tag = tag_table->lookup(word);
                if(tag==0)
                    tag = buffer->create_tag(word);                
    
                tag->property_foreground()="darkgreen";                          
                buffer->apply_tag(tag,start,end);
                }
            while(match_info_gtk_struct.next());
            }
        }
    while(match_info_word.next());
    }

void source_view::on_text_insert(const Gtk::TextIter& iter, const Glib::ustring& text, int bytes)
{
    for(int i = combo_box_func.get_active_row_number()+1;i<vector_curr_file_func.size();i++)
         vector_curr_file_func[i].pos+=bytes;
        
    for(int i = 0;i<vector_fold_text.size();i++)
    {
        if(vector_fold_text[i].start_pos>iter.get_offset())
             vector_fold_text[i].start_pos+=bytes;
        if(vector_fold_text[i].end_pos!=-1 && vector_fold_text[i].end_pos>iter.get_offset())
            vector_fold_text[i].end_pos+=bytes;
        }
    
    apply_tag_at_current_line();
    }
void source_view::on_text_deleted_after(const Gtk::TextIter& start, const Gtk::TextIter& end)
{
    apply_tag_at_current_line();
    }

void source_view::on_text_deleted(const Gtk::TextIter& start, const Gtk::TextIter& end)
{
    for(int i = combo_box_func.get_active_row_number()+1;i<vector_curr_file_func.size();i++)
         vector_curr_file_func[i].pos -=end.get_offset()-start.get_offset();
        
    for(int i =0;i<vector_fold_text.size();i++)
    {
        if(vector_fold_text[i].start_pos>start.get_offset())
             vector_fold_text[i].start_pos+=start.get_offset()-end.get_offset();
        if(vector_fold_text[i].end_pos!=-1 && vector_fold_text[i].end_pos>start.get_offset())
            vector_fold_text[i].end_pos+=start.get_offset()-end.get_offset();
        }
    }

bool source_view::on_mouse_press(GdkEventButton* event)
{
    return false;    
    }

void source_view::on_combo_box_func_changed()
{
    int active = combo_box_func.get_active_row_number();
    int offset = vector_curr_file_func[active].pos;
    Gtk::TextIter iter  = buffer->get_iter_at_offset(offset);
    buffer->select_range(buffer->get_iter_at_line(iter.get_line()),get_line_end_iter(iter.get_line()));
    scroll_to_iter(iter,0.0);
    }

void source_view::on_tree_view_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
    Gtk::TextBuffer::iterator current_iter;
    current_iter = buffer->get_iter_at_mark(buffer->get_insert());
    
    int j=0,k=0;
    std::string line_text = buffer->get_text(buffer->get_iter_at_line(current_iter.get_line()),get_line_end_iter(current_iter.get_line()));
    std::string current_word ="";
    
    if(line_text !="")
    {                    
        for( j = current_iter.get_line_offset(); j<line_text.size();j++)
        {                        
             if(!(isalnum(line_text[j]) || line_text[j] == '_'))
                 break;
            }                    
        for( k = current_iter.get_line_offset()-1; k>=0;k--)
             if(!(isalnum(line_text[k]) || line_text[k] == '_'))
                 break;
        k++;      
        }
    
    buffer->erase(buffer->get_iter_at_line_offset(current_iter.get_line(),k),buffer->get_iter_at_line_offset(current_iter.get_line(),j));
    current_iter = buffer->get_iter_at_mark(buffer->get_insert());
    
    Glib::ustring path_str = path.to_string();
    std::string str_index = path_str.substr(path_str.find(':')+1);
    int index = string_to_integer(str_index);    
    
    std::string to_insert = tree_view.get_text(index,0);
    tree_row_text = to_insert;
    if(to_insert.find("(")!=std::string::npos)
    {
        is_tree_row_activated=true;
        to_insert = to_insert.substr(0,to_insert.find("("));
        to_insert = to_insert.substr(to_insert.rfind(" "));
        }
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = get_source_buffer();
    
    buffer->insert(current_iter,to_insert);
    if(frame.get_parent())
        frame.get_parent()->remove(frame);
    
    grab_focus();
    line_number_tooltip = buffer->get_iter_at_mark(buffer->get_insert()).get_line();    
    }

void source_view::navigate_back()
{
    can_add_to_history=false;
    buffer= get_source_buffer();
    int current_line = buffer->get_iter_at_mark(buffer->get_insert()).get_line()+1;
    std::vector<int>::iterator find_it = find(lines_array.begin(),lines_array.end(),current_line);
    if(find_it==lines_array.end())
        return;
    
    find_it++;
    int navigate_to_line = *find_it;
    navigate_to_line--;
    Gtk::TextIter navigate_to_line_iter = buffer->get_iter_at_line(navigate_to_line);
    buffer->place_cursor(navigate_to_line_iter);
    scroll_to(navigate_to_line_iter);
    can_add_to_history = true;
    }

void source_view::navigate_forward()
{
    can_add_to_history=false;
    buffer= get_source_buffer();
    int current_line = buffer->get_iter_at_mark(buffer->get_insert()).get_line()+1;
    std::vector<int>::iterator find_it = find(lines_array.begin(),lines_array.end(),current_line);
    if(find_it==lines_array.end())
        return;
    
    find_it--;
    int navigate_to_line = *find_it;
    navigate_to_line--;
    Gtk::TextIter navigate_to_line_iter = buffer->get_iter_at_line(navigate_to_line);
    buffer->place_cursor(navigate_to_line_iter);
    scroll_to(navigate_to_line_iter);
    can_add_to_history = true;
    }

Gtk::TextIter source_view::get_line_end_iter(int line)
{
    Gtk::TextIter iter;
    if(line+1 == buffer->get_line_count())
         return buffer->end();
    iter = buffer->get_iter_at_line(line+1);
    return buffer->get_iter_at_offset(iter.get_offset()-1);
    }

void source_view::get_curr_file_funcs()
{  
    vector_c_symbol.erase(vector_c_symbol.begin(),vector_c_symbol.end());
    std::string contents = buffer->get_text();    
    vector_curr_file_func.erase(vector_curr_file_func.begin(),vector_curr_file_func.end());
    combo_box_func.clear_items();
    vector_curr_file_func.insert(vector_curr_file_func.end(),function("","Global Scope","",0));
    combo_box_func.append_text("Global Scope");
    
    int start=0,end=0;
       
    Glib::RefPtr<Glib::Regex> regex_func_def;
    Glib::MatchInfo match_info_func_def;    
    regex_func_def = Glib::Regex::create("[\\w*]+[\\s*]+[\\w*]+\\s*\\(+.+\\)\\s*{");
    if(regex_func_def->match(contents,match_info_func_def))
    {        
        do
        {
            std::string func_def = match_info_func_def.fetch(0);
            match_info_func_def.fetch_pos(0,start,end);
            
            func_def = func_def.substr(0,func_def.find(")")+1);
            function func = function(func_def,start+1);        
            combo_box_func.append_text(func.get_func_str());
            vector_curr_file_func.insert(vector_curr_file_func.end(),func);
            }
        while(match_info_func_def.next());
        }
    Glib::RefPtr<Glib::Regex> regex_define;
    Glib::MatchInfo match_info_define;    
    regex_define = Glib::Regex::create("#define+.+");
    if(regex_define->match(contents,match_info_define))
    {
        do
        {
            int start,end;
            match_info_define.fetch_pos(0,start,end);
            std::string define_str = match_info_define.fetch(0);
            int space_first,space_second;
            space_first  = define_str.find(" ");
            space_second = define_str.find(" ",space_first+1);
            if(space_second==std::string::npos)
                space_second = define_str.length();            
            vector_c_symbol.insert(vector_c_symbol.end(),c_symbol(define_str.substr(space_first+1,space_second-space_first-1),"#define",start));
            }
        while(match_info_define.next());
        }
    
    Glib::RefPtr<Glib::Regex> regex_struct;
    Glib::MatchInfo match_info_struct;    
    regex_struct = Glib::Regex::create("\\bstruct\\b.+?};",static_cast< Glib::RegexCompileFlags>(Glib::REGEX_DOTALL));
    if(regex_struct->match(contents,match_info_struct))
    {
        do
        {
            int start,end;
            match_info_struct.fetch_pos(0,start,end);
            std::string struct_str = match_info_struct.fetch(0);
            int space_first,space_second;
            space_first  = struct_str.find(" ");
            space_second = struct_str.find(" ",space_first+1);
            if(space_second==std::string::npos)
            {
                space_second = struct_str.find("\n",space_first+1);
                if(space_second==std::string::npos)
                {
                    space_second = struct_str.find("{",space_first+1);
                    if(space_second==std::string::npos)
                       space_second = struct_str.length();
                    }
                }
            
            std::string struct_str2 = struct_str.substr(space_first+1,space_second-space_first);
            int find_pos = struct_str2.find("\n");
            if(find_pos!=std::string::npos)
                struct_str2 = struct_str2.substr(0,find_pos);
            find_pos = struct_str2.find(" ");
            if(find_pos!=std::string::npos)
                struct_str2 = struct_str2.substr(0,find_pos);
            
            struct_str = struct_str.replace(struct_str.rfind("};"),struct_str.length(),"");
            c_symbol _c_symbol = c_symbol(struct_str2,"struct",start);
            Glib::RefPtr<Glib::Regex> regex_struct_members;
            Glib::MatchInfo match_info_struct_members;    
            regex_struct_members = Glib::Regex::create("[^\\s]+.+;");
            if(regex_struct_members->match(struct_str,match_info_struct_members))
            {
                do
                {
                    std::string member = match_info_struct_members.fetch(0);
                    int start2;
                    match_info_struct_members.fetch_pos(0,start2,end);
                    find_pos = member.rfind(" ");
                    _c_symbol.child_c_symbols.insert(_c_symbol.child_c_symbols.end(),c_symbol(member.substr(find_pos+1),member.substr(0,find_pos),start+start2));
                    std::cout<<start+start2<<std::endl;
                    }
                while(match_info_struct_members.next());
                }
            vector_c_symbol.insert(vector_c_symbol.end(),_c_symbol);
            }
        while(match_info_struct.next());
        }
    std::cout<<"size"<<vector_c_symbol.size()<<std::endl;
    }

void source_view::fill_from_include_files()
{
    std::string text = buffer->get_text();
    Glib::RefPtr<Glib::Regex> regex_include_file;
    Glib::MatchInfo match_info_include_file;    
    regex_include_file = Glib::Regex::create("#include+.+");
    if(!regex_include_file->match(text,match_info_include_file))
        return;
        
    do
    {
        func_include_file_line(match_info_include_file.fetch(0));
        }
    while(match_info_include_file.next());
    }

void source_view::func_include_file_line(std::string line_text)
{
    int curr_dir_include_file = line_text.find("#include\"");
    if (filename == "")
        return;
    if(line_text.find("#include<")!=std::string::npos);
    //so the file is a library file, do something to include it :P :) :D
    else if(curr_dir_include_file!=std::string::npos)
    {
        //so the file is in the current dir
        if(line_text.find("\"",curr_dir_include_file+9)!=std::string::npos)
        {
            //successful in finding the file name
            std::string include_file_name = line_text.substr(curr_dir_include_file+9,line_text.find("\"",curr_dir_include_file+9)-curr_dir_include_file-9);
                      
            std::string dir = filename.substr(0,filename.rfind("/")+1);
            include_file_name = dir+include_file_name;
            int i;
            for(i = 0;i <vector_include_files.size();i++)
                if(vector_include_files[i]==include_file_name)
                    break;
            if(i==vector_include_files.size())
            {
                //new include file, create a new thread to include it 
                vector_include_files.insert(vector_include_files.end(),include_file_name);
                include_file_thread = Glib::Thread::create(sigc::bind<std::string>(sigc::mem_fun(*this,&source_view::include_file_thread_func),include_file_name),false);
                }
            }
        }
    }

void source_view::include_file_thread_func(std::string filepath)
{
    std::string contents = Glib::file_get_contents(filepath);
    //status_bar.push("Parsing file "+filepath);
    //use glib::dispatcher to send data etc. :P :D :o
    
    int curr_file_funcs_vector_bound = -1;
    Glib::RefPtr<Glib::Regex> regex_func_dec;
    Glib::MatchInfo match_info_func_dec;    
    regex_func_dec = Glib::Regex::create("[\\w*]+[\\s*]+[\\w*]+\\(+.+\\)\\s*;");
    if(!regex_func_dec->match(contents,match_info_func_dec))
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
        curr_file_funcs_vector_bound = vector_include_func.size();
        vector_include_func.insert(vector_include_func.end(),function(func_dec,0));
        }
    while(match_info_func_dec.next());    
    
    Glib::RefPtr<Glib::Regex> regex_func_def;
    Glib::MatchInfo match_info_func_def;    
    regex_func_def = Glib::Regex::create("[\\w*]+[\\s*]+[\\w*]+\\(+.+\\)\\s*{");
    if(!regex_func_def->match(contents,match_info_func_def))
    {
        std::cout<<"Not Found Any Function Definition"<<std::endl;
        return;
        }
    do
    {
        int j;
        std::string func_def = match_info_func_def.fetch(0);
        func_def = func_def.substr(0,func_def.find(")")+1);
        function func = function(func_def,0);
        for(j = curr_file_funcs_vector_bound; j<vector_include_func.size();j++)
            if(vector_include_func[j]==func)
                break;
        if(j!=vector_include_func.size())
            continue;
        
        vector_include_func.insert(vector_include_func.end(),func);
        }
    while(match_info_func_def.next());   
    
    Glib::RefPtr<Glib::Regex> regex_include_file;
    Glib::MatchInfo match_info_include_file;    
    regex_include_file = Glib::Regex::create("#include+.+");
    if(!regex_include_file->match(contents,match_info_include_file))
        return;
    
    do
    {
        filepath = match_info_include_file.fetch(0);
        if(filepath.find("<")!=std::string::npos);
        else if(filepath.find("\"")!=std::string::npos)
        {
            filepath = filepath.substr(filepath.find("\"")+1,filepath.rfind("\"")-filepath.find("\"")-1);
            filepath = filename.substr(0,filename.rfind("/")+1)+filepath;
            include_file_thread_func(filepath);
            }
        }
    while(match_info_include_file.next());
    //status_bar.push("Parsing completed of file " + filepath);
    }

bool source_view::on_expose_event(GdkEventExpose* event)
{    
    Glib::RefPtr<Gdk::Window> m_refGdkWindow = code_folding_widget.get_window();
    Gdk::Rectangle rectangle(0,0,m_refGdkWindow->get_width(),m_refGdkWindow->get_height());
    m_refGdkWindow->invalidate_rect(rectangle,true);
    m_refGdkWindow->process_updates(true);
    
    m_refGdkWindow = line_numbers_widget.get_window();
    Gdk::Rectangle rectangle1(0,0,m_refGdkWindow->get_width(),m_refGdkWindow->get_height());
    m_refGdkWindow->invalidate_rect(rectangle1,true);
    m_refGdkWindow->process_updates(true);
    
    gtksourceview::SourceView::on_expose_event(event);
    return true;
    }
void source_view::set_show_line_numbers(bool _b)
{   
    line_numbers_widget.set_visible(_b);
    }

bool source_view::get_show_line_numbers()
{
    return line_numbers_widget.get_visible();
    }

void source_view::on_mark_set(const Gtk::TextBuffer::iterator& iterator,const Glib::RefPtr<Gtk::TextBuffer::Mark>& mark)
{    
    Gtk::TextIter current_iter = buffer->get_iter_at_mark(buffer->get_insert());
    
    status_bar.push("Char " + integer_to_string(current_iter.get_offset()) + " Col " + integer_to_string(current_iter.get_line_offset()) + " Line " + integer_to_string(current_iter.get_line()));
    
    if(frame.get_parent())
        frame.get_parent()->remove(frame);
            
    for(int i = 0; i <vector_fold_text.size();i++)
    {
        if(vector_fold_text[i].start_pos <current_iter.get_offset() && vector_fold_text[i].end_pos > current_iter.get_offset())
        {
            Gtk::TextIter iter = buffer->get_iter_at_offset(vector_fold_text[i].start_pos);
            buffer->place_cursor(iter);
            break;
            }
        }
    
    int line = current_iter.get_line()+1;
    int offset  = current_iter.get_offset();
    if(!can_add_to_history)
        return;
            
    std::string line_text = buffer->get_text(buffer->get_iter_at_line(line),get_line_end_iter(line));
    if(line_text.find("#include")!= std::string::npos)
         func_include_file_line(line_text);
        
    if(prev_line!=line)
    {
        if(lines_array.size()==0)
            lines_array.insert(lines_array.begin(),line);
        else
        {            
            std::vector<int>::iterator find_it = find(lines_array.begin(),lines_array.end(),line);
            if(find_it == lines_array.end())
            {
                if(lines_array.size()==5)
                    lines_array.erase(lines_array.end()-1);
                lines_array.insert(lines_array.begin(),line);
                }
            else
            {
                lines_array.erase(find_it);
                lines_array.insert(lines_array.begin(),line);
                }
            }
        int i;
        for(i =vector_curr_file_func.size()-1;i>=0;i--)
        {
            if(vector_curr_file_func[i].pos<=offset)
                break;
            }
        if(i!=vector_curr_file_func.size())
        {
            connection_combo_box.disconnect();
            combo_box_func.set_active(i);
            connection_combo_box= combo_box_func.signal_changed().connect(sigc::mem_fun(*this,&source_view::on_combo_box_func_changed));
            }
        }        
    prev_line=line;
    }

bool source_view::on_tree_view_key_release(GdkEventKey *event)
{
    return false;
    }

bool source_view::on_txtinput_key_release(GdkEventKey *event)
{
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = get_source_buffer();
    Gtk::TextBuffer::iterator current_iter;
    current_iter = buffer->get_iter_at_mark(buffer->get_insert());
    int col = current_iter.get_line_offset(),chars = current_iter.get_offset(),line = current_iter.get_line();   

    switch (event->keyval)
    {
        case 40: //40 for Shift+9 = (
            if(is_tree_row_activated && line_number_tooltip == line)
            {
                stack_tooltip_text.insert(stack_tooltip_text.begin(),tree_row_text);
                set_tooltip_text(tree_row_text);
                }
            break;
        case 41:
            if(stack_tooltip_text.size()>1 && line_number_tooltip == line)
            {
                stack_tooltip_text.erase(stack_tooltip_text.begin(),stack_tooltip_text.begin()+1);
                tree_row_text = stack_tooltip_text[stack_tooltip_text.size()-1];
                set_tooltip_text(tree_row_text);
                }
            else if(stack_tooltip_text.size()==1 && line_number_tooltip == line)
            { 
                stack_tooltip_text.erase(stack_tooltip_text.begin(),stack_tooltip_text.begin()+1);
                tree_row_text ="";
                set_tooltip_text(tree_row_text);
                is_tree_row_activated = false;
                }
        case GDK_KEY_Escape:
        case GDK_KEY_Right:
        case GDK_KEY_Left:
        case GDK_KEY_Return:
        case GDK_KEY_Down:
        case GDK_KEY_Up:            
            break;
        
        default:
            
            if(is_tree_row_activated&& line_number_tooltip == line)                
                set_tooltip_text(tree_row_text);
                
            grab_focus();
            
            if(code_completion!=true)
                return false;
            
            tree_view.clear_items();
            int j=0,k=0;
            std::string line_text = buffer->get_text(buffer->get_iter_at_line(line),get_line_end_iter(line));
            std::string current_word ="";
            if(line_text !="")
            {                    
                for( j = col; j<line_text.size();j++)
                {                        
                     if(!(isalnum(line_text[j]) || line_text[j] == '_'))
                         break;
                    }                    
                for( k = col-1; k>=0;k--)
                     if(!(isalnum(line_text[k]) || line_text[k] == '_'))
                         break;
                k++;      
                if(j-k>4)
                current_word = line_text.substr(k,j-k);
                }
            
            bool find = false;
            if(current_word=="")
                return false;
                
            if(current_word.find("_",current_word.find("_")+1)!=std::string::npos)
            {
                std::string widget_type = current_word.substr(0,current_word.find("_",current_word.find("_")));
                if(widget_type==current_word)
                {
                    for(int i =0;i<vector_gtk_function.size();i++)
                    {                    
                        if(vector_gtk_function[i].widget_type.find(widget_type)!=std::string::npos)
                        {                        
                            find = true;
                            for(int j = 0; j<vector_gtk_function[i].vector_function.size();j++)
                                 tree_view.append_text(vector_gtk_function[i].vector_function[j].get_func_str());
                            }
                        }
                    }
                else
                {
                    for(int i =0;i<vector_gtk_function.size();i++)
                    {                    
                        if(vector_gtk_function[i].widget_type.find(widget_type)!=std::string::npos)
                        {                        
                            find = true;
                            for(int j = 0; j<vector_gtk_function[i].vector_function.size();j++)
                            {
                                std::string func_str = vector_gtk_function[i].vector_function[j].get_func_str();
                                if(func_str.find(current_word)!=std::string::npos)
                                     tree_view.append_text(func_str);
                                }
                            }
                        }
                    }
                }
            for(int i =0;i<vector_include_func.size();i++)
            {                
                if(vector_include_func[i].name.find(current_word)!=std::string::npos)
                {
                    find = true;
                    tree_view.append_text(vector_include_func[i].get_func_str());
                    }
                }
            for(int i =0;i<vector_curr_file_func.size();i++)
            {
                if(vector_curr_file_func[i].name.find(current_word)!=std::string::npos)
                {
                    find = true;
                    tree_view.append_text(vector_curr_file_func[i].get_func_str());
                    }
                }
            
            if(find == false)
                return false;

            Gdk::Rectangle location;
            get_iter_location(current_iter,location);
            int window_x,window_y;
            buffer_to_window_coords(Gtk::TEXT_WINDOW_WIDGET,location.get_x()+location.get_width(),location.get_y()+location.get_height(),window_x,window_y);
            if(frame.get_parent())
                 frame.get_parent()->remove(frame);
            add_child_in_window(frame,Gtk::TEXT_WINDOW_TEXT,window_x,window_y);
            show_all_children();
            tree_view.grab_focus();
            grab_focus();
        }
    return false;
    }

bool source_view::on_txtinput_key_press(GdkEventKey* event)
{    
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = get_source_buffer();
    Gtk::TextBuffer::iterator current_iter;
    current_iter = buffer->get_iter_at_mark(buffer->get_insert());
    int col = current_iter.get_line_offset(),chars = current_iter.get_offset(),line = current_iter.get_line();
    switch(event->keyval)
    {
        case GDK_KEY_Escape:
            if(frame.get_parent())
            {
                frame.get_parent()->remove(frame);
                return true;
                }
        case GDK_KEY_Return:
            if(frame.get_parent())
            {
                Gtk::TreeModel::iterator iter = tree_view.get_selection()->get_selected();
                Gtk::TreePath path = Gtk::TreePath(iter);
                Gtk::TreeViewColumn* tree_col = tree_view.get_column(0);
                tree_view.row_activated(path,*tree_col);
                return true;
                }
        case GDK_KEY_Up:
            if(frame.get_parent())
            {
                Gtk::TreeModel::iterator iter = tree_view.get_selection()->get_selected();
                iter--;
                if(iter) 
                    tree_view.get_selection()->select(iter);
                return true;
                }            
            break;
        
        case GDK_KEY_Down:
            if(frame.get_parent())
            {
                Gtk::TreeModel::iterator iter = tree_view.get_selection()->get_selected();
                iter++;
                if(iter) 
                    tree_view.get_selection()->select(iter);
                return true;
                }            
            break;
        }
    
    if (indentation == true)
    {
        Gtk::TextBuffer::iterator line_start_iter;
        line_start_iter = buffer->get_iter_at_line_offset(current_iter.get_line(),0);
        std::string line_text = buffer->get_text(line_start_iter,current_iter);
        std::string::const_iterator str_iter;
        int index=0,count_open_brace=0,count_close_brace=0,count_spaces = 0;
        //remember to change the indentation marks, they should be do,def,class and others
        switch (event->keyval)
        {
            case GDK_KEY_Return:
                count_open_brace = count_str(line_text,open_brace);
                count_close_brace = count_str(line_text,close_brace);
                 
                str_iter  = line_text.begin();
                while(*str_iter++==' ')
                    count_spaces++;
                    
                int i;
                if (count_open_brace>count_close_brace)
                {
                    buffer->insert_at_cursor("\n");
                    for (i=0;i<indent_width+count_spaces;i++)
                        buffer->insert_at_cursor(" ");
                    }
                else if (count_open_brace<count_close_brace)
                {
                    buffer->insert_at_cursor("\n");
                    for (i=0;i<count_spaces-indent_width;i++)
                        buffer->insert_at_cursor(" ");
                    }
                else if(count_open_brace==count_close_brace)
                {
                    buffer->insert_at_cursor("\n");
                    for (i=0;i<count_spaces;i++)
                        buffer->insert_at_cursor(" ");
                    }
                return true;
                break;
            case GDK_KEY_Left:
                str_iter  = line_text.begin();
                while(*str_iter++==' ')
                    count_spaces++;
                    
                if (col<=count_spaces&&col>0)
                {
                    int new_line_offset=0;
                    if(col%indent_width == 0)
                        new_line_offset = col-indent_width;
                    else
                        new_line_offset = col-(col%indent_width);
                    Gtk::TextBuffer::iterator new_line_iter;
                    new_line_iter = buffer->get_iter_at_line_offset(line,new_line_offset);
                    buffer->place_cursor(new_line_iter);
                    }
                else
                    return false;
                break;
            case GDK_KEY_Home:
                str_iter  = line_text.begin();
                while(*str_iter++==' ')
                    count_spaces++;

                if (col>count_spaces)
                {
                    Gtk::TextBuffer::iterator new_line_iter;
                    new_line_iter = buffer->get_iter_at_line_offset(line,count_spaces);
                    buffer->place_cursor(new_line_iter);
                    }
                else
                    return false;
                break;
            case GDK_KEY_BackSpace:
                str_iter  = line_text.begin();
                while(*str_iter++==' ')
                    count_spaces++;
                
                if(col<=count_spaces&&col>0)
                {
                    int new_line_offset = 0;
                    if(col%indent_width==0)
                        new_line_offset = col-indent_width+1;
                    else
                        new_line_offset=col-(col%indent_width)+1;
                    Gtk::TextIter new_iter;
                    new_iter = buffer->get_iter_at_line_offset(line,new_line_offset);
                    buffer->erase_interactive(new_iter,current_iter,true);
                    }
            default:                
                return false;
                break;
            }
        }
    }