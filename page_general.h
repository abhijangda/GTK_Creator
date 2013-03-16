//173 Lines
#include<gtkmm.h>
#include"frame.h"
#include"object_box.h"
#include"menubar_editor.h"

#ifndef PAGE_GENERAL_H
#define PAGE_GENERAL_H
class Model_Column : public Gtk::TreeModel::ColumnRecord
{
    public:
        Model_Column(){add(col);} 
        Gtk::TreeModelColumn<std::string> col;
    };

class PageGeneral : public Gtk::Table
{
    public:
        PageGeneral(Frame&,ObjectBox&);
        ~PageGeneral();
        Gtk::Entry txtName;
        std::vector<Gtk::Widget*> value_widget_vector;
        typedef sigc::signal<bool,std::string> type_signal_name_changed;
        type_signal_name_changed signal_name_changed();
        void set_property_values(Gtk::Widget&,std::string);
                
    private:
        Frame& current_frame;
        ObjectBox& object_box;
        Gtk::Label lblName;
        Glib::RefPtr<Gtk::EntryBuffer> txtNameBuffer;
        void on_txtentry_text_deleted(guint pos, guint chars);
        void on_txtentry_text_inserted(guint pos, const gchar* text, guint chars);
        Gtk::Widget* current_widget;
        std::string current_widget_type;
        Gtk::Widget* current_widget_parent;
        std::string current_widget_parent_type;
        bool send_name_change_signal;
        type_signal_name_changed m_signal_name_changed;
        Gtk::Button cmdEditToolbar;
        Gtk::Button cmdEditMenubar;
        
        std::vector<Gtk::Label*> label_vector;    
        int label_vector_size;
        
        Glib::RefPtr<Gtk::ListStore> cb_tree_model_win_type,cb_tree_model_true_false;
        Glib::RefPtr<Gtk::ListStore> cb_tree_model_scrollbar_policy,cb_tree_model_wrap_mode;        
        Glib::RefPtr<Gtk::ListStore> cb_tree_model_justification,cb_tree_model_toolbar_style;
        Glib::RefPtr<Gtk::ListStore> cb_tree_model_tab_position,cb_tree_model_pack_direction;
        Glib::RefPtr<Gtk::ListStore> cb_tree_model_stock;
        
        Model_Column model_column, model_column_scrollbar_policy,model_column_wrap_mode;
        Model_Column model_column_justification, model_win_type, model_column_toolbar_style;
        Model_Column model_column_tab_position,model_column_pack_direction;
        Model_Column_Stock model_column_stock;
        
        //gtk_label
        void on_lbltext_deleted(const Gtk::TextIter&,const Gtk::TextIter&);        
        void on_lbltext_inserted(const Gtk::TextIter&,const std::string&,int);       
        
        //gtk_window
        void cb_win_type_changed();
        void txt_win_title_deleted(int pos, int chars);
        void txt_win_title_inserted(int pos, const char* text, int chars);
        void sb_win_default_height_changed();
        void sb_win_default_width_changed();
        void cb_win_resizable();
        void cb_win_modal();
        void cb_win_destroy_with_parent();
        
        //gtk_vbox and gtk_hbox
        void sb_box_spacing_changed();
        void sb_box_number_of_items_changed();
        void cb_box_homogeneous_changed();
        
        //gtk_table
        void sb_table_row_spacing_changed();
        void sb_table_col_spacing_changed();
        void cb_table_homogeneous_changed();
        void sb_table_rows_changed();
        void sb_table_cols_changed();
        
        //gtk_scrollwin
        void cb_scroll_win_horizontal_policy_changed();
        void cb_scroll_win_vertical_policy_changed();
        
        //gtk_textview
        void sb_text_view_pixels_above_lines_changed();
        void sb_text_view_pixels_below_lines_changed();
        void sb_text_view_pixels_inside_wrap_changed();
        void cb_text_view_editable_changed();
        void cb_text_view_wrap_mode_changed();
        void cb_text_view_justification_changed();
        void cb_text_view_cursor_visible_changed();
        
        //gtk_button
        void sb_button_horizontal_alignment_changed();
        void sb_button_vertical_alignment_changed();
        void cb_button_focus_on_click_changed();
        void on_buttontext_deleted(const Gtk::TextIter&,const Gtk::TextIter&);
        void on_buttontext_inserted(const Gtk::TextIter&,const std::string&,int);
        void cb_stock_changed();
        
        //gtk_combobox and gtk_comboboxtext
        void sb_combo_box_set_active_changed();
        void sb_combo_box_row_span_changed();
        void sb_combo_box_column_span_changed();
        void sb_combo_box_wrap_width_changed();
        
        //gtk_togglebutton and gtk_radiobutton
        void cb_toggle_button_active_changed();
        void cb_toggle_button_inconsistent_changed();
        void cb_toggle_button_focus_on_click_changed();
        void sb_toggle_button_horizontal_alignment_changed();
        void sb_toggle_button_vertical_alignment_changed();
        void on_togglebuttontext_deleted(const Gtk::TextIter&,const Gtk::TextIter&);
        void on_togglebuttontext_inserted(const Gtk::TextIter&,const std::string&,int);
        
        //Gtk::Adjustment adjustment;
        //gtk_toolbar
        void cmdEditToolbar_clicked();
        void cb_toolbar_show_arrow_changed();
        void sb_toolbar_icon_size_changed();
        void cb_toolbar_toolbar_style_changed();
        
        //gtk_notebook
        void cb_notebook_tab_pos_changed();
        void cb_notebook_show_tabs_changed();
        void cb_notebook_show_border_changed();
        void cb_notebook_scrollable_changed();
        void sb_notebook_page_count_changed();
        
        //gtk_menubar
        void cmdEditMenubar_clicked();
        void update_menubar(Gtk::TreeModel::Children::iterator,item*,ModelColumnMenuBarEditor&);
        void cb_menubar_pack_direction_changed();
        void cb_menubar_child_pack_direction_changed();
        
        //gtk_offscreenwindow
        void cb_offscreen_window_focus_visible_changed();
        
        //gtk_eventbox
        void cb_event_box_visible_window_changed();
        void cb_event_box_above_child_changed();
        
        //gtk_expander
        void cb_expander_expanded_changed();
        void cb_expander_use_underline_changed();
        void cb_expander_use_markup_changed();
        void sb_expander_spacing_changed();
        void cb_expander_label_fill_changed();
        
        //gtk_vscale or gtk_hscale
        void sb_scale_digits_changed();
        void cb_scale_draw_value_changed();
        void cb_scale_inverted_changed();
        void cb_scale_show_fill_level_changed();
        void cb_scale_restrict_to_fill_level_changed();
        
        //gtk_progressbar
        void sb_progress_bar_fractions_changed();
        void sb_progress_bar_pulse_step_changed();
        
        //gtk_treeview
        void cb_tree_view_headers_visible_changed();
        void cb_tree_view_headers_clickable_changed();
        void cb_tree_view_reorderable_changed();
        void cb_tree_view_rules_hint_changed();
        //void cb_tree_view_headers_visible_changed();
        void sb_tree_view_search_column_changed();
        void cb_tree_view_fixed_height_mode_changed();
        void cb_tree_view_hover_selection_changed();
        void cb_tree_view_show_expanders_changed();
    };
#endif
