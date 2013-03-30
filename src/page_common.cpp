//199 Lines
#include"page_common.h"
 
PageCommon::~PageCommon(){}
PageCommon::PageCommon()
    :Gtk::Table(2,18,false), lblwidth_request("Width Request"), lblheight_request("Height Request"), lbltooltip_text("ToolTip Text"), lblvisible("Visible"), 
    lblsensitive("Sensitive"), lblcanfocus("Can Focus"), lblhasfocus("Has Focus"), lblisfocus("Is Focus"), lblcandefault("Can Default"),
    lblhasdefault("Has Default"), lblhastooltip("Has ToolTip"), lblhorizontal_alignment("Horizontal Alignment"), lblvertical_alignment("Vertical Alignment"),
    lblleft_margin("Left Margin"), lblright_margin("Right Margin"), lbltop_margin("Top Margin"), lblbottom_margin("Bottom Margin"),
    width_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0),height_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0),horizontal_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0),
    vertical_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0), left_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0), right_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0),
    top_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0), bottom_adjustment(1.0,0.0,1000.0,1.0,1.0,0.0) 
{
    attach(lblwidth_request,0,1,0,1);
    attach(lblheight_request,0,1,1,2);
    attach(lbltooltip_text,0,1,2,3);
    attach(lblvisible,0,1,3,4);
    attach(lblsensitive,0,1,4,5);
    attach(lblcanfocus,0,1,5,6);
    attach(lblhasfocus,0,1,6,7);
    attach(lblisfocus,0,1,7,8);
    attach(lblcandefault,0,1,8,9);
    attach(lblhasdefault,0,1,9,10);
    attach(lblhastooltip,0,1,10,11);
    attach(lblhorizontal_alignment,0,1,11,12);
    attach(lblvertical_alignment,0,1,12,13);
    attach(lblleft_margin,0,1,13,14);
    attach(lblright_margin,0,1,14,15);
    attach(lbltop_margin,0,1,15,16);
    attach(lblbottom_margin,0,1,16,17); 
    
    attach(sbwidth_request,1,2,0,1);
    attach(sbheight_request,1,2,1,2);        
    attach(tooltip_text,1,2,2,3);
    attach(cbvisible,1,2,3,4);
    attach(cbsensitive,1,2,4,5);
    attach(cbcanfocus,1,2,5,6);
    attach(cbhasfocus,1,2,6,7);
    attach(cbisfocus,1,2,7,8);
    attach(cbcandefault,1,2,8,9);
    attach(cbhasdefault,1,2,9,10);
    attach(cbhastooltip,1,2,10,11);
    attach(sbhorizontal_alignment,1,2,11,12);
    attach(sbvertical_alignment,1,2,12,13);
    attach(sbleft_margin,1,2,13,14);
    attach(sbright_margin,1,2,14,15);
    attach(sbtop_margin,1,2,15,16);
    attach(sbbottom_margin,1,2,16,17);   
    
    sbwidth_request.configure(width_adjustment,1.0,0);
    sbheight_request.configure(height_adjustment,1.0,0); 
    sbhorizontal_alignment.configure(horizontal_adjustment,1.0,0); 
    sbvertical_alignment.configure(vertical_adjustment,1.0,0);  
    sbleft_margin.configure(left_adjustment,1.0,0); 
    sbright_margin.configure(right_adjustment,1.0,0); 
    sbtop_margin.configure(top_adjustment,1.0,0); 
    sbbottom_margin.configure(bottom_adjustment,1.0,0);
    
    cb_tree_model=Gtk::ListStore::create(model_column);
    Gtk::TreeModel::Row row = *(cb_tree_model->append());
    row[model_column.col_true_false] = "TRUE";
    row = *(cb_tree_model->append());
    row[model_column.col_true_false] = "FALSE";
    
    cbvisible.set_model(cb_tree_model);
    cbvisible.pack_start(model_column.col_true_false);
    cbsensitive.set_model(cb_tree_model);
    cbsensitive.pack_start(model_column.col_true_false);
    cbcanfocus.set_model(cb_tree_model);
    cbcanfocus.pack_start(model_column.col_true_false);
    cbhasfocus.set_model(cb_tree_model);
    cbhasfocus.pack_start(model_column.col_true_false);
    cbhastooltip.set_model(cb_tree_model);  
    cbhastooltip.pack_start(model_column.col_true_false);
    cbisfocus.set_model(cb_tree_model);  
    cbisfocus.pack_start(model_column.col_true_false);
    cbcandefault.set_model(cb_tree_model);  
    cbcandefault.pack_start(model_column.col_true_false);
    cbhasdefault.set_model(cb_tree_model);  
    cbhasdefault.pack_start(model_column.col_true_false);   
    
    can_update_height_and_width=false;
    
    width_adjustment.signal_value_changed().connect(sigc::mem_fun(*this,&PageCommon::on_sbsize_request_digits_changed));
    height_adjustment.signal_value_changed().connect(sigc::mem_fun(*this,&PageCommon::on_sbsize_request_digits_changed));
    cbvisible.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbvisible_changed));
    cbsensitive.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbsensitive_changed));
    cbcanfocus.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbcanfocus_changed));
    cbhasfocus.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbhasfocus_changed));
    cbhastooltip.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbhastooltip_changed));
    cbisfocus.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbisfocus_changed));
    cbcandefault.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbcandefault_changed));
    cbhasdefault.signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_cbhasdefault_changed));
    
    tooltip_text.get_buffer()->signal_changed().connect(sigc::mem_fun(*this,&PageCommon::on_tooltip_text_changed));
    }

