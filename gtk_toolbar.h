//12 Lines 
#include<gtkmm/toolbar.h>

class gtk_toolbar : public Gtk::Toolbar
{
    public:
        gtk_toolbar();
        ~gtk_toolbar();
        std::string get_toolbarstyle();
        void set_toolbarstyle(std::string _toolbar_style);
    private:
        std::string toolbar_style;
    };