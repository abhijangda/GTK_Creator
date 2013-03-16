//40 Lines
#include<gtkmm/widget.h>
#include<iostream>

#ifndef TREEITEM_H
#define TREEITEM_H

class item
{
    public:        
        Gtk::Widget* widget;
        std::string type;
        item* parent;
        item* child;
        item* prev;
        item* next;
        int index;
        
        item(Gtk::Widget&,std::string,item* parent_item, item* child_item,item* prev, item* next);
        ~item();
        
        bool is_parent_of_type(std::string);
        void add_child(item*);
        void add_next_child(item*);
        void add_next_item(item*);
        void insert_child_at(item*,int);        
        void add_prev_item(item*);
        void remove_next_item();
        void remove_prev_item();
        void get_index_value();
        void remove_child(item*);
        item* get_last_child();
        item* get_parent();
        std::vector<int> index_vector;
        std::vector<int> index_value(item* __item);
        int level;
            
    private:
        bool _is_parent_of_type(std::string type, item*);
    };
#endif