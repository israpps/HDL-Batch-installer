#include "NDBMan.h"

//(*InternalHeaders(NDBMan)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(NDBMan)
const long NDBMan::ID_STATICTEXT1 = wxNewId();
const long NDBMan::ID_BUTTON1 = wxNewId();
const long NDBMan::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NDBMan,wxDialog)
    //(*EventTable(NDBMan)
    //*)
END_EVENT_TABLE()

NDBMan::NDBMan(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(NDBMan)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("NOTE: In order to properly install the driver you will need to start windows on secure mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    NBDINS = new wxButton(this, ID_BUTTON1, _("install"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(NBDINS, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    NBDUINST = new wxButton(this, ID_BUTTON2, _("Uninstall"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer3->Add(NBDUINST, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NDBMan::OnNBDINSClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NDBMan::OnNBDUINSTClick);
    //*)
}

NDBMan::~NDBMan()
{
    //(*Destroy(NDBMan)
    //*)
}
extern wxString EXEC_PATH;

void NDBMan::OnNBDINSClick(wxCommandEvent& event)
{
    wxBeginBusyCursor();
    wxExecute(wxString::Format("Common\\WNBD\\wnbd-client.exe install-driver \"%sCommon\\WNBD\\wnbd.inf\"",EXEC_PATH),wxEXEC_SYNC);
    wxEndBusyCursor();
}

void NDBMan::OnNBDUINSTClick(wxCommandEvent& event)
{
    wxBeginBusyCursor();
    wxExecute("Common\\WNBD\\wnbd-client.exe uninstall-driver",wxEXEC_SYNC);
    wxEndBusyCursor();
}
