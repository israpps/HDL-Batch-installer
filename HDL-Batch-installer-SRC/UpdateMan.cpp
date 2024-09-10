#include "UpdateMan.h"

#include <wx/arrstr.h>
//(*InternalHeaders(UpdateMan)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(UpdateMan)
const long UpdateMan::ID_STATICTEXT2 = wxNewId();
const long UpdateMan::ID_TEXTCTRL1 = wxNewId();
const long UpdateMan::ID_BUTTON1 = wxNewId();
const long UpdateMan::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(UpdateMan,wxDialog)
	//(*EventTable(UpdateMan)
	//*)
END_EVENT_TABLE()

UpdateMan::UpdateMan(wxWindow* parent, wxString newv, wxString oldv, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
	//(*Initialize(UpdateMan)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxRESIZE_BORDER|wxDIALOG_NO_PARENT|wxMAXIMIZE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	heading = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
	heading->SetMinSize(wxSize(200,0));
	BoxSizer2->Add(heading, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 2, wxALL|wxEXPAND, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Changes:"));
	UpdateDetails = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	UpdateDetails->SetMinSize(wxSize(700,200));
	StaticBoxSizer1->Add(UpdateDetails, 2, wxEXPAND, 5);
	BoxSizer1->Add(StaticBoxSizer1, 3, wxLEFT|wxRIGHT|wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	OK = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer4->Add(OK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CANCEL = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer4->Add(CANCEL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&UpdateMan::OnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&UpdateMan::OnCANCELClick);
	//*)
	wxString msg;
	msg.Printf(_("There's an update available for this program!\n\nGo to download page?\n\nCurrent version: [%s]\nLatest version: [%s]"), oldv, newv);
    heading->SetLabel(msg);
    wxArrayString data;
    long a = wxExecute("Common\\WGET.EXE -q https://github.com/israpps/HDL-Batch-installer/raw/main/Release/changes.log -O -", data, wxEXEC_SYNC);
    if (a == 0) {
        for (size_t x=0, s=0; x < data.GetCount() && s < 2; x++) {
            if (data.Item(x) == wxEmptyString) {
                //std::cout << "empty line at :"<<x<<"\n";
                s++;
            }
            UpdateDetails->AppendText(data.Item(x));
            UpdateDetails->AppendText("\n");
        }
    } else {UpdateDetails->AppendText(_("Failed to obtain update changelog!"));}
	wxBell();
}

UpdateMan::~UpdateMan()
{
	//(*Destroy(UpdateMan)
	//*)
}


void UpdateMan::OnOKClick(wxCommandEvent& event)
{
    EndModal(wxYES);
}

void UpdateMan::OnCANCELClick(wxCommandEvent& event)
{
    EndModal(wxNO);
}
