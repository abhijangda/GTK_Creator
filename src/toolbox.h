//72 Lines
#include<gtkmm.h>

#ifndef TOOLBOX_H
#define TOOLBOX_H

class ToolBox : public Gtk::VBox
{
    public:
        ToolBox();
        ~ToolBox();
        Gtk::Expander expander_container, expander_control_display,expander_windows;
        Gtk::Table table_windows, table_container, table_control_display;
        
        Gtk::ToggleButton cmdWindow, cmdVBox, cmdHBox, cmdTable, cmdFixed, cmdButton;
        Gtk::ToggleButton cmdTextview, cmdEntry,cmdScrolledWindow,cmdLabel;
        Gtk::ToggleButton cmdToggleButton, cmdStatusBar,cmdComboBox,cmdComboBoxText;
        Gtk::ToggleButton cmdCheckButton,cmdRadioButton,cmdMenuBar, cmdToolBar;
        Gtk::ToggleButton cmdNotebook,cmdOffscreenWindow,cmdDialog,cmdFrame;
        Gtk::ToggleButton cmdPaned,cmdHButtonBox,cmdVButtonBox,cmdEventBox, cmdExpander;
        Gtk::ToggleButton cmdVScale, cmdSpinButton,cmdFileChooserButton,cmdColorChooserButton;
        Gtk::ToggleButton cmdFontButton,cmdHScale,cmdScrollbar,cmdProgressBar;
        Gtk::ToggleButton cmdSpinner, cmdTreeView;
    
        Gtk::Image imgcmdWindow, imgcmdVBox, imgcmdHBox, imgcmdTable, imgcmdFixed, imgcmdButton, imgcmdTextview;
        Gtk::Image imgcmdEntry,imgcmdScrolledWindow,imgcmdLabel;
        Gtk::Image imgcmdToggleButton, imgcmdStatusBar,imgcmdComboBox,imgcmdComboBoxText,imgcmdCheckButton;
        Gtk::Image imgcmdRadioButton,imgcmdMenuBar, imgcmdToolBar;
        Gtk::Image imgcmdNotebook,imgcmdOffscreenWindow,imgcmdDialog,imgcmdFrame,imgcmdPaned,imgcmdHButtonBox;
        Gtk::Image imgcmdVButtonBox,imgcmdEventBox, imgcmdExpander;
        Gtk::Image imgcmdVScale, imgcmdSpinButton,imgcmdFileChooserButton,imgcmdColorChooserButton;
        Gtk::Image imgcmdFontButton,imgcmdHScale,imgcmdScrollbar,imgcmdProgressBar;
        Gtk::Image  imgcmdSpinner, imgcmdTreeView;
        
        void cmdWindow_clicked();
        void cmdVBox_clicked();
        void cmdHBox_clicked();
        void cmdTable_clicked();
        void cmdFixed_clicked();
        void cmdScrolledWindow_clicked();
        void cmdTextview_clicked();
        void cmdEntry_clicked();
        void cmdButton_clicked();
        void cmdLabel_clicked();
        void cmdToggleButton_clicked();
        void cmdComboBox_clicked();
        void cmdComboBoxText_clicked();
        void cmdCheckButton_clicked();
        void cmdRadioButton_clicked();
        void cmdStatusBar_clicked();
        void cmdMenuBar_clicked();
        void cmdToolBar_clicked();
        void cmdNotebook_clicked();
        void cmdOffscreenWindow_clicked();
        void cmdFrame_clicked();
        void cmdEventBox_clicked();
        void cmdExpander_clicked();
        void cmdVScale_clicked();
        void cmdSpinButton_clicked();
        void cmdFileChooserButton_clicked();
        void cmdColorChooserButton_clicked();
        void cmdFontButton_clicked();
        void cmdHScale_clicked();
        void cmdScrollbar_clicked();
        void cmdProgressBar_clicked();
        void cmdSpinner_clicked();
        void cmdTreeView_clicked();
        void cmdIconView_clicked();
        
        void set_active_false();
        void set_others_false(Gtk::ToggleButton&);
        
        typedef sigc::signal<void,std::string> type_signal_can_draw_widget;
        type_signal_can_draw_widget signal_can_draw_widget();
    
    private:
        type_signal_can_draw_widget m_signal_can_draw_widget;
    };

#endif
