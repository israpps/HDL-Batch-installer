#include "mkpartdlg.h"
#include <iostream>
#include <iomanip>
#include "PFSShell.h"
#include <wx/msgdlg.h>
extern PFSShell PFSSHELL;

//(*InternalHeaders(mkpartdlg)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#define NORMALIZE_APA_SIZE(SIZE) ((SIZE % 128)==0) ? (SIZE) : (SIZE + (128 - SIZE % 128)) // if SIZE is not a multiple of 128 advance to the nearest larger one

//(*IdInit(mkpartdlg)
const long mkpartdlg::ID_TEXTCTRL1 = wxNewId();
const long mkpartdlg::ID_SLIDER1 = wxNewId();
const long mkpartdlg::ID_STATICTEXT1 = wxNewId();
const long mkpartdlg::ID_STATICTEXT2 = wxNewId();
const long mkpartdlg::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(mkpartdlg,wxDialog)
	//(*EventTable(mkpartdlg)
	//*)
END_EVENT_TABLE()

mkpartdlg::mkpartdlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(mkpartdlg)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	SetClientSize(wxSize(369,296));
	SetMinSize(wxSize(369,296));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partition Name"));
	PARTName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	PARTName->SetMaxLength(32);
	StaticBoxSizer1->Add(PARTName, 1, wxALL|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partition Size"));
	HDDSize = new wxSlider(this, ID_SLIDER1, 1, 1, 1024, wxDefaultPosition, wxSize(274,28), 0, wxDefaultValidator, _T("ID_SLIDER1"));
	StaticBoxSizer2->Add(HDDSize, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer3->AddGrowableCol(1);
	FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	MB = new wxStaticText(this, ID_STATICTEXT1, _("128Mb"), wxDefaultPosition, wxSize(61,21), 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(MB, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
	GB = new wxStaticText(this, ID_STATICTEXT2, _("0.12Gb"), wxDefaultPosition, wxSize(65,21), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(GB, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 10);
	FlexGridSizer3->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
	mkpart = new wxButton(this, ID_BUTTON1, _("Create"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	mkpart->Disable();
	FlexGridSizer1->Add(mkpart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();
	Center();

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&mkpartdlg::onPartitionNameChange);
	Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&mkpartdlg::OnSlider1CmdScrollChanged);
	Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&mkpartdlg::OnSlider1CmdScrollChanged);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&mkpartdlg::OnmkpartClick);
	//*)
}

mkpartdlg::~mkpartdlg()
{
	//(*Destroy(mkpartdlg)
	//*)
}


void mkpartdlg::OnmkpartClick(wxCommandEvent& event)
{
    wxBeginBusyCursor();
    unsigned long val = HDDSize->GetValue();
    int ret;
    val = val*128;
    val = NORMALIZE_APA_SIZE(val);
    ret = PFSSHELL.mkpart(PARTName->GetValue().mb_str(), val, "PFS");
    std::cout << "returned " << ret << "\n";
    if (ret == 0 ) wxMessageBox(_("Partition Creation was successfull"), wxMessageBoxCaptionStr, wxICON_INFORMATION);
    else wxMessageBox(_("Partition Creation Failed!\nPlease check log to find more information..."), wxMessageBoxCaptionStr, wxICON_ERROR);
    wxEndBusyCursor();
}

void mkpartdlg::OnSlider1CmdScrollChanged(wxScrollEvent& event)
{
    int val = HDDSize->GetValue();
    val = val*128;
    val = NORMALIZE_APA_SIZE(val);
    float gb = val;
    gb = gb /1024;
    MB->SetLabel(wxString::Format("%dMb", val));
    GB->SetLabel(wxString::Format(" %.2fGb", gb));

}

bool isAlphaNumChar(char fch){
	return (fch >='a'  && fch <='z') || (fch>='A' && fch<='Z') || (fch>='0' && fch<='9');
}

bool isAlphaString(const wxString &fs){
	for (size_t i=0; i<fs.Length(); ++i) {
		if (!isAlphaNumChar(fs[i]) && fs[i] != '_' && fs[i] != '.')
		{
#ifdef DEBUG
		    std::cout << fs << "\n" << std::setw(i+1) << std::setfill('-') << "^"<< std::resetiosflags(std::ios::showbase) <<"\t(" << i <<")\n";
#endif
            return false;
		}
	}
	return true;
}

void mkpartdlg::onPartitionNameChange(wxCommandEvent& event)
{
    wxString PART = PARTName->GetValue();

    if ((PART == "__mbr") || (PART == "__extend") || (PART.length() < 3) || !isAlphaString(PART))
    {
        mkpart->Disable();
        return;
    }

    mkpart->Enable(!PARTName->IsEmpty());

}
