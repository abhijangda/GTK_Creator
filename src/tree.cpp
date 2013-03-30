//66 Lines
#include"tree.h"

item* tree::get_item_at_index(std::vector<int> item_index)
{
    depth = 0;
    if(item_index[0]==0)
        return parent_item;
    item* __item=parent_item;
    depth++;
    while(item_index[depth]!=-1)
    {
        int i=0;
        __item=__item->child;
        for(i=0;i<item_index[depth];i++)
            __item = __item->next;
        depth++;
        }
    depth = 0;
    return __item;        
    }

item* tree::get_item_from_widget(Gtk::Widget* widget)
{
    item_found=NULL;
    return item_from_widget(parent_item,widget);
    }

item* tree::item_from_widget(item* __item, Gtk::Widget* widget)
{    
    while(__item)
    {
        if(__item->widget==widget)
        {
            //std::cout<<"ITEM FOUND WITH WIDGET"<<std::endl;
            item_found=__item;
            return __item;
            }
        if(__item->child != NULL)
            item_from_widget(__item->child,widget);
        __item = __item->next;
        }    
    return item_found;          
    }

item* tree::get_item_from_name(std::string name)
{
    item_found=NULL;
    return item_from_name(parent_item,name);
    }

item* tree::item_from_name(item* __item, std::string name)
{
    while(__item)
    {
        if(__item->widget->get_name()==name)
        {
            //std::cout<<"ITEM FOUND WITH WIDGET"<<std::endl;
            item_found=__item;
            return __item;
            }
        if(__item->child != NULL)
            item_from_name(__item->child,name);
        __item = __item->next;
        }    
    return item_found;
    }