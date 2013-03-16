#include"stock_functions.h"

Gtk::ComboBox* get_stock_combo_box(Model_Column_Stock& model_column_stock,Glib::RefPtr<Gtk::ListStore>& cb_tree_model_stock)
{
    Gtk::ComboBox* combo_box = new Gtk::ComboBox();
    
    cb_tree_model_stock=Gtk::ListStore::create(model_column_stock);
    Gtk::TreeModel::Row row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "NONE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "ABOUT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "ADD";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "APPLY";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "BOLD";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CANCEL";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CDROM";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CLEAR";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CLOSE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "COLOR_PICKER";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CONVERT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CONNECT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "COPY";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "CUT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DELETE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DIALOG_AUTHENTICATION";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DIALOG_ERROR";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DIALOG_INFO";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DIALOG_QUESTION";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DIALOG_WARNING";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DISCONNECT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DND";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "DND_MULTIPLE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "EDIT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "EXECUTE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "FILE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "FIND";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "FIND_AND_REPLACE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "FLOPPY";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "FULLSCREEN";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GOTO_BOTTOM";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GOTO_FIRST";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GOTO_LAST";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GOTO_TOP";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GO_BACK";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GO_DOWN";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GO_FORWARD";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "GOUP";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "HARDDISK";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "HELP";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "HOME";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "INDENT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "INDEX";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "INFO";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "ITALIC";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "JUMP_TO";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "JUSTIFY_CENTER";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "JUSTIFY_FILL";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "JUSTIFY_LEFT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "JUSTIFY_RIGHT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "LEAVE_FULLSCREEN";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_FORWARD";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_NEXT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_PAUSE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_PLAY";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_PREVIOUS";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_RECORD";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_REWIND";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MEDIA_STOP";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "MISSING_IMAGE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "NETWORK";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "NEW";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "NO";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "OK";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "OPEN";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "PASTE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "PREFERENCES";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "PRINT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "PRINT_PREVIEW";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "PROPERTIES";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "QUIT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "REDO";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "REFRESH";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "REMOVE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "REVERT_TO_SAVED";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SAVE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SAVE_AS";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SELECT_COLOR";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SELECT_FONT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SORT_ASCENDING";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SORT_DESCENDING";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "SPELL_CHECK";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "STOP";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "STRIKE_THROUGH";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "UNDELETE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "UNDERLINE";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "UNDO";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "UNINDENT";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "YES";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "ZOOM_100";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "ZOOM_FIT";
    row = *(cb_tree_model_stock->append());;
    row[model_column_stock.col] = "ZOOM_IN";
    row = *(cb_tree_model_stock->append());
    row[model_column_stock.col] = "ZOOM_OUT";
    
    combo_box->set_model(cb_tree_model_stock);
    combo_box->pack_start(model_column_stock.col);   
    
    return combo_box;
    }

