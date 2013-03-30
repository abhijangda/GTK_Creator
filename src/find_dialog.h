//32 Lines
#include<gtkmm/dialog.h>
#include<gtkmm/entry.h>
#include"source_view.h"

#ifndef FIND_DIALOG_H
#define FIND_DIALOG_H

class find_dialog : public Gtk::Dialog
{
    public:
        find_dialog(source_view&, Gtk::Window&,bool in_selectio=false);
        ~find_dialog();
        
    private:
        bool in_selection;
        void cmdfind_clicked(Gtk::Entry& entry);
        void cmdfindnext_clicked(Gtk::Entry& entry);
        void cmdfindprevious_clicked(Gtk::Entry& entry);
        void cmdclose_clicked();
        source_view& current_source_view;
        Glib::RefPtr<gtksourceview::SourceBuffer> buffer;
        Gtk::Button cmdfind;
        Gtk::Button cmdfindnext;
        Gtk::Button cmdfindprevious;
        Gtk::Button cmdclose;
        Gtk::Entry entry;
        Gtk::HBox hbox;
        Gtk::Label label;
        Gtk::TextIter selection_end,selection_start;
    };
#endif