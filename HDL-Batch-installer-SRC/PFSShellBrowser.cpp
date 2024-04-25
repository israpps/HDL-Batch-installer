#include "PFSShellBrowser.h"
#include "PFSShell.h"

extern PFSShell PFSSHELL;


enum LIST_ITEMS {
    NAME = 0,
    SIZET,
    TYPE,
};
std::vector<iox_dirent_t> ITEMLIST;

//(*InternalHeaders(PFSShellBrowser)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PFSShellBrowser)
const long PFSShellBrowser::ID_RADIOBUTTON1 = wxNewId();
const long PFSShellBrowser::ID_CHOICE1 = wxNewId();
const long PFSShellBrowser::ID_RADIOBUTTON2 = wxNewId();
const long PFSShellBrowser::ID_FILEPICKERCTRL1 = wxNewId();
const long PFSShellBrowser::ID_BUTTON1 = wxNewId();
const long PFSShellBrowser::ID_BUTTON2 = wxNewId();
const long PFSShellBrowser::ID_LISTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PFSShellBrowser,wxDialog)
	//(*EventTable(PFSShellBrowser)
	//*)
END_EVENT_TABLE()

PFSShellBrowser::PFSShellBrowser(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PFSShellBrowser)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	HDDRealRadio = new wxRadioButton(this, ID_RADIOBUTTON1, _("HDD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	HDDRealRadio->SetValue(true);
	BoxSizer4->Add(HDDRealRadio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	HDDRealDLG = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	BoxSizer4->Add(HDDRealDLG, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	HDDFileRadio = new wxRadioButton(this, ID_RADIOBUTTON2, _("File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	BoxSizer5->Add(HDDFileRadio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	HDDFileDLG = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, _T("D:\\Baul\\Paula\\Desktop\\DEV9hdd.raw"), wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	HDDFileDLG->Disable();
	BoxSizer5->Add(HDDFileDLG, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer5, 1, wxALL|wxEXPAND, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	OpenHDD = new wxButton(this, ID_BUTTON1, _("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer6->Add(OpenHDD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CloseHDD = new wxButton(this, ID_BUTTON2, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	CloseHDD->Disable();
	BoxSizer6->Add(CloseHDD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	FileList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_AUTOARRANGE|wxLC_HRULES|wxLC_VRULES, wxDefaultValidator, _T("ID_LISTCTRL1"));
	BoxSizer3->Add(FileList, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer3, 3, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnHDDRealRadioSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnHDDFileRadioSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PFSShellBrowser::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PFSShellBrowser::OnButton2Click);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&PFSShellBrowser::OnFileListItemActivated);
	//*)
	wxListItem col0;
    col0.SetId(LIST_ITEMS::NAME);
    col0.SetText( _("Name") );
    col0.SetWidth(350);//180
    FileList->InsertColumn(LIST_ITEMS::NAME, col0);

    // Add second column
    wxListItem col1;
    col1.SetId(LIST_ITEMS::SIZET);
    col1.SetText( _("Size") );
    col1.SetWidth(100);
    FileList->InsertColumn(LIST_ITEMS::SIZET, col1);

    // Add third column
    wxListItem col2;
    col2.SetId(LIST_ITEMS::TYPE);
    col2.SetText( _("Type") );
    col2.SetWidth(100);
    FileList->InsertColumn(LIST_ITEMS::TYPE, col2);
}

PFSShellBrowser::~PFSShellBrowser()
{
	//(*Destroy(PFSShellBrowser)
	//*)
}



void PFSShellBrowser::OnHDDRealRadioSelect(wxCommandEvent& event)
{
    HDDRealDLG->Enable(true);
    HDDFileDLG->Enable(false);
}

void PFSShellBrowser::OnHDDFileRadioSelect(wxCommandEvent& event)
{
    HDDRealDLG->Enable(false);
    HDDFileDLG->Enable(true);
}

void PFSShellBrowser::OnButton1Click(wxCommandEvent& event)
{
    const char* hdd =
    HDDFileDLG->GetPath().mb_str();
    if (!PFSSHELL.SelectDevice(hdd)) {
        OpenHDD->Enable(false);
        CloseHDD->Enable(true);
        PFSSHELL.lspart(1, nullptr);
        RefreshList();
    } else {
        std::cout << "HDD OPEN ERR\n";
        PFSSHELL.CloseDevice();
    }
}

void PFSShellBrowser::OnButton2Click(wxCommandEvent& event)
{
    PFSSHELL.CloseDevice();
    OpenHDD->Enable(true);
    CloseHDD->Enable(false);
}

void PFSShellBrowser::RefreshList(void) {

    FileList->DeleteAllItems();
    PFSSHELL.lspart(1, &ITEMLIST);
    wxString TMP, TMP2, cmd;
    wxArrayString ARR;
    for (size_t x = ITEMLIST.size()-1; x >= 0; x--)
    {
        bool is_subpartition = (ITEMLIST[x].stat.attr == 1);
        const int m = ITEMLIST[x].stat.mode;
        if (m != PARTITION_TYPE::PFS &&
            (m & FIO_S_IFMT) != FIO_S_IFLNK &&
            (m & FIO_S_IFMT) != FIO_S_IFREG &&
            (m & FIO_S_IFMT) != FIO_S_IFDIR
            ) //placeholder for ignoring non PFS Partitions
            continue;
        std::cout << ITEMLIST[x].name << std::endl;
        long itemIndex = FileList->InsertItem(LIST_ITEMS::NAME, ITEMLIST[x].name);// col. 1
        FileList->SetItem(itemIndex, LIST_ITEMS::SIZET, wxString::Format("%uMB",ITEMLIST[x].stat.size / 2048)); // col. 3
        switch (ITEMLIST[x].stat.mode)
        {
        case PARTITION_TYPE::MBR:
            TMP = "MBR";
            FileList->SetItemTextColour(itemIndex, wxColour(255, 139, 0));
            break;
        case PARTITION_TYPE::EXT2SWAP:
            FileList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "EXT2SWAP";
            break;
        case PARTITION_TYPE::EXT2:
            FileList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "EXT2";
            break;
        case PARTITION_TYPE::REISER:
            FileList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "REISER";
            break;
        case PARTITION_TYPE::PFS:
            FileList->SetItemTextColour(itemIndex, wxColour(0, 0x80, 0x80));
            TMP = "PFS";
            break;
        case PARTITION_TYPE::CFS:
            FileList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "CFS";
            break;
        case PARTITION_TYPE::HDL:
            FileList->SetItemTextColour(itemIndex, *wxGREEN);
            TMP = "HDL";
            break;
        case PARTITION_TYPE::FREE:
            FileList->SetItemBackgroundColour(itemIndex, *wxLIGHT_GREY);
            TMP = _("Empty Segment");
            break;

        default:
            TMP = wxString::Format("UNKNOWN %#4x", ITEMLIST[x].stat.mode);
            FileList->SetItemTextColour(itemIndex, *wxRED);
            break;
        }
        if (is_subpartition) TMP += "-(SUBPART)";
        FileList->SetItem(itemIndex, LIST_ITEMS::TYPE, TMP); // col. 4
    }
}

void PFSShellBrowser::OnFileListItemActivated(wxListEvent& event)
{
    long item = -1;
    item = FileList->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    std::cout << "Item activated " << item << "\n";
}
