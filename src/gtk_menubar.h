//14 Lines
#include<gtkmm/menubar.h>

class gtk_menubar : public Gtk::MenuBar
{
    public:
        gtk_menubar();
        ~gtk_menubar();
        void set_packdirection(std::string);
        std::string get_packdirection();
        void set_childpackdirection(std::string _direction);
        std::string get_childpackdirection();
        void remove_child_widget(Gtk::MenuItem*);
    };