std::string get_stock_string(Gtk::BuiltinStockID stockid) 
{
    if(stockid==Gtk::Stock::DIALOG_AUTHENTICATION)
         return "DIALOG_AUTHENTICATION";
    if(stockid==Gtk::Stock::DIALOG_INFO)
        return "DIALOG_INFO";
    if(stockid==Gtk::Stock::DIALOG_WARNING) 
        return "DIALOG_WARNING";
    if(stockid==Gtk::Stock::DIALOG_ERROR) 
        return "DIALOG_ERROR";
    if(stockid==Gtk::Stock::DIALOG_QUESTION) 
        return "DIALOG_QUESTION";
    if(stockid==Gtk::Stock::DND)    
     return "DND";
    if(stockid==Gtk::Stock::DND_MULTIPLE)    
     return "DND_MULTIPLE";
    if(stockid==Gtk::Stock::ABOUT)    
     return "ABOUT";
    if(stockid==Gtk::Stock::ADD)  
       return "ADD";
    if(stockid==Gtk::Stock::APPLY)  
       return "APPLY";
    if(stockid==Gtk::Stock::BOLD)    
     return "BOLD";
    if(stockid==Gtk::Stock::CANCEL) 
       return "CANCEL";
    if(stockid==Gtk::Stock::CAPS_LOCK_WARNING)   
      return "CAPS_LOCK_WARNING";
    if(stockid==Gtk::Stock::CDROM)   
      return "CDROM";
    if(stockid==Gtk::Stock::CLEAR)     
    return "CLEAR";
    if(stockid==Gtk::Stock::CLOSE) 
        return "CLOSE";
    if(stockid==Gtk::Stock::COLOR_PICKER) 
        return "COLOR_PICKER";
    if(stockid==Gtk::Stock::CONVERT)   
      return "CONVERT";
    if(stockid==Gtk::Stock::CONNECT)  
       return "CONNECT";
    if(stockid==Gtk::Stock::COPY)   
      return "COPY";
    if(stockid==Gtk::Stock::CUT)  
       return "CUT";
    if(stockid==Gtk::Stock::DELETE)  
       return "DELETE";
    if(stockid==Gtk::Stock::DIRECTORY) 
        return "DIRECTORY";
    if(stockid==Gtk::Stock::DISCARD) 
        return "DISCARD";
    if(stockid==Gtk::Stock::DISCONNECT)  
       return "DISCONNECT";
    if(stockid==Gtk::Stock::EDIT)  
       return "EDIT";
    if(stockid==Gtk::Stock::EXECUTE)  
       return "EXECUTE";
    if(stockid==Gtk::Stock::FILE) 
        return "FILE";
    if(stockid==Gtk::Stock::FIND) 
        return "FIND";
    if(stockid==Gtk::Stock::FIND_AND_REPLACE) 
        return "FIND_AND_REPLACE";
    if(stockid==Gtk::Stock::FLOPPY)  
       return "FLOPPY";
    if(stockid==Gtk::Stock::FULLSCREEN)    
     return "FULLSCREEN";
    if(stockid==Gtk::Stock::LEAVE_FULLSCREEN)   
      return "LEAVE_FULLSCREEN";
    if(stockid==Gtk::Stock::GOTO_BOTTOM) 
        return "GOTO_BOTTOM";
    if(stockid==Gtk::Stock::GOTO_FIRST)    
     return "GOTO_FIRST";
    if(stockid==Gtk::Stock::GOTO_LAST)   
      return "GOTO_LAST";
    if(stockid==Gtk::Stock::GOTO_TOP)   
      return "GOTO_TOP";
    if(stockid==Gtk::Stock::GO_BACK)  
       return "GO_BACK";
    if(stockid==Gtk::Stock::GO_DOWN) 
        return "GO_DOWN";
    if(stockid==Gtk::Stock::GO_FORWARD)
         return "GO_FORWARD";
    if(stockid==Gtk::Stock::GO_UP)   
      return "GO_UP";
    if(stockid==Gtk::Stock::HARDDISK) 
        return "HARDDISK";
    if(stockid==Gtk::Stock::HELP)  
       return "HELP";
    if(stockid==Gtk::Stock::HOME)   
      return "HOME";
    if(stockid==Gtk::Stock::INDEX)  
       return "INDEX";
    if(stockid==Gtk::Stock::INFO)      
     return "INFO";
    if(stockid==Gtk::Stock::INDENT)  
       return "INDENT";
    if(stockid==Gtk::Stock::UNINDENT) 
        return "UNINDENT";
    if(stockid==Gtk::Stock::ITALIC)     
    return "ITALIC";
    if(stockid==Gtk::Stock::JUMP_TO)  
       return "JUMP_TO";
    if(stockid==Gtk::Stock::JUSTIFY_CENTER)  
       return "JUSTIFY_CENTER";
    if(stockid==Gtk::Stock::JUSTIFY_FILL)   
      return "JUSTIFY_FILL";
    if(stockid==Gtk::Stock::JUSTIFY_LEFT)  
       return "JUSTIFY_LEFT";
    if(stockid==Gtk::Stock::JUSTIFY_RIGHT)
         return "JUSTIFY_RIGHT";
    if(stockid==Gtk::Stock::MISSING_IMAGE) 
        return "MISSING_IMAGE";
    if(stockid==Gtk::Stock::MEDIA_FORWARD)   
      return "MEDIA_FORWARD";
    if(stockid==Gtk::Stock::MEDIA_NEXT)    
     return "MEDIA_NEXT";
    if(stockid==Gtk::Stock::MEDIA_PAUSE)  
       return "MEDIA_PAUSE";
    if(stockid==Gtk::Stock::MEDIA_PLAY)   
      return "MEDIA_PLAY";
    if(stockid==Gtk::Stock::MEDIA_PREVIOUS) 
        return "MEDIA_PREVIOUS";
    if(stockid==Gtk::Stock::MEDIA_RECORD)    
     return "MEDIA_RECORD";
    if(stockid==Gtk::Stock::MEDIA_REWIND)   
      return "MEDIA_REWIND";
    if(stockid==Gtk::Stock::MEDIA_STOP)   
      return "MEDIA_STOP";
    if(stockid==Gtk::Stock::NETWORK)   
      return "NETWORK";
    if(stockid==Gtk::Stock::NEW)   
      return "NEW";
    if(stockid==Gtk::Stock::NO)     
    return "NO";
    if(stockid==Gtk::Stock::OK) 
        return "OK";
    if(stockid==Gtk::Stock::OPEN)  
       return "OPEN";
    if(stockid==Gtk::Stock::ORIENTATION_PORTRAIT)   
      return "ORIENTATION_PORTRAIT";
    if(stockid==Gtk::Stock::ORIENTATION_LANDSCAPE) 
        return "ORIENTATION_LANDSCAPE";
    if(stockid==Gtk::Stock::ORIENTATION_REVERSE_LANDSCAPE)   
      return "ORIENTATION_REVERSE_LANDSCAPE";
    if(stockid==Gtk::Stock::ORIENTATION_REVERSE_PORTRAIT)  
       return "ORIENTATION_REVERSE_PORTRAIT";
    if(stockid==Gtk::Stock::PASTE)     
       return "PASTE";
    if(stockid==Gtk::Stock::PREFERENCES) 
       return "PREFERENCES";
    if(stockid==Gtk::Stock::PAGE_SETUP)  
       return "PAGE_SETUP";
    if(stockid==Gtk::Stock::PRINT)     
    return "PRINT";
    if(stockid==Gtk::Stock::PRINT_ERROR) 
        return "PRINT_ERROR";
    if(stockid==Gtk::Stock::PRINT_PREVIEW) 
        return "PRINT_PREVIEW";
    if(stockid==Gtk::Stock::PRINT_REPORT)  
       return "PRINT_REPORT";
    if(stockid==Gtk::Stock::PRINT_WARNING) 
        return "PRINT_WARNING";
    if(stockid==Gtk::Stock::PROPERTIES) 
        return "PROPERTIES";
    if(stockid==Gtk::Stock::QUIT)   
      return "QUIT";
    if(stockid==Gtk::Stock::REDO)   
      return "REDO";
    if(stockid==Gtk::Stock::REFRESH)
         return "REFRESH";
    if(stockid==Gtk::Stock::REMOVE)  
       return "REMOVE";
    if(stockid==Gtk::Stock::REVERT_TO_SAVED) 
        return "REVERT_TO_SAVED";
    if(stockid==Gtk::Stock::SAVE)    
     return "SAVE";
    if(stockid==Gtk::Stock::SAVE_AS)  
       return "SAVE_AS";
    if(stockid==Gtk::Stock::SELECT_ALL)    
     return "SELECT_ALL";
    if(stockid==Gtk::Stock::SELECT_COLOR)  
       return "SELECT_COLOR";
    if(stockid==Gtk::Stock::SELECT_FONT) 
        return "SELECT_FONT";
    if(stockid==Gtk::Stock::SORT_ASCENDING)  
       return "SORT_ASCENDING";
    if(stockid==Gtk::Stock::SORT_DESCENDING)  
       return "SORT_DESCENDING";
    if(stockid==Gtk::Stock::SPELL_CHECK) 
        return "SPELL_CHECK";
    if(stockid==Gtk::Stock::STOP)  
       return "STOP";
    if(stockid==Gtk::Stock::STRIKETHROUGH)    
     return "STRIKETHROUGH";
    if(stockid==Gtk::Stock::UNDELETE)  
       return "UNDELETE";
    if(stockid==Gtk::Stock::UNDERLINE)    
     return "UNDERLINE";
    if(stockid==Gtk::Stock::UNDO)  
       return "UNDO";
    if(stockid==Gtk::Stock::YES)    
     return "YES";
    if(stockid==Gtk::Stock::ZOOM_100)     
    return "ZOOM_100";
    if(stockid==Gtk::Stock::ZOOM_FIT)   
      return "ZOOM_FIT";
    if(stockid==Gtk::Stock::ZOOM_IN)  
      return "ZOOM_IN";
    if(stockid==Gtk::Stock::ZOOM_OUT) 
        return "ZOOM_OUT";
    
    return "";
    }

