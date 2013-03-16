//27 Lines
#include<gtkmm/dialog.h>
#include<gtkmm/button.h>
#include<gtkmm/entry.h>
#include<gtkmm/label.h>
#include"source_view.h"
#include<glibmm/regex.h>

#ifndef REG_EXP_SEARCH_H
#define REG_EXP_SEARCH_H

class reg_exp_search_dialog : public Gtk::Dialog
{
    public:
        reg_exp_search_dialog(source_view&);
        ~reg_exp_search_dialog();
        
    private:
        int counter;
        source_view& current_source_view;
        Gtk::Button cmd_search,cmd_close;
        Gtk::Label lbl_regexp;
        Gtk::Entry entry_regexp;
        Gtk::HBox hbox;       
        void cmd_search_clicked();
        void cmd_close_clicked();
    };
#endif