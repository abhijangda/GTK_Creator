//428 Lines
#include"project_preferences_dialog.h"

proj_pref_dialog::proj_pref_dialog(Gtk::Window& _parent,project_class& _proj)
: lbl_name("Name"),lbl_type("Type"),lbl_files("Files"),lbl_gcc("GCC Command"),current_proj(_proj),lbl_gcc_other_args("Other Arguments"),
  chk_compile_only("Compile only, do not assemble or link(-S)"), chk_warning("Treats warning as errors(-Werror)"),
  chk_inline("Disable use of inline, asm and typeof as keywrods(-fno-asm)"), chk_support_89("Support all C89 features(-ansi)"),
  chk_compile_assemble("Compile and assemble, do not link(-c)"), chk_optimize("Optimize with level (-O)"),
  chk_add_dir("Add Directories to compile search paths(-B<directory>)"), chk_symbols("Define Symbols"),
  cmd_add_file("Add File"), cmd_rem_file("Remove File"), cmd_ren_file("Rename File"), cmd_rem_all("Remove All"),
  cmd_add_dir("Add "), cmd_rem_dir("Remove"), cmd_add_env("Add"), cmd_rem_env("Remove"),
  lbl_out_dir("Output Directory"), lbl_param("Parameters"),lbl_curr_dir("Current Directory"), 
  lbl_env_var("Environment Variable"), chk_ext_console("Run on external console"),Gtk::Dialog("Project Preferences",_parent,false,true)
{
    notebook.append_page(fixed_general,"General");
    notebook.append_page(fixed_compiler,"Compiler");
    notebook.append_page(fixed_execution,"Execution");
    
    fixed_general.put(lbl_name,20,30);
    lbl_name.set_size_request(67,21);
    
    fixed_general.put(entry_name,100,26);
    entry_name.set_size_request(571,31);
    
    fixed_general.put(lbl_type,20,80);
    lbl_type.set_size_request(67,21);
    
    fixed_general.put(lbl_proj_type,100,80);
    lbl_proj_type.set_size_request(381,21);
    
    fixed_general.put(lbl_files,20,150);
    lbl_files.set_size_request(67,21);
    
    fixed_general.put(list_view_file,100,130);
    list_view_file.set_size_request(541,301);
    
    fixed_general.put(cmd_add_file,650,180);
    cmd_add_file.set_size_request(95,31);
    fixed_general.put(cmd_rem_file,650,230);
    cmd_rem_file.set_size_request(95,31);
    fixed_general.put(cmd_ren_file,650,280);
    cmd_ren_file.set_size_request(95,31);
    fixed_general.put(cmd_rem_all,650,330);
    cmd_rem_all.set_size_request(95,31);    
    
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
    
    fixed_compiler.put(lbl_gcc,10,413);
    lbl_gcc.set_size_request(101,21);
    
    fixed_compiler.put(entry_other_args,110,360);
    entry_other_args.set_size_request(640,31);
    
    fixed_compiler.put(lbl_gcc_other_args,10,350);
    lbl_gcc_other_args.set_size_request(91,41);
    lbl_gcc_other_args.set_line_wrap(true);
    
    fixed_execution.put(lbl_out_dir,10,20);
    lbl_out_dir.set_size_request(121,21);
    
    fixed_execution.put(lbl_param,10,70);
    lbl_param.set_size_request(67,21);
    
    fixed_execution.put(lbl_curr_dir,10,370);
    lbl_curr_dir.set_size_request(121,21);
    
    fixed_execution.put(lbl_env_var,10,114);
    lbl_env_var.set_size_request(181,21);
    
    fixed_execution.put(entry_out_dir,140,14);
    entry_out_dir.set_size_request(601,31);
    
    fixed_execution.put(entry_param,140,60);
    entry_param.set_size_request(601,31);
    
    fixed_execution.put(entry_curr_dir,140,370);
    entry_curr_dir.set_size_request(601,31);
    
    fixed_execution.put(chk_ext_console,10,410);
    chk_ext_console.set_size_request(191,26);

    fixed_execution.put(cmd_add_env,620,200);
    cmd_add_env.set_size_request(95,31);
    
    fixed_execution.put(cmd_rem_env,620,240);
    cmd_rem_env.set_size_request(95,31);
    
    fixed_execution.put(list_view_env_var,10,140);
    list_view_env_var.set_size_request(581,211);
    
    Gtk::VBox* dialog_vbox = get_vbox();
    dialog_vbox->pack_start(notebook,Gtk::PACK_EXPAND_WIDGET);
    
    Gtk::ButtonBox *dialog_button_box = get_action_area();
    
    //dialog_button_box->pack_end(cmd_apply);
    //dialog_button_box->pack_end(cmd_ok);
    //dialog_button_box->pack_end(cmd_cancel);
    
    Gtk::Button* cmd_ok = add_button("OK",1);
    Gtk::Button* cmd_cancel = add_button("Cancel",0);

    chk_optimize.signal_toggled().connect(sigc::bind<Gtk::Widget&>(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_toggled),spin_optimize)); 
    chk_add_dir.signal_toggled().connect(sigc::bind<Gtk::Widget&>(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_toggled),list_view_dir)); 
    chk_symbols.signal_toggled().connect(sigc::bind<Gtk::Widget&>(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_toggled),entry_symbols));
    
    cmd_add_file.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_add_file_clicked));
    cmd_rem_file.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_rem_file_clicked));
    cmd_ren_file.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_ren_file_clicked));
    cmd_rem_all.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_rem_all_clicked));
    
    cmd_add_dir.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_add_dir_clicked));
    cmd_rem_dir.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_rem_dir_clicked));
    
    cmd_add_env.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_add_env_clicked));
    cmd_rem_env.signal_clicked().connect(sigc::mem_fun(*this,&proj_pref_dialog::cmd_rem_env_clicked));
    
    file_tree_model = Gtk::ListStore::create(file_columns);
    list_view_file.set_model(file_tree_model);
    list_view_file.append_column("Files", file_columns.m_col);
    
    dir_tree_model = Gtk::ListStore::create(dir_columns);
    list_view_dir.set_model(dir_tree_model);
    list_view_dir.append_column("Directories", dir_columns.m_col);
    
    env_tree_model = Gtk::ListStore::create(env_columns);
    list_view_env_var.set_model(env_tree_model);
    list_view_env_var.append_column_editable("Name", env_columns.m_col_name);
    list_view_env_var.append_column_editable("Value", env_columns.m_col_value);
    
    chk_compile_only.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_compile_only_toggled));
    chk_warning.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_warning_toggled)); 
    chk_inline.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_inline_toggled));
    chk_support_89.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_support_89_toggled));
    chk_compile_assemble.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_compile_assemble_toggled));
    chk_optimize.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_optimize_only_toggled));
    chk_add_dir.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_add_dir_toggled)); 
    chk_symbols.signal_toggled().connect(sigc::mem_fun(*this,&proj_pref_dialog::on_chk_symbols_toggled));     
        
    Gtk::Adjustment* adjustment = spin_optimize.get_adjustment();
    adjustment->set_upper(9);
    adjustment->set_lower(0);
    adjustment->set_step_increment(1);     
    adjustment->set_page_increment(1);        
    spin_optimize.set_numeric(true);
    spin_optimize.set_adjustment(*adjustment);
    
    load_preferences();
    }

