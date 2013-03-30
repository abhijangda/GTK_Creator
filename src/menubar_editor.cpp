//214 Lines
#include"menubar_editor.h"
//just add the values of the widget in fixed
menubar_editor::menubar_editor(item* _menubar_item)
:  Gtk::Dialog("Edit Menubar",true,true),cmdAddItem("Add Item"),cmdRemove("Remove"), cmdAddMenu("Add Menu"),lblName("Name"),lblText("Text"),
   entry_name(),entry_text(),type_group(),type_frame("Type"),type_item("Item"), type_separator("Separator"), type_radio("Radio"),type_check("Check"),
   menubar_item(_menubar_item),tree_view(),cmdRemoveMenu("Remove Menu"),chk_active("Active"),scrollwin(),lblStock("Stock")
{
    create_menu = false;
    
    tree_selection = tree_view.get_selection();
    
    type_item.set_group(type_group);  
    type_separator.set_group(type_group);
    type_radio.set_group(type_group);
    type_check.set_group(type_group);
    
    fixed.put(scrollwin,3,5);
    tree_view.set_size_request(331,402);
    
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
    
    fixed.put(cmdAddItem,360,307);
    cmdAddItem.set_size_request(121,31);
    
    fixed.put(cmdRemove,494,307);
    cmdRemove.set_size_request(121,31);
    
    fixed.put(cmdAddMenu,360,341);
    cmdAddMenu.set_size_request(121,31);
    
    fixed.put(cmdRemoveMenu,495,341);
    cmdRemoveMenu.set_size_request(121,31);
    
    fixed_type.put(type_item,10,5);
    type_item.set_size_request(131,26);
    
    fixed_type.put(type_check,10,38);
    type_check.set_size_request(161,26);
    
    fixed_type.put(type_radio,10,78);
    type_radio.set_size_request(151,26);
    
    fixed_type.put(type_separator,10,115);
    type_separator.set_size_request(191,26);   
    
    fixed_type.put(chk_active,170,38);
    chk_active.set_size_request(81,26);
    
    cmdSave=add_button("Save",1);  
    cmdCancel = add_button("Cancel",0);     
    treemodel = Gtk::TreeStore::create(columns);
    tree_view.set_model(treemodel);
    tree_view.append_column("Name",columns.col_name);
    tree_view.append_column("Text",columns.col_text);
    tree_view.append_column("Type",columns.col_type);
    tree_view.append_column("Stock",columns.col_stock);
    
    //treemodel->append();
    //Load ToolbarItems
    /*item* toolbar_child = toolbar_item->child;
    std::string type;
    while(toolbar_child!=NULL)
    {
        if(toolbar_child->type=="gtk_toolbutton")
            type="Button";
        else if(toolbar_child->type=="gtk_separatoritem")
            type="Separator";
        else if(toolbar_child->type == "gtk_radiotoolbutton")
            type="Radio";
            
        Gtk::TreeModel::Row row = *(treemodel->append());
        row[columns.col_name]=toolbar_child->widget->get_name();
        if(toolbar_child->type=="gtk_toolbutton")
            row[columns.col_text]=dynamic_cast<Gtk::ToolButton*>(toolbar_child->widget)->get_label();
        if(toolbar_child->type=="gtk_radiotoolbutton")
            row[columns.col_text]=dynamic_cast<Gtk::RadioToolButton*>(toolbar_child->widget)->get_label();
        row[columns.col_type]=type;  
        toolbar_child=toolbar_child->next;
        }*/
    //End
    
    cmdAddItem.signal_clicked().connect(sigc::mem_fun(*this,&menubar_editor::cmdAddItem_clicked));
    cmdRemove.signal_clicked().connect(sigc::mem_fun(*this,&menubar_editor::cmdRemove_clicked));
    cmdAddMenu.signal_clicked().connect(sigc::mem_fun(*this,&menubar_editor::cmdAddMenu_clicked));
    combo_stock->signal_changed().connect(sigc::mem_fun(*this,&menubar_editor::combo_stock_active_changed)); 
    cmdRemoveMenu.signal_clicked().connect(sigc::mem_fun(*this,&menubar_editor::cmdRemoveMenu_clicked));
    
    type_item.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&menubar_editor::item_type_changed),type_item));
    type_separator.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&menubar_editor::item_type_changed),type_separator));
    type_radio.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&menubar_editor::item_type_changed),type_radio));
    type_check.signal_toggled().connect(sigc::bind<Gtk::RadioButton&>(sigc::mem_fun(*this,&menubar_editor::item_type_changed),type_check));
    
    tree_selection->signal_changed().connect(sigc::mem_fun(*this,&menubar_editor::on_tree_selection_changed));
    
    cmdSave->signal_clicked().connect(sigc::mem_fun(*this,&menubar_editor::cmdSave_clicked));
    cmdCancel->signal_clicked().connect(sigc::mem_fun(*this,&menubar_editor::cmdCancel_clicked));
    
    type_frame.add(fixed_type);
    
    scrollwin.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    scrollwin.add(tree_view);
    
    get_vbox()->add(fixed);  
    update_treeview(_menubar_item->child,treemodel->children().begin(),treemodel->children().begin());   

    tree_selection->select(treemodel->children().begin());

    Gtk::TreeIter iter = combo_stock->get_model()->children().begin();
    std::string iter_str = combo_stock->get_model()->get_string(iter);                
    std::istringstream oss(iter_str);
    int index; 
    oss>>index;
    combo_stock->set_active(index);
    }

