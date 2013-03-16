//332 Lines
#include"code_widget.h"
#include<iostream>
#include<vector>
#include<algorithm>

int code_widget::code_folding_area_width =16;
int code_widget::line_number_area_width=10;
bool code_widget::show_scope = true;

code_widget::code_widget(Gtk::Statusbar& status_bar, std::string _f )
:combo_box_func(false),_source_view(status_bar,_f,combo_box_func,code_folding_area,line_number_area),scrollwin(),Gtk::VBox(false,5)
{
    scrollwin.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    scrollwin.add(_source_view);
    pack_start(combo_box_func,Gtk::PACK_SHRINK);
    pack_start(hbox,Gtk::PACK_EXPAND_WIDGET);
    hbox.pack_start(line_number_area,Gtk::PACK_SHRINK);    
    hbox.pack_start(code_folding_area,Gtk::PACK_SHRINK);    
    hbox.pack_start(scrollwin,Gtk::PACK_EXPAND_WIDGET);
           
    code_folding_area.set_size_request(code_folding_area_width,100);
    line_number_area.set_size_request(line_number_area_width,100);
    code_folding_area.signal_expose_event().connect(sigc::mem_fun(*this,&code_widget::on_code_folding_area_expose_event));
    line_number_area.signal_expose_event().connect(sigc::mem_fun(*this,&code_widget::on_line_number_area_expose_event));
    
    code_folding_area.add_events(Gdk::BUTTON_PRESS_MASK);
    code_folding_area.signal_button_press_event().connect(sigc::mem_fun(*this,&code_widget::on_code_folding_area_mouse_press));
    
    if(!show_scope)
        combo_box_func.set_visible(false);
    }

