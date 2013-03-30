//31 Lines
#include"helper_functions.h"

std::string integer_to_string(int integer)
{
    std::ostringstream oss;
    oss<<integer;
    return oss.str();
    }

int string_to_integer(std::string str)
{
    if(str == "")
        return 0;
    std::istringstream os(str);
    int x;
    os>>x;
    return x;
    }

bool string_to_bool(std::string str)
{
    if(str=="TRUE"||str=="true"||str=="True")
        return true;
    return false;
    }

std::string bool_to_string(bool _b)
{
    if(_b)
        return "TRUE";
    return "FALSE";
    }