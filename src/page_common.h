//84 Lines
#include<gtkmm.h>
#include<string>

#ifndef PAGE_COMMON_H
#define PAGE_COMMON_H

class ModelColumn : public Gtk::TreeModel::ColumnRecord
{
    public:
        ModelColumn(){add(col_true_false);} 
        Gtk::TreeModelColumn<std::string> col_true_false;
    };

class PageCommon : public Gtk::Table
{
    public:
        PageCommon();
        ~PageCommon();
        
        Gtk::SpinButton sbwidth_request;
        Gtk::SpinButton sbheight_request;        
        Gtk::TextView tooltip_text;
        Gtk::ComboBox cbvisible;
        Gtk::ComboBox cbsensitive;
        Gtk::ComboBox cbcanfocus;
        Gtk::ComboBox cbhasfocus;
        Gtk::ComboBox cbisfocus;
        Gtk::ComboBox cbcandefault;
        Gtk::ComboBox cbhasdefault;
        Gtk::ComboBox cbhastooltip;
        Gtk::SpinButton sbhorizontal_alignment;
        Gtk::SpinButton sbvertical_alignment;
        Gtk::SpinButton sbleft_margin;
        Gtk::SpinButton sbright_margin;
        Gtk::SpinButton sbtop_margin;
        Gtk::SpinButton sbbottom_margin;        
        
        void set_property_values(Gtk::Widget&,std::string);
        
    private:
        bool can_update_height_and_width;
        void on_sbsize_request_digits_changed();
        void on_cbvisible_changed();
        void on_cbsensitive_changed();
        void on_cbcanfocus_changed();
        void on_cbhasfocus_changed();
        void on_cbhastooltip_changed();
        void on_cbisfocus_changed();
        void on_cbcandefault_changed();
        void on_cbhasdefault_changed();
        void on_tooltip_text_changed();
        Gtk::Widget* current_widget;
        Glib::RefPtr<Gtk::ListStore> cb_tree_model;
        
        ModelColumn model_column;
        
        Gtk::Adjustment width_adjustment;
        Gtk::Adjustment height_adjustment;
        Gtk::Adjustment horizontal_adjustment;
        Gtk::Adjustment vertical_adjustment;
        Gtk::Adjustment left_adjustment;
        Gtk::Adjustment right_adjustment;
        Gtk::Adjustment top_adjustment;
        Gtk::Adjustment bottom_adjustment;
        
        Gtk::Label lblwidth_request;
        Gtk::Label lblheight_request;
        Gtk::Label lbltooltip_text;
        Gtk::Label lblvisible;
        Gtk::Label lblsensitive;
        Gtk::Label lblcanfocus;
        Gtk::Label lblhasfocus;
        Gtk::Label lblisfocus;
        Gtk::Label lblcandefault;
        Gtk::Label lblhasdefault;
        Gtk::Label lblhastooltip;
        Gtk::Label lblhorizontal_alignment;
        Gtk::Label lblvertical_alignment;
        Gtk::Label lblleft_margin;
        Gtk::Label lblright_margin;
        Gtk::Label lbltop_margin;
        Gtk::Label lblbottom_margin; 
    };
#endif