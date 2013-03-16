//15 Lines
//6963 Total lines
#include"main_window.h"
#include<gtksourceviewmm/init.h>

int main(int argc,char *argv[])
{
    Glib::thread_init();
    Gtk::Main kit(argc,argv);
    gtksourceview::init();
    main_window main_win;
    
    Gtk::Main::run(main_win);
    
    return 0;
    }