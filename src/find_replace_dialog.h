//27 Lines
#include<gtkmm/dialog.h>
#include<gtkmm/entry.h>
#include<gtkmm/fixed.h>
#include"source_view.h"

#ifndef FIND_REPLACE_DIALOG_H
#define FIND_REPLACE_DIALOG_H

class find_replace_dialog : public Gtk::Dialog
{
    public:
        find_replace_dialog(source_view&, Gtk::Window&);
        ~find_replace_dialog();
        
    private:
        source_view& current_source_view;
        Glib::RefPtr<gtksourceview::SourceBuffer> buffer;
        Gtk::Button cmdfind,cmdreplace,cmdreplaceall,cmdclose;
        Gtk::Fixed fixed;
        Gtk::Label lblfind,lblreplace;
        Gtk::Entry entry_find,entry_replace;
        void cmdreplace_clicked(Gtk::Entry& entry_find,Gtk::Entry& entry_replace);
        void cmdreplaceall_clicked(Gtk::Entry& entry_find,Gtk::Entry& entry_replace);
        void cmdfind_clicked(Gtk::Entry& entry);
        void cmdclose_clicked(){destroy_();}
    };
#endif