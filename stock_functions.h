#include<gtkmm.h>

#ifndef STOCK_FUNCTIONS_H
#define STOCK_FUNCTIONS_H
class Model_Column_Stock : public Gtk::TreeModel::ColumnRecord
{
    public:
        Model_Column_Stock(){add(col);} 
        Gtk::TreeModelColumn<std::string> col;
    };

std::string get_stock_string(Gtk::BuiltinStockID stockid);
Gtk::BuiltinStockID get_stock_from_string(std::string);
std::string get_stock_label(Gtk::BuiltinStockID  stockid);
Gtk::ComboBox* get_stock_combo_box(Model_Column_Stock&,Glib::RefPtr<Gtk::ListStore>&);
std::string get_gml_string_from_stock_string(std::string);
std::string get_stock_string_from_gml_string(std::string);
#endif