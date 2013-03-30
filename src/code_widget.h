//44 Lines
#include"source_view.h"

#ifndef CODE_WIDGET_H
#define CODE_WIDGET_H

class code_folding_position
{
    public:
        code_folding_position(int _y1, int _y2, int _pos, int __pos)
        {
            y1=_y1;
            y2=_y2;
            start_pos=_pos;
            end_pos=__pos;
            }        
        int y1,y2,start_pos,end_pos;
    };

class code_widget : public Gtk::VBox
{
    public:
        code_widget(Gtk::Statusbar& , std::string);
        ~code_widget();
        
        Gtk::ComboBoxText combo_box_func;
        source_view _source_view;
        Gtk::ScrolledWindow scrollwin;
        Gtk::HBox hbox;
        Gtk::DrawingArea code_folding_area;        
        Gtk::DrawingArea line_number_area;
        
        static int code_folding_area_width;
        static int line_number_area_width;
        static bool show_scope;        

        std::vector<code_folding_position> vector_code_folding_pos;
        bool on_code_folding_area_expose_event(GdkEventExpose*);
        bool on_line_number_area_expose_event(GdkEventExpose*);
        bool on_code_folding_area_mouse_press(GdkEventButton* event);
        
        std::string get_tag_name();
    };

#endif