//434 Lines
#include"options_dialog.h"

options_dialog::options_dialog(Gtk::Window& _parent, std::string command)
: lbl_gcc("GCC Command"),lbl_gcc_other_args("Other Arguments"),chk_compile_only("Compile only, do not assemble or link(-S)"), 
  chk_warning("Treats warning as errors(-Werror)"),  chk_inline("Disable use of inline, asm and typeof as keywrods(-fno-asm)"), 
  chk_support_89("Support all C89 features(-ansi)"),chk_compile_assemble("Compile and assemble, do not link(-c)"), 
  chk_optimize("Optimize with level (-O)"), chk_add_dir("Add Directories to compile search paths(-B<directory>)"), 
  chk_symbols("Define Symbols"),cmd_add_dir("Add "), cmd_rem_dir("Remove"),chk_indentation("Indentation"), chk_auto_save("Auto Save"),
  chk_word_wrap("Word Wrap"), chk_recent_projects("Recent Projects"), chk_recent_files("Recent Files"), chk_line_numbers("Show Line Numbers"),
  chk_code_completion("Enable Code Completion"), chk_highlight_line("Highlight Current Line"),lbl_indentation("Indentation Width"), 
  lbl_auto_save("Auto Save file after every (min)"),lbl_tab("Tab Width(Spaces per Tab)"), rb_current("Auto Save Current File"), rb_all("Auto Save all open files")
{
    notebook.append_page(fixed_general,"General");
    notebook.append_page(fixed_compiler,"Compiler");
    
    rb_current.set_group(rb_auto_save_group);
    rb_all.set_group(rb_auto_save_group);
    
    fixed_general.put(chk_indentation,10,10);
    chk_indentation.set_size_request(131,26);
    
    fixed_general.put(lbl_indentation,33,50);
    lbl_indentation.set_size_request(201,21);
    
    fixed_general.put(sb_indent_width,290,50);
    sb_indent_width.set_size_request(59,31);
    
    fixed_general.put(chk_auto_save,10,100);
    chk_auto_save.set_size_request(131,26);
    
    fixed_general.put(lbl_auto_save,33,138);
    lbl_auto_save.set_size_request(211,21);
    
    fixed_general.put(sb_auto_save_time,290,138);
    sb_auto_save_time.set_size_request(59,31);
    
    fixed_general.put(rb_current,30,180);
    rb_current.set_size_request(191,26);
    
    fixed_general.put(rb_all,290,180);
    rb_all.set_size_request(191,26);   
    
    fixed_general.put(lbl_tab,20,240);
    lbl_tab.set_size_request(67,21);
    
    fixed_general.put(sb_tab_width,290,240);
    sb_tab_width.set_size_request(59,31);
    
    fixed_general.put(chk_word_wrap,10,280);
    chk_word_wrap.set_size_request(141,26);
    
    fixed_general.put(chk_recent_projects,290,280);
    chk_recent_projects.set_size_request(161,26);
    
    fixed_general.put(chk_recent_files,10,320);
    chk_recent_files.set_size_request(121,26);
    
    fixed_general.put(chk_line_numbers,290,320);
    chk_line_numbers.set_size_request(161,26);
    
    fixed_general.put(chk_code_completion,10,360);
    chk_code_completion.set_size_request(191,26);
    
    fixed_general.put(chk_highlight_line,290,360);
    chk_highlight_line.set_size_request(191,26);  
    
    fixed_compiler.put(chk_compile_only,10,10);
    chk_compile_only.set_size_request(301,26);
    
    fixed_compiler.put(chk_warning,480,10);
    chk_warning.set_size_request(261,26);
    
    fixed_compiler.put(chk_inline,10,50);
    chk_inline.set_size_request(421,26);
    
    fixed_compiler.put(chk_support_89,480,40);
    chk_support_89.set_size_request(241,26);
    
    fixed_compiler.put(chk_compile_assemble,480,70);
    chk_compile_assemble.set_size_request(271,26);
    
    fixed_compiler.put(chk_optimize,480,100);
    chk_optimize.set_size_request(191,31);
    
    fixed_compiler.put(chk_add_dir,10,140);
    chk_add_dir.set_size_request(411,26);
    
    fixed_compiler.put(chk_symbols,10,90);
    chk_symbols.set_size_request(131,26);
    
    fixed_compiler.put(cmd_add_dir,620,210);
    cmd_add_dir.set_size_request(95,31);
    
    fixed_compiler.put(cmd_rem_dir,620,270);
    cmd_rem_dir.set_size_request(95,31);
    
    fixed_compiler.put(spin_optimize,670,100);
    spin_optimize.set_size_request(59,31);
    
    fixed_compiler.put(list_view_dir,10,170);
    list_view_dir.set_size_request(591,181);
    
    fixed_compiler.put(entry_symbols,150,90);
    entry_symbols.set_size_request(321,31);
    
    fixed_compiler.put(entry_command,110,410);
    entry_command.set_size_request(640,31);
    entry_command.set_text(command);
    
    fixed_compiler.put(lbl_gcc,10,413);
    lbl_gcc.set_size_request(101,21);
    
    fixed_compiler.put(entry_other_args,110,360);
    entry_other_args.set_size_request(640,31);
    
    fixed_compiler.put(lbl_gcc_other_args,10,350);
    lbl_gcc_other_args.set_size_request(91,41);
    lbl_gcc_other_args.set_line_wrap(true);
    
    Gtk::Adjustment* adjustment = sb_tab_width.get_adjustment();
    adjustment->set_upper(1000);
    adjustment->set_lower(0);
    adjustment->set_step_increment(1);     
    adjustment->set_page_increment(1);        
    sb_tab_width.set_numeric(true);
    sb_tab_width.set_adjustment(*adjustment);

    adjustment = sb_indent_width.get_adjustment();
    adjustment->set_upper(1000);
    adjustment->set_lower(0);
    adjustment->set_step_increment(1);     
    adjustment->set_page_increment(1);        
    sb_indent_width.set_numeric(true);
    sb_indent_width.set_adjustment(*adjustment);
    
    adjustment = sb_auto_save_time.get_adjustment();
    adjustment->set_upper(1000);
    adjustment->set_lower(0);
    adjustment->set_step_increment(1);     
    adjustment->set_page_increment(1);        
    sb_auto_save_time.set_numeric(true);
    sb_auto_save_time.set_adjustment(*adjustment);
    
    adjustment = spin_optimize.get_adjustment();
    adjustment->set_upper(9);
    adjustment->set_lower(0);
    adjustment->set_step_increment(1);     
    adjustment->set_page_increment(1);        
    spin_optimize.set_numeric(true);
    spin_optimize.set_adjustment(*adjustment);
    
    dir_tree_model = Gtk::ListStore::create(dir_columns);
    list_view_dir.set_model(dir_tree_model);
    list_view_dir.append_column("Directories", dir_columns.m_col);
    
    Gtk::VBox* dialog_vbox = get_vbox();
    dialog_vbox->pack_start(notebook,Gtk::PACK_EXPAND_WIDGET);
    
    
    Gtk::Button* cmd_ok = add_button("OK",1);
    Gtk::Button* cmd_cancel = add_button("Cancel",0);
    
    chk_optimize.set_active(true);
    chk_add_dir.set_active(true);
    chk_symbols.set_active(true);
    
    chk_optimize.signal_toggled().connect(sigc::bind<Gtk::Widget&>(sigc::mem_fun(*this,&options_dialog::on_chk_toggled),spin_optimize)); 
    chk_add_dir.signal_toggled().connect(sigc::bind<Gtk::Widget&>(sigc::mem_fun(*this,&options_dialog::on_chk_toggled),list_view_dir)); 
    chk_symbols.signal_toggled().connect(sigc::bind<Gtk::Widget&>(sigc::mem_fun(*this,&options_dialog::on_chk_toggled),entry_symbols));

    load_options();
    
    chk_compile_only.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_compile_only_toggled));
    chk_warning.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_warning_toggled)); 
    chk_inline.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_inline_toggled));
    chk_support_89.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_support_89_toggled));
    chk_compile_assemble.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_compile_assemble_toggled));
    chk_optimize.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_optimize_only_toggled));
    chk_add_dir.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_add_dir_toggled)); 
    chk_symbols.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_symbols_toggled));
    
    chk_indentation.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_indent_toggled));
    chk_auto_save.signal_toggled().connect(sigc::mem_fun(*this,&options_dialog::on_chk_auto_save_toggled));
    
    cmd_add_dir.signal_clicked().connect(sigc::mem_fun(*this,&options_dialog::cmd_add_dir_clicked));
    cmd_rem_dir.signal_clicked().connect(sigc::mem_fun(*this,&options_dialog::cmd_rem_dir_clicked));
    
    
    }

