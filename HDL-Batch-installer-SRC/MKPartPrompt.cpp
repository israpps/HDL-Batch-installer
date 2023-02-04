#include "MKPartPrompt.h"

//(*InternalHeaders(MKPartPrompt)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(MKPartPrompt)
const long MKPartPrompt::ID_TEXTCTRL1 = wxNewId();
const long MKPartPrompt::ID_CHOICE1 = wxNewId();
const long MKPartPrompt::ID_SPINCTRL1 = wxNewId();
const long MKPartPrompt::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MKPartPrompt,wxDialog)
	//(*EventTable(MKPartPrompt)
	//*)
END_EVENT_TABLE()

#define MSI(CALCULATE, BASE) (CALCULATE + (BASE - CALCULATE % BASE)) // APA partitions size must be a multiple of 128m. we will use this macro to rectify the scpinctrl value if user inputs value on size control

MKPartPrompt::MKPartPrompt(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(MKPartPrompt)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partition Name"));
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(185,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetMaxLength(32);
	StaticBoxSizer1->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("FileSystem ID"));
	FileSystem = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FileSystem->Append(_("PFS"));
	FileSystem->Append(_("EXT2SWAP"));
	FileSystem->Append(_("EXT2"));
	FileSystem->Append(_("REISER"));
	FileSystem->Append(_("CFS"));
	StaticBoxSizer3->Add(FileSystem, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("size (Mb)"));
	SizeSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(78,23), 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	SizeSpinCtrl->SetValue(_T("0"));
	SizeSpinCtrl->SetIncrement(128); // PS2 partitions size MUST be a multiple of 128mb
	StaticBoxSizer2->Add(SizeSpinCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	Create = new wxButton(this, ID_BUTTON1, _("Create"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(Create, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

MKPartPrompt::~MKPartPrompt()
{
	//(*Destroy(MKPartPrompt)
	//*)
}


void MKPartPrompt::OnCreateClick(wxCommandEvent& event)
{
}

void MKPartPrompt::OnSizeSpinCtrlChange(wxSpinEvent& event)
{
    int siz = SizeSpinCtrl->GetValue();
    int niu;
    niu = MSI(siz, 128);
    if (siz != niu)
        SizeSpinCtrl->SetValue(niu);
}
