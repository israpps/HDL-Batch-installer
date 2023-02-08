#include "MD5Report.h"

//(*InternalHeaders(MD5Report)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(MD5Report)
const long MD5Report::ID_STATICTEXT1 = wxNewId();
const long MD5Report::ID_TEXTCTRL1 = wxNewId();
const long MD5Report::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MD5Report,wxDialog)
	//(*EventTable(MD5Report)
	//*)
END_EVENT_TABLE()

MD5Report::MD5Report(wxWindow* parent, wxString _FILEPATH, wxString _HASH, wxWindowID id,const wxPoint& pos,const wxSize& size):
    FILEPATH(_FILEPATH), HASH(_HASH)
{
	//(*Initialize(MD5Report)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("MD5 Hash report"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableRow(1);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	FILENAME = new wxStaticText(this, ID_STATICTEXT1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(FILENAME, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	DHASH = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(505,30), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(DHASH, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	redumpsearch = new wxButton(this, ID_BUTTON1, _("Search on redump.org"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer3->Add(redumpsearch, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MD5Report::OnredumpsearchClick);
	//*)
	FILENAME->SetLabel(FILEPATH);
	DHASH->Clear();
	DHASH->AppendText(HASH);
}

MD5Report::~MD5Report()
{
	//(*Destroy(MD5Report)
	//*)
}


void MD5Report::OnredumpsearchClick(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser(wxString::Format("http://redump.org/discs/quicksearch/%s/", HASH));
}