proj_pref_dialog::~proj_pref_dialog()
{
    }

void proj_pref_dialog::on_chk_optimize_only_toggled()
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

void proj_pref_dialog::on_chk_compile_only_toggled()
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
void proj_pref_dialog::on_chk_warning_toggled()
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
void proj_pref_dialog::on_chk_inline_toggled()
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
void proj_pref_dialog::on_chk_support_89_toggled()
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
void proj_pref_dialog::on_chk_compile_assemble_toggled()
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
void proj_pref_dialog::on_chk_add_dir_toggled()
{
    
    }
void proj_pref_dialog::on_chk_symbols_toggled()
{
    }

void proj_pref_dialog::cmd_add_env_clicked()
{
    Gtk::TreeModel::Row row;
    row = *(env_tree_model->append());
    }

void proj_pref_dialog::cmd_rem_env_clicked()
{
    Gtk::TreeModel::Row row = *(list_view_env_var.get_selection()->get_selected());
    env_tree_model->erase(list_view_env_var.get_selection()->get_selected());
    }
        
void proj_pref_dialog::cmd_add_dir_clicked()
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

void proj_pref_dialog::cmd_rem_dir_clicked()
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

void proj_pref_dialog::cmd_add_file_clicked()
{
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
    
    int result = dialog.run();
    if(result == Gtk::RESPONSE_OK)
    {
        Gtk::TreeModel::Row row;
        row = *(file_tree_model->append());
        row[file_columns.m_col]= dialog.get_filename();
        }
    }