options_dialog::~options_dialog()
{
    }

void options_dialog::load_options()
{
    int pos_start, pos_end;
    std::string str = Glib::file_get_contents("./settings.ini");    

    pos_start = str.find("<indentation>")+13;
    pos_end=str.find("</indentation>");
    chk_indentation.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<indent_width>")+14;
    pos_end=str.find("</indent_width>");
    sb_indent_width.set_value(string_to_integer(str.substr(pos_start,pos_end-pos_start)));        
    
    pos_start = str.find("<auto_save>")+11;
    pos_end=str.find("</auto_save>");
    chk_auto_save.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));  
    
    pos_start = str.find("<auto_save_time>")+16;
    pos_end=str.find("</auto_save_time>");
    sb_auto_save_time.set_value(string_to_integer(str.substr(pos_start,pos_end-pos_start)));   
    
    pos_start = str.find("<line_numbers>")+14;
    pos_end=str.find("</line_numbers>");
    chk_line_numbers.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<auto_save_current>")+21;
    pos_end=str.find("</auto_save_current>");
    rb_current.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<auto_save_all>")+15;
    pos_end=str.find("</auto_save_all>");
    rb_all.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<tab_width>")+11;
    pos_end=str.find("</tab_width>");
    sb_tab_width.set_value(string_to_integer(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<word_wrap>")+11;
    pos_end=str.find("</word_wrap>");
    chk_word_wrap.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<recent_projects>")+17;
    pos_end=str.find("</recent_projects>");
    chk_recent_projects.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<recent_files>")+14;
    pos_end=str.find("</recent_files>");
    chk_recent_files.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<code_completion>")+17;
    pos_end=str.find("</code_completion>");
    chk_code_completion.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<highlight_line>")+16;
    pos_end=str.find("</highlight_line>");
    chk_highlight_line.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));    
    
    pos_start = str.find("<optimize>")+10;
    pos_end=str.find("</optimize>");
    chk_optimize.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    if(chk_optimize.get_active())
    {        
        pos_start = str.find("<optimize_level>")+16;
        pos_end=str.find("</optimize_level>");
        spin_optimize.set_value(string_to_integer(str.substr(pos_start,pos_end-pos_start)));
        }
    else
        spin_optimize.set_value(0);
    
    pos_start = str.find("<compile_assemble>")+18;
    pos_end=str.find("</compile_assemble>");
    chk_compile_assemble.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<support_c89>")+13;
    pos_end=str.find("</support_c89>");
    chk_support_89.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<warning_as_errors>")+19;
    pos_end=str.find("</warning_as_errors>");
    chk_warning.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<add_dir>")+9;
    pos_end=str.find("</add_dir>");
    chk_add_dir.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    if(chk_add_dir.get_active())
    {        
        pos_start = 0;
        pos_end = 0;
        Gtk::TreeModel::Row row;
        while((pos_start=str.find("<dir>",pos_start+1))!=-1 && (pos_end=str.find("</dir>",pos_end+1))!=-1)
        {
            row = *(dir_tree_model->append());
            row[dir_columns.m_col]= str.substr(pos_start+5,pos_end-pos_start-5);
            }
        }
    
    pos_start = str.find("<define_symbols>")+16;
    pos_end=str.find("</define_symbols>");
    chk_symbols.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<symbols>")+9;
    pos_end=str.find("</symbols>");
    entry_symbols.set_text(str.substr(pos_start,pos_end-pos_start));
    
    pos_start = str.find("<disable_inline>")+16;
    pos_end=str.find("</disable_inline>");
    chk_inline.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<compile_only>")+14;
    pos_end=str.find("</compile_only>");
    chk_compile_only.set_active(string_to_bool(str.substr(pos_start,pos_end-pos_start)));
    
    pos_start = str.find("<other_args>")+12;
    pos_end=str.find("</other_args>");
    entry_other_args.set_text(str.substr(pos_start,pos_end-pos_start));
    }

