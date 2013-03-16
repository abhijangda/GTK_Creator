//391 Lines
#include"toolbox.h"
#include"focused_widget.h"

extern Gtk::Widget* focussed_widget;
extern focused_widget current_focused_widget;

ToolBox::ToolBox()
    : Gtk::VBox(false,2),expander_windows("Windows"),table_windows(3,1), cmdWindow(), cmdOffscreenWindow(),
      expander_container("Container"), table_container(3,4), cmdVBox(), cmdHBox(), cmdTable(), cmdFixed(), cmdScrolledWindow(),cmdToolBar(),
      cmdMenuBar(),cmdNotebook(), cmdFrame(),cmdEventBox(),cmdExpander(),
      expander_control_display("Control and Display"),table_control_display(3,7),cmdFileChooserButton(),cmdColorChooserButton(),
      cmdFontButton(), cmdScrollbar(),cmdProgressBar(),cmdSpinner(), cmdTreeView(),cmdButton(),cmdLabel(),cmdToggleButton(), cmdTextview(), 
      cmdEntry(), cmdComboBox(), cmdComboBoxText(),cmdCheckButton(),cmdRadioButton(),cmdStatusBar(),cmdVScale(), cmdHScale(), cmdSpinButton(),
    
      imgcmdWindow("./gtk_window.png"),imgcmdOffscreenWindow("./gtk_offscreenwindow.png"),
      imgcmdVBox("./gtk_vbox.png"), imgcmdHBox("./gtk_hbox.png"), imgcmdTable("./gtk_table.png"), imgcmdFixed("./gtk_fixed.png"),  imgcmdScrolledWindow("./gtk_scrollwin.png"),
      imgcmdToolBar("./gtk_toolbar.png"),   imgcmdNotebook("./gtk_notebook.png"),imgcmdFrame("./gtk_frame.png"),imgcmdEventBox("./gtk_eventbox.png"), 
    imgcmdExpander("./gtk_expander.png"),imgcmdMenuBar("./gtk_menubar.png"), 
     imgcmdButton("./gtk_button.png"), imgcmdTextview("./gtk_textview.png"), imgcmdEntry("./gtk_entry.png"), imgcmdLabel("./gtk_label.png"),
     imgcmdToggleButton("./gtk_togglebutton.png"), imgcmdStatusBar("./gtk_statusbar.png"), imgcmdComboBox("./gtk_combobox.png"), imgcmdComboBoxText("./gtk_comboboxtext.png"), 
    imgcmdCheckButton("./gtk_checkbutton.png"),imgcmdRadioButton("./gtk_radiobutton.png"),imgcmdVScale("./gtk_vscale.png"), imgcmdSpinButton("./gtk_spinbutton.png"), 
    imgcmdFileChooserButton("./gtk_filechooserbutton.png"), imgcmdColorChooserButton("./gtk_colorchooserbutton.png"), imgcmdFontButton("./gtk_fontbutton.png"),
     imgcmdHScale("./gtk_hscale.png"),imgcmdScrollbar("./gtk_hscrollbar.png"),imgcmdProgressBar("./gtk_progressbar.png"),
      imgcmdSpinner("./gtk_spinner.png"), imgcmdTreeView("./gtk_treeview.png")
{
    table_windows.attach(cmdWindow,0,1,0,1);
    //cmdWindow.set_size_request(50,50);
    cmdWindow.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdWindow_clicked),true);
    table_windows. attach(cmdOffscreenWindow,1,2,0,1);
    //cmdOffscreenWindow.set_size_request(50,50); 
    cmdOffscreenWindow.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdOffscreenWindow_clicked),true);     
    
    cmdWindow.add(imgcmdWindow);
    cmdOffscreenWindow.add(imgcmdOffscreenWindow);
    expander_windows.add(table_windows);
    
    table_container.attach(cmdVBox,0,1,0,1);
    //cmdVBox.set_size_request(50,10);
    cmdVBox.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdVBox_clicked));
    table_container.attach(cmdHBox,1,2,0,1);
    //cmdHBox.set_size_request(50,10);
    cmdHBox.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdHBox_clicked));
    table_container.attach(cmdTable,2,3,0,1);
    //cmdTable.set_size_request(50,10);
    cmdTable.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdTable_clicked));
    
    table_container.attach(cmdFixed,0,1,1,2);
    //cmdFixed.set_size_request(50,10);
    cmdFixed.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdFixed_clicked));    
    table_container.attach(cmdScrolledWindow,1,2,1,2);
    //cmdScrolledWindow.set_size_request(50,10);
    cmdScrolledWindow.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdScrolledWindow_clicked));
    table_container.attach(cmdMenuBar,2,3,1,2);
    //cmdMenuBar.set_size_request(50,10); 
    cmdMenuBar.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdMenuBar_clicked));  
    
    table_container.attach(cmdToolBar,0,1,2,3);
    //cmdToolBar.set_size_request(50,10); 
    cmdToolBar.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdToolBar_clicked));      
    table_container.attach(cmdNotebook,1,2,2,3);
    //cmdNotebook.set_size_request(50,10); 
    cmdNotebook.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdNotebook_clicked));    
    table_container.attach(cmdFrame,2,3,2,3);
    //cmdFrame.set_size_request(50,10); 
    cmdFrame.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdFrame_clicked));    
     
    table_container.attach(cmdEventBox,0,1,3,4);
    //cmdEventBox.set_size_request(50,10); 
    cmdEventBox.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdEventBox_clicked)); 
    table_container.attach(cmdExpander,1,2,3,4);
    //cmdExpander.set_size_request(50,10); 
    cmdExpander.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdExpander_clicked));         
    
    cmdVBox.add(imgcmdVBox);
    cmdHBox.add(imgcmdHBox);
    cmdTable.add(imgcmdTable);
    cmdFixed.add(imgcmdFixed);
    cmdScrolledWindow.add(imgcmdScrolledWindow);
    cmdMenuBar.add(imgcmdMenuBar);
    cmdToolBar.add(imgcmdToolBar);
    cmdNotebook.add(imgcmdNotebook);
    cmdFrame.add(imgcmdFrame);
    cmdEventBox.add(imgcmdEventBox);
    cmdExpander.add(imgcmdExpander);
    expander_container.add(table_container);
    
    table_control_display.attach(cmdButton,0,1,0,1);
    //cmdButton.set_size_request(50,10);
    cmdButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdButton_clicked));   
    table_control_display.attach(cmdTextview,1,2,0,1);
    //cmdTextview.set_size_request(50,10);
    cmdTextview.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdTextview_clicked));
    table_control_display.attach(cmdEntry,2,3,0,1);
    //cmdEntry.set_size_request(50,10);
    cmdEntry.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdEntry_clicked));
    
    table_control_display.attach(cmdLabel,0,1,1,2);
    //cmdLabel.set_size_request(50,10);
    cmdLabel.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdLabel_clicked));
    table_control_display.attach(cmdToggleButton,1,2,1,2);
    //cmdToggleButton.set_size_request(50,10);  
    cmdToggleButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdToggleButton_clicked));
    table_control_display.attach(cmdComboBox,2,3,1,2);
    //cmdComboBox.set_size_request(50,10); 
    cmdComboBox.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdComboBox_clicked));  
    
    table_control_display.attach(cmdComboBoxText,0,1,2,3);
    //cmdComboBoxText.set_size_request(50,10); 
    cmdComboBoxText.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdComboBoxText_clicked));  
    table_control_display.attach(cmdCheckButton,1,2,2,3);
    //cmdCheckButton.set_size_request(50,10); 
    cmdCheckButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdCheckButton_clicked));  
    table_control_display.attach(cmdRadioButton,2,3,2,3);
    //cmdRadioButton.set_size_request(50,10); 
    cmdRadioButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdRadioButton_clicked));  
    
    table_control_display.attach(cmdStatusBar,0,1,3,4);
    //cmdStatusBar.set_size_request(50,10); 
    cmdStatusBar.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdStatusBar_clicked));      
    table_control_display.attach(cmdFontButton,1,2,3,4);
    //cmdFontButton.set_size_request(50,10); 
    cmdFontButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdFontButton_clicked));     
    table_control_display.attach(cmdSpinButton,2,3,3,4);
    //cmdSpinButton.set_size_request(50,10); 
    cmdSpinButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdSpinButton_clicked)); 
    
    table_control_display.attach(cmdFileChooserButton,0,1,4,5);
    //cmdFileChooserButton.set_size_request(50,10); 
    cmdFileChooserButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdFileChooserButton_clicked));    
    table_control_display.attach(cmdColorChooserButton,1,2,4,5);
    //cmdColorChooserButton.set_size_request(50,10); 
    cmdColorChooserButton.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdColorChooserButton_clicked));        
    table_control_display.attach(cmdVScale,2,3,4,5);
    //cmdVScale.set_size_request(50,10); 
    cmdVScale.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdVScale_clicked)); 
    
    table_control_display.attach(cmdHScale,0,1,5,6);
    //cmdHScale.set_size_request(50,10); 
    cmdHScale.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdHScale_clicked));    
    table_control_display.attach(cmdScrollbar,1,2,5,6);
    //cmdScrollbar.set_size_request(50,10); 
    cmdScrollbar.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdScrollbar_clicked));     
    table_control_display.attach(cmdProgressBar,2,3,5,6);
    //cmdProgressBar.set_size_request(50,10); 
    cmdProgressBar.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdProgressBar_clicked)); 
    
    table_control_display.attach(cmdSpinner,0,1,6,7);
    //cmdSpinner.set_size_request(50,10); 
    cmdSpinner.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdSpinner_clicked));    
    table_control_display.attach(cmdTreeView,1,2,6,7);
    //cmdTreeView.set_size_request(50,10); 
    cmdTreeView.signal_clicked().connect(sigc::mem_fun(*this,&ToolBox::cmdTreeView_clicked));   
    
    cmdButton.add(imgcmdButton);
    cmdTextview.add(imgcmdTextview);
    cmdEntry.add(imgcmdEntry);
    cmdLabel.add(imgcmdLabel);
    cmdToggleButton.add(imgcmdToggleButton);
    cmdComboBox.add(imgcmdComboBox);
    cmdComboBoxText.add(imgcmdComboBoxText);
    cmdCheckButton.add(imgcmdCheckButton);
    cmdRadioButton.add(imgcmdRadioButton);
    
    cmdStatusBar.add(imgcmdStatusBar);
    cmdFontButton.add(imgcmdFontButton);
    cmdSpinButton.add(imgcmdSpinButton);
    
    cmdFileChooserButton.add(imgcmdFileChooserButton);
    cmdColorChooserButton.add(imgcmdColorChooserButton);    
    cmdVScale.add(imgcmdVScale);
    cmdHScale.add(imgcmdHScale);
    cmdScrollbar.add(imgcmdScrollbar);
    cmdProgressBar.add(imgcmdProgressBar);
    cmdSpinner.add(imgcmdSpinner);
    cmdTreeView.add(imgcmdTreeView);
    expander_control_display.add(table_control_display);
    
    expander_windows.set_expanded();
    expander_container.set_expanded();
    expander_control_display.set_expanded();
    
    pack_start(expander_windows,false,false);
    pack_start(expander_container,false,false);
    pack_start(expander_control_display,false,false);
    } 

