//59 Lines
#include"reg_exp_search_dialog.h"

reg_exp_search_dialog::reg_exp_search_dialog(source_view& _source_view)
: Gtk::Dialog("Regular Expression Search"), hbox(false,5), cmd_search("Search"), cmd_close("Close"),
  lbl_regexp("Regular Expression"),current_source_view(_source_view)
{
    hbox.pack_start(lbl_regexp,false,false,5);
    hbox.pack_start(entry_regexp,true,true,5);
    Gtk::VBox* vbox = get_vbox();
    vbox->pack_start(hbox,true,true,5);
    
    Gtk::ButtonBox *dialog_button_box = get_action_area();
    dialog_button_box->pack_start(cmd_search);
    dialog_button_box->pack_start(cmd_close);
    
    cmd_search.signal_clicked().connect(sigc::mem_fun(*this,&reg_exp_search_dialog::cmd_search_clicked));
    cmd_close.signal_clicked().connect(sigc::mem_fun(*this,&reg_exp_search_dialog::cmd_close_clicked));
    counter = 0;
    }

reg_exp_search_dialog::~reg_exp_search_dialog()
{}

void reg_exp_search_dialog::cmd_search_clicked()
{
    std::string reg_exp;
    reg_exp = entry_regexp.get_text();
    Glib::RefPtr<gtksourceview::SourceBuffer> buffer= current_source_view.get_source_buffer();
    Gtk::TextIter start_iter, end_iter;
    start_iter = buffer->begin();
    end_iter = buffer->end();
    std::string text = buffer->get_text();
    Glib::RefPtr<Glib::Regex> regex;
    Glib::MatchInfo match_info;
    
    int start=0,end=0;
    regex = Glib::Regex::create(reg_exp);
    if(!regex->match(text,match_info))
        return;
        
    for(int i =0;i<counter;i++)
        match_info.next();
    if(!match_info.fetch_pos(0,start,end))
    {
        counter = 0;
        return;
        }
    
    start_iter = buffer->get_iter_at_offset(start);
    end_iter = buffer->get_iter_at_offset(end);
    buffer->select_range(start_iter,end_iter);
    current_source_view.scroll_to(start_iter);
    counter++;    
    }

void reg_exp_search_dialog::cmd_close_clicked()
{
    destroy_();
    }