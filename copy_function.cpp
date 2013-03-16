#include"copy_function.h"
#include"gtk_window.h"
#include"gtk_vbox.h"
#include"gtk_hbox.h"
#include"gtk_table.h"
#include"gtk_fixed.h"
#include"gtk_scrollwin.h"
#include"gtk_textview.h"
#include"gtk_label.h"
#include"box_dialog.h"
#include"gtk_button.h"
#include"gtk_notebook.h"
#include"gtk_toolbar.h"
#include"gtk_menubar.h"
#include"gtk_eventbox.h"
#include"gtk_offscreenwindow.h"
#include"gtk_frame.h"
#include"gtk_button.h"
#include"gtk_combobox.h"
#include"gtk_entry.h"
#include"gtk_spinbutton.h"
#include"gtk_scale.h"
#include"gtk_hscrollbar.h"
#include"gtk_treeview.h"
#include"gtk_progressbar.h"
#include"gtk_spinner.h"
#include<gtkmm/statusbar.h>
#include<gtkmm/expander.h>
#include<gtkmm/filechooserbutton.h>
#include<gtkmm/colorbutton.h>
#include<gtkmm/fontbutton.h>

Gtk::Widget* copy_function(Gtk::Widget* widget, std::string type, Frame* frame)
{
    Gtk::Widget* _copy;
    if(type == "gtk_window")
    {
        //gtk_window* window = new gtk_window(scrollwin.get_style()->get_bg(Gtk::STATE_NORMAL));
        return NULL;
        }
    else if(type == "gtk_offscreenwindow")
    {
        //gtk_offscreenwindow* window = new gtk_offscreenwindow(scrollwin.get_style()->get_bg(Gtk::STATE_NORMAL));
        return NULL;
        }
    else if(type == "gtk_vbox")
    {
        gtk_vbox* current = dynamic_cast<gtk_vbox*>(widget);
        gtk_vbox* copy = new gtk_vbox(current->get_homogeneous(),current->get_spacing(),current->get_number_of_widgets()); 
        }
    else if(type == "gtk_button")       
    {        
        gtk_button* b = dynamic_cast<gtk_button*>(widget);
        gtk_button* copy = new gtk_button(b->get_label());
        float h,w;
        b->get_alignment(h,w);
        copy->set_alignment(h,w);    
        copy->set_focus_on_click(b->get_focus_on_click()); 
        copy->set_stock(b->get_stock());
        copy->set_use_stock(b->get_use_stock()); 
        _copy=copy;
        }      
        
    else if(type == "gtk_hbox")
    {
        gtk_hbox* current = dynamic_cast<gtk_hbox*>(widget);
        gtk_hbox* copy  = new gtk_hbox(current->get_homogeneous(),current->get_spacing(),current->get_number_of_widgets()); 
        _copy=copy;
        }
    else if(type == "gtk_table")
    {         
        gtk_table* current = dynamic_cast<gtk_table*>(widget);
        gtk_table* copy  = new gtk_table(current->get_rows(),current->get_cols(),current->get_homogeneous(),current->get_row_spacing(),current->get_col_spacing());
        _copy=copy;
        }
    else if(type == "gtk_fixed")
    {
        gtk_fixed* current = dynamic_cast<gtk_fixed*>(widget);
        gtk_fixed* copy  = new gtk_fixed(); 
        _copy=copy;
        }
    else if(type == "gtk_scrollwin")
    {
        gtk_scrollwin* current = dynamic_cast<gtk_scrollwin*>(widget);
        gtk_scrollwin* copy  = new gtk_scrollwin(); 
        _copy=copy;
        copy->set_horizontal_policy(current->get_horizontal_policy());
        copy->set_vertical_policy(current->get_vertical_policy());
        
        }
    else if(type == "gtk_textview")
    {
        gtk_textview* current = dynamic_cast<gtk_textview*>(widget);
        gtk_textview* copy  = new gtk_textview(); 
        _copy=copy;
        copy->set_pixels_above_lines(current->get_pixels_above_lines());                         
        copy->set_pixels_below_lines(current->get_pixels_below_lines());
        copy->set_pixels_inside_wrap(current->get_pixels_inside_wrap());
        copy->set_editable(current->get_editable());
        copy->set_wrapmode(current->get_wrapmode());
        copy->set_cursor_visible(current->get_cursor_visible());
        copy->set_justifi(current->get_justifi());
        }
    else if(type == "gtk_entry")
    {
        gtk_entry* current = dynamic_cast<gtk_entry*>(widget);
        gtk_entry* copy = new gtk_entry(); 
        _copy=copy;
        
        }
    else if(type == "gtk_label")
    {
        gtk_label* current = dynamic_cast<gtk_label*>(widget);
        gtk_label* copy = new gtk_label(current->get_text()); 
        _copy=copy;
        }
    else if(type == "gtk_togglebutton")
    {
        gtk_togglebutton* current = dynamic_cast<gtk_togglebutton*>(widget);
        gtk_togglebutton* copy = new gtk_togglebutton(current->get_label());
        
        _copy=copy;
        
        float h,w;
        current->get_alignment(h,w);
        copy->set_alignment(h,w);    
        copy->set_focus_on_click(current->get_focus_on_click());          
        copy->set_active(current->get_active());
        copy->set_inconsistent(current->get_inconsistent());
        }
    else if(type == "gtk_combobox")
    {
        gtk_combobox* current = dynamic_cast<gtk_combobox*>(widget);
        gtk_combobox* copy = new gtk_combobox(); 
        _copy=copy;
        copy->set_active(current->get_active());
        copy->set_row_span_column(current->get_row_span_column());
        copy->set_column_span_column(current->get_column_span_column());
        copy->set_wrap_width(current->get_wrap_width());
        }
    else if(type == "gtk_comboboxtext")
    {
        gtk_comboboxtext* current = dynamic_cast<gtk_comboboxtext*>(widget);
        gtk_comboboxtext* copy = new gtk_comboboxtext(true); 
        _copy=copy;
        copy->set_active(current->get_active());
        copy->set_row_span_column(current->get_row_span_column());
        copy->set_column_span_column(current->get_column_span_column());
        copy->set_wrap_width(current->get_wrap_width());
        }
    else if(type == "gtk_checkbutton")
    {
        gtk_checkbutton* current = dynamic_cast<gtk_checkbutton*>(widget);
        gtk_checkbutton* copy = new gtk_checkbutton("Check Button"); 
        _copy=copy;
        float h,w;
        current->get_alignment(h,w);
        copy->set_alignment(h,w);    
        copy->set_focus_on_click(current->get_focus_on_click());          
        copy->set_active(current->get_active());
        copy->set_inconsistent(current->get_inconsistent());
        }
    else if(type == "gtk_radiobutton")
    {
        gtk_radiobutton* current = dynamic_cast<gtk_radiobutton*>(widget);
        gtk_radiobutton* copy = new gtk_radiobutton("Radio Button");        
        _copy=copy;
        float h,w;
        current->get_alignment(h,w);
        copy->set_alignment(h,w);    
        copy->set_focus_on_click(current->get_focus_on_click());          
        copy->set_active(current->get_active());
        copy->set_inconsistent(current->get_inconsistent());
        }
    else if(type == "gtk_statusbar")
    {
        Gtk::Statusbar* current = dynamic_cast<Gtk::Statusbar*>(widget);
        Gtk::Statusbar* copy = new Gtk::Statusbar(); 
        _copy=copy;
        }
    else if(type == "gtk_menubar")
    {
        gtk_menubar* current = dynamic_cast<gtk_menubar*>(widget);
        gtk_menubar* copy = new gtk_menubar(); 
        _copy=copy;
        copy->set_packdirection(current->get_packdirection());
        copy->set_childpackdirection(current->get_childpackdirection());
        }
    else if(type == "gtk_toolbar")
    {
        gtk_toolbar* current = dynamic_cast<gtk_toolbar*>(widget);
        gtk_toolbar* copy = new gtk_toolbar();         
        _copy=copy;
        copy->set_toolbarstyle(current->get_toolbarstyle());
        }
    else if(type == "gtk_eventbox")
    {
        gtk_eventbox* current = dynamic_cast<gtk_eventbox*>(widget);
        gtk_eventbox* copy = new gtk_eventbox(current->get_style()->get_bg(Gtk::STATE_NORMAL));
        _copy=copy;
        }
    else if(type == "gtk_expander")
    {
        Gtk::Expander* current = dynamic_cast<Gtk::Expander*>(widget);
        Gtk::Expander* copy = new Gtk::Expander("Expander");        
        _copy=copy;
        copy->set_expanded(current->get_expanded());
        copy->set_use_underline(current->get_use_underline());
        copy->set_use_markup(current->get_use_markup());
        copy->set_spacing(current->get_spacing());
        copy->set_label_fill(current->get_label_fill());
        }
    else if(type == "gtk_spinbutton")
    {
        gtk_spin_button* current = dynamic_cast<gtk_spin_button*>(widget);
        gtk_spin_button* copy = new gtk_spin_button();
        _copy=copy;
        }
    else if(type == "gtk_filechooserbutton")
    {
        Gtk::FileChooserButton* current = dynamic_cast<Gtk::FileChooserButton*>(widget);
        Gtk::FileChooserButton* copy = new Gtk::FileChooserButton("File Chooser Button");
        _copy=copy;
        }
    else if(type == "gtk_colorchooserbutton")
    {
        Gtk::ColorButton* current = dynamic_cast<Gtk::ColorButton*>(widget);
        Gtk::ColorButton* copy = new Gtk::ColorButton();        
        _copy=copy;
        }
    else if(type == "gtk_fontbutton")
    {
        Gtk::FontButton* current = dynamic_cast<Gtk::FontButton*>(widget);
        Gtk::FontButton* copy = new Gtk::FontButton("Font Button");   
        _copy=copy;
        }
    else if(type == "gtk_hscale")
    {
        gtk_hscale* current = dynamic_cast<gtk_hscale*>(widget);
        gtk_hscale* copy = new gtk_hscale();
        copy->set_digits(current->get_digits());
        copy->set_draw_value(current->get_draw_value());
        copy->set_inverted(current->get_inverted());
        copy->set_show_fill_level(current->get_show_fill_level());
        copy->set_restrict_to_fill_level(current->get_restrict_to_fill_level());
        _copy=copy;
        }
    else if(type == "gtk_vscale")
    {
        gtk_vscale* current = dynamic_cast<gtk_vscale*>(widget);
        gtk_vscale* copy = new gtk_vscale();
        _copy=copy;
        copy->set_digits(current->get_digits());
        copy->set_draw_value(current->get_draw_value());
        copy->set_inverted(current->get_inverted());
        copy->set_show_fill_level(current->get_show_fill_level());
        copy->set_restrict_to_fill_level(current->get_restrict_to_fill_level());
        }
    else if(type == "gtk_hscrollbar")
    {
        gtk_hscrollbar* current = dynamic_cast<gtk_hscrollbar*>(widget);
        gtk_hscrollbar* copy = new gtk_hscrollbar();
        //copy->set_fraction(current ->get_fraction());
        //copy->set_pulse_step(current->get_pulse_step());
        _copy=copy;
        }
    else if(type == "gtk_progressbar")
    {
        gtk_progressbar* current = dynamic_cast<gtk_progressbar*>(widget);
        gtk_progressbar* copy = new gtk_progressbar();
        _copy=copy;
        copy->set_fraction(current ->get_fraction());
        copy->set_pulse_step(current->get_pulse_step());
        }
    else if(type == "gtk_spinner")
    {
        gtk_spinner* current = dynamic_cast<gtk_spinner*>(widget);
        gtk_spinner* copy = new gtk_spinner();
        _copy=copy;
        }
    else if(type == "gtk_treeview")
    {
        gtk_treeview* current = dynamic_cast<gtk_treeview*>(widget);
        gtk_treeview* copy = new gtk_treeview();
        _copy=copy;
        copy->set_headers_visible(current->get_headers_visible());
        copy->set_headers_clickable(current->get_headers_clickable());
        copy->set_reorderable(current->get_reorderable());
        copy->set_rules_hint(current->get_rules_hint());
        copy->set_search_column(current->get_search_column());
        copy->set_fixed_height_mode(current->get_fixed_height_mode());
        copy->set_hover_selection(current->get_hover_selection());
        copy->set_show_expanders(current->get_show_expanders());
        }
    else if(type == "gtk_frame")
    {
        gtk_frame* current = dynamic_cast<gtk_frame*>(widget);
        gtk_label* label = new gtk_label(current->get_label()->get_text());
        gtk_frame* copy = new gtk_frame(label);
        _copy=copy;
        }
    else if(type=="gtk_notebook")
    {
        gtk_notebook* current = dynamic_cast<gtk_notebook*>(widget);
        gtk_notebook* copy = new gtk_notebook(current->get_style()->get_bg(Gtk::STATE_NORMAL));        
        copy->signal_notebook_page_added().connect(sigc::mem_fun(*frame,&Frame::on_notebook_page_added));       
        copy->set_tab_pos(current->get_tab_pos());
        copy->set_show_tabs(current->get_show_tabs());
        copy->set_show_border(current->get_show_border());
        copy->set_scrollable(current->get_scrollable());
        copy->set_page_count(current->get_n_pages());
        _copy=copy;
        }  
    
    if(!_copy)
         return NULL;
        
    _copy->set_tooltip_text(widget->get_tooltip_text());    
    _copy->set_has_tooltip(widget->get_has_tooltip());        
    _copy->set_sensitive(widget->get_sensitive());         
    _copy->set_can_focus(widget->get_can_focus());       
    //copy->setwidget->has_focus()    
    _copy->set_has_tooltip(widget->get_has_tooltip()); 
    //widget->is_focus()       
    _copy->set_can_default(widget->get_can_default());
    //copywidget->has_default()
    _copy->set_size_request(widget->get_width(),widget->get_height());
    //_copy->get_parent()->set_size_request(widget->get_width()+2,widget->get_height()+2);
    _copy->set_name(widget->get_name());
    return _copy;
    }