void ToolBox::set_active_false()
{   
    cmdWindow.set_active(false);
    cmdVBox.set_active(false);
    cmdHBox.set_active(false);
    cmdTable.set_active(false);
    cmdFixed.set_active(false);
    cmdButton.set_active(false);
    cmdTextview.set_active(false);
    cmdEntry.set_active(false);
    cmdScrolledWindow.set_active(false);
    cmdLabel.set_active(false);
    cmdToggleButton.set_active(false);        
    cmdStatusBar.set_active(false);
    cmdComboBox.set_active(false);
    cmdComboBoxText.set_active(false);
    cmdCheckButton.set_active(false);
    cmdRadioButton.set_active(false);
    cmdMenuBar.set_active(false);
    cmdToolBar.set_active(false);
    cmdNotebook.set_active(false);
    cmdOffscreenWindow.set_active(false);
    cmdDialog.set_active(false);
    cmdFrame.set_active(false);
    cmdPaned.set_active(false);
    cmdHButtonBox.set_active(false);
    cmdVButtonBox.set_active(false);
    cmdEventBox.set_active(false);
    cmdExpander.set_active(false);
    cmdVScale.set_active(false);
    cmdSpinButton.set_active(false);
    cmdFileChooserButton.set_active(false);
    cmdColorChooserButton.set_active(false);
    cmdFontButton.set_active(false);
    cmdHScale.set_active(false);
    cmdScrollbar.set_active(false);
    cmdProgressBar.set_active(false);
    cmdSpinner.set_active(false);        
    cmdTreeView.set_active(false);
    }