void menubar_editor::on_tree_selection_changed()
{
    Gtk::TreeIter iter = tree_selection->get_selected();
    
    std::string name = (*iter)[columns.col_name];
    entry_name.get_buffer()->set_text(name);
    if(name=="")
        return;
        
    std::string type = (*iter)[columns.col_type];
    
    if(type=="Menu Item")
        type_item.set_active(true);
        
    else if(type=="Separator Menu Item")
        type_separator.set_active(true);
        
    else if(type=="Check Menu Item")
        type_check.set_active(true);
        
    else if(type == "Radio Menu Item")
        type_radio.set_active(true);
    
    std::string label = (*iter)[columns.col_text];
    entry_text.get_buffer()->set_text(label);
    
    if(type=="Menu Item" || type == "Menu")
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

void menubar_editor::item_type_changed(Gtk::RadioButton& radio_button)
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
           (*iter)[columns.col_type]="Menu Item";
        combo_stock->set_sensitive(true);
        //combo_stock->set_active_row_number(0);
        }
    if(radio_button.get_label() == type_separator.get_label())
    {
        if(iter)
            (*iter)[columns.col_type]="Separator Menu Item";
        combo_stock->set_sensitive(false);
        }
    if(radio_button.get_label() == type_radio.get_label())
    {
        if(iter)
            (*iter)[columns.col_type]="Radio Menu Item";
        combo_stock->set_sensitive(false);
        }
    if(radio_button.get_label() == type_check.get_label())
    {
        if(iter)
            (*iter)[columns.col_type]="Check Menu Item";     
        combo_stock->set_sensitive(false);   
        }
    chk_active.set_sensitive(type_check.get_active());
    }

void menubar_editor::cmdRemoveMenu_clicked()
{
    }

void menubar_editor::combo_stock_active_changed()
{
    Gtk::TreeIter iter1 = combo_stock->get_active();
    Gtk::TreeIter iter = tree_selection->get_selected();    
    
    if(!iter || !iter1)
       return;
    
    std::string name = (*iter)[columns.col_name];
    std::string stock = (*iter1)[model_column_stock.col];
    if(stock=="NONE")
    {
        if(name!="")
            (*iter)[columns.col_stock]="NONE";
        entry_text.set_sensitive(true);

        type_item.set_sensitive(true);
        type_separator.set_sensitive(true);
        type_radio.set_sensitive(true);
        type_check.set_sensitive(true);
        type_frame.set_sensitive(true);
        }
    else
    {
        if(name!="")
            (*iter)[columns.col_stock]=stock;
            
        entry_text.set_sensitive(false);
        type_item.set_sensitive(false);
        type_separator.set_sensitive(false);
        type_radio.set_sensitive(false);
        type_check.set_sensitive(false);
        type_item.set_active(true);
        type_frame.set_sensitive(false);
        entry_text.get_buffer()->set_text(get_stock_label(get_stock_from_string(stock)));
        }    
    }

