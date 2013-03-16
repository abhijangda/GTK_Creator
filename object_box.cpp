//123 Lines
#include"object_box.h"
#include<iostream>

ObjectBox::ObjectBox()
: frame(""), scroll_win()
{
    tree_model = Gtk::TreeStore::create(model_columns);
    tree_view.set_model(tree_model);
    tree_view.set_reorderable();
    tree_view.append_column("Object",model_columns.col_object);
    tree_view.append_column("Class",model_columns.col_class);
    
    parent_row = *(tree_model->append());
    parent_row[model_columns.col_object]="";
    parent_row[model_columns.col_class]="";
    
    add_events(Gdk::BUTTON_RELEASE_MASK);
    signal_button_release_event().connect(sigc::mem_fun(*this,&ObjectBox::on_mouse_released));
    scroll_win.add(tree_view);
    //frame.add(scroll_win);
    //add(frame);
    add(scroll_win);
    
    refTreeSelection = tree_view.get_selection();
    }

ObjectBox::~ObjectBox(){}

std::string ObjectBox::get_name(std::string type)
{
    /*Gtk::TreeModel::Children::iterator iter = tree_model->children().begin();
    std::string _name;
    std::string str_num = "";
    int max_num,num;
    while(iter)
    {
        _name = (*iter)[model_columns.col_object];
        if(_name.find(type)==0)
        {
            std::string::iterator iter = _name.begin()+type.size();
            for(iter;iter != _name.end();iter++)
                str_num += *iter;
            std::cout<<"STR_NUM"<<str_num<<std::endl;
            std::istringstream isstr_num(str_num);
            isstr_num>>num;
            if(max_num<num)max_num=num;
            }
        else
        {
            if(++iter);            
        }    */
    }

void ObjectBox::add_parent_row(std::string name, std::string str_class)
{
    //parent_row = *(tree_model->append());
    //Gtk::TreeModel::Row _parent_row;
    //_parent_row = *(tree_model->children()->begin());
    parent_row[model_columns.col_object]=name;
    parent_row[model_columns.col_class]=str_class;
    }

void ObjectBox::delete_child_rows(std::string parent_name)
{    
    Gtk::TreeModel::Children::iterator iter = tree_model->children().begin();
    iter = get_iter_from_string(iter,parent_name);
    iter = (*iter).children().begin();
    std::string _name = (*iter)[model_columns.col_object];
    while(iter)
    {
       _name = (*iter)[model_columns.col_object];
        iter = tree_model->erase(iter);        
        }
    }

void ObjectBox::remove_child_row(std::string child_name, std::string parent_name)
{
    std::cout<<child_name<<std::endl;
    Gtk::TreeModel::Children::iterator iter = tree_model->children().begin();
    iter = get_iter_from_string(iter,parent_name);
    refTreeSelection->select(iter);
    iter = (*iter).children().begin();
    std::string _name = (*iter)[model_columns.col_object];
    while(iter)
    {
        _name = (*iter)[model_columns.col_object];       
        if(_name == child_name)
        {       
            if(iter)
            {
                tree_model->erase(iter);                 
                }
            break;
            }
        else
            iter++;
        }
    }

GtkTreeChildIter ObjectBox::get_iter_from_string(GtkTreeChildIter iter, std::string name)
{
    while(iter)
    {
        std::string _name = (*iter)[model_columns.col_object];
        if(_name==name)
        {
            iter_found = iter;
            return iter;
            }
        if((*iter).children().begin())
            get_iter_from_string((*iter).children().begin(),name);
        iter++;
        }
    return iter_found;
    }

void ObjectBox::add_child_row(std::string parent_name, std::string name, std::string str_class)
{
    Gtk::TreeModel::Children children = tree_model->children();
    Gtk::TreeModel::Children::iterator iter = children.begin();
    iter = get_iter_from_string(iter,parent_name);
    std::string clas = (*iter)[model_columns.col_class];

    Gtk::TreeModel::Row _row= *(tree_model->append((*iter).children()));
    _row[model_columns.col_class] = str_class;
    _row[model_columns.col_object] = name;
    refTreeSelection = tree_view.get_selection();
    refTreeSelection->select(_row);
    }

void ObjectBox::set_selection_from_widget(Gtk::Widget& widget,std::string type)
{
    current_widget = &widget;
    Gtk::TreeModel::Children::iterator iter = get_iter_from_string(tree_model->children().begin(),widget.get_name());
    refTreeSelection = tree_view.get_selection();
    if(iter)
    {
        std::string n = (*iter)[model_columns.col_object];
        if(n==widget.get_name())
            refTreeSelection->select(iter);
        }
    }

void ObjectBox::change_name(std::string new_name,std::string old_name)
{
    Gtk::TreeModel::Children::iterator iter = get_iter_from_string(tree_model->children().begin(),old_name);
    (*iter)[model_columns.col_object]=new_name;    
    }

std::string ObjectBox::get_current_name()
{
    refTreeSelection = tree_view.get_selection();
    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    return (*iter)[model_columns.col_object];
    }