void ToolBox::set_others_false(Gtk::ToggleButton& button)
{   
    if(button.get_label()!= cmdWindow.get_label())
         cmdWindow.set_active(false);
    if(button.get_label()!= cmdVBox.get_label())
    cmdVBox.set_active(false);
    if(button.get_label()!= cmdHBox.get_label())
    cmdHBox.set_active(false);
    if(button.get_label()!= cmdTable.get_label())
    cmdTable.set_active(false);
    if(button.get_label()!= cmdFixed.get_label())
    cmdFixed.set_active(false);
    if(button.get_label()!= cmdButton.get_label())
    cmdButton.set_active(false);
    if(button.get_label()!= cmdTextview.get_label())
    cmdTextview.set_active(false);
    if(button.get_label()!= cmdEntry.get_label())
    cmdEntry.set_active(false);
    if(button.get_label()!= cmdScrolledWindow.get_label())
    cmdScrolledWindow.set_active(false);
    if(button.get_label()!= cmdLabel.get_label())
    cmdLabel.set_active(false);
    if(button.get_label()!= cmdToggleButton.get_label())
    cmdToggleButton.set_active(false);        
    if(button.get_label()!= cmdStatusBar.get_label())
    cmdStatusBar.set_active(false);
    if(button.get_label()!= cmdComboBox.get_label())
    cmdComboBox.set_active(false);
    if(button.get_label()!= cmdComboBoxText.get_label())
    cmdComboBoxText.set_active(false);
    if(button.get_label()!= cmdCheckButton.get_label())
    cmdCheckButton.set_active(false);
    if(button.get_label()!= cmdRadioButton.get_label())
    cmdRadioButton.set_active(false);
    if(button.get_label()!= cmdMenuBar.get_label())
    cmdMenuBar.set_active(false);
    if(button.get_label()!= cmdToolBar.get_label())
    cmdToolBar.set_active(false);
    if(button.get_label()!= cmdNotebook.get_label())
    cmdNotebook.set_active(false);
    if(button.get_label()!= cmdOffscreenWindow.get_label())
    cmdOffscreenWindow.set_active(false);
    if(button.get_label()!= cmdDialog.get_label())
    cmdDialog.set_active(false);
    if(button.get_label()!= cmdFrame.get_label())
    cmdFrame.set_active(false);
    if(button.get_label()!= cmdPaned.get_label())
    cmdPaned.set_active(false);
    if(button.get_label()!= cmdHButtonBox.get_label())    
    cmdHButtonBox.set_active(false);
    if(button.get_label()!= cmdVButtonBox.get_label())
    cmdVButtonBox.set_active(false);
    if(button.get_label()!= cmdEventBox.get_label())
    cmdEventBox.set_active(false);
    if(button.get_label()!= cmdExpander.get_label())
    cmdExpander.set_active(false);
    if(button.get_label()!= cmdVScale.get_label())
    cmdVScale.set_active(false);
    if(button.get_label()!= cmdSpinButton.get_label())
    cmdSpinButton.set_active(false);
    if(button.get_label()!= cmdFileChooserButton.get_label())
    cmdFileChooserButton.set_active(false);
    if(button.get_label()!= cmdColorChooserButton.get_label())
    cmdColorChooserButton.set_active(false);
    if(button.get_label()!= cmdFontButton.get_label())
    cmdFontButton.set_active(false);
    if(button.get_label()!= cmdHScale.get_label())
    cmdHScale.set_active(false);
    if(button.get_label()!= cmdScrollbar.get_label())
    cmdScrollbar.set_active(false);
    if(button.get_label()!= cmdProgressBar.get_label())
    cmdProgressBar.set_active(false);
    if(button.get_label()!= cmdSpinner.get_label())
    cmdSpinner.set_active(false);        
    if(button.get_label()!= cmdTreeView.get_label())
    cmdTreeView.set_active(false);
    }