bool code_widget::on_line_number_area_expose_event(GdkEventExpose*)
{
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = _source_view.get_source_buffer();
    Glib::RefPtr<Gdk::Window> gdk_win = line_number_area.get_window();
    Cairo::RefPtr<Cairo::Context> cr = gdk_win->create_cairo_context();
    
    if(gdk_win)
    {
        gdk_win->clear();
        cr->set_source_rgb(0,0,0);
        cr->set_line_width(1);
        cr->select_font_face("Calibri",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
        Gdk::Rectangle location;
        _source_view.get_visible_rect(location);
        
        int window_x,window_y;
        Gtk::TextIter start_visible_iter,end_visible_iter,iter;
        _source_view.get_iter_at_location(start_visible_iter,location.get_x(),location.get_y());        
        _source_view.get_iter_at_location(end_visible_iter,location.get_x()+location.get_width(),location.get_height()+location.get_y());
               
        Cairo::TextExtents extents;
        
        cr->set_font_size(14);
        cr->set_source_rgb(0,0,0);
        int prev_window_y;
        
        for(int i = end_visible_iter.get_line();i>= start_visible_iter.get_line();i--)
        {
            iter = buffer->get_iter_at_line(i);
            Gdk::Rectangle location2;
            _source_view.get_iter_location(iter,location2);
            int window_x,window_y;
            _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_WIDGET,location2.get_x(),location2.get_y() ,window_x,window_y);  
            if(i == buffer->get_iter_at_mark(buffer->get_insert()).get_line())
                cr->select_font_face("Calibri",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_BOLD);
            else
                cr->select_font_face("Calibri",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
            if(prev_window_y==window_y)
            {
                cr->show_text("...");       
                }
            else
            {
                cr->move_to(0,window_y+15);
                cr->show_text(integer_to_string(i+1));       
                }
            prev_window_y=window_y;
            }
        cr->get_text_extents(integer_to_string(end_visible_iter.get_line()),extents);
        line_number_area.set_size_request(extents.width+2,100);
        }
    return true;
    }

std::string code_widget::get_tag_name()
{
    if(_source_view.vector_fold_text.size()==0)
        return "TAG 0";
    
    std::string tag_name = _source_view.vector_fold_text[_source_view.vector_fold_text.size()-1].tag_name;
    std::string num_str = tag_name.substr(tag_name.find(" ")+1);
    int num  = string_to_integer(num_str);
    num++;
    return "TAG " + integer_to_string(num);
    }

 bool code_widget::on_code_folding_area_mouse_press(GdkEventButton* event)
{
    _source_view.connection_mark_set.disconnect();
    
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = _source_view.get_source_buffer();
    int y = event->y;
    int i;
    //for(i = 0;i<vector_code_folding_pos.size();i++)
        //std::cout<<vector_code_folding_pos[i].y1<<"LL"<<vector_code_folding_pos[i].y2<<"start_pos"<<vector_code_folding_pos[i].start_pos<<std::endl;
    for(i = 0;i<vector_code_folding_pos.size();i++)
    {
        if(vector_code_folding_pos[i].y1<=y &&vector_code_folding_pos[i].y2>=y)
            break;
        }
    if(i<vector_code_folding_pos.size())
    {
        if(vector_code_folding_pos[i].start_pos!=-1 && vector_code_folding_pos[i].end_pos!=-1)
        {
            int j;
            for(j = 0;j<_source_view.vector_fold_text.size();j++)
            {
                if(_source_view.vector_fold_text[j].start_pos==vector_code_folding_pos[i].start_pos &&_source_view.vector_fold_text[j].end_pos+6==vector_code_folding_pos[i].end_pos)
                    break;
                }            
            
            if(j!=_source_view.vector_fold_text.size())
            {                
                Gtk::TextIter start = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos+1);
                Gtk::TextIter end = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos+1+_source_view.fold_str.length());
                buffer->erase(start,end);
                Glib::RefPtr<Gtk::TextBuffer::Tag> tag = buffer->get_tag_table()->lookup(_source_view.vector_fold_text[j].tag_name);
                
                tag->property_invisible()=false;       
                std::vector<fold_text>::iterator __iter = _source_view.vector_fold_text.begin() + j;
                _source_view.vector_fold_text.erase(__iter);
                
                buffer->get_tag_table()->remove(tag);
                }
            else
            {                
                Gtk::TextIter start = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos+1);
                Gtk::TextIter end = buffer->get_iter_at_offset(vector_code_folding_pos[i].end_pos);
                Gtk::TextIter end_line = buffer->get_iter_at_line(end.get_line());
                int end_pos = end_line.get_offset()+end.get_line_offset();
                
                std::string tag_name = get_tag_name();
                std::cout<<tag_name<<std::endl;
                Glib::RefPtr<Gtk::TextBuffer::Tag> tag = buffer->create_tag(tag_name);
                tag->property_invisible()=true;
                
                buffer->apply_tag(tag,start,end);
                start = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos+1);
                buffer->insert(start,_source_view.fold_str);
                _source_view.vector_fold_text.insert(_source_view.vector_fold_text.end(),fold_text(tag_name,vector_code_folding_pos[i].start_pos,end_pos));
                }
            }
        else if(vector_code_folding_pos[i].end_pos ==-1 && vector_code_folding_pos[i].start_pos !=-1)
        {
            int brace_count  = 0;
            int line;
            Gtk::TextIter iter = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos);
            line = iter.get_line();
            std::string line_text;
            do
            {                
                iter = buffer->get_iter_at_line(line);
                Gtk::TextIter line_end_iter=_source_view.get_line_end_iter(line);
                line_text = buffer->get_text(iter,line_end_iter);
                brace_count = brace_count + _source_view.count_str(line_text,_source_view.open_brace)-_source_view.count_str(line_text,_source_view.close_brace);
                line++;
                }
            while(brace_count!=0);
            
            int close_brace_offset = iter.get_offset()+line_text.find("}");
            Gtk::TextIter start = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos+1);
            Gtk::TextIter end = buffer->get_iter_at_offset(close_brace_offset);
            int end_pos = end.get_offset();
            
            std::string tag_name = get_tag_name();
            Glib::RefPtr<Gtk::TextBuffer::Tag> tag = buffer->create_tag(tag_name);
            tag->property_invisible()=true;
            
            buffer->apply_tag(tag,start,end);
            start = buffer->get_iter_at_offset(vector_code_folding_pos[i].start_pos+1);
            buffer->insert(start,_source_view.fold_str);
            _source_view.vector_fold_text.insert(_source_view.vector_fold_text.end(),fold_text(tag_name,vector_code_folding_pos[i].start_pos,end_pos));
            }
        }
    _source_view.connection_mark_set = buffer->signal_mark_set().connect(sigc::mem_fun(&_source_view,&source_view::on_mark_set));
    return false;
    }