Gtk::BuiltinStockID get_stock_from_string(std::string stockid)
{
    if(stockid=="DIALOG_AUTHENTICATION")
         return Gtk::Stock::DIALOG_AUTHENTICATION;
    if(stockid=="DIALOG_INFO")
        return Gtk::Stock::DIALOG_INFO;
    if(stockid=="DIALOG_WARNING") 
        return Gtk::Stock::DIALOG_WARNING;
    if(stockid=="DIALOG_ERROR") 
        return Gtk::Stock::DIALOG_ERROR;
    if(stockid=="DIALOG_QUESTION") 
        return Gtk::Stock::DIALOG_QUESTION;
    if(stockid=="DND")    
     return Gtk::Stock::DND;
    if(stockid=="DND_MULTIPLE")    
     return Gtk::Stock::DND_MULTIPLE;
    if(stockid=="ABOUT")    
     return Gtk::Stock::ABOUT;
    if(stockid=="ADD")  
       return Gtk::Stock::ADD;
    if(stockid=="APPLY")  
       return Gtk::Stock::APPLY;
    if(stockid=="BOLD")    
     return Gtk::Stock::BOLD;
    if(stockid=="CANCEL") 
       return Gtk::Stock::CANCEL;
    if(stockid=="CAPS_LOCK_WARNING")   
      return Gtk::Stock::CAPS_LOCK_WARNING;
    if(stockid=="CDROM")   
      return Gtk::Stock::CDROM;
    if(stockid=="CLEAR")     
    return Gtk::Stock::CLEAR;
    if(stockid=="CLOSE") 
        return Gtk::Stock::CLOSE;
    if(stockid=="COLOR_PICKER") 
        return Gtk::Stock::COLOR_PICKER;
    if(stockid=="CONVERT")   
      return Gtk::Stock::CONVERT;
    if(stockid=="CONNECT")  
       return Gtk::Stock::CONNECT;
    if(stockid=="COPY")   
      return Gtk::Stock::COPY;
    if(stockid=="CUT")  
       return Gtk::Stock::CUT;
    if(stockid=="DELETE")  
       return Gtk::Stock::DELETE;
    if(stockid=="DIRECTORY") 
        return Gtk::Stock::DIRECTORY;
    if(stockid=="DISCARD") 
        return Gtk::Stock::DISCARD;
    if(stockid=="DISCONNECT")  
       return Gtk::Stock::DISCONNECT;
    if(stockid=="EDIT")  
       return Gtk::Stock::EDIT;
    if(stockid=="EXECUTE")  
       return Gtk::Stock::EXECUTE;
    if(stockid=="FILE") 
        return Gtk::Stock::FILE;
    if(stockid=="FIND") 
        return Gtk::Stock::FIND;
    if(stockid=="FIND_AND_REPLACE") 
        return Gtk::Stock::FIND_AND_REPLACE;
    if(stockid=="FLOPPY")  
       return Gtk::Stock::FLOPPY;
    if(stockid=="FULLSCREEN")    
     return Gtk::Stock::FULLSCREEN;
    if(stockid=="LEAVE_FULLSCREEN")   
      return Gtk::Stock::LEAVE_FULLSCREEN;
    if(stockid=="GOTO_BOTTOM") 
        return Gtk::Stock::GOTO_BOTTOM;
    if(stockid=="GOTO_FIRST")    
     return Gtk::Stock::GOTO_FIRST;
    if(stockid=="GOTO_LAST")   
      return Gtk::Stock::GOTO_LAST;
    if(stockid=="GOTO_TOP")   
      return Gtk::Stock::GOTO_TOP;
    if(stockid=="GO_BACK")  
       return Gtk::Stock::GO_BACK;
    if(stockid=="GO_DOWN") 
        return Gtk::Stock::GO_DOWN;
    if(stockid=="GO_FORWARD")
         return Gtk::Stock::GO_FORWARD;
    if(stockid=="GO_UP")   
      return Gtk::Stock::GO_UP;
    if(stockid=="HARDDISK") 
        return Gtk::Stock::HARDDISK;
    if(stockid=="HELP")  
       return Gtk::Stock::HELP;
    if(stockid=="HOME")   
      return Gtk::Stock::HOME;
    if(stockid=="INDEX")  
       return Gtk::Stock::INDEX;
    if(stockid=="INFO")      
     return Gtk::Stock::INFO;
    if(stockid=="INDENT")  
       return Gtk::Stock::INDENT;
    if(stockid=="UNINDENT") 
        return Gtk::Stock::UNINDENT;
    if(stockid=="ITALIC")     
    return Gtk::Stock::ITALIC;
    if(stockid=="JUMP_TO")  
       return Gtk::Stock::JUMP_TO;
    if(stockid=="JUSTIFY_CENTER")  
       return Gtk::Stock::JUSTIFY_CENTER;
    if(stockid=="JUSTIFY_FILL")   
      return Gtk::Stock::JUSTIFY_FILL;
    if(stockid=="JUSTIFY_LEFT")  
       return Gtk::Stock::JUSTIFY_LEFT;
    if(stockid=="JUSTIFY_RIGHT")
         return Gtk::Stock::JUSTIFY_RIGHT;
    if(stockid=="MISSING_IMAGE") 
        return Gtk::Stock::MISSING_IMAGE;
    if(stockid=="MEDIA_FORWARD")   
      return Gtk::Stock::MEDIA_FORWARD;
    if(stockid=="MEDIA_NEXT")    
     return Gtk::Stock::MEDIA_NEXT;
    if(stockid=="MEDIA_PAUSE")  
       return Gtk::Stock::MEDIA_PAUSE;
    if(stockid=="MEDIA_PLAY")   
      return Gtk::Stock::MEDIA_PLAY;
    if(stockid=="MEDIA_PREVIOUS") 
        return Gtk::Stock::MEDIA_PREVIOUS;
    if(stockid=="MEDIA_RECORD")    
     return Gtk::Stock::MEDIA_RECORD;
    if(stockid=="MEDIA_REWIND")   
      return Gtk::Stock::MEDIA_REWIND;
    if(stockid=="MEDIA_STOP")   
      return Gtk::Stock::MEDIA_STOP;
    if(stockid=="NETWORK")   
      return Gtk::Stock::NETWORK;
    if(stockid=="NEW")   
      return Gtk::Stock::NEW;
    if(stockid=="NO")     
    return Gtk::Stock::NO;
    if(stockid=="OK") 
        return Gtk::Stock::OK;
    if(stockid=="OPEN")  
       return Gtk::Stock::OPEN;
    if(stockid=="ORIENTATION_PORTRAIT")   
      return Gtk::Stock::ORIENTATION_PORTRAIT;
    if(stockid=="ORIENTATION_LANDSCAPE") 
        return Gtk::Stock::ORIENTATION_LANDSCAPE;
    if(stockid=="ORIENTATION_REVERSE_LANDSCAPE")   
      return Gtk::Stock::ORIENTATION_REVERSE_LANDSCAPE;
    if(stockid=="ORIENTATION_REVERSE_PORTRAIT")  
       return Gtk::Stock::ORIENTATION_REVERSE_PORTRAIT;
    if(stockid=="PASTE")     
    return Gtk::Stock::PASTE;
    if(stockid=="PREFERENCES") 
       return Gtk::Stock::PREFERENCES;
    if(stockid=="PAGE_SETUP")  
       return Gtk::Stock::PAGE_SETUP;
    if(stockid=="PRINT")     
    return Gtk::Stock::PRINT;
    if(stockid=="PRINT_ERROR") 
        return Gtk::Stock::PRINT_ERROR;
    if(stockid=="PRINT_PREVIEW") 
        return Gtk::Stock::PRINT_PREVIEW;
    if(stockid=="PRINT_REPORT")  
       return Gtk::Stock::PRINT_REPORT;
    if(stockid=="PRINT_WARNING") 
        return Gtk::Stock::PRINT_WARNING;
    if(stockid=="PROPERTIES") 
        return Gtk::Stock::PROPERTIES;
    if(stockid=="QUIT")   
      return Gtk::Stock::QUIT;
    if(stockid=="REDO")   
      return Gtk::Stock::REDO;
    if(stockid=="REFRESH")
         return Gtk::Stock::REFRESH;
    if(stockid=="REMOVE")  
       return Gtk::Stock::REMOVE;
    if(stockid=="REVERT_TO_SAVED") 
        return Gtk::Stock::REVERT_TO_SAVED;
    if(stockid=="SAVE")    
     return Gtk::Stock::SAVE;
    if(stockid=="SAVE_AS")  
       return Gtk::Stock::SAVE_AS;
    if(stockid=="SELECT_ALL")    
     return Gtk::Stock::SELECT_ALL;
    if(stockid=="SELECT_COLOR")  
       return Gtk::Stock::SELECT_COLOR;
    if(stockid=="SELECT_FONT") 
        return Gtk::Stock::SELECT_FONT;
    if(stockid=="SORT_ASCENDING")  
       return Gtk::Stock::SORT_ASCENDING;
    if(stockid=="SORT_DESCENDING")  
       return Gtk::Stock::SORT_DESCENDING;
    if(stockid=="SPELL_CHECK") 
        return Gtk::Stock::SPELL_CHECK;
    if(stockid=="STOP")  
       return Gtk::Stock::STOP;
    if(stockid=="STRIKETHROUGH")    
     return Gtk::Stock::STRIKETHROUGH;
    if(stockid=="UNDELETE")  
       return Gtk::Stock::UNDELETE;
    if(stockid=="UNDERLINE")    
     return Gtk::Stock::UNDERLINE;
    if(stockid=="UNDO")  
       return Gtk::Stock::UNDO;
    if(stockid=="YES")    
     return Gtk::Stock::YES;
    if(stockid=="ZOOM_100")     
    return Gtk::Stock::ZOOM_100;
    if(stockid=="ZOOM_FIT")   
      return Gtk::Stock::ZOOM_FIT;
    if(stockid=="ZOOM_IN")  
      return Gtk::Stock::ZOOM_IN;
    if(stockid=="ZOOM_OUT") 
        return Gtk::Stock::ZOOM_OUT;
    }

