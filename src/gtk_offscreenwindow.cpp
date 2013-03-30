//16 Lines
#include "gtk_offscreenwindow.h"

extern Gtk::Widget* focussed_widget;
extern bool can_set_focus;

gtk_offscreenwindow::gtk_offscreenwindow(Gdk::Color color)
    : gtk_window(color)
{
    }

gtk_offscreenwindow::~gtk_offscreenwindow()
{
    }