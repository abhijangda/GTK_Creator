//396 Lines
#include"project_class.h"

project_class::project_class(std::string _name,std::string _location,std::string _type)
:vector_dir(0),env_var_vector(0,env_var("")),file_path_vector(0)
{
    name=_name;
    location=_location;
    type=_type;
    compile_only=false;
    disable_inline=false;
    define_symbols=false;
    add_dir=false;
    warning_as_errors=false;
    support_c89=false;
    compile_assemble =false;
    optimize=false;
    optimize_level=-1;
    other_args="-o";
    out_dir=location+"/bin";
    curr_dir=location;
    params="";
    run_on_ext_console=true;
    }

project_class::project_class()
:file_path_vector(0)
{
    compile_only=false;
    disable_inline=false;
    define_symbols=false;
    add_dir=false;
    warning_as_errors=false;
    support_c89=false;
    compile_assemble =false;
    optimize=false;
    optimize_level=-1;
    other_args="-o";
    out_dir=location+"/bin";
    curr_dir=location;
    params="";
    run_on_ext_console=true;
    }

project_class::~project_class(){}

void project_class::set_files_to_location()
{
    Glib::ustring filepath,filename;
    for(int i = 0;i<file_path_vector.size();i++)
    {
        filepath = file_path_vector[i];
        filename = filepath.substr(filepath.rfind("/")+1);
        file_path_vector[i] = location+"/"+filename;
        }
    }

void project_class::append_file(std::string filepath)
{
    file_path_vector.insert(file_path_vector.end(),filepath);
    //proj_str+=proj_str + "<file>"+filepath+"</file>\n";
    write_to_file();
    }

std::string project_class::get_project_str()
{
    proj_str="";
    proj_str = "<name>"+name+"</name>\n"+"<type>"+type+"</type>\n"+"<location>"+location+"</location>\n";
    for(int i = 0;i<file_path_vector.size();i++)
        proj_str+="<file>"+file_path_vector[i]+"</file>\n";
    
    proj_str+="<compile_only>" +bool_to_string(compile_only)+"</compile_only>\n" ;
    proj_str+="<disable_inline>"+bool_to_string(disable_inline)+"</disable_inline>\n";
    proj_str+="<define_symbols>"+bool_to_string(define_symbols)+"</define_symbols>\n";
    proj_str+="<symbols>"+symbols+"</symbols>\n";
    proj_str+="<add_dir>"+bool_to_string(add_dir)+"</add_dir>\n";
    for(int i =0;i<vector_dir.size();i++)
        proj_str+="<dir>"+vector_dir[i]+"</dir>\n";
               
    proj_str+="<warning_as_errors>"+bool_to_string(warning_as_errors)+"</warning_as_errors>\n";
    proj_str+="<support_c89>"+bool_to_string(support_c89)+"</support_c89>\n";
    proj_str+="<compile_assemble>"+bool_to_string(compile_assemble)+"</compile_assemble>\n";
    proj_str+="<optimize>"+bool_to_string(optimize)+"</optimize>\n";
    proj_str+="<optimize_level>"+integer_to_string(optimize_level)+"</optimize_level>\n";
    proj_str+="<run_on_ext_console>"+bool_to_string(run_on_ext_console)+"</run_on_ext_console>\n";
    proj_str+="<out_dir>"+out_dir+"</out_dir>\n";
    proj_str+="<curr_dir>"+curr_dir+"</curr_dir>\n";
    proj_str+="<params>"+params+"</params>\n";    
    proj_str+="<other_args>"+other_args+"</other_args>\n";
    for(int i =0;i<env_var_vector.size();i++)
        proj_str+="<env>"+env_var_vector[i].get_string()+"</env>\n";

    return proj_str;
    }

void project_class::write_to_file()
{
    Glib::file_set_contents(proj_path,get_project_str());
    }

void project_class::set_location(std::string _l)
{
    location = _l;
    out_dir=location+"/bin";
    curr_dir=location;
    }

void project_class::clear()
{
    name="";
    location="";
    type="";
    file_path_vector.erase(file_path_vector.begin(),file_path_vector.end());
    proj_str="";
    proj_path="";
    compile_only=false;
    disable_inline=false;
    define_symbols=false;
    add_dir=false;
    warning_as_errors=false;
    support_c89=false;
    compile_assemble =false;
    optimize=false;
    optimize_level=-1;
    other_args="-o";
    out_dir=location+"/bin";
    curr_dir=location;
    params="";
    run_on_ext_console=true;
    }

