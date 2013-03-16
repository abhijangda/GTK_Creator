//122 Lines
#include"find_dialog.h"

find_dialog::find_dialog(source_view& _source_view, Gtk::Window& parent,bool _in_selection)
: Gtk::Dialog("Find",parent,false,true), current_source_view(_source_view), cmdfind("Find",true),cmdfindnext("Find Next",true),
  cmdfindprevious("Find Previous",true),cmdclose("Close",true),in_selection(_in_selection)
{
    Gtk::VBox *dialog_vbox = get_vbox();
    label.set_text("Find");
    
    hbox.pack_start(label,Gtk::PACK_SHRINK,5);
    hbox.pack_start(entry,Gtk::PACK_EXPAND_WIDGET);
    dialog_vbox->pack_start(hbox);
    Gtk::ButtonBox *dialog_button_box = get_action_area();
    
    dialog_button_box->pack_start(cmdfind);
    dialog_button_box->pack_start(cmdfindnext);
    dialog_button_box->pack_start(cmdfindprevious);
    dialog_button_box->pack_start(cmdclose);    
    cmdfind.signal_clicked().connect(sigc::bind<Gtk::Entry&>(sigc::mem_fun(*this,&find_dialog::cmdfind_clicked),entry));
    cmdfindnext.signal_clicked().connect(sigc::bind<Gtk::Entry&>(sigc::mem_fun(*this,&find_dialog::cmdfindnext_clicked),entry));
    cmdfindprevious.signal_clicked().connect(sigc::bind<Gtk::Entry&>(sigc::mem_fun(*this,&find_dialog::cmdfindprevious_clicked),entry));
    cmdclose.signal_clicked().connect(sigc::mem_fun(*this,&find_dialog::cmdclose_clicked));  
    
    if(in_selection)
         _source_view.get_buffer()->get_selection_bounds(selection_start,selection_end);
    }

find_dialog::~find_dialog()
{
    }

void find_dialog::cmdfind_clicked(Gtk::Entry& entry)
{
    buffer = current_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator search_start_iter,search_end_iter;
    search_start_iter = buffer->get_iter_at_offset(0);
    if(in_selection)
        search_start_iter = selection_start;
        
    if(search_start_iter.forward_search(entry.get_text(),Gtk::TEXT_SEARCH_TEXT_ONLY,search_start_iter,search_end_iter))
    {        
        if(in_selection)
        {
            if(search_start_iter.get_offset()>=selection_start.get_offset() && search_end_iter.get_offset()<=selection_end.get_offset())
            {
                buffer->select_range(search_start_iter,search_end_iter);
                current_source_view.scroll_to(search_start_iter);
                search_start_iter = search_end_iter;
                }
            }
        else
        {            
            buffer->select_range(search_start_iter,search_end_iter);
            current_source_view.scroll_to(search_start_iter);
            search_start_iter = search_end_iter;
            }
        }
    }

void find_dialog::cmdfindnext_clicked(Gtk::Entry& entry)
{
    buffer = current_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator search_start_iter,search_end_iter;
    if (buffer->get_has_selection()==true)
    {
        buffer->get_selection_bounds(search_end_iter,search_start_iter);
        if(search_start_iter.forward_search(entry.get_text(),Gtk::TEXT_SEARCH_TEXT_ONLY,search_start_iter,search_end_iter))
        {
            if(in_selection)
            {
                if(search_start_iter.get_offset()>=selection_start.get_offset() && search_end_iter.get_offset()<=selection_end.get_offset())
                {
                    buffer->select_range(search_start_iter,search_end_iter);
                    current_source_view.scroll_to(search_start_iter);
                    search_start_iter = search_end_iter;
                    }
                }
            else
            {            
                buffer->select_range(search_start_iter,search_end_iter);
                current_source_view.scroll_to(search_start_iter);
                search_start_iter = search_end_iter;
                }
            }
        }
    }

void find_dialog::cmdfindprevious_clicked(Gtk::Entry& entry)
{
    buffer = current_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator search_start_iter,search_end_iter;
     if (buffer->get_has_selection()==true)
    {
        buffer->get_selection_bounds(search_end_iter,search_start_iter);
        search_start_iter = buffer->get_iter_at_offset(search_start_iter.get_offset()-1);
        if(search_start_iter.backward_search(entry.get_text(),Gtk::TEXT_SEARCH_TEXT_ONLY,search_start_iter,search_end_iter))
        {
            if(in_selection)
            {
                if(search_start_iter.get_offset()>=selection_start.get_offset() && search_end_iter.get_offset()<=selection_end.get_offset())
                {
                    buffer->select_range(search_start_iter,search_end_iter);
                    current_source_view.scroll_to(search_start_iter);
                    search_start_iter = search_end_iter;
                    }
                }
            else
            {            
                buffer->select_range(search_start_iter,search_end_iter);
                current_source_view.scroll_to(search_start_iter);
                search_start_iter = search_end_iter;
                }
            }
        }
    }

void find_dialog::cmdclose_clicked()
{
    destroy_();
    }
