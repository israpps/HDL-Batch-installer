#include "HDDManager.h"
#include "PFSShell.h"
#include <stdint.h>
#include <iostream>
#include <wx/arrstr.h>
#include <wx/utils.h>

extern
PFSShell PFSSHELL;
//(*InternalHeaders(HDDManager)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HDDManager)
const long HDDManager::ID_LISTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HDDManager,wxDialog)
	//(*EventTable(HDDManager)
	//*)
END_EVENT_TABLE()

struct apaFsType
{
    const char *desc;
    uint16_t type;
};

static const struct apaFsType fsTypes[] = {
    {"MBR",           PARTITION_TYPE::MBR},
    {"EXT2SWAP", PARTITION_TYPE::EXT2SWAP},
    {"EXT2",         PARTITION_TYPE::EXT2},
    {"REISER",     PARTITION_TYPE::REISER},
    {"PFS",           PARTITION_TYPE::PFS},
    {"CFS",           PARTITION_TYPE::CFS},
    {"HDL",           PARTITION_TYPE::HDL}
};

HDDManager::HDDManager(wxWindow* parent, std::string HDDTOK,wxWindowID id,const wxPoint& pos,const wxSize& size):
    HDD_TOKEN(HDDTOK)
{
	//(*Initialize(HDDManager)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	PARTList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(1030,307), wxLC_REPORT|wxLC_SORT_ASCENDING|wxLC_HRULES|wxLC_VRULES, wxDefaultValidator, _T("ID_LISTCTRL1"));
	FlexGridSizer2->Add(PARTList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&HDDManager::OnPARTListBeginDrag);
	//*)
	PFSSHELL.SelectDevice(HDD_TOKEN);
	wxListItem col0;
    col0.SetId(0);
    col0.SetText( _("Start Sector") );
    col0.SetWidth(180);//180
    PARTList->InsertColumn(0, col0);

    // Add second column
    wxListItem col1;
    col1.SetId(1);
    col1.SetText( _("Partition") );
    col1.SetWidth(350);
    PARTList->InsertColumn(1, col1);

    // Add third column
    wxListItem col2;
    col2.SetId(2);
    col2.SetText( _("Size") );
    col2.SetWidth(100);
    PARTList->InsertColumn(2, col2);

    // Add 4th column
    wxListItem col3;
    col3.SetId(3);
    col3.SetText( _("Partition Type") );
    col3.SetWidth(120);
    PARTList->InsertColumn(3, col3);

    // Add 5th column
    wxListItem col4;
    col4.SetId(4);
    col4.SetText( _("Game Title") );
    col4.SetWidth(280);
    PARTList->InsertColumn(4, col4);

    PFSSHELL.lspart(1, &PART_LIST);
    wxString TMP, TMP2, cmd;
    wxArrayString ARR;
    for (size_t x=0; x<PART_LIST.size(); x++)
    {
        long itemIndex = PARTList->InsertItem(0, wxString::Format("%#8x",PART_LIST[x].stat.private_5) );// col. 1
        PARTList->SetItem(itemIndex, 1, PART_LIST[x].name); // col. 2
        PARTList->SetItem(itemIndex, 2, wxString::Format("%uMB",PART_LIST[x].stat.size / 2048)); // col. 3
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

        default:
            TMP = wxString::Format("UNKNOWN %#4x", PART_LIST[x].stat.mode);
            PARTList->SetItemTextColour(itemIndex, *wxRED);
            break;
        }
        PARTList->SetItem(itemIndex, 3, TMP); // col. 4
        if (PART_LIST[x].stat.mode == PARTITION_TYPE::HDL)
        {
            cmd = wxString::Format("HDL.EXE info hdd%s: %s", HDD_TOKEN.substr(strlen("\\\\.\\PHYSICALDRIVE")), PART_LIST[x].name);
            std::cout << cmd << "\n";
            long ret = wxExecute(cmd, ARR, wxEXEC_SYNC);
            if (ret == 0)
            {
                TMP2 = ARR.Item(0);
                PARTList->SetItem(itemIndex, 4, TMP2.SubString(TMP2.find_first_of('[')+1, TMP2.find_last_of(']')-1));
            } else {
                PARTList->SetItem(itemIndex, 4, wxString::Format(_("Error: %ld"), ret));
            }
        }

    }
}

HDDManager::~HDDManager()
{
	//(*Destroy(HDDManager)
	//*)
}


void HDDManager::OnPARTListBeginDrag(wxListEvent& event)
{
}
