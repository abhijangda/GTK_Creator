//264 Lines
#include"treeitem.h"

item::item(Gtk::Widget& _widget,std::string _type,item* parent_item=NULL, item* child_item=NULL,item* prev_item=NULL, item* next_item=NULL)
    :level(0),widget(&_widget),type(_type),index_vector(10,-1)
{
    parent = parent_item;
    child = child_item;
    prev = prev_item;
    next = next_item;
    index=-1;
    }

item::~item()
{
    //if(child)
       //delete child;
    //if(next)
        //delete next;
    }
bool item::is_parent_of_type(std::string type)
{
    return _is_parent_of_type(type,this);
    }

bool item::_is_parent_of_type(std::string type, item* _item)
{
    item* parent = _item->get_parent();
    if(!parent)
        return false;
    if(parent->type==type)
        return true;
    else
    {
        if(_is_parent_of_type(type,parent))
            return true;
        }
    return false;
    }

item* item::get_last_child()
{
    item* __item = child;
    if(!child)
        return NULL;
    while(__item->next)
        __item=__item->next;
    return __item;
    }

item* item::get_parent()
{
    item* __item;
    if(prev)
        __item=prev;
    else{//std::cout<<"PARENTFOUND"<<std::endl;
        return parent;}
    while(__item->prev)
         __item=__item->prev;
    //std::cout<<"PARENTFOUND"<<std::endl;
    return __item->parent;
    }

void item::remove_child(item* item_to_remove)
{
    item* __item = child;
    if(item_to_remove==child)
    {
        if(child->next==NULL)
            child=NULL;
        else
        {
            item* item_to_remove  = child;
            child = item_to_remove->next;
            item_to_remove->parent  = this;
            }
        }
    else
    {        
        while(__item && __item->next != item_to_remove)
            __item  = __item->next;

        if(__item)
            __item->remove_next_item();
        }
    }

void item::get_index_value()
{
    level=0;
    std::fill(index_vector.begin(),index_vector.end(),-1);
    index_value(this);    
    }

std::vector<int> item::index_value(item* __item)
{
    if(__item == NULL)
        return index_vector;
    
    int i=0;    
    while(__item->prev)
    {
        __item = __item->prev;
        i++;
        }
    std::fill(index_vector.begin()+level,index_vector.begin()+level+1,i);
    level++;   
    index_value(__item->parent);
    }

void item::insert_child_at(item* child_item, int at_index)
{
    if(at_index==-1)
        return;
        
    int _index = -1;
    
    //std::cout<<"inserting child for parent "<<widget->get_name()<<std::endl;
    
    //Check whether all are continuous or not    
    item* __item = child,*equal_index_item=NULL;
    child_item->index  = at_index;
    //std::cout<<"ADDING NEXT CHILD "<<child_item->widget->get_name()<<" INDEX "<<child_item->index<<" AT INDEX "<<at_index<<std::endl;
    
    while(__item!=NULL)
    {        
        _index++;
        if(at_index==__item->index)
            equal_index_item=__item;
            
        if(_index!=__item->index)
            break;
        
        __item=__item->next;
        }
    //if yes, then inserting at a place, changes the index of all items after that
    if(!__item)
    { 
        if(equal_index_item)
        {
            //std::cout<<"FOUND equal_index_item of widget "<<equal_index_item->widget->get_name()<<" type "<<equal_index_item->type<<" with index "<<equal_index_item->index<<std::endl;
            equal_index_item->prev->add_next_item(child_item);
            while(equal_index_item)
            {
                equal_index_item->index++;
                equal_index_item=equal_index_item->next;
                }
            }
        else
            //no item has index equal to at_index, i.e. inserting element at last
             add_next_child(child_item);
        }
    //if no,then find the last item having index smaller than at_index
    else
    {
        __item=child;
        while(__item)
        {
            if(at_index<__item->index)
                break;
            __item=__item->next;
            }
        if(__item) //found first item with index greater than at_index
        {
            //__item can be the first child
            if(__item->prev) //if not the first child
            {
                __item=__item->prev; //last item with index smaller than at_index            
                __item->add_next_item(child_item);
                }
            else //if it is the first child
                add_child(child_item);
            }
        //if no item with index greater than at_index is found, then 
        else
        {
            if(get_last_child()->index==at_index)//either the index of last child and at_index are equal 
            {
                get_last_child()->prev->add_next_item(child_item);
                child_item->index++;
                }
            else //or at_index is greater than any other element
            {
                add_next_child(child_item);
                child_item->index=at_index;
                }            
            }
        }
    child_item->index=at_index;
    /*__item=child;
    while(__item)
    {
        std::cout<<"ITEM WITH WIDGET "<<__item->widget->get_name()<<" INDEX "<<__item->index<<std::endl;
        __item=__item->next;
        }*/
    } 

void item::add_child(item* child_item)
{
    if(child)
    {
        item* __item = child;
        child = child_item;
        child->parent=this;
        __item->parent=NULL; 
        child->add_next_item(__item);
        }
    else
    {
        child = child_item;
        child->parent = this;
        }
    child_item->index=0;
    }

void item::add_next_child(item* child_item)
{
    item* __item = child;
    if(!__item)
    {
        add_child(child_item);
        return;
        }
    while(__item->next)
        __item=__item->next;
    __item->add_next_item(child_item);
    }

void item::add_next_item(item* _next)
{
    item* old_next = next;
    next = _next;
    if(old_next)
        next->next = old_next;
    next->prev=this;    
    
    //change index only if it is continuos
    item* __item=get_parent()->child;
    int _index = -1;
    while(__item!=NULL)
    {        
        _index++;          
        if(_index!=__item->index)
            break;
        
        __item=__item->next;
        }
    if(!__item)
        _next->index = index+1;
    if(old_next!=NULL)
        old_next->prev = next;
    }

void item::add_prev_item(item* _prev)
{
    item* old_prev = prev;
    prev = _prev;    
    prev->next = this;
    prev->prev=_prev;
    _prev->index=index;
    index--;
    if(old_prev!=NULL)
        old_prev->next = prev;
    }

void item::remove_next_item()
{
    if(next ==NULL)
        return;
        
    item *item_to_remove = next;
    next = item_to_remove->next;
    if(item_to_remove->next != NULL)
         item_to_remove->next->prev = this;     
    delete item_to_remove;
    }

void item::remove_prev_item()
{
    item* item_to_remove  = next;
    prev = item_to_remove->next;
    if(item_to_remove->prev ==NULL)
        return;
    item_to_remove->prev->next  = this;
    index--;
    //delete item_to_remove;
    }