void options_dialog::on_chk_indent_toggled()
{
    lbl_indentation.set_sensitive(chk_indentation.get_active());
    sb_indent_width.set_sensitive(chk_indentation.get_active());
    }

void options_dialog::on_chk_auto_save_toggled()
{
    rb_current.set_sensitive(chk_auto_save.get_active());
    rb_all.set_sensitive(chk_auto_save.get_active());
    lbl_auto_save.set_sensitive(chk_auto_save.get_active());
    sb_auto_save_time.set_sensitive(chk_auto_save.get_active());
    }

void options_dialog::on_chk_toggled(Gtk::Widget& widget)
{
    widget.set_sensitive(!widget.get_sensitive());
    }

void options_dialog::cmd_add_dir_clicked()
{
    if(!chk_add_dir.get_active())
        return;
        
    Gtk::FileChooserDialog dialog(*this,"Select Folder",Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.add_button("Cancel",Gtk::RESPONSE_CANCEL);
    dialog.add_button("Open",Gtk::RESPONSE_OK);
    
    dialog.show_all_children();
    if(dialog.run()==Gtk::RESPONSE_OK)
    {
        Gtk::TreeModel::Row row;
        row = *(dir_tree_model->append());
        row[dir_columns.m_col]= dialog.get_filename();
        }
    }

void options_dialog::cmd_rem_dir_clicked()
{
    if(!chk_add_dir.get_active())
        return;

    Gtk::TreeModel::Row row = *(list_view_dir.get_selection()->get_selected());
    Glib::ustring file_path = row.get_value(dir_columns.m_col);
    Gtk::MessageDialog dialog(*this,Glib::ustring("Are you sure you want to remove the directory from search paths?"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
    if(dialog.run()==Gtk::RESPONSE_NO)
        return;
    dir_tree_model->erase(list_view_dir.get_selection()->get_selected());
    }

void options_dialog::on_chk_optimize_only_toggled()
{
    if(chk_optimize.get_active())
         entry_command.set_text(entry_command.get_text()+"-O"+integer_to_string(spin_optimize.get_value()));
    else
    {
        Glib::ustring command = entry_command.get_text();
        int i = command.find("-O");
        command = command.substr(0,i) + command.substr(i+3);
        entry_command.set_text(command);
        }
    }

void options_dialog::on_chk_compile_only_toggled()
{
    if(chk_compile_only.get_active())
         entry_command.set_text(entry_command.get_text()+"-S ");
    else
    {
        Glib::ustring command = entry_command.get_text();
        int i = command.find("-S ");
        command = command.substr(0,i) + command.substr(i+3);
        entry_command.set_text(command);
        }
    }
void options_dialog::on_chk_warning_toggled()
{
    if(chk_warning.get_active())
         entry_command.set_text(entry_command.get_text()+"-Werror ");
    else
    {
        Glib::ustring command = entry_command.get_text();
        int i = command.find("-Werror ");
        command = command.substr(0,i) + command.substr(i+8);        
        entry_command.set_text(command);
        }
    }
void options_dialog::on_chk_inline_toggled()
{
    if(chk_inline.get_active())
         entry_command.set_text(entry_command.get_text()+"-fno-asm ");
    else
    {
        Glib::ustring command = entry_command.get_text();
        int i = command.find("-fno-asm ");
        command = command.substr(0,i) + command.substr(i+9);
        entry_command.set_text(command);
        }
    }
void options_dialog::on_chk_support_89_toggled()
{
    if(chk_support_89.get_active())
         entry_command.set_text(entry_command.get_text()+"-ansi ");
    else
    {
        Glib::ustring command = entry_command.get_text();
        int i = command.find("-ansi ");
        command = command.substr(0,i) + command.substr(i+6);
        entry_command.set_text(command);
        }
    }
void options_dialog::on_chk_compile_assemble_toggled()
{
    if(chk_compile_assemble.get_active())
         entry_command.set_text(entry_command.get_text()+"-c ");
    else
    {
        Glib::ustring command = entry_command.get_text();
        int i = command.find("-c ");
        command = command.substr(0,i) + command.substr(i+3);
        entry_command.set_text(command);
        }
    }
void options_dialog::on_chk_add_dir_toggled()
{
    
    }
void options_dialog::on_chk_symbols_toggled()
{
    
    }