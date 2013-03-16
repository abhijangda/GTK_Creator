//68 Lines
#include"box_dialog.h"

BoxDialog::BoxDialog(std::string title)
    : Dialog(title,true), lblSlots("Slots"), lblHomogeneous("Homogeneous"), lblSpacing("Spacing"), entrySlots(), entrySpacing(),grpRadio(),
    rbFalse("False"), rbTrue("True"), hboxSlots(false,2), hboxSpacing(false,2), hboxHomogeneous(false,2), vbox(true,2), vboxTrueFalse(true,2)
{
    hboxSlots.pack_start(lblSlots,false,false);
    hboxSlots.pack_start(entrySlots,true,true);
    
    hboxSpacing.pack_start(lblSpacing,false,false);
    hboxSpacing.pack_start(entrySpacing,true,true);
    
    vboxTrueFalse.pack_start(rbFalse,true,true);
    vboxTrueFalse.pack_start(rbTrue,true,true);
    rbFalse.set_group(grpRadio);
    rbTrue.set_group(grpRadio);
    hboxHomogeneous.pack_start(lblHomogeneous,false,false);
    hboxHomogeneous.pack_start(vboxTrueFalse,true,true);
    
    vbox.pack_start(hboxSlots,true,true);
    vbox.pack_start(hboxSpacing,true,true);
    vbox.pack_start(hboxHomogeneous,true,true);   
    
    add_button("Create",1);
    add_button("Cancel",0);
    
    get_vbox()->add(vbox);
    }

BoxDialog::~BoxDialog(){}

TableDialog::TableDialog(std::string title)
:Dialog(title,true), lblRows("Rows"), lblColumns("Columns"),lblHomogeneous("Homogeneous"), lblRowSpacing("Row Spacing"), lblColumnSpacing("Column Spacing"),
    entryRows(), entryColumns(), entryRowSpacing(), entryColumnSpacing(), grpRadio(), rbFalse("False"), rbTrue("True"), hboxRows(false,2),hboxColumns(false,2), 
    hboxRowSpacing(false,2),hboxColumnSpacing(false,2), hboxHomogeneous(false,2), vbox(true,2), vboxTrueFalse(true,2)
{
    hboxRows.pack_start(lblRows,false,false);
    hboxRows.pack_start(entryRows,true,true);
    
    hboxColumns.pack_start(lblColumns,false,false);
    hboxColumns.pack_start(entryColumns,true,true);
    
    hboxRowSpacing.pack_start(lblRowSpacing,false,false);
    hboxRowSpacing.pack_start(entryRowSpacing,true,true);
    
    hboxColumnSpacing.pack_start(lblColumnSpacing,false,false);
    hboxColumnSpacing.pack_start(entryColumnSpacing,true,true);
    
    vboxTrueFalse.pack_start(rbFalse,true,true);
    vboxTrueFalse.pack_start(rbTrue,true,true);
    rbFalse.set_group(grpRadio);
    rbTrue.set_group(grpRadio);
    hboxHomogeneous.pack_start(lblHomogeneous,false,false);
    hboxHomogeneous.pack_start(vboxTrueFalse,true,true);
    
    vbox.pack_start(hboxRows,true,true);
    vbox.pack_start(hboxColumns,true,true);
    vbox.pack_start(hboxRowSpacing,true,true);
    vbox.pack_start(hboxColumnSpacing,true,true);
    vbox.pack_start(hboxHomogeneous,true,true);   
    
    add_button("Create",1);
    add_button("Cancel",0);
    
    get_vbox()->add(vbox);
    }
TableDialog::~TableDialog(){}