void menubar_editor::update_treeview(item* _item,Gtk::TreeModel::Children::iterator child_iter,Gtk::TreeModel::Children::iterator parent_iter)
{
    std::string _type;
    while(_item)
    {        
        std::string _name = _item->widget->get_name();
        _type = _item->type;
        //std::cout<<"NAME "<<_name<<"TYPE "<<_type<<std::endl;
        
        if(_type=="gtk_image_menu_item")
        {
            gtk_image_menu_item* menuitem = dynamic_cast<gtk_image_menu_item*>(_item->widget);
            std::string _text = menuitem->get_label();    
            if(parent_iter )//&& (*parent_iter).children())
                child_iter = treemodel->append((*parent_iter).children());
            else
                child_iter = treemodel->append();
            (*child_iter)[columns.col_name] =_name;
            (*child_iter)[columns.col_text]=_text;
            (*child_iter)[columns.col_type]="Menu Item";
            (*child_iter)[columns.col_stock]=menuitem->get_stock();            
            
            if(_item->child)
                update_treeview(_item->child,child_iter,parent_iter);
            }
        else if(_type=="gtk_menu")
        {
            (*child_iter)[columns.col_type]="Menu";
            if(_item->child)
                update_treeview(_item->child,(*child_iter).children(),child_iter);
            }
        else if(_type=="gtk_separatormenuitem")
        {
            gtk_separator_menu_item* menuitem = dynamic_cast<gtk_separator_menu_item*>(_item->widget);
            
            if(parent_iter )//&& (*parent_iter).children())
                child_iter = treemodel->append((*parent_iter).children());
            else
                child_iter = treemodel->append();
            (*child_iter)[columns.col_name] =_name;
            (*child_iter)[columns.col_text]="";
            (*child_iter)[columns.col_type]="Separator Menu Item";
            }
        else if(_type=="gkt_radiomenuitem")
        {
            gtk_radio_menu_item* menuitem = dynamic_cast<gtk_radio_menu_item*>(_item->widget);
            std::string _text = menuitem->get_label();    
            if(parent_iter )//&& (*parent_iter).children())
                child_iter = treemodel->append((*parent_iter).children());
            else
                child_iter = treemodel->append();
            (*child_iter)[columns.col_name] =_name;
            (*child_iter)[columns.col_text]=_text;
            (*child_iter)[columns.col_type]="Radio Menu Item";
            }
        else if(_type=="gtk_checkmenuitem")
        {
           gtk_check_menu_item* menuitem = dynamic_cast<gtk_check_menu_item*>(_item->widget);
            std::string _text = menuitem->get_label();    
            if(parent_iter )//&& (*parent_iter).children())
                child_iter = treemodel->append((*parent_iter).children());
            else
                child_iter = treemodel->append();
            (*child_iter)[columns.col_name] =_name;
            (*child_iter)[columns.col_text]=_text;
            (*child_iter)[columns.col_type]="Menu Item";
            }
        //std::cout<<"NAME "<<_name<<std::endl;        
        _item = _item->next;
        }
    if(_type!="gtk_menu")
    {        
        if(child_iter)
             treemodel->append((*(*child_iter).parent()).children());
        else
            treemodel->append();
        }
    }

void menubar_editor::cmdAddItem_clicked()
{
    Gtk::TreeModel::Row row;
    tree_selection = tree_view.get_selection();
    Gtk::TreeModel::iterator iter = tree_selection->get_selected();
    
    if(!iter)
        return;
    
    std::string type = (*iter)[columns.col_type];
    if(type!="")
       return;
    
    row=(*iter);
    row[columns.col_name]=entry_name.get_buffer()->get_text();
    row[columns.col_text]=entry_text.get_buffer()->get_text();
    
    if(type_item.get_active())
        type="Menu Item";
    else if(type_separator.get_active())
        type="Separator";
    else if(type_radio.get_active())
        type="Radio";
    else if(type_check.get_active())
        type="Check";
    row[columns.col_type]=type;
    
    Gtk::TreeIter iter1 = combo_stock->get_active();
    std::string stock = (*iter1)[model_column_stock.col];
    row[columns.col_stock]=stock;
    
    treemodel->append((*(*iter).parent()).children());
    
    create_menu = false;
    }
void menubar_editor::cmdRemove_clicked()
{
    tree_selection = tree_view.get_selection();
    Gtk::TreeModel::iterator iter = tree_selection->get_selected();
    if(iter)
        treemodel->erase(iter);
    }
void menubar_editor::cmdAddMenu_clicked()
{
    tree_selection = tree_view.get_selection();
    Gtk::TreeModel::iterator iter = tree_selection->get_selected();
    if(!iter)
        return;
    std::string _type = (*iter)[columns.col_type];
    if(_type!="Menu Item")
        return;
    (*iter)[columns.col_type]="Menu";
    treemodel->append((*iter).children());
    create_menu = true;
    }
void menubar_editor::cmdSave_clicked()
{
    response(1);
    }
void menubar_editor::cmdCancel_clicked()
{
    response(0);
    }