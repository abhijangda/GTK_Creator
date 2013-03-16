//103 Lines
#include"toolbar_editor.h"
#include"gtk_tool_button.h"

toolbar_editor::toolbar_editor(item* _toolbar_item)
    : Gtk::Dialog("Edit Toolbar",true,true),cmdAdd("Add Item"),cmdRemove("Remove Item"),lblName("Name"),lblText("Text"),
   entry_name(),entry_text(),type_group(),type_frame("Type"),type_item("Tool Button"), type_separator("Separator"), type_radio("Radio Tool Button"),type_check("Check Tool Button"),
   toolbar_item(_toolbar_item),tree_view(),chk_active("Active"),scrollwin(),lblStock("Stock")        
{    
    cmdSave=add_button("Save",1);  
    cmdCancel = add_button("Cancel",0);     
    treemodel = Gtk::ListStore::create(columns);
    tree_view.set_model(treemodel);
    tree_view.append_column("Name",columns.col_name);
    tree_view.append_column("Text",columns.col_text);
    tree_view.append_column("Type",columns.col_type);
    tree_view.append_column("Stock",columns.col_stock);
    
    //Load ToolbarItems
    item* toolbar_child = toolbar_item->child;
    std::string type;
    while(toolbar_child!=NULL)
    {
        if(toolbar_child->type=="gtk_tool_button")
            type="Button";
        else if(toolbar_child->type=="gtk_separator_item")
            type="Separator";
        else if(toolbar_child->type == "gtk_radio_tool_button")
            type="Radio";
            
        Gtk::TreeModel::Row row = *(treemodel->append());
        row[columns.col_name]=toolbar_child->widget->get_name();
        if(toolbar_child->type=="gtk_tool_button")
        {
            row[columns.col_text]=dynamic_cast<gtk_tool_button*>(toolbar_child->widget)->get_label();
            row[columns.col_stock]=dynamic_cast<gtk_tool_button*>(toolbar_child->widget)->get_stock();
            }
        if(toolbar_child->type=="gtk_radio_tool_button")
        {
            row[columns.col_text]=dynamic_cast<gtk_radio_tool_button*>(toolbar_child->widget)->get_label();
            }
        row[columns.col_type]=type;
        toolbar_child=toolbar_child->next;
        }
    //End
    
    cmdAdd.signal_clicked().connect(sigc::mem_fun(*this,&toolbar_editor::cmdAdd_clicked));
    cmdRemove.signal_clicked().connect(sigc::mem_fun(*this,&toolbar_editor::cmdRemove_clicked));
    cmdSave->signal_clicked().connect(sigc::mem_fun(*this,&toolbar_editor::cmdSave_clicked));
    cmdCancel->signal_clicked().connect(sigc::mem_fun(*this,&toolbar_editor::cmdCancel_clicked));
    
    tree_selection = tree_view.get_selection();
    
    type_item.set_group(type_group);  
    type_separator.set_group(type_group);
    type_radio.set_group(type_group);
    type_check.set_group(type_group);
    
    fixed.put(scrollwin,3,5);
    tree_view.set_size_request(331,350);
    
    combo_stock = get_stock_combo_box(model_column_stock,tree_model_stock);
    
    fixed.put(*combo_stock,420,50);
    //combo_stock->set_size_request(100,40);
    
    fixed.put(lblStock,360,54);
    lblStock.set_size_request(51,21);
    
    fixed.put(lblText,360,14);
    lblText.set_size_request(51,21);
    
    fixed.put(entry_text,420,10);
    entry_text.set_size_request(113,31);
    
    fixed.put(lblName,360,95);
    lblName.set_size_request(51,21);
    
    fixed.put(entry_name,420,90);
    entry_name.set_size_request(113,31);
    
    fixed.put(type_frame,362,129);
    type_frame.set_size_request(271,171);
    type_frame.set_border_width(0);
    
    fixed.put(cmdAdd,360,307);
    cmdAdd.set_size_request(121,31);
    
    fixed.put(cmdRemove,494,307);
    cmdRemove.set_size_request(121,31);
    
    fixed_type.put(type_item,10,5);
    type_item.set_size_request(131,26);
        
    fixed_type.put(type_radio,10,55);
    type_radio.set_size_request(151,26);
    
    fixed_type.put(type_separator,10,105);
    type_separator.set_size_request(191,26);   
    
    type_item.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&toolbar_editor::item_type_changed),type_item));
    type_separator.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&toolbar_editor::item_type_changed),type_separator));
    type_radio.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&toolbar_editor::item_type_changed),type_radio));
    type_check.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&toolbar_editor::item_type_changed),type_check));
    
    tree_selection->signal_changed().connect(sigc::mem_fun(*this,&toolbar_editor::on_tree_selection_changed));
    
    type_frame.add(fixed_type);
    
    scrollwin.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    scrollwin.add(tree_view);
    
    get_vbox()->add(fixed);  
    combo_stock->signal_changed().connect(sigc::mem_fun(*this,&toolbar_editor::combo_stock_active_changed)); 

    treemodel->append();    
    tree_selection->select(treemodel->children().begin());
    
    Gtk::TreeIter iter = combo_stock->get_model()->children().begin();
    std::string iter_str = combo_stock->get_model()->get_string(iter);                
    std::istringstream oss(iter_str);
    int index; 
    oss>>index;
    combo_stock->set_active(index);
    }

