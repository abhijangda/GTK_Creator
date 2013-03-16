//38 Lines
#include<gtkmm/dialog.h>
#include<gtkmm/label.h>
#include<gtkmm/button.h>
#include<gtkmm/entry.h>
#include<gtkmm/window.h>

#ifndef BOX_DIALOG_H
#define BOX_DIALOG_H

class BoxDialog : public Gtk::Dialog
{
    public:
        BoxDialog(std::string);
        ~BoxDialog();
    
        Gtk::Label lblSlots, lblHomogeneous, lblSpacing;
        Gtk::Entry entrySlots, entrySpacing;
        Gtk::RadioButton rbFalse, rbTrue;
        Gtk::HBox hboxSlots, hboxSpacing, hboxHomogeneous;
        Gtk::VBox vbox, vboxTrueFalse;
        Gtk::RadioButtonGroup grpRadio;
    };

class TableDialog : public Gtk::Dialog
{
    public:
        TableDialog(std::string);
        ~TableDialog();
        
        Gtk::Label lblRows, lblColumns, lblHomogeneous, lblRowSpacing, lblColumnSpacing;
        Gtk::Entry entryRows, entryColumns, entryRowSpacing, entryColumnSpacing;
        Gtk::RadioButton rbFalse, rbTrue;
        Gtk::RadioButtonGroup grpRadio;
        Gtk::HBox hboxRows, hboxColumns, hboxHomogeneous, hboxRowSpacing,hboxColumnSpacing;
        Gtk::VBox vbox, vboxTrueFalse;
    };
#endif