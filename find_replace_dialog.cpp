//78 Lines
#include"find_replace_dialog.h"

find_replace_dialog::find_replace_dialog(source_view& _source_view, Gtk::Window& parent)
: current_source_view(_source_view), Gtk::Dialog("Find and Replace",parent,false,false),cmdfind("Find",true),
  cmdreplace("Replace",true),cmdreplaceall("Replace All",true),cmdclose("Close",true)
{    
    lblfind.set_text("Find");
    lblreplace.set_text("Replace");
    
    entry_find.set_size_request(230,31);
    fixed.put(entry_find,100,10);   
    entry_replace.set_size_request(230,31);
    fixed.put(entry_replace,100,50);   
    lblfind.set_size_request(66,21);
    fixed.put(lblfind,10,17);   
    lblreplace.set_size_request(66,21);
    fixed.put(lblreplace,10,51);   
    cmdfind.set_size_request(95,31);
    fixed.put(cmdfind,350,10);
    cmdfind.signal_clicked().connect(sigc::bind<Gtk::Entry&>(sigc::mem_fun(*this,&find_replace_dialog::cmdfind_clicked),entry_find));
    cmdreplace.set_size_request(95,31);
    fixed.put(cmdreplace,350,50); 
    cmdreplace.signal_clicked().connect(sigc::bind<Gtk::Entry&,Gtk::Entry&>(sigc::mem_fun(*this,&find_replace_dialog::cmdreplace_clicked),entry_find,entry_replace));
    cmdreplaceall.set_size_request(95,31);
    fixed.put(cmdreplaceall,350,90); 
    cmdreplaceall.signal_clicked().connect(sigc::bind<Gtk::Entry&,Gtk::Entry&>(sigc::mem_fun(*this,&find_replace_dialog::cmdreplaceall_clicked),entry_find,entry_replace));
    cmdclose.set_size_request(95,31);
    fixed.put(cmdclose,350,130);
    cmdclose.signal_clicked().connect(sigc::mem_fun(*this,&find_replace_dialog::cmdclose_clicked));
    
    Gtk::VBox* dialog_vbox = get_vbox();
    dialog_vbox->pack_start(fixed);
    }

find_replace_dialog::~find_replace_dialog()
{
    }

void find_replace_dialog::cmdfind_clicked(Gtk::Entry& entry)
{
    buffer = current_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator search_start_iter,search_end_iter;
    search_start_iter = buffer->get_iter_at_offset(0);
    if(search_start_iter.forward_search(entry.get_text(),Gtk::TEXT_SEARCH_TEXT_ONLY,search_start_iter,search_end_iter))
    {
        buffer->select_range(search_start_iter,search_end_iter);
        current_source_view.scroll_to(search_start_iter);
        search_start_iter = search_end_iter;
        }
    }

void find_replace_dialog::cmdreplace_clicked(Gtk::Entry& entry_find,Gtk::Entry& entry_replace)
{
    buffer = current_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator search_start_iter = buffer->get_iter_at_mark(buffer->get_insert()), search_end_iter;
    if(search_start_iter.forward_search(entry_find.get_text(),Gtk::TEXT_SEARCH_TEXT_ONLY,search_start_iter,search_end_iter))
    {
        buffer->select_range(search_start_iter,search_end_iter);
        current_source_view.scroll_to(search_start_iter);
        if (buffer->erase_selection())
            buffer->insert_at_cursor(entry_replace.get_text());  
        }
    }

void find_replace_dialog::cmdreplaceall_clicked(Gtk::Entry& entry_find,Gtk::Entry& entry_replace)
{
    buffer = current_source_view.get_source_buffer();
    Gtk::TextBuffer::iterator search_start_iter = buffer->get_iter_at_offset(0), search_end_iter;
    while(search_start_iter.forward_search(entry_find.get_text(),Gtk::TEXT_SEARCH_TEXT_ONLY,search_start_iter,search_end_iter))
    {
        buffer->select_range(search_start_iter,search_end_iter);
        current_source_view.scroll_to(search_start_iter);
        int offset = search_end_iter.get_offset();
        if (buffer->erase_selection())
            buffer->insert_at_cursor(entry_replace.get_text());  
        search_start_iter = buffer->get_iter_at_offset(offset);
        }
    }