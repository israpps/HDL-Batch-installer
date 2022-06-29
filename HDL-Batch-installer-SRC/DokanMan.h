#ifndef DOKANMAN_H
#define DOKANMAN_H

//(*Headers(DokanMan)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)
#include <wx/arrstr.h>
class DokanMan: public wxDialog
{
public:

    DokanMan(wxWindow* parent, wxArrayString PARTITIONS_, wxString HDD, wxWindowID id=wxID_ANY);
    virtual ~DokanMan();

    //(*Declarations(DokanMan)
    wxButton* ART_TRANSFER;
    wxButton* Mount ;
    wxButton* Unmount;
    wxButton* call_explorer_exe;
    wxChoice* Drive_selector;
    wxChoice* partyselector;
    wxGauge* Gauge1;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxTextCtrl* PART_FREE;
    wxTextCtrl* PART_TOTAL;
    wxTextCtrl* currhdd;
    //*)

protected:

    //(*Identifiers(DokanMan)
    static const long ID_CHOICE1;
    static const long ID_TEXTCTRL1;
    static const long ID_CHOICE2;
    static const long ID_STATICTEXT1;
    static const long ID_TEXTCTRL2;
    static const long ID_STATICTEXT2;
    static const long ID_TEXTCTRL3;
    static const long ID_GAUGE1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long ID_BUTTON4;
    static const long ID_BUTTON5;
    //*)

private:
    wxArrayString PARTITION_LIST;
    wxString CURR_HDD;
    //(*Handlers(DokanMan)
    void Mount_Partition(wxCommandEvent& event);
    void OnpartyselectorSelect(wxCommandEvent& event);
    void OnDrive_selectorSelect(wxCommandEvent& event);
    void OnUnmountClick(wxCommandEvent& event);
    void Oncall_explorer_exeClick(wxCommandEvent& event);
    void Onmanual_ExitClick(wxCommandEvent& event);
    void OnART_TRANSFERClick(wxCommandEvent& event);
    //*)
    wxString HDLBINST_APPDATA_2;
    DECLARE_EVENT_TABLE()
};

#endif
