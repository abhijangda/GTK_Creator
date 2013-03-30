//19 lines
#include<gtkmm/widget.h>

#ifndef FOCUSED_WIDGET_H
#define FOCUSED_WIDGET_H

class focused_widget
{
    public:
        focused_widget();
        ~focused_widget();
        void set_value(Gtk::Widget*);
        Gtk::Widget* get_value();
        typedef sigc::signal<void,Gtk::Widget*,Gtk::Widget*> type_signal_focused_widget_change;
        type_signal_focused_widget_change signal_focused_widget_change();
    private:
        Gtk::Widget *widget;
        type_signal_focused_widget_change m_signal_focused_widget_change;
    };
#endif