#ifndef COPYHDD_H
#define COPYHDD_H

//(*Headers(CopyHDD)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

class CopyHDD: public wxDialog
{
public:

    CopyHDD(wxWindow* parent,wxArrayString HDDs, int selectedHDD, wxString COPY_LIST,  wxWindowID id=wxID_ANY, const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~CopyHDD();
    //(*Declarations(CopyHDD)
    wxButton* Transfer;
    wxChoice* Destination;
    wxChoice* Source;
    wxStaticText* StaticText1;
    //*)

protected:

    //(*Identifiers(CopyHDD)
    static const long ID_CHOICE1;
    static const long ID_STATICTEXT1;
    static const long ID_CHOICE2;
    static const long ID_BUTTON1;
    //*)

private:

    //(*Handlers(CopyHDD)
    void OnTransferClick(wxCommandEvent& event);
    void OnHDDsSelection(wxCommandEvent& event);
    //*)
    wxArrayString HDDS;
    int SELECTED_HDD;
    wxString INSTALL_LIST;

    DECLARE_EVENT_TABLE()
};

#endif