bool code_widget::on_code_folding_area_expose_event(GdkEventExpose*)
{
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer = _source_view.get_source_buffer();
    Glib::RefPtr<Gdk::Window> gdk_win = code_folding_area.get_window();
    Cairo::RefPtr<Cairo::Context> cr = gdk_win->create_cairo_context();
    
    vector_code_folding_pos.erase(vector_code_folding_pos.begin(),vector_code_folding_pos.end());
    
    std::vector<function>& vector_curr_file_func= _source_view.vector_curr_file_func;
    if(gdk_win)
    {
        cr->set_source_rgb(0,0,0);
        cr->set_line_width(1);
        
        Gdk::Rectangle location;
        _source_view.get_visible_rect(location);
        
        int window_x,window_y;
        Gtk::TextIter start_visible_iter,end_visible_iter,iter;
        _source_view.get_iter_at_location(start_visible_iter,location.get_x(),location.get_y());        
        _source_view.get_iter_at_location(end_visible_iter,location.get_x()+location.get_width(),location.get_height()+location.get_y());        
        
        int i;
        for(i =1;i<vector_curr_file_func.size();i++)
        {            
            if(vector_curr_file_func[i].pos>=start_visible_iter.get_offset() && vector_curr_file_func[i].pos<=end_visible_iter.get_offset())
                   break;
            }
        int inside_region_func_index = i;
        if(i<vector_curr_file_func.size())
        {
            iter = buffer->get_iter_at_offset(vector_curr_file_func[i].pos);
            int line;
            std::string line_text;
            
            if(i>=1)
            {                
                Gdk::Rectangle close_brace_location;
                line = iter.get_line()-1;
                do
                {                    
                    iter = buffer->get_iter_at_line(line);
                    Gtk::TextIter line_end_iter = _source_view.get_line_end_iter(line);
                    line_text = buffer->get_text(iter,line_end_iter);          
                    line--;                                        
                    }
                while(_source_view.count_str(line_text,_source_view.close_brace)==0 && line >=start_visible_iter.get_line());
                if(line>start_visible_iter.get_line())
                {                    
                    _source_view.get_iter_location(iter,close_brace_location);
                    int x2,y2;   
                    _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_TEXT,location.get_x()-10,location.get_y(),x2,y2);                
                    cr->move_to(code_folding_area_width/2,0);
                    
                    int window_x,window_y;
                   _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_TEXT,location.get_x()-10,close_brace_location.get_height()+close_brace_location.get_y() ,window_x,window_y);
                    cr->line_to(code_folding_area_width/2,window_y);   
                    
                    cr->move_to(code_folding_area_width/2,window_y);             
                    cr->line_to(code_folding_area_width/2+code_folding_area_width/2,window_y);                       
                    //vector_code_folding_pos.insert(vector_code_folding_pos.end(),code_folding_position(0,window_y,-1,iter.get_offset()+line_text.find("}")));
                    }
                 }
            
            i = inside_region_func_index;
           
            while(i<vector_curr_file_func.size()&&vector_curr_file_func[i].pos<=end_visible_iter.get_offset())
            {
                iter = buffer->get_iter_at_offset(vector_curr_file_func[i].pos);
                line = iter.get_line()+1;
                int start_line = line;                
                std::string start_line_text="";
                int brace_count = 0;                
                bool first_time = true;
                Gdk::Rectangle last_location,first_location;
                
                do
                {                    
                    iter = buffer->get_iter_at_line(line);
                    Gtk::TextIter line_end_iter = _source_view.get_line_end_iter(line);
                    line_text = buffer->get_text(iter,line_end_iter);
                    brace_count = brace_count + _source_view.count_str(line_text,_source_view.open_brace)-_source_view.count_str(line_text,_source_view.close_brace);                   
            
                    if(first_time)
                    {
                        start_line_text = line_text;
                         _source_view.get_iter_location(iter,first_location);
                        }
                    else
                        _source_view.get_iter_location(iter,last_location);
                    
                    first_time = false;
                    line++;
                    }
                while(brace_count!=0 && line <= end_visible_iter.get_line());               
               
                int window_x,window_y;
                _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_TEXT,first_location.get_x()-10,first_location.get_y(),window_x,window_y);
                cr->move_to(code_folding_area_width/2,window_y);     
                
                int x2,y2;   
                _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_TEXT,first_location.get_x()-10,last_location.get_height()+last_location.get_y(),x2,y2);
                cr->line_to(code_folding_area_width/2,y2);
                
                cr->move_to(code_folding_area_width/2,window_y);
                cr->line_to(code_folding_area_width/2+code_folding_area_width/2,window_y);              
                
                cr->move_to(code_folding_area_width/2,y2);
                cr->line_to(code_folding_area_width/2+code_folding_area_width/2,y2);
                
                int start_pos = buffer->get_iter_at_line(start_line).get_offset()+start_line_text.find("{");
                if(line<=end_visible_iter.get_line())
                     vector_code_folding_pos.insert(vector_code_folding_pos.end(),code_folding_position(window_y,y2,start_pos,iter.get_offset()+line_text.find("}")));
                else
                    vector_code_folding_pos.insert(vector_code_folding_pos.end(),code_folding_position(window_y,y2,start_pos,-1));           
                
                i++;
                }            
            }
        else if(i==vector_curr_file_func.size())
        {
            _source_view.get_iter_location(start_visible_iter,location);
            int window_x,window_y;
            _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_TEXT,location.get_x()-10,location.get_y(),window_x,window_y);
            if(window_y<0)window_y=0;
            cr->move_to(code_folding_area_width/2,0);     
            Gdk::Rectangle location2;
            end_visible_iter = buffer->get_iter_at_line(end_visible_iter.get_line());
            _source_view.get_iter_location(end_visible_iter,location2);
            int x2,y2;   
            _source_view.buffer_to_window_coords(Gtk::TEXT_WINDOW_TEXT,location.get_x()-10,location2.get_y(),x2,y2);
            cr->line_to(code_folding_area_width/2,get_height());
            }
        cr->stroke();     
        }
    return true;
    }

code_widget::~code_widget()
{
    }
