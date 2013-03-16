//70 Lines
#include"treeitem.h"

#ifndef TREE_H
#define TREE_H

class tree
{
    public:
        tree(item* parent){parent_item = parent;}
        tree(){parent_item=NULL;}
        item* parent_item;
        item* get_item_at_index(std::vector<int>);
        item* get_item_from_widget(Gtk::Widget*);
        item* get_item_from_name(std::string);
        ~tree(){delete parent_item;}
    private:
        item* __item;   
        int depth;
        item* item_from_widget(item*, Gtk::Widget*);
        item* item_from_name(item*, std::string);
        item* item_found;
    public:        
        class treeiter;
        friend class treeiter;       
        
        class treeiter
        {
            private:       
                tree* _tree;
                item* current_item;
            public:
                treeiter(tree& __tree){_tree=&__tree;current_item=_tree->parent_item;}
                treeiter(tree& __tree, item& __current_item){_tree=&__tree;current_item=&__current_item;}
                treeiter* operator++()
                {
                    if(current_item->next==NULL)
                        return NULL;
                    current_item=current_item->next;
                    return this;
                    }
                
                treeiter* operator++(int){return operator++();}
                treeiter* operator--()
                {
                    if(current_item->prev)
                        current_item=current_item->prev;
                    return this;
                    }
                treeiter* operator--(int){return operator--();}                
                item* operator*(){return current_item;}
                treeiter* parent()
                {
                    if(current_item->parent==NULL)
                        return NULL;
                    current_item = current_item->parent;
                    return this;
                    }
                treeiter* child()
                {
                    if(current_item->child==NULL)
                        return NULL;
                    current_item = current_item->child;
                    return this;
                    }
            };
        treeiter begin() {return treeiter(*this);}
    };

#endif