void PageCommon::on_tooltip_text_changed()
{
    current_widget->set_tooltip_text(tooltip_text.get_buffer()->get_text());
    }

void PageCommon::on_cbvisible_changed()
{    
    }

void PageCommon::on_cbsensitive_changed()
{
    current_widget->set_sensitive(!cbsensitive.get_active_row_number());
    }

void PageCommon::on_cbcanfocus_changed()
{
    current_widget->set_can_focus(!cbcanfocus.get_active_row_number());
    }

void PageCommon::on_cbhasfocus_changed()
{
    //current_widget->set_sensitive(cbsensitive.set_value());
    }

void PageCommon::on_cbhastooltip_changed()
{
    current_widget->set_has_tooltip(!cbhastooltip.get_active_row_number());
    }

void PageCommon::on_cbisfocus_changed()
{
    //current_widget->set_sensitive(cbsensitive.set_value());
    }

void PageCommon::on_cbcandefault_changed()
{
    current_widget->set_can_default(!cbcandefault.get_active_row_number());
    }

void PageCommon::on_cbhasdefault_changed()
{
    //current_widget->set_sensitive(cbsensitive.set_value());
    }

void PageCommon::set_property_values(Gtk::Widget& widget, std::string type)
{
    current_widget = &widget;
    can_update_height_and_width=false;
    sbwidth_request.set_value(widget.size_request().width);
    sbheight_request.set_value(widget.size_request().height);
    can_update_height_and_width=true;
    tooltip_text.get_buffer()->set_text(widget.get_tooltip_text());
    
    if(widget.get_has_tooltip())
        cbvisible.set_active(0);
    else
        cbvisible.set_active(1);
        
    if(widget.get_sensitive())
        cbsensitive.set_active(0);
    else
        cbsensitive.set_active(1);
    
    if(widget.get_can_focus())
        cbcanfocus.set_active(0);
    else
        cbcanfocus.set_active(1);
        
    if(widget.has_focus())
        cbhasfocus.set_active(0);
    else
        cbhasfocus.set_active(1);
    
    if(widget.get_has_tooltip())
        cbhastooltip.set_active(0);
    else
        cbhastooltip.set_active(1);       
    
    if(widget.is_focus())
        cbisfocus.set_active(0);
    else
        cbisfocus.set_active(1);       
        
    if(widget.get_can_default())
        cbcandefault.set_active(0);
    else
        cbcandefault.set_active(1);       
        
    if(widget.has_default())
        cbhasdefault.set_active(0);
    else
        cbhasdefault.set_active(1);
    }

void PageCommon::on_sbsize_request_digits_changed()
{
    if(can_update_height_and_width)
    {
        current_widget->set_size_request(sbwidth_request.get_value(),sbheight_request.get_value());
        current_widget->get_parent()->set_size_request(sbwidth_request.get_value()+2,sbheight_request.get_value()+2);
        }    
    }