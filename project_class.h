//97 Lines
#include<string>
#include<vector>
#include<glibmm.h>
#include<iostream>
#include"helper_functions.h"

#ifndef PROJECT_CLASS_H
#define PROJECT_CLASS_H

class env_var
{
    public:
        env_var(std::string _name,std::string _val){name=_name;val=_val;}
        env_var(std::string full_str)
        {
            name = full_str.substr(0,full_str.find(" "));
            val=full_str.substr(full_str.find(" ")+1);
            };
        std::string get_string(){return name+" "+val;}
        std::string get_key_val_pair(){return name+"="+val;}
        std::string name;
        std::string val;
    };

class project_class
{
    public:
        project_class(std::string _name,std::string _location,std::string _type);
        project_class();
        ~project_class();
        void set_name(std::string _n){name=_n;}
        std::string get_name(){return name;}
        std::string get_path(){return location+"/"+name+".gtk_proj";}
        std::string get_location(){return location;}
        std::string get_type(){return type;}
        void set_location(std::string _l);
        void set_type(std::string _t){type=_t;}
        void set_path(std::string _p){proj_path=_p;}
        void append_file(std::string filepath);
        void clear();
        void set_data_from_string(std::string _s);
        std::vector<Glib::ustring> file_path_vector;
        void write_to_file();
        void set_files_to_location();
        std::string get_project_str();
        
        bool get_compile_only();
        void set_compile_only(bool _b);
        bool get_disable_inline();
        void set_disable_inline(bool _b);
        bool get_define_symbols();
        void set_define_symbols(bool _b);
        bool get_add_dir();
        void set_add_dir(bool _b);
        bool get_run_on_ext_console();
        void set_run_on_ext_console(bool _b);
        bool get_optimize();
        void set_optimize(bool _b);
        bool get_warning_as_errors();
        void set_warning_as_errors(bool _b);
        bool get_support_c89();
        void set_support_c89(bool _b);
        bool get_compile_assemble();
        void set_compile_assemble(bool _b);
        
        void set_curr_dir(std::string _s);
        std::string get_curr_dir();
        void set_out_dir(std::string _s);
        std::string get_out_dir();
        void set_params(std::string _s);
        std::string get_params();
        void set_other_args(std::string _s);
        std::string get_other_args();
        std::string get_command();
        
        int get_optimize_level();
        void set_optimize_level(int _l);
        
        std::vector<std::string> vector_dir;
        std::string symbols;
        std::vector<env_var> env_var_vector;
        
    private:
        std::string name;
        std::string location;
        std::string type;
        Glib::ustring proj_path;
        std::string proj_str;
        bool compile_only, disable_inline,define_symbols;
        bool add_dir,warning_as_errors,support_c89;
        bool compile_assemble, optimize;
        int optimize_level;
        std::string other_args;
        std::string out_dir,curr_dir,params;        
        bool run_on_ext_console;
    };
#endif