#include "HDDManager.h"
#include "mkpartdlg.h"
#include "PFSShell.h"
#include <stdint.h>
#include <iostream>
#include <wx/arrstr.h>
#include <wx/msgdlg.h>
#include <wx/utils.h>

extern
PFSShell PFSSHELL;
//(*InternalHeaders(HDDManager)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HDDManager)
const long HDDManager::ID_LISTCTRL1 = wxNewId();
const long HDDManager::ID_BUTTON1 = wxNewId();
const long HDDManager::ID_MENUITEM1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HDDManager,wxDialog)
	//(*EventTable(HDDManager)
	//*)
END_EVENT_TABLE()


enum PARTLIST_ITEMS {
    START_SECTOR = 0,
    NAME,
    PARTSIZE,
    TYPE,
    GAME_TITLE,
};
HDDManager::HDDManager(wxWindow* parent, std::string HDDTOK, bool DGT, bool DSP, wxWindowID id,const wxPoint& pos,const wxSize& size):
    HDD_TOKEN(HDDTOK), DISPLAY_GAME_TITLE(DGT), DISPLAY_SUB_PARTITIONS(DSP)
{
	//(*Initialize(HDDManager)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer3;

	Create(parent, id, _("HDDManager"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU|wxRESIZE_BORDER, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(4, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	PARTList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(1030,307), wxLC_REPORT|wxLC_SORT_ASCENDING|wxLC_HRULES|wxLC_VRULES, wxDefaultValidator, _T("ID_LISTCTRL1"));
	BoxSizer1->Add(PARTList, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	MKPart = new wxButton(this, ID_BUTTON1, _("Create Partition"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(MKPart, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
	SetSizer(FlexGridSizer1);
	MenuItem1 = new wxMenuItem((&HDDManagerMenu), ID_MENUITEM1, _("Delete Partition"), wxEmptyString, wxITEM_NORMAL);
	HDDManagerMenu.Append(MenuItem1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&HDDManager::OnPARTListBeginDrag);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&HDDManager::OnPARTListItemRClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDDManager::OnMKPartClick);
	Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDDManager::OnPartitionDeleteRequest);
	//*)
	PFSSHELL.SelectDevice(HDD_TOKEN);
	wxListItem col0;
    col0.SetId(PARTLIST_ITEMS::START_SECTOR);
    col0.SetText( _("Start Sector") );
    col0.SetWidth(180);//180
    PARTList->InsertColumn(PARTLIST_ITEMS::START_SECTOR, col0);

    // Add second column
    wxListItem col1;
    col1.SetId(PARTLIST_ITEMS::NAME);
    col1.SetText( _("Partition") );
    col1.SetWidth(350);
    PARTList->InsertColumn(PARTLIST_ITEMS::NAME, col1);

    // Add third column
    wxListItem col2;
    col2.SetId(PARTLIST_ITEMS::PARTSIZE);
    col2.SetText( _("Size") );
    col2.SetWidth(100);
    PARTList->InsertColumn(PARTLIST_ITEMS::PARTSIZE, col2);

    // Add 4th column
    wxListItem col3;
    col3.SetId(PARTLIST_ITEMS::TYPE);
    col3.SetText( _("Partition Type") );
    col3.SetWidth(120);
    PARTList->InsertColumn(PARTLIST_ITEMS::TYPE, col3);

    // Add 5th column
    wxListItem col4;
    col4.SetId(PARTLIST_ITEMS::GAME_TITLE);
    col4.SetText( _("Game Title") );
    col4.SetWidth(280);
    PARTList->InsertColumn(PARTLIST_ITEMS::GAME_TITLE, col4);
    UpdateList();
}

HDDManager::~HDDManager()
{
    PFSSHELL.CloseDevice(); //don't leave device attached 'al pedo'
	//(*Destroy(HDDManager)
	//*)
}


void HDDManager::OnPARTListBeginDrag(wxListEvent& event)
{
}

void HDDManager::OnPARTListItemRClick(wxListEvent& event)
{
    PopupMenu(&HDDManagerMenu);
}

void HDDManager::OnPartitionDeleteRequest(wxCommandEvent& event)
{
    wxArrayString _PART, _TYPE;
    long item = -1;
    while ( (item = PARTList->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {

        _PART.Add(PARTList->GetItemText(item, PARTLIST_ITEMS::NAME)) ;
        _TYPE.Add(PARTList->GetItemText(item, PARTLIST_ITEMS::TYPE));
    }
    if (_PART.GetCount() > 1)
    {
        for (size_t x=0; x<_PART.GetCount(); x++)
        {
            wxString PART = _PART.Item(x),
            TYPE = _TYPE.Item(x);
            if (PART == "__mbr" || PART == "__extend" || TYPE == "MBR")
            {
                std::cout << "User requested deletion of '__mbr'. skipping\n";
                continue;
            } else if ((PART == "__net") || (PART == "__system") || (PART == "__sysconf") || (PART == "__common") || (PART == "__contents"))
            {
                std::cout << "User requested deletion of '"<<PART<<"' partition. skipping\n";
                continue;
            } else if (PART == "__empty") continue;

            int ret = PFSSHELL.RemovePartition(PART.mb_str());
            if (ret < 0)
                return;
        }
    } else {

        wxString PART = _PART.Item(0),
        TYPE = _TYPE.Item(0);
        if (PART == "__mbr" || PART == "__extend" || TYPE == "MBR")
        {
            std::cout << "User requested deletion of '__mbr'. skipping\n";
            return;
        } else if (PART == "__empty") return;
        else if ((PART == "__net") || (PART == "__system") || (PART == "__sysconf") || (PART == "__common") || (PART == "__contents"))
            if (wxMessageBox(_("You requested the deletion of a system partition\nthis is not recommended unless you truly understand what you are doing\n\nContinue anyways?"),wxMessageBoxCaptionStr, wxICON_INFORMATION|wxYES_NO|wxNO_DEFAULT)
                == wxNO) return;
        PFSSHELL.RemovePartition(PART.mb_str());
    }
    UpdateList();
}

void HDDManager::UpdateList(void)
{
    PARTList->DeleteAllItems();
    PFSSHELL.lspart(1, &PART_LIST);
    wxString TMP, TMP2, cmd;
    wxArrayString ARR;
    for (size_t x=0; x<PART_LIST.size(); x++)
    {
        bool is_subpartition = (PART_LIST[x].stat.attr == 1);
        if ((is_subpartition) && (DISPLAY_SUB_PARTITIONS))
            continue;
        std::cout << PART_LIST[x].name << std::endl;
        long itemIndex = PARTList->InsertItem(PARTLIST_ITEMS::START_SECTOR, wxString::Format("%#8x",PART_LIST[x].stat.private_5) );// col. 1
        PARTList->SetItem(itemIndex, PARTLIST_ITEMS::NAME, PART_LIST[x].name); // col. 2
        PARTList->SetItem(itemIndex, PARTLIST_ITEMS::PARTSIZE, wxString::Format("%uMB",PART_LIST[x].stat.size / 2048)); // col. 3
        switch (PART_LIST[x].stat.mode)
        {

        case PARTITION_TYPE::MBR:
            TMP = "MBR";
            PARTList->SetItemTextColour(itemIndex, wxColour(255, 139, 0));
            break;
        case PARTITION_TYPE::EXT2SWAP:
            PARTList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "EXT2SWAP";
            break;
        case PARTITION_TYPE::EXT2:
            PARTList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "EXT2";
            break;
        case PARTITION_TYPE::REISER:
            PARTList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "REISER";
            break;
        case PARTITION_TYPE::PFS:
            PARTList->SetItemTextColour(itemIndex, wxColour(0, 0x80, 0x80));
            TMP = "PFS";
            break;
        case PARTITION_TYPE::CFS:
            PARTList->SetItemTextColour(itemIndex, *wxLIGHT_GREY);
            TMP = "CFS";
            break;
        case PARTITION_TYPE::HDL:
            PARTList->SetItemTextColour(itemIndex, *wxGREEN);
            TMP = "HDL";
            break;
        case PARTITION_TYPE::FREE:
            PARTList->SetItemBackgroundColour(itemIndex, *wxLIGHT_GREY);
            TMP = _("Empty Segment");
            break;

        default:
            TMP = wxString::Format("UNKNOWN %#4x", PART_LIST[x].stat.mode);
            PARTList->SetItemTextColour(itemIndex, *wxRED);
            break;
        }
        if (is_subpartition) TMP += "-(SUBPART)";
        PARTList->SetItem(itemIndex, PARTLIST_ITEMS::TYPE, TMP); // col. 4
        if ((PART_LIST[x].stat.mode == PARTITION_TYPE::HDL && (!is_subpartition)) && DISPLAY_GAME_TITLE) //display game title ONLY if this is a game partition index, and if enabled
        {
            cmd = wxString::Format("HDL.EXE info hdd%s: %s", HDD_TOKEN.substr(strlen("\\\\.\\PHYSICALDRIVE")), PART_LIST[x].name);
            std::cout << cmd << "\n";
            ARR.clear();
            long ret = wxExecute(cmd, ARR, wxEXEC_SYNC);
            if (ret == 0)
            {
                TMP2 = ARR.Item(0);
                PARTList->SetItem(itemIndex, PARTLIST_ITEMS::GAME_TITLE, TMP2.SubString(TMP2.find_first_of('[')+1, TMP2.find_last_of(']')-1));
            } else {
                PARTList->SetItem(itemIndex, PARTLIST_ITEMS::GAME_TITLE, wxString::Format(_("Error: %ld"), ret));
            }
        }
    }
}

void HDDManager::OnMKPartClick(wxCommandEvent& event)
{
    mkpartdlg *MAN = new mkpartdlg(this);
    MAN->ShowModal();
    delete MAN;
    UpdateList();
}