void toolbar_editor::combo_stock_active_changed()
{
    Gtk::TreeIter iter1 = combo_stock->get_active();
    Gtk::TreeIter iter = tree_selection->get_selected();    
    
    if(!iter1)
       return;
    
    std::string name;
    if(iter)
        name = (*iter)[columns.col_name];
        
    std::string stock = (*iter1)[model_column_stock.col];
    if(stock=="NONE")
    {
        if(name!="" && iter)
            (*iter)[columns.col_stock]="NONE";
        entry_text.set_sensitive(true);

        type_item.set_sensitive(true);
        type_separator.set_sensitive(true);
        type_radio.set_sensitive(true);
        type_frame.set_sensitive(true);
        }
    else
    {
        if(name!="" && iter)
            (*iter)[columns.col_stock]=stock;
            
        entry_text.set_sensitive(false);
        type_item.set_sensitive(false);
        type_separator.set_sensitive(false);
        type_radio.set_sensitive(false);
        type_item.set_active(true);
        type_frame.set_sensitive(false);
        entry_text.get_buffer()->set_text(get_stock_label(get_stock_from_string(stock)));
        }
    }

void toolbar_editor::item_type_changed(Gtk::RadioButton& radio_button)
{
    Gtk::TreeIter iter = tree_selection->get_selected();
    if(iter)
    {
        std::string name = (*iter)[columns.col_name];
        if(name=="")
            return;
        }
    if(radio_button.get_label() == type_item.get_label())
    {        
        if(iter)
           (*iter)[columns.col_type]="Button";
        combo_stock->set_sensitive(true);
        //combo_stock->set_active_row_number(0);
        }
    if(radio_button.get_label() == type_separator.get_label())
    {
        if(iter)
            (*iter)[columns.col_type]="Separator";
        combo_stock->set_sensitive(false);
        }
    if(radio_button.get_label() == type_radio.get_label())
    {
        if(iter)
            (*iter)[columns.col_type]="Radio";
        combo_stock->set_sensitive(false);
        }
    }

void toolbar_editor::on_tree_selection_changed()
{
    Gtk::TreeIter iter = tree_selection->get_selected();
    
    std::string name = (*iter)[columns.col_name];
    entry_name.get_buffer()->set_text(name);
    if(name=="")
        return;
        
    std::string type = (*iter)[columns.col_type];
    
    if(type=="Button")
        type_item.set_active(true);
        
    else if(type=="Separator")
        type_separator.set_active(true);
                
    else if(type == "Radio")
        type_radio.set_active(true);
    
    std::string label = (*iter)[columns.col_text];
    entry_text.get_buffer()->set_text(label);
    
    if(type=="Button" )
    {        
        std::string stock  = (*iter)[columns.col_stock];
        iter = combo_stock->get_model()->children().begin();
        combo_stock->set_sensitive(true);
        while(iter)
        {
            std::string name = (*iter)[model_column_stock.col];
            if(name == stock)
            {                
                std::string iter_str = combo_stock->get_model()->get_string(iter);                
                std::istringstream oss(iter_str);
                int index; 
                oss>>index;
                combo_stock->set_active(index);
                break;
                }
            iter++;
            }
        }
    else
         combo_stock->set_sensitive(false);
    }
        
void toolbar_editor::cmdSave_clicked()
{
    response(1);
    }

void toolbar_editor::cmdCancel_clicked()
{    
    response(0);
    }

void toolbar_editor::cmdAdd_clicked()
{
    std::string type;
    if(type_item.get_active())
        type="Button";
    else if(type_separator.get_active())
        type="Separator";
    else if(type_radio.get_active())
        type="Radio";
    
    Gtk::TreeIter iter  = tree_selection->get_selected();
    if(!iter)
        return;
        
    Gtk::TreeModel::Row row = *iter;    
    row[columns.col_name]=entry_name.get_buffer()->get_text();
    row[columns.col_text]=entry_text.get_buffer()->get_text();
    row[columns.col_type]=type;
    
    Gtk::TreeIter iter1 = combo_stock->get_active();
    std::string stock = (*iter1)[model_column_stock.col];
    
    row[columns.col_stock]=stock;
    treemodel->append();
    }

void toolbar_editor::cmdRemove_clicked()
{
    tree_selection = tree_view.get_selection();
    Gtk::TreeModel::iterator iter = tree_selection->get_selected();
    if(iter)
        treemodel->erase(iter);
    }