void proj_pref_dialog::cmd_rem_file_clicked()
{
    Gtk::TreeModel::Row row = *(list_view_file.get_selection()->get_selected());
    Glib::ustring file_path = row.get_value(file_columns.m_col);
    Gtk::MessageDialog dialog(*this,Glib::ustring("Are you sure you want to remove the file?"),false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
    if(dialog.run()==Gtk::RESPONSE_NO)
        return;
    file_tree_model->erase(list_view_file.get_selection()->get_selected());
    }

void proj_pref_dialog::cmd_ren_file_clicked()
{
    
    }

void proj_pref_dialog::cmd_rem_all_clicked()
{
    file_tree_model->clear();
    }
        
void proj_pref_dialog::on_chk_toggled(Gtk::Widget& widget)
{
    widget.set_sensitive(!widget.get_sensitive());
    }

void proj_pref_dialog::load_preferences()
{
    entry_name.set_text(current_proj.get_name());
    lbl_proj_type.set_label(current_proj.get_type());
    
    Gtk::TreeModel::Row row;
    for(int i = 0;i<current_proj.file_path_vector.size();i++)
    {
        row = *(file_tree_model->append());
        row[file_columns.m_col]=current_proj.file_path_vector[i];
        }
    chk_compile_only.set_active(current_proj.get_compile_only());
    chk_warning.set_active(current_proj.get_warning_as_errors());
    chk_inline.set_active(current_proj.get_disable_inline());
    chk_support_89.set_active(current_proj.get_support_c89());
    chk_optimize.set_active(current_proj.get_optimize());
    if(current_proj.get_optimize())
    {
        spin_optimize.set_sensitive(true);
        spin_optimize.set_value(current_proj.get_optimize_level());
        }
    else
        spin_optimize.set_sensitive(false);
         
    chk_add_dir.set_active(current_proj.get_add_dir());
    if(current_proj.get_add_dir())
    {
        list_view_dir.set_sensitive(true);
        for(int i = 0;i<current_proj.vector_dir.size();i++)
        {
            row = *(dir_tree_model->append());
            row[dir_columns.m_col]=current_proj.vector_dir[i];
            }
        }
    else
        list_view_dir.set_sensitive(false);
        
    chk_symbols.set_active(current_proj.get_define_symbols());
    if(current_proj.get_define_symbols())
    {
        entry_symbols.set_sensitive(true);
        entry_symbols.set_text(current_proj.symbols);
        }
    else
        entry_symbols.set_sensitive(false);
    
    chk_ext_console.set_active(current_proj.get_run_on_ext_console());
    
    entry_out_dir.set_text(current_proj.get_out_dir());
    entry_param.set_text(current_proj.get_params());
    entry_curr_dir.set_text(current_proj.get_curr_dir());    
    
    entry_command.set_text(current_proj.get_command());
    entry_other_args.set_text(current_proj.get_other_args());
    show_all_children();
    }