std::string get_stock_label(Gtk::BuiltinStockID  stockid)
{
    if(stockid==Gtk::Stock::ABOUT)
    return "About";
    if(stockid==Gtk::Stock::ADD)
    return "Add";
    if(stockid==Gtk::Stock::APPLY)
    return "Apply";
    if(stockid==Gtk::Stock::BOLD)
    return "Bold";
    if(stockid==Gtk::Stock::CANCEL)
    return "Cancel";
    if(stockid==Gtk::Stock::CDROM)
    return "CD-Rom";    
    if(stockid==Gtk::Stock::CLEAR)
    return "Clear";
    if(stockid==Gtk::Stock::CLOSE)
    return "Close";
    if(stockid==Gtk::Stock::COLOR_PICKER)
    return "Color Picker";    
    if(stockid==Gtk::Stock::CONVERT)
    return "Convert";
    if(stockid==Gtk::Stock::CONNECT)
    return "Connect";
    if(stockid==Gtk::Stock::COPY)
    return "Copy";
    if(stockid==Gtk::Stock::CUT)
    return "Cut";
    if(stockid==Gtk::Stock::DELETE)
    return "Delete";
    if(stockid==Gtk::Stock::DIALOG_AUTHENTICATION)
    return "Auntication";
    if(stockid==Gtk::Stock::DIALOG_ERROR)
    return "Error";
    if(stockid==Gtk::Stock::DIALOG_INFO)
    return "Information";
    if(stockid==Gtk::Stock::DIALOG_QUESTION)
    return "Question";
    if(stockid==Gtk::Stock::DIALOG_WARNING)
    return "Warning";
    if(stockid==Gtk::Stock::DISCONNECT)
    return "Disconnect";    
    if(stockid==Gtk::Stock::DND)
    return "Drag And Drop";
    if(stockid==Gtk::Stock::DND_MULTIPLE)
    return "Drag And Drop multiple";
    if(stockid==Gtk::Stock::EDIT)
    return "Edit";
    if(stockid==Gtk::Stock::EXECUTE)
    return "Execute";
    if(stockid==Gtk::Stock::FILE)
    return "File";
    if(stockid==Gtk::Stock::FIND)
    return "Find";
    if(stockid==Gtk::Stock::FIND_AND_REPLACE)
    return "Find and Replace";
    if(stockid==Gtk::Stock::FLOPPY)
    return "Floppy";
    if(stockid==Gtk::Stock::FULLSCREEN)
    return "Fullscreen";
    if(stockid==Gtk::Stock::GOTO_BOTTOM)
    return "Bottom";
    if(stockid==Gtk::Stock::GOTO_FIRST)
    return "First";
    if(stockid==Gtk::Stock::GOTO_LAST)
    return "Last";
    if(stockid==Gtk::Stock::GOTO_TOP)
    return "Top";
    if(stockid==Gtk::Stock::GO_BACK)
    return "Back";
    if(stockid==Gtk::Stock::GO_DOWN)
    return "Down";
    if(stockid==Gtk::Stock::GO_FORWARD)
    return "Forward";
    if(stockid==Gtk::Stock::GO_UP)
    return "Up";
    if(stockid==Gtk::Stock::HARDDISK)
    return "Hard disk";
    if(stockid==Gtk::Stock::HELP)
    return "Help";
    if(stockid==Gtk::Stock::HOME)
    return "Home";
    if(stockid==Gtk::Stock::INDENT)
    return "Indent";
    if(stockid==Gtk::Stock::INDEX)
    return "Index";
    if(stockid==Gtk::Stock::INFO)
    return "Info";
    if(stockid==Gtk::Stock::ITALIC)
    return "Italic";
    if(stockid==Gtk::Stock::JUMP_TO)
    return "Jump";
    if(stockid==Gtk::Stock::JUSTIFY_CENTER)
    return "Center";
    if(stockid==Gtk::Stock::JUSTIFY_FILL)
    return "Fill";
    if(stockid==Gtk::Stock::JUSTIFY_LEFT)
    return "Left";
    if(stockid==Gtk::Stock::JUSTIFY_RIGHT)
    return "Right";
    if(stockid==Gtk::Stock::LEAVE_FULLSCREEN)
    return "Leave";
    if(stockid==Gtk::Stock::MEDIA_FORWARD)
    return "Media forward";
    if(stockid==Gtk::Stock::MEDIA_NEXT)
    return "Media next";
    if(stockid==Gtk::Stock::MEDIA_PAUSE)
    return "Media pause";
    if(stockid==Gtk::Stock::MEDIA_PLAY)
    return "Media play" ;
    if(stockid==Gtk::Stock::MEDIA_PREVIOUS)
    return "Media previous";
    if(stockid==Gtk::Stock::MEDIA_RECORD)
    return "Media record";
    if(stockid==Gtk::Stock::MEDIA_REWIND)
    return "Media rewind" ;
    if(stockid==Gtk::Stock::MEDIA_STOP)
    return "Media stop";
    if(stockid==Gtk::Stock::MISSING_IMAGE)
    return "Missing";
    if(stockid==Gtk::Stock::NETWORK)
    return "Network";
    if(stockid==Gtk::Stock::NEW)
    return "New";
    if(stockid==Gtk::Stock::NO)
    return "No";
    if(stockid==Gtk::Stock::OK)
    return "Ok";
    if(stockid==Gtk::Stock::OPEN)
    return "Open";
    if(stockid==Gtk::Stock::PASTE)
    return "Paste";
    if(stockid==Gtk::Stock::PREFERENCES)
    return "Preferences";
    if(stockid==Gtk::Stock::PRINT)
    return "Print";
    if(stockid==Gtk::Stock::PRINT_PREVIEW)
    return "Print Preview";
    if(stockid==Gtk::Stock::PROPERTIES)
    return "Properties";
    if(stockid==Gtk::Stock::QUIT)
    return "Quit";
    if(stockid==Gtk::Stock::REDO)
    return "Redo";
    if(stockid==Gtk::Stock::REFRESH)
    return "Refresh";
    if(stockid==Gtk::Stock::REMOVE)
    return "Remove";
    if(stockid==Gtk::Stock::REVERT_TO_SAVED)
    return "Revert";
    if(stockid==Gtk::Stock::SAVE)
    return "Save";
    if(stockid==Gtk::Stock::SAVE_AS)
    return "Save As";
    if(stockid==Gtk::Stock::SELECT_COLOR)
    return "Color";
    if(stockid==Gtk::Stock::SELECT_FONT)
    return "Font";
    if(stockid==Gtk::Stock::SORT_ASCENDING)
    return "Ascending";
    if(stockid==Gtk::Stock::SORT_DESCENDING)
    return "Descending";
    if(stockid==Gtk::Stock::SPELL_CHECK)
    return "Spell Check";
    if(stockid==Gtk::Stock::STOP)
    return "Stop";
    if(stockid==Gtk::Stock::STRIKETHROUGH)
    return "Strikethrough";
    if(stockid==Gtk::Stock::UNDELETE)
    return "Undelete";
    if(stockid==Gtk::Stock::UNDERLINE)
    return "Underline";
    if(stockid==Gtk::Stock::UNDO)
    return "Undo";
    if(stockid==Gtk::Stock::UNINDENT)
    return "Unindent";
    if(stockid==Gtk::Stock::YES)
    return "Yes";
    if(stockid==Gtk::Stock::ZOOM_100)
    return "Zoom";
    if(stockid==Gtk::Stock::ZOOM_FIT)
    return "Zoom Fit";
    if(stockid==Gtk::Stock::ZOOM_IN)
    return "Zoom In";
    if(stockid==Gtk::Stock::ZOOM_OUT)
    return "Zoom Out";
    
    return "";
    }

