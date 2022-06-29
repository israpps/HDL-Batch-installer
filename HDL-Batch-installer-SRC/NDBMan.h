#ifndef NDBMAN_H
#define NDBMAN_H

//(*Headers(NDBMan)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

class NDBMan: public wxDialog
{
public:

    NDBMan(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~NDBMan();

    //(*Declarations(NDBMan)
    wxButton* NBDINS;
    wxButton* NBDUINST;
    wxStaticText* StaticText1;
    //*)

protected:

    //(*Identifiers(NDBMan)
    static const long ID_STATICTEXT1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    //*)

private:

    //(*Handlers(NDBMan)
    void OnNBDINSClick(wxCommandEvent& event);
    void OnNBDUINSTClick(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
