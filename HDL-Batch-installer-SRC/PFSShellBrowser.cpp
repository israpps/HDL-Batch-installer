#include "PFSShellBrowser.h"
#include "PFSShell.h"

#include <wx/event.h>
#include <wx/imaglist.h>
#include <folder.xpm>
#include <harddisk.xpm>
#include <filesave.xpm>

extern PFSShell PFSSHELL;


enum LIST_ITEMS {
    NAME = 0,
    SIZET,
    TYPE,
};
std::vector<iox_dirent_t> ITEMLIST;

namespace CTX {
    wxString CWD = "./";
    bool ISMOUNTED = false;
    wxString MNT = wxEmptyString;
}

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
const long PFSShellBrowser::ID_MENUITEM1 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM2 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM3 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM4 = wxNewId();
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
	FileList->SetMinSize(wxSize(550,300));
	BoxSizer3->Add(FileList, 1, wxTOP|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer3, 3, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	MenuItem1 = new wxMenuItem((&BrowserMenu), ID_MENUITEM1, _("Delete"), wxEmptyString, wxITEM_NORMAL);
	BrowserMenu.Append(MenuItem1);
	MenuItem2 = new wxMenuItem((&BrowserMenu), ID_MENUITEM2, _("Extract"), wxEmptyString, wxITEM_NORMAL);
	BrowserMenu.Append(MenuItem2);
	MenuItem3 = new wxMenuItem((&BrowserMenu), ID_MENUITEM3, _("Rename"), wxEmptyString, wxITEM_NORMAL);
	BrowserMenu.Append(MenuItem3);
	MenuItem4 = new wxMenuItem((&BrowserMenu), ID_MENUITEM4, _("Create Folder"), wxEmptyString, wxITEM_NORMAL);
	BrowserMenu.Append(MenuItem4);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnHDDRealRadioSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnHDDFileRadioSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PFSShellBrowser::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PFSShellBrowser::OnButton2Click);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&PFSShellBrowser::OnFileListItemActivated);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&PFSShellBrowser::OnFileListItemRClick);
	//*)
	FileList->DragAcceptFiles(true);
	//FileList->Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(PFSShellBrowser::OnDropFiles), NULL, this);
	FileList->Connect(wxEVT_DROP_FILES, (wxObjectEventFunction)&PFSShellBrowser::OnDropFiles, NULL, this);
	//Connect(ID_LISTCTRL1, wxEVT_DROP_FILES,(wxObjectEventFunction)&PFSShellBrowser::OnDropFiles);
	//Connect(ID_LISTCTRL1, wxEVT_DROP_FILES, wxDropFilesEventHandler(PFSShellBrowser::OnDropFiles));
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

    IMGLIST = new wxImageList(16, 16, true);
    IMGLIST->Add(wxIcon(folder_xpm));
    IMGLIST->Add(wxIcon(harddisk_xpm));
    IMGLIST->Add(wxIcon(filesave_xpm));
    FileList->SetImageList(IMGLIST, wxIMAGE_LIST_SMALL);
}

PFSShellBrowser::~PFSShellBrowser()
{
    delete IMGLIST;
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
    const char* hdd = HDDFileDLG->GetPath().mb_str();
    if (!PFSSHELL.SelectDevice(hdd)) {
        OpenHDD->Enable(false);
        CloseHDD->Enable(true);
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
    std::cout << "Listing '"<<CTX::CWD<<"'\n";
    FileList->DeleteAllItems();
    if (!CTX::ISMOUNTED) {
        PFSSHELL.lspart(1, &ITEMLIST);
    } else {
        PFSSHELL.ls(CTX::MNT.mb_str(), CTX::CWD.mb_str(), &ITEMLIST);
    }
    wxString tyype, TMP2, cmd;
    wxArrayString ARR;
    //std::cout << "ENTRIES "<<ITEMLIST.size()<<"\n";
    for (size_t x = ITEMLIST.size()-1; x < ITEMLIST.size(); x--)
    {
        std::cout << ITEMLIST.size() << "|" << x << std::endl;
        bool is_subpartition = (ITEMLIST[x].stat.attr == 1);
        unsigned int m = ITEMLIST[x].stat.mode;
        if ((m != PARTITION_TYPE::PFS &&
            (m & FIO_S_IFMT) != FIO_S_IFLNK &&
            (m & FIO_S_IFMT) != FIO_S_IFREG &&
            (m & FIO_S_IFMT) != FIO_S_IFDIR
            ) || !strcasecmp(".", ITEMLIST[x].name)) //placeholder for ignoring non PFS Partitions
            continue;
        long itemIndex = FileList->InsertItem(LIST_ITEMS::NAME, ITEMLIST[x].name);// col. 1
        if ((m & FIO_S_IFMT) != FIO_S_IFDIR) FileList->SetItem(itemIndex, LIST_ITEMS::SIZET, wxString::Format("%uMB",ITEMLIST[x].stat.size / 2048)); // col. 3
        tyype = _("Unknown");
        if (m == PARTITION_TYPE::PFS) {
            tyype = _("PFS Partition");
            FileList->SetItemImage(itemIndex, 1);
        } else if ((m & FIO_S_IFMT) == FIO_S_IFLNK || (m & FIO_S_IFMT) == FIO_S_IFREG){
            tyype = _("File");
            FileList->SetItemImage(itemIndex, 2);
        } else if ((m & FIO_S_IFMT) == FIO_S_IFDIR) {
            tyype = _("Folder");
            FileList->SetItemImage(itemIndex, 0);
        }
        FileList->SetItem(itemIndex, LIST_ITEMS::TYPE, tyype);
        //Sleep(1000);
    }
}

void PFSShellBrowser::OnFileListItemActivated(wxListEvent& event)
{
    long item = -1;
    item = FileList->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    wxString E = FileList->GetItemText(item, 0);
    std::cout << "enter '" << E << "'\n";
    if ((!CTX::ISMOUNTED) && E != "..") {
        CTX::ISMOUNTED = true;
        CTX::MNT = "hdd0:"+E;
        CTX::CWD = "./";
        RefreshList();
    } else {
        if (E != "..") {
            CTX::CWD << E << "/";
            RefreshList();
        } else {
        ///PLACEHOLDER, GO BACK
            size_t P = CTX::CWD.find_last_of('/');
            if (P != wxNOT_FOUND) {
                CTX::CWD = CTX::CWD.substr(0, P-1);
                if (CTX::CWD == "") {
                    CTX::MNT = "";
                    CTX::ISMOUNTED = false;
                }
                RefreshList();
            }
        }
    }
}

void PFSShellBrowser::OnDropFiles(wxDropFilesEvent& event) {
        wxBeginBusyCursor();
    std::cout << "DROPEVENT\n";
    if (event.GetNumberOfFiles() > 0) {

        wxString* dropped = event.GetFiles();
        wxASSERT(dropped);

        wxString name;
        wxArrayString files;

        for (int i = 0; i < event.GetNumberOfFiles(); i++) {
            name = dropped[i];
            std::cout << "DROP: "<<name<<"\n";
        }

        //wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
        //wxASSERT(textCtrl);
        //textCtrl->Clear();
        //for (size_t i = 0; i < files.size(); i++) {
        //    *textCtrl << files[i] << wxT('\n');
        //}
    }
        wxEndBusyCursor();
}

void PFSShellBrowser::OnFileListItemRClick(wxListEvent& event)
{
    PopupMenu(&BrowserMenu);
}