std::string get_gml_string_from_stock_string(std::string stock_str)
{
    Gtk::BuiltinStockID stock = get_stock_from_string(stock_str);
    
    if(stock==Gtk::Stock::ABOUT)
        return "gtk-about";
    if(stock==Gtk::Stock::ADD)
        return "gtk-add";
    if(stock==Gtk::Stock::APPLY)
        return "gtk-apply";
    if(stock==Gtk::Stock::BOLD)
        return "gtk-bold";
    if(stock==Gtk::Stock::CANCEL)
        return "gtk-cancel";
    if(stock==Gtk::Stock::CDROM)
        return "gtk-cdrom";
    if(stock==Gtk::Stock::CLEAR)
        return "gtk-clear";
    if(stock==Gtk::Stock::CLOSE)
        return "gtk-close";
    if(stock==Gtk::Stock::COLOR_PICKER)
        return "gtk-color-picker";
    if(stock==Gtk::Stock::CONVERT)
        return "gtk-convert";
    if(stock==Gtk::Stock::CONNECT)
        return "gtk-connect";
    if(stock==Gtk::Stock::COPY)
        return "gtk-copy";
    if(stock==Gtk::Stock::CUT)
        return "gtk-cut";
    if(stock==Gtk::Stock::DELETE)
        return "gtk-delete";
    if(stock==Gtk::Stock::DIALOG_AUTHENTICATION)
        return "gtk-dialog-authentication";
    if(stock==Gtk::Stock::DIALOG_ERROR)
        return "gtk-dialog-error";
    if(stock==Gtk::Stock::DIALOG_INFO)
        return "gtk-dialog-info";
    if(stock==Gtk::Stock::DIALOG_QUESTION)
        return "gtk-dialog-question";
    if(stock==Gtk::Stock::DIALOG_WARNING)
        return "gtk-dialog-warning";
    if(stock==Gtk::Stock::DISCONNECT)
        return "gtk-disconnect";
    if(stock==Gtk::Stock::DND)
        return "gtk-dnd";
    if(stock==Gtk::Stock::DND_MULTIPLE)
        return "gtk-dnd-multiple";
    if(stock==Gtk::Stock::EDIT)
        return "gtk-edit";
    if(stock==Gtk::Stock::EXECUTE)
        return "gtk-execute";
    if(stock==Gtk::Stock::FILE)
        return "gtk-file";
    if(stock==Gtk::Stock::FIND)
        return "gtk-find";
    if(stock==Gtk::Stock::FIND_AND_REPLACE)
        return "gtk-find-and-replace";
    if(stock==Gtk::Stock::FLOPPY)
        return "gtk-floppy";
    if(stock==Gtk::Stock::FULLSCREEN)
        return "gtk-fullscreen";
    if(stock==Gtk::Stock::GOTO_BOTTOM)
        return "gtk-goto-bottom";
    if(stock==Gtk::Stock::GOTO_FIRST)
        return "gtk-goto-first";
    if(stock==Gtk::Stock::GOTO_LAST)
        return "gtk-goto-last";
    if(stock==Gtk::Stock::GOTO_TOP)
        return "gtk-goto-top";
    if(stock==Gtk::Stock::GO_BACK)
        return "gtk-go-back";
    if(stock==Gtk::Stock::GO_DOWN)
        return "gtk-go-down";
    if(stock==Gtk::Stock::GO_FORWARD)
        return "gtk-go-forward";
    if(stock==Gtk::Stock::GO_UP)
        return "gtk-go-up";
    if(stock==Gtk::Stock::HARDDISK)
        return "gtk-harddisk";
    if(stock==Gtk::Stock::HELP)
        return "gtk-help";
    if(stock==Gtk::Stock::HOME)
        return "gtk-home";
    if(stock==Gtk::Stock::INDENT)
        return "gtk-indent";
    if(stock==Gtk::Stock::INDEX)
        return "gtk-index";
    if(stock==Gtk::Stock::INFO)
        return "gtk-info";
    if(stock==Gtk::Stock::ITALIC)
        return "gtk-italic";
    if(stock==Gtk::Stock::JUMP_TO)
        return "gtk-jump-to";
    if(stock==Gtk::Stock::JUSTIFY_CENTER)
        return "gtk-justify-center";
    if(stock==Gtk::Stock::JUSTIFY_FILL)
        return "gtk-justify-fill";
    if(stock==Gtk::Stock::JUSTIFY_LEFT)
        return "gtk-justify-left";
    if(stock==Gtk::Stock::JUSTIFY_RIGHT)
        return "gtk-justify-right";
    if(stock==Gtk::Stock::LEAVE_FULLSCREEN)
        return "gtk-leave-fullscreen";
    if(stock==Gtk::Stock::MEDIA_FORWARD)
        return "gtk-media-forward";
    if(stock==Gtk::Stock::MEDIA_NEXT)
        return "gtk-media-next";
    if(stock==Gtk::Stock::MEDIA_PAUSE)
        return "gtk-media-pause";
    if(stock==Gtk::Stock::MEDIA_PLAY)
        return "gtk-media-play";
    if(stock==Gtk::Stock::MEDIA_PREVIOUS)
        return "gtk-media-previous";
    if(stock==Gtk::Stock::MEDIA_RECORD)
        return "gtk-media-record";
    if(stock==Gtk::Stock::MEDIA_REWIND)
        return "gtk-media-rewind";
    if(stock==Gtk::Stock::MEDIA_STOP)
        return "gtk-media-stop";
    if(stock==Gtk::Stock::MISSING_IMAGE)
        return "gtk-missing-image";
    if(stock==Gtk::Stock::NETWORK)
        return "gtk-network";
    if(stock==Gtk::Stock::NEW)
        return "gtk-new";
    if(stock==Gtk::Stock::NO)
        return "gtk-no";
    if(stock==Gtk::Stock::OK)
        return "gtk-ok";
    if(stock==Gtk::Stock::OPEN)
        return "gtk-open";
    if(stock==Gtk::Stock::PASTE)
        return "gtk-paste";
    if(stock==Gtk::Stock::PREFERENCES)
        return "gtk-preferences";
    if(stock==Gtk::Stock::PRINT)
        return "gtk-print";
    if(stock==Gtk::Stock::PRINT_PREVIEW)
        return "gtk-print-preview";
    if(stock==Gtk::Stock::PROPERTIES)
        return "gtk-properties";
    if(stock==Gtk::Stock::QUIT)
        return "gtk-quit";
    if(stock==Gtk::Stock::REDO)
        return "gtk-redo";
    if(stock==Gtk::Stock::REFRESH)
        return "gtk-refresh";
    if(stock==Gtk::Stock::REMOVE)
        return "gtk-remove";
    if(stock==Gtk::Stock::REVERT_TO_SAVED)
        return "gtk-revert-to-saved";
    if(stock==Gtk::Stock::SAVE)
        return "gtk-save";
    if(stock==Gtk::Stock::SAVE_AS)
        return "gtk-save-as";
    if(stock==Gtk::Stock::SELECT_COLOR)
        return "gtk-select-color";
    if(stock==Gtk::Stock::SELECT_FONT)
        return "gtk-select-font";
    if(stock==Gtk::Stock::SORT_ASCENDING)
        return "gtk-sort-ascending";
    if(stock==Gtk::Stock::SORT_DESCENDING)
        return "gtk-sort-descending";
    if(stock==Gtk::Stock::SPELL_CHECK)
        return "gtk-spell-check";
    if(stock==Gtk::Stock::STOP)
        return "gtk-stop";
    if(stock==Gtk::Stock::STRIKETHROUGH)
        return "gtk-strikethrough";
    if(stock==Gtk::Stock::UNDELETE)
        return "gtk-undelete";
    if(stock==Gtk::Stock::UNDERLINE)
        return "gtk-underline";
    if(stock==Gtk::Stock::UNDO)
        return "gtk-undo";
    if(stock==Gtk::Stock::UNINDENT)
        return "gtk-unindent";
    if(stock==Gtk::Stock::YES)
        return "gtk-yes";
    if(stock==Gtk::Stock::ZOOM_100)
        return "gtk-zoom-100";
    if(stock==Gtk::Stock::ZOOM_FIT)
        return "gtk-zoom-fit";
    if(stock==Gtk::Stock::ZOOM_IN)
        return "gtk-zoom-in";
    if(stock==Gtk::Stock::ZOOM_OUT)
        return "gtk-zoom-out";
    return "";
    }

