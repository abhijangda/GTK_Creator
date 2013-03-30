//181 Lines
#include"compiler.h"

compiler_win::compiler_win(Gtk::Window& _parent, std::string _command,std::string _mode,project_class& _p)
: cmdRun("Run"),cmdCancel("Cancel"),command(_command),Gtk::Dialog("Compiling",_parent),lbl_source_name("",Gtk::ALIGN_START,Gtk::ALIGN_START),
 lbl_destination_name("",Gtk::ALIGN_START,Gtk::ALIGN_START),lbl_compiler_name("GNU C Compiler",Gtk::ALIGN_START,Gtk::ALIGN_START),mode(_mode),
current_proj(_p),frame("")
{
    lbl_compiler.set_text("Compiler           ");
    hbox_compiler.pack_start(lbl_compiler,Gtk::PACK_SHRINK,5);
    hbox_compiler.pack_start(lbl_compiler_name,Gtk::PACK_EXPAND_WIDGET,5);

    lbl_source.set_text("Source File        ");
    
    hbox_source.pack_start(lbl_source,Gtk::PACK_SHRINK,5);
    hbox_source.pack_start(lbl_source_name,Gtk::PACK_EXPAND_WIDGET,5);
    
    lbl_destination.set_text("Destination File");   
    hbox_destination.pack_start(lbl_destination,Gtk::PACK_SHRINK,5);
    hbox_destination.pack_start(lbl_destination_name,Gtk::PACK_EXPAND_WIDGET,5);
    
    cmdRun.signal_clicked().connect(sigc::mem_fun(*this,&compiler_win::cmdRun_clicked));
    cmdCancel.signal_clicked().connect(sigc::mem_fun(*this,&compiler_win::cmdCancel_clicked));
    cmdRun.set_sensitive(false);
    
    Gtk::ButtonBox *dialog_button_box = get_action_area();
    
    dialog_button_box->pack_start(cmdCancel);
    dialog_button_box->pack_start(cmdRun);
    
    cmdRun.set_size_request(95,31);
    cmdCancel.set_size_request(95,31);
    
    scrollwin.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    scrollwin.set_border_width(5);
    scrollwin.add(list_view_output);
    frame.add(scrollwin);
    frame.set_border_width(0);
    
    vbox.pack_start(hbox_compiler,Gtk::PACK_SHRINK,5);
    vbox.pack_start(hbox_source,Gtk::PACK_SHRINK,5);
    vbox.pack_start(hbox_destination,Gtk::PACK_SHRINK,5);
    vbox.pack_start(frame,Gtk::PACK_EXPAND_WIDGET,5);
        
    tree_model_output = Gtk::ListStore::create(out_columns);
    list_view_output.set_model(tree_model_output);
    list_view_output.append_column("Errors and Warnings", out_columns.m_col);
    
    set_size_request(600,500);
    set_border_width(5);
    
    Gtk::VBox *dialog_vbox = get_vbox();
    dialog_vbox->pack_start(vbox);
    }

compiler_win::~compiler_win(){}

void compiler_win::compile(std::string path)
{
    std::string out,err,new_path;
    int exit=0;
    std::string::iterator start_iter = path.begin(),end_iter = path.end();
    while(start_iter != end_iter)
    {
        if(*start_iter == ' ' || *start_iter == '#')
            new_path = new_path + '\\' + *start_iter;
        else
            new_path = new_path + *start_iter;
        start_iter++;
        }
    Glib::spawn_command_line_sync("/bin/bash -c \'"+command+"\'",&out,&err,&exit);
    if (err == "" && out == "")
    {
        Gtk::TreeModel::Row row;
        row = *(tree_model_output->append());
        row[out_columns.m_col] = "Program Successfully Compiled";
        cmdRun.set_sensitive(true);
        }
    else
    {
        int pos_start=0,pos_end=0;
        Gtk::TreeModel::Row row;
        while((pos_end=err.find("\n",pos_end+1))!=-1)
        {
            row = *(tree_model_output->append());
            row[out_columns.m_col] = err.substr(pos_start+1,pos_end-pos_start-1);
            pos_start=err.find("\n",pos_start+1);
            }
        cmdRun.set_sensitive(false);
        }
    lbl_destination_name.set_text(compiled_path);
    lbl_source_name.set_text(path);
    show_all_children();
    }

void compiler_win::cmdRun_clicked()
{
    if(mode == "FILE")
    {
        file_run_dialog dialog(*this);
        dialog.show_all_children();
        if(dialog.run()==1)
        {
            std::vector<std::string> argv(0);
            if(dialog.chk_run_on_ext_console.get_active())
            {
                argv.insert(argv.end(),"./shell");
                argv.insert(argv.end(),compiled_path + " " + dialog.entry_args.get_text());
                }
            else
            {
                argv.insert(argv.end(),compiled_path);
                int pos_start=0,pos_end=0;
                while((pos_end=dialog.entry_args.get_text().find(" ",pos_end+1))!=-1)
                {
                    argv.insert(argv.end(),dialog.entry_args.get_text().substr(pos_start+1,pos_end-pos_start-1));
                    pos_start=dialog.entry_args.get_text().find(" ",pos_start+1);
                    }
                }
            std::string env_str = dialog.txt_envs.get_buffer()->get_text();           
            std::vector<std::string> envp(0);
            int pos_start=0,pos_end=0;
            while((pos_end=env_str.find(" ",pos_end+1))!=-1)
            {
                envp.insert(envp.end(),env_str.substr(pos_start+1,pos_end-pos_start-1));
                pos_start=env_str.find(" ",pos_start+1);
                }
            if(envp.size()==0)
                 Glib::spawn_async(dialog.entry_curr_dir.get_text(),argv);
            else
                 Glib::spawn_async(dialog.entry_curr_dir.get_text(),argv,envp);
            }       
        }
    else if(mode == "PROJECT")
    {
        std::vector<std::string> argv(0);
        if(current_proj.get_run_on_ext_console())
        {
            argv.insert(argv.end(),"/media/sda11/C++/gtkmm/gtk_creator_source/shell");
            argv.insert(argv.end(),compiled_path + " " +current_proj.get_params());
            }
        else 
        {
            argv.insert(argv.end(),compiled_path);
            int pos_start=0,pos_end=0;
            while((pos_end=current_proj.get_params().find(" ",pos_end+1))!=-1)
            {
                argv.insert(argv.end(),current_proj.get_params().substr(pos_start+1,pos_end-pos_start-1));
                pos_start=current_proj.get_params().find(" ",pos_start+1);
                }
            }
        std::vector<std::string> envp(0);
        for(int i = 0;i <current_proj.env_var_vector.size();i++)
             envp.insert(envp.end(),current_proj.env_var_vector[i].get_key_val_pair());
        if(envp.size()==0)
             Glib::spawn_async(current_proj.get_curr_dir(),argv);
        else
              Glib::spawn_async(current_proj.get_curr_dir(),argv,envp);
        }
    }

void compiler_win::cmdCancel_clicked()
{
    delete this;
    }

void compiler_win::run_and_compile(project_class& _proj,std::string _compile_path)
{
    current_proj = _proj;
    compiled_path = _compile_path;
    compile(current_proj.get_path());
    }
void compiler_win::run_and_compile(std::string source_path,std::string _compile_path)
{
    compiled_path = _compile_path;
    compile(source_path);
    //cmdRun_clicked();
    }