ToolBox::type_signal_can_draw_widget ToolBox::signal_can_draw_widget()
{
    return m_signal_can_draw_widget;
    }

void ToolBox:: cmdOffscreenWindow_clicked()
{
    set_others_false(cmdOffscreenWindow);
    m_signal_can_draw_widget("gtk_offscreenwindow");
    }

void ToolBox::cmdFrame_clicked()
{
    set_others_false(cmdFrame);
    m_signal_can_draw_widget("gtk_frame");
    }

void ToolBox::cmdEventBox_clicked()
{
    set_others_false(cmdEventBox);
    m_signal_can_draw_widget("gtk_eventbox");
    }
void ToolBox::cmdExpander_clicked()
{
    set_others_false(cmdExpander);
    m_signal_can_draw_widget("gtk_expander");
    }

void ToolBox::cmdSpinButton_clicked()
{
    set_others_false(cmdSpinButton);
    m_signal_can_draw_widget("gtk_spinbutton");
    }
void ToolBox::cmdFileChooserButton_clicked()
{
    set_others_false(cmdFileChooserButton);
    m_signal_can_draw_widget("gtk_filechooserbutton");
    }
void ToolBox::cmdColorChooserButton_clicked()
{
    set_others_false(cmdColorChooserButton);
    m_signal_can_draw_widget("gtk_colorchooserbutton");
    }