std::string get_stock_string_from_gml_string(std::string stock_gml)
{
    Gtk::BuiltinStockID _stock_id;
    Gtk::BuiltinStockID stock_id = _stock_id;
    if(stock_gml=="gtk-about")
        stock_id=Gtk::Stock::ABOUT;
    if(stock_gml=="gtk-add")
        stock_id=Gtk::Stock::ADD;
    if(stock_gml=="gtk-apply")
        stock_id=Gtk::Stock::APPLY;
    if(stock_gml=="gtk-bold")
        stock_id=Gtk::Stock::BOLD;
    if(stock_gml=="gtk-cancel")
        stock_id=Gtk::Stock::CANCEL;
    if(stock_gml=="gtk-cdrom")
        stock_id=Gtk::Stock::CDROM;
    if(stock_gml=="gtk-clear")
        stock_id=Gtk::Stock::CLEAR;
    if(stock_gml=="gtk-close")
        stock_id=Gtk::Stock::CLOSE;
    if(stock_gml=="gtk-color-picker")
        stock_id=Gtk::Stock::COLOR_PICKER;
    if(stock_gml=="gtk-convert")
        stock_id=Gtk::Stock::CONVERT;
    if(stock_gml=="gtk-connect")
        stock_id=Gtk::Stock::CONNECT;
    if(stock_gml=="gtk-copy")
        stock_id=Gtk::Stock::COPY;
    if(stock_gml=="gtk-cut")
        stock_id=Gtk::Stock::CUT;
    if(stock_gml=="gtk-delete")
        stock_id=Gtk::Stock::DELETE;
    if(stock_gml=="gtk-dialog-authentication")
        stock_id=Gtk::Stock::DIALOG_AUTHENTICATION;
    if(stock_gml=="gtk-dialog-error")
        stock_id=Gtk::Stock::DIALOG_ERROR;
    if(stock_gml=="gtk-dialog-info")
        stock_id=Gtk::Stock::DIALOG_INFO;
    if(stock_gml=="gtk-dialog-question")
        stock_id=Gtk::Stock::DIALOG_QUESTION;
    if(stock_gml=="gtk-dialog-warning")
        stock_id=Gtk::Stock::DIALOG_WARNING;
    if(stock_gml=="gtk-disconnect")
        stock_id=Gtk::Stock::DISCONNECT;
    if(stock_gml=="gtk-dnd")
        stock_id=Gtk::Stock::DND;
    if(stock_gml=="gtk-dnd-multiple")
        stock_id=Gtk::Stock::DND_MULTIPLE;
    if(stock_gml=="gtk-edit")
        stock_id=Gtk::Stock::EDIT;
    if(stock_gml=="gtk-execute")
        stock_id=Gtk::Stock::EXECUTE;
    if(stock_gml=="gtk-file")
        stock_id=Gtk::Stock::FILE;
    if(stock_gml=="gtk-find")
        stock_id=Gtk::Stock::FIND;
    if(stock_gml=="gtk-find-and-replace")
        stock_id=Gtk::Stock::FIND_AND_REPLACE;
    if(stock_gml=="gtk-floppy")
        stock_id=Gtk::Stock::FLOPPY;
    if(stock_gml=="gtk-fullscreen")
        stock_id=Gtk::Stock::FULLSCREEN;
    if(stock_gml=="gtk-goto-bottom")
        stock_id=Gtk::Stock::GOTO_BOTTOM;
    if(stock_gml=="gtk-goto-first")
        stock_id=Gtk::Stock::GOTO_FIRST;
    if(stock_gml=="gtk-goto-last")
        stock_id=Gtk::Stock::GOTO_LAST;
    if(stock_gml=="gtk-goto-top")
        stock_id=Gtk::Stock::GOTO_TOP;
    if(stock_gml=="gtk-go-back")
        stock_id=Gtk::Stock::GO_BACK;
    if(stock_gml=="gtk-go-down")
        stock_id=Gtk::Stock::GO_DOWN;
    if(stock_gml=="gtk-go-forward")
        stock_id=Gtk::Stock::GO_FORWARD;
    if(stock_gml=="gtk-go-up")
        stock_id=Gtk::Stock::GO_UP;
    if(stock_gml=="gtk-harddisk")
        stock_id=Gtk::Stock::HARDDISK;
    if(stock_gml=="gtk-help")
        stock_id=Gtk::Stock::HELP;
    if(stock_gml=="gtk-home")
        stock_id=Gtk::Stock::HOME;
    if(stock_gml=="gtk-indent")
        stock_id=Gtk::Stock::INDENT;
    if(stock_gml=="gtk-index")
        stock_id=Gtk::Stock::INDEX;
    if(stock_gml=="gtk-info")
        stock_id=Gtk::Stock::INFO;
    if(stock_gml=="gtk-italic")
        stock_id=Gtk::Stock::ITALIC;
    if(stock_gml=="gtk-jump-to")
        stock_id=Gtk::Stock::JUMP_TO;
    if(stock_gml=="gtk-justify-center")
        stock_id=Gtk::Stock::JUSTIFY_CENTER;
    if(stock_gml=="gtk-justify-fill")
        stock_id=Gtk::Stock::JUSTIFY_FILL;
    if(stock_gml=="gtk-justify-left")
        stock_id=Gtk::Stock::JUSTIFY_LEFT;
    if(stock_gml=="gtk-justify-right")
        stock_id=Gtk::Stock::JUSTIFY_RIGHT;
    if(stock_gml=="gtk-leave-fullscreen")
        stock_id=Gtk::Stock::LEAVE_FULLSCREEN;
    if(stock_gml=="gtk-media-forward")
        stock_id=Gtk::Stock::MEDIA_FORWARD;
    if(stock_gml=="gtk-media-next")
        stock_id=Gtk::Stock::MEDIA_NEXT;
    if(stock_gml=="gtk-media-pause")
        stock_id=Gtk::Stock::MEDIA_PAUSE;
    if(stock_gml=="gtk-media-play")
        stock_id=Gtk::Stock::MEDIA_PLAY;
    if(stock_gml=="gtk-media-previous")
        stock_id=Gtk::Stock::MEDIA_PREVIOUS;
    if(stock_gml=="gtk-media-record")
        stock_id=Gtk::Stock::MEDIA_RECORD;
    if(stock_gml=="gtk-media-rewind")
        stock_id=Gtk::Stock::MEDIA_REWIND;
    if(stock_gml=="gtk-media-stop")
        stock_id=Gtk::Stock::MEDIA_STOP;
    if(stock_gml=="gtk-missing-image")
        stock_id=Gtk::Stock::MISSING_IMAGE;
    if(stock_gml=="gtk-network")
        stock_id=Gtk::Stock::NETWORK;
    if(stock_gml=="gtk-new")
        stock_id=Gtk::Stock::NEW;
    if(stock_gml=="gtk-no")
        stock_id=Gtk::Stock::NO;
    if(stock_gml=="gtk-ok")
        stock_id=Gtk::Stock::OK;
    if(stock_gml=="gtk-open")
        stock_id=Gtk::Stock::OPEN;
    if(stock_gml=="gtk-paste")
        stock_id=Gtk::Stock::PASTE;
    if(stock_gml=="gtk-preferences")
        stock_id=Gtk::Stock::PREFERENCES;
    if(stock_gml=="gtk-print")
        stock_id=Gtk::Stock::PRINT;
    if(stock_gml=="gtk-print-preview")
        stock_id=Gtk::Stock::PRINT_PREVIEW;
    if(stock_gml=="gtk-properties")
        stock_id=Gtk::Stock::PROPERTIES;
    if(stock_gml=="gtk-quit")
        stock_id=Gtk::Stock::QUIT;
    if(stock_gml=="gtk-redo")
        stock_id=Gtk::Stock::REDO;
    if(stock_gml=="gtk-refresh")
        stock_id=Gtk::Stock::REFRESH;
    if(stock_gml=="gtk-remove")
        stock_id=Gtk::Stock::REMOVE;
    if(stock_gml=="gtk-revert-to-saved")
        stock_id=Gtk::Stock::REVERT_TO_SAVED;
    if(stock_gml=="gtk-save")
        stock_id=Gtk::Stock::SAVE;
    if(stock_gml=="gtk-save-as")
        stock_id=Gtk::Stock::SAVE_AS;
    if(stock_gml=="gtk-select-color")
        stock_id=Gtk::Stock::SELECT_COLOR;
    if(stock_gml=="gtk-select-font")
        stock_id=Gtk::Stock::SELECT_FONT;
    if(stock_gml=="gtk-sort-ascending")
        stock_id=Gtk::Stock::SORT_ASCENDING;
    if(stock_gml=="gtk-sort-descending")
        stock_id=Gtk::Stock::SORT_DESCENDING;
    if(stock_gml=="gtk-spell-check")
        stock_id=Gtk::Stock::SPELL_CHECK;
    if(stock_gml=="gtk-stop")
        stock_id=Gtk::Stock::STOP;
    if(stock_gml=="gtk-strikethrough")
        stock_id=Gtk::Stock::STRIKETHROUGH;
    if(stock_gml=="gtk-undelete")
        stock_id=Gtk::Stock::UNDELETE;
    if(stock_gml=="gtk-underline")
        stock_id=Gtk::Stock::UNDERLINE;
    if(stock_gml=="gtk-undo")
        stock_id=Gtk::Stock::UNDO;
    if(stock_gml=="gtk-unindent")
        stock_id=Gtk::Stock::UNINDENT;
    if(stock_gml=="gtk-yes")
        stock_id=Gtk::Stock::YES;
    if(stock_gml=="gtk-zoom-100")
        stock_id=Gtk::Stock::ZOOM_100;
    if(stock_gml=="gtk-zoom-fit")
        stock_id=Gtk::Stock::ZOOM_FIT;
    if(stock_gml=="gtk-zoom-in")
        stock_id=Gtk::Stock::ZOOM_IN;
    if(stock_gml=="gtk-zoom-out")
        stock_id=Gtk::Stock::ZOOM_OUT;
    
    if(stock_id==_stock_id)
        return "";
        
    return get_stock_string(stock_id);
    }