void project_class::set_data_from_string(std::string _s)
{
    proj_str = _s;
    Glib::ustring str(_s);
    
    int pos_start = str.find("<name>")+6;//length_of_<name>
    int pos_end= str.find("</name>");    
    name = str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<type>")+6;
    pos_end = str.find("</type>");    
    type = str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<location>")+10;
    pos_end=str.find("</location>");
    location  = str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = 0;
    pos_end = 0;
    while((pos_start=str.find("<file>",pos_start+1))!=-1 && (pos_end=str.find("</file>",pos_end+1))!=-1)
        file_path_vector.insert(file_path_vector.end(),str.substr(pos_start+6,pos_end-pos_start-6));
    
    pos_start = str.find("<run_on_ext_console>")+20;
    pos_end=str.find("</run_on_ext_console>");
    run_on_ext_console=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<optimize>")+10;
    pos_end=str.find("</optimize>");
    optimize=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    if(optimize)
    {        
        pos_start = str.find("<optimize_level>")+16;
        pos_end=str.find("</optimize_level>");
        optimize_level=string_to_integer(str.substr(pos_start,pos_end-pos_start));
        //str.erase(pos_start,pos_end-pos_start);
        }
    else
        optimize_level=-1;
    
    pos_start = str.find("<compile_assemble>")+18;
    pos_end=str.find("</compile_assemble>");
    compile_assemble=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<support_c89>")+13;
    pos_end=str.find("</support_c89>");
    support_c89=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<warning_as_errors>")+19;
    pos_end=str.find("</warning_as_errors>");
    warning_as_errors=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<add_dir>")+9;
    pos_end=str.find("</add_dir>");
    add_dir=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    if(add_dir)
    {        
        pos_start = 0;
        pos_end = 0;
        while((pos_start=str.find("<dir>",pos_start+1))!=-1 && (pos_end=str.find("</dir>",pos_end+1))!=-1)
            vector_dir.insert(vector_dir.end(),str.substr(pos_start+5,pos_end-pos_start-5));
        }
    
    pos_start = str.find("<define_symbols>")+16;
    pos_end=str.find("</define_symbols>");
    define_symbols=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<symbols>")+9;
    pos_end=str.find("</symbols>");
    symbols=str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<disable_inline>")+16;
    pos_end=str.find("</disable_inline>");
    disable_inline=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<compile_only>")+14;
    pos_end=str.find("</compile_only>");
    compile_only=string_to_bool(str.substr(pos_start,pos_end-pos_start));
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<params>")+8;
    pos_end=str.find("</params>");    
    params=str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<curr_dir>")+10;
    pos_end=str.find("</curr_dir>");    
    curr_dir =str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);
    
    pos_start = str.find("<out_dir>")+9;
    pos_end=str.find("</out_dir>");
    out_dir=str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);    
    
    pos_start = str.find("<other_args>")+12;
    pos_end=str.find("</other_args>");
    other_args=str.substr(pos_start,pos_end-pos_start);
    //str.erase(pos_start,pos_end-pos_start);    
    
    pos_start = 0;
    pos_end = 0;
    while((pos_start=str.find("<env>",pos_start+1))!=-1 && (pos_end=str.find("</env>",pos_end+1))!=-1)
        env_var_vector.insert(env_var_vector.end(),env_var(str.substr(pos_start+5,pos_end-pos_start-5)));
    }

int project_class::get_optimize_level()
{
    return optimize_level;
    }
void project_class::set_optimize_level(int _l)
{
    optimize_level=_l;
    }
        
bool project_class::get_compile_only()
{
    return compile_only;
    }
void project_class::set_compile_only(bool _b)
{
    compile_only=_b;
    }
bool project_class::get_disable_inline()
{
    return disable_inline;
    }
void project_class::set_disable_inline(bool _b)
{
    disable_inline=_b;
    }
bool project_class::get_define_symbols()
{
    return define_symbols;
    }
void project_class::set_define_symbols(bool _b)
{
    define_symbols=_b;
    }
bool project_class::get_add_dir()
{
    return add_dir;
    }
void project_class::set_add_dir(bool _b)
{
    add_dir=_b;
    }
bool project_class::get_run_on_ext_console()
{
    return run_on_ext_console;
    }
void project_class::set_run_on_ext_console(bool _b)
{
    run_on_ext_console=_b;
    }
bool project_class::get_optimize()
{
    return optimize;
    }
void project_class::set_optimize(bool _b)
{
    optimize=_b;
    }
bool project_class::get_warning_as_errors()
{
    return warning_as_errors;
    }
void project_class::set_warning_as_errors(bool _b)
{
    warning_as_errors=_b;
    }
bool project_class::get_support_c89()
{
    return support_c89;
    }
void project_class::set_support_c89(bool _b)
{
    support_c89=_b;
    }
bool project_class::get_compile_assemble()
{
    return compile_assemble;
    }
void project_class::set_compile_assemble(bool _b)
{
    compile_assemble=_b;
    }

void project_class::set_curr_dir(std::string _s)
{
    curr_dir=_s;
    }
std::string project_class::get_curr_dir()
{
    return curr_dir;
    }
void project_class::set_out_dir(std::string _s)
{
    out_dir=_s;
    }
std::string project_class::get_out_dir()
{
    return out_dir;
    }
void project_class::set_params(std::string _s)
{
    params=_s;
    }
std::string project_class::get_params()
{
    return params;
    }

void project_class::set_other_args(std::string _s)
{
    other_args=_s;
    }
std::string project_class::get_other_args()
{
    return other_args;
    }
std::string project_class::get_command()
{
    std::string command = "gcc <input> ";
    int i = other_args.find("-o ");
    if (i!=std::string::npos)
         command += other_args.substr(0,other_args.find("-o ")+3)+" <output> " + other_args.substr(other_args.find("-o ")+3);
        //command += other_args +" <output> ";
    else
        command +=other_args;
    
    if(compile_only)
        command += "-S ";
    if(disable_inline)
        command += "-fno-asm ";
    if(define_symbols)
         command += "-D "+ symbols;
    if(add_dir) // Remember to do it
        command +="";
    if(warning_as_errors)
         command += "-Werror ";
    if(support_c89)
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