void ToolBox::cmdFontButton_clicked()
{
    set_others_false(cmdFontButton);
    m_signal_can_draw_widget("gtk_fontbutton");
    }
void ToolBox::cmdHScale_clicked()
{
    set_others_false(cmdHScale);
    m_signal_can_draw_widget("gtk_hscale");
    }
void ToolBox::cmdVScale_clicked()
{
    set_others_false(cmdVScale);
    m_signal_can_draw_widget("gtk_vscale");
    }
void ToolBox::cmdScrollbar_clicked()
{
    set_others_false(cmdScrollbar);
    m_signal_can_draw_widget("gtk_hscrollbar");
    }
void ToolBox::cmdProgressBar_clicked()
{
    set_others_false(cmdProgressBar);
    m_signal_can_draw_widget("gtk_progressbar");
    }
void ToolBox::cmdSpinner_clicked()
{
    set_others_false(cmdSpinner);
    m_signal_can_draw_widget("gtk_spinner");
    }
void ToolBox::cmdTreeView_clicked()
{
    set_others_false(cmdTreeView);
    m_signal_can_draw_widget("gtk_treeview");
    }
void ToolBox::cmdIconView_clicked()
{
    //set_others_false(cmdIconView);
    m_signal_can_draw_widget("gtk_iconview");
    }
        
void ToolBox::cmdNotebook_clicked()
{
    set_others_false(cmdNotebook);
    m_signal_can_draw_widget("gtk_notebook");
    }

void ToolBox::cmdToolBar_clicked()
{
    set_others_false(cmdToolBar);

    m_signal_can_draw_widget("gtk_toolbar");
    }

void ToolBox::cmdMenuBar_clicked()
{
    set_others_false(cmdMenuBar);
    m_signal_can_draw_widget("gtk_menubar");
    }

void ToolBox::cmdStatusBar_clicked()
{
    set_others_false(cmdStatusBar);
    m_signal_can_draw_widget("gtk_statusbar");
    }

void ToolBox::cmdCheckButton_clicked()
{
    set_others_false(cmdCheckButton);
    m_signal_can_draw_widget("gtk_checkbutton");
    }

void ToolBox::cmdRadioButton_clicked()
{
    set_others_false(cmdRadioButton);
    m_signal_can_draw_widget("gtk_radiobutton");
    }

void ToolBox::cmdComboBoxText_clicked()
{
    set_others_false(cmdComboBoxText);
    m_signal_can_draw_widget("gtk_comboboxtext");
    }

void ToolBox::cmdComboBox_clicked()
{
    set_others_false(cmdComboBox);
    m_signal_can_draw_widget("gtk_combobox");
    }

void ToolBox::cmdToggleButton_clicked()
{
    set_others_false(cmdToggleButton);
    m_signal_can_draw_widget("gtk_togglebutton");
    }

void ToolBox::cmdLabel_clicked()
{
    set_others_false(cmdLabel);
    m_signal_can_draw_widget("gtk_label");
    }

void ToolBox::cmdEntry_clicked()
{
    set_others_false(cmdEntry);
    m_signal_can_draw_widget("gtk_entry");
    }

void ToolBox::cmdTextview_clicked()
{
    set_others_false(cmdTextview);
    m_signal_can_draw_widget("gtk_textview");
    }

void ToolBox::cmdScrolledWindow_clicked()
{
    set_others_false(cmdScrolledWindow);
    m_signal_can_draw_widget("gtk_scrollwin");
    }

void ToolBox::cmdFixed_clicked()
{
    set_others_false(cmdFixed);
    m_signal_can_draw_widget("gtk_fixed");
    }

void ToolBox::cmdTable_clicked()
{
    set_others_false(cmdTable);
    m_signal_can_draw_widget("gtk_table");
    }

void ToolBox::cmdHBox_clicked()
{
    set_others_false(cmdHBox);
    m_signal_can_draw_widget("gtk_hbox");
    }

void ToolBox::cmdButton_clicked()
{
    set_others_false(cmdButton);
    m_signal_can_draw_widget("gtk_button");
    }

void ToolBox::cmdVBox_clicked()
{
    set_others_false(cmdVBox);
    m_signal_can_draw_widget("gtk_vbox");
    }

void ToolBox::cmdWindow_clicked()
{
    set_others_false(cmdWindow);
    m_signal_can_draw_widget("gtk_window");
    }

ToolBox::~ToolBox(){}
