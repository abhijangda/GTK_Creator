//26 lines
#include"focused_widget.h"

focused_widget::focused_widget()
: widget(0)
{
    }

focused_widget::~focused_widget()
{
    }

void focused_widget::set_value(Gtk::Widget* _widget)
{
    m_signal_focused_widget_change(widget,_widget);
    widget=_widget;
    }

Gtk::Widget* focused_widget::get_value()
{
    return widget;
    }

focused_widget::type_signal_focused_widget_change focused_widget::signal_focused_widget_change()
{
    return m_signal_focused_widget_change;
    }