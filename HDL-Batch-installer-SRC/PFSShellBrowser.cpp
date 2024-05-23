#include "PFSShellBrowser.h"
//#include "DnDFile.h"
#include "PFSShell.h"

#include <wx/event.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/arrstr.h>
#include <wx/dnd.h>
#include <wx/textdlg.h>
#include <wx/dirdlg.h>
#include <wx/progdlg.h>

///ICONS
#include <folder.xpm>
#include <harddisk.xpm>
#include <filesave.xpm>
#include <new_dir.xpm>
#include <delete.xpm>
#include <toparent.xpm>
#include <motif/question.xpm>

namespace XPM {
    int FOLDER;
    int PARTITION;
    int FILE;
    int UNKNOWN;
    int TOPARENT;
}

static int wxCALLBACK CompareBasedOnIconType(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData);
#undef wxDIRCTRL_EDIT_LABELS ///hack to circunvent code::blocks shitdesign
#define wxDIRCTRL_EDIT_LABELS wxDIRCTRL_MULTIPLE

const wxString check_terminal_4_detailed_err = _("Check terminal for detailed errors");

extern PFSShell PFSSHELL;

enum LIST_ITEMS {
    NAME = 0,
    SIZET,
    TYPE,
};
std::vector<iox_dirent_t> ITEMLIST;

namespace CTX {
    wxString CWD = "/";
    bool ISMOUNTED = false;
    wxString MNT = wxEmptyString;
}


class DnDFile : public wxFileDropTarget
{
public:
    DnDFile(wxListCtrl *pOwner = nullptr) { m_pOwner = pOwner; }

    virtual bool OnDropFiles(wxCoord x, wxCoord y,
                             const wxArrayString& filenames) override;
    bool OnDropFiles_aditional(const wxString individual_item);

private:
    wxListCtrl *m_pOwner;
};
#define DND_CONNECT(x) \
    x->SetDropTarget(new DnDFile(x));

bool DnDFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
    int x, errcnt;
    size_t nFiles = filenames.GetCount();
    std::cout << nFiles << " files dropped\n";
    wxProgressDialog* D = new wxProgressDialog(_("Writing files..."), "", nFiles);
    if (m_pOwner != nullptr)
    {
        for ( size_t n = 0; n < nFiles; n++ ) {
            D->Update(n, filenames[n]);
            wxFileName FinalPath(filenames[n], wxPATH_DOS);
            std::cout << "WRITE '" << FinalPath.GetFullPath() << "' -> '" << CTX::MNT <<":pfs:"<< CTX::CWD+FinalPath.GetFullName() <<"'\n";
            x = PFSSHELL.copyto(CTX::MNT, CTX::CWD+FinalPath.GetFullName(), FinalPath.GetFullPath().mb_str());
            if (x < 0) errcnt++;
        }
    }
    delete D;
    if (errcnt > 0) wxMessageBox(wxString::Format(_("%d errors while copying files to partition"), errcnt)+'\n'+check_terminal_4_detailed_err, wxMessageBoxCaptionStr, wxICON_ERROR);
    return true;
}

//(*InternalHeaders(PFSShellBrowser)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
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
const long PFSShellBrowser::ID_GENERICDIRCTRL1 = wxNewId();
const long PFSShellBrowser::ID_LISTCTRL1 = wxNewId();
const long PFSShellBrowser::ID_TEXTCTRL1 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM2 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM4 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM3 = wxNewId();
const long PFSShellBrowser::ID_MENUITEM1 = wxNewId();
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
	wxBoxSizer* BoxSizer7;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("PFS Browser"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	HDDRealRadio = new wxRadioButton(this, ID_RADIOBUTTON1, _("HDD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	HDDRealRadio->SetValue(true);
	BoxSizer4->Add(HDDRealRadio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	HDDRealDLG = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	BoxSizer4->Add(HDDRealDLG, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	HDDFileRadio = new wxRadioButton(this, ID_RADIOBUTTON2, _("File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	BoxSizer5->Add(HDDFileRadio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	HDDFileDLG = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, wxEmptyString, _("Choose HDD Image"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	HDDFileDLG->Disable();
	BoxSizer5->Add(HDDFileDLG, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
	BoxSizer7 = new wxBoxSizer(wxVERTICAL);
	DirCtrl = new wxGenericDirCtrl(this, ID_GENERICDIRCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_EDIT_LABELS, wxEmptyString, 0, _T("ID_GENERICDIRCTRL1"));
	BoxSizer7->Add(DirCtrl, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND, 5);
	BoxSizer3->Add(BoxSizer7, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FileList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_AUTOARRANGE, wxDefaultValidator, _T("ID_LISTCTRL1"));
	FileList->SetMinSize(wxSize(550,300));
	FileList->Disable();
	FlexGridSizer1->Add(FileList, 3, wxTOP|wxRIGHT|wxEXPAND, 5);
	FileListPathDisp = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_NO_VSCROLL|wxTE_PROCESS_ENTER|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FileListPathDisp->Disable();
	FlexGridSizer1->Add(FileListPathDisp, 1, wxBOTTOM|wxRIGHT|wxEXPAND, 5);
	BoxSizer3->Add(FlexGridSizer1, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer3, 3, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	MenuItem2 = new wxMenuItem((&BrowserMenu), ID_MENUITEM2, _("Extract"), wxEmptyString, wxITEM_NORMAL);
	MenuItem2->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_BUTTON));
	BrowserMenu.Append(MenuItem2);
	BrowserMenu.AppendSeparator();
	MenuItem4 = new wxMenuItem((&BrowserMenu), ID_MENUITEM4, _("Create Folder"), wxEmptyString, wxITEM_NORMAL);
	MenuItem4->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW_DIR")),wxART_BUTTON));
	BrowserMenu.Append(MenuItem4);
	MenuItem3 = new wxMenuItem((&BrowserMenu), ID_MENUITEM3, _("Rename"), wxEmptyString, wxITEM_NORMAL);
	MenuItem3->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FIND_AND_REPLACE")),wxART_BUTTON));
	BrowserMenu.Append(MenuItem3);
	MenuItem1 = new wxMenuItem((&BrowserMenu), ID_MENUITEM1, _("Delete"), wxEmptyString, wxITEM_NORMAL);
	MenuItem1->SetBitmap(wxIcon(delete_xpm));
	BrowserMenu.Append(MenuItem1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnHDDRealRadioSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnHDDFileRadioSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PFSShellBrowser::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PFSShellBrowser::OnButton2Click);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&PFSShellBrowser::OnFileListItemActivated);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&PFSShellBrowser::OnFileListItemRClick);
	Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnRecoverFileFromHDD);
	Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnMkdirFromHDD);
	Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnRenameFileFromHDD);
	Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PFSShellBrowser::OnDeleteFileFromHDD);
	//*)
	FileList->DragAcceptFiles(true);
    //FileList->DragAcceptFiles(true);
    //FileList->Bind(wxEVT_DROP_FILES, &PFSShellBrowser::OnDropFiles, this);
    DirCtrl->Connect(wxEVT_TREE_BEGIN_DRAG, wxTreeEventHandler(PFSShellBrowser::OnDragFromDirCtrl), NULL, this);
    FileList->SetDropTarget(new DnDFile(FileList));
	//DND_CONNECT(FileList);

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
    XPM::PARTITION = IMGLIST->Add(wxIcon(harddisk_xpm));
    XPM::FILE = IMGLIST->Add(wxIcon(filesave_xpm));
    XPM::UNKNOWN = IMGLIST->Add(wxIcon(question_xpm));
    XPM::TOPARENT = IMGLIST->Add(wxIcon(toparent_xpm));
    XPM::FOLDER = IMGLIST->Add(wxIcon(folder_xpm));
    FileList->SetImageList(IMGLIST, wxIMAGE_LIST_SMALL);


    wxString line;
	wxArrayString RET, ERR;

	long retcode = wxExecute("wmic diskdrive get Caption,DeviceID,InterfaceType", RET, ERR, wxEXEC_SYNC);
	if (retcode == 0)
    {
        for (size_t x=0; x<RET.GetCount();x++)
        {
            line = RET.Item(x);
            wxString drive = line.SubString(line.find("\\\\.\\PHYSICALDRIVE"), line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE")));
            std::cout << drive << "\n";
            if (line == wxEmptyString || x == 0)
                continue;

            //std::cout << line.SubString(line.find("\\\\.\\PHYSICALDRIVE"), line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE"))) << "\n";
            //std::cout << line.Mid(line.find_first_of(' ', line.find("\\\\.\\PHYSICALDRIVE"))) << "|\n";
            //std::cout << line.SubString(0, line.find("\\\\.\\PHYSICALDRIVE")-1) << "\n";
            HDDRealDLG->Append(drive);// col. 1
        }
    }//*/

}

int GetItemIcon(wxListCtrl* CONTROL, long item) {
    wxListItem T;
    T.SetMask(wxLIST_MASK_IMAGE);
    T.SetId(item);
    CONTROL->GetItem(T);
    return T.GetImage();
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
    wxString hdd;
    if (HDDFileRadio->GetValue()) hdd = HDDFileDLG->GetPath().mb_str();
    if (HDDRealRadio->GetValue()) {
        if (HDDRealDLG->GetSelection() < 0) return;
        hdd = HDDRealDLG->GetString(HDDRealDLG->GetSelection());
    }
    /*
    if (wxFileExists(hdd)) {
        std::cout << "aaa\n";
    } else std::cout << "bbb\n";*/
    if (!PFSSHELL.SelectDevice(std::string(hdd))) {
        OpenHDD->Enable(false);
        CloseHDD->Enable();
        FileList->Enable();
        FileListPathDisp->Enable();
        RefreshList();
        EnableCloseButton(false);
    } else {
        wxMessageBox(check_terminal_4_detailed_err, _("Could not open HDD")+"\n"+hdd, wxICON_ERROR);
        std::cout << "HDD OPEN ERR\n";
        PFSSHELL.CloseDevice();
    }
}

void PFSShellBrowser::OnButton2Click(wxCommandEvent& event)
{
    PFSSHELL.CloseDevice();
    OpenHDD->Enable(true);
    CloseHDD->Enable(false);
    CTX::CWD = "/";
    CTX::MNT = "";
    CTX::ISMOUNTED = false;
    FileList->Enable(false);
    FileList->DeleteAllItems();
    FileListPathDisp->Enable(false);
    EnableCloseButton(true);
}

#define MAX_FMT_I (4-1) //to avoid out of bounds request on S and FMT arrays
static wxString humanSize(size_t bytes, int startindx = 0, bool is_PFS_sectors = false)
{
    double temp = bytes;
    int i = startindx;
    std::string S[] = {"B", "KB", "MB", "GB"};
    std::string FMT[] = {"%.00lf", "%.02lf %s", "%.02lf %s", "%.01lf %s"};
    if (is_PFS_sectors) temp /= 2; // PFS sector size can be assumed to be kb*2 size. so treat as kb and divide in half to get real size

    if (temp >= 1024 && (i < MAX_FMT_I)) {temp /= 1024; i++;} //MB
    if (temp >= 1024 && (i < MAX_FMT_I)) {temp /= 1024; i++;} //GB
    if (temp >= 1024 && (i < MAX_FMT_I)) {temp /= 1024; i++;} //GB
	return wxString::Format(FMT[i].c_str(), temp, S[i]);
}

void PFSShellBrowser::RefreshList(void) {
    std::cout << "Listing '"<<CTX::CWD<<"'\n";
    FileList->DeleteAllItems();
    if (!CTX::ISMOUNTED) {
        FileListPathDisp->SetValue("hdd:");
        PFSSHELL.lspart(1, &ITEMLIST);
    } else {
        FileListPathDisp->SetValue(CTX::MNT + CTX::CWD);
        PFSSHELL.ls(CTX::MNT.mb_str(), CTX::CWD.mb_str(), &ITEMLIST);
    }
    wxString tyype, TMP2, cmd;
    wxArrayString ARR;
    //std::cout << "ENTRIES "<<ITEMLIST.size()<<"\n";
    for (size_t x = ITEMLIST.size()-1; x < ITEMLIST.size(); x--)
    {
        bool is_subpartition = ((ITEMLIST[x].stat.attr == 1));
        unsigned int m = ITEMLIST[x].stat.mode;
        if ((m != PARTITION_TYPE::PFS) &&
            (m & FIO_S_IFMT) != FIO_S_IFLNK &&
            (m & FIO_S_IFMT) != FIO_S_IFREG &&
            (m & FIO_S_IFMT) != FIO_S_IFDIR
             || !strcasecmp(".", ITEMLIST[x].name)) // ignoring non PFS Partitions
            continue;
        long itemIndex = FileList->InsertItem(LIST_ITEMS::NAME, ITEMLIST[x].name);// col. 1
        if ((m & FIO_S_IFMT) != FIO_S_IFDIR) {
            wxString z;
            if (!CTX::ISMOUNTED)
                z = humanSize(ITEMLIST[x].stat.size, 1, true);
            else
                z = humanSize(ITEMLIST[x].stat.size, 0);
            FileList->SetItem(itemIndex, LIST_ITEMS::SIZET, z);
        }
        tyype = _("Unknown");
        if (m == PARTITION_TYPE::PFS) {
            tyype = _("PFS Partition");
            FileList->SetItemImage(itemIndex, XPM::PARTITION);
        } else if ((m & FIO_S_IFMT) == FIO_S_IFLNK || (m & FIO_S_IFMT) == FIO_S_IFREG){
            tyype = _("File");
            FileList->SetItemImage(itemIndex, XPM::FILE);
        } else if ((m & FIO_S_IFMT) == FIO_S_IFDIR) {
            tyype = _("Folder");
            FileList->SetItemImage(itemIndex, (!strcasecmp("..", ITEMLIST[x].name)) ? XPM::TOPARENT : XPM::FOLDER);
        } else {
            FileList->SetItemImage(itemIndex, XPM::UNKNOWN);
            tyype += wxString::Format(" (0x%X)", m);
        }
        FileList->SetItem(itemIndex, LIST_ITEMS::TYPE, tyype);
        //Sleep(1000);
    }
    //FileList->SortItems(CompareBasedOnIconType, 0);
}

void PFSShellBrowser::OnFileListItemActivated(wxListEvent& event)
{
    long item = -1;
    item = FileList->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    wxString E = FileList->GetItemText(item, 0);
    int T = GetItemIcon(FileList, item);
    if (T != XPM::FOLDER && T != XPM::PARTITION && T != XPM::TOPARENT) {
        std::cerr << __FUNCTION__ << " Attempt to enter an item wich is not folder or partition ("<< T <<")\n";
        return;
    }
    std::cout << "enter '" << E << "' CWD '" << CTX::CWD << "'\n";
    if (!CTX::ISMOUNTED) {
        CTX::ISMOUNTED = true;
        CTX::MNT = "hdd0:"+E;
        CTX::CWD = "/";
        RefreshList();
    } else {
        if (E != "..") {
            //CTX::CWD << E << "/";
            CTX::CWD << E << "/";
            RefreshList();
        } else {
        ///PLACEHOLDER, GO BACK
            if (CTX::CWD == "/") {
                CTX::MNT = "";
                CTX::ISMOUNTED = false;
                RefreshList();
                return;
            }
            if (CTX::CWD.EndsWith('/')) CTX::CWD.RemoveLast(1);
            size_t P = CTX::CWD.find_last_of('/');
            if (P == 0) {
                CTX::CWD = "/";
            } else if (P != wxNOT_FOUND) {
                CTX::CWD = CTX::CWD.substr(0, P);
                std::cout <<"["<< CTX::CWD << "]" << P << "\n";
            } else {
                CTX::MNT = "";
                CTX::ISMOUNTED = false;
            }
                RefreshList();
        }
    }
}

void PFSShellBrowser::OnDragFromDirCtrl(wxTreeEvent& event) {
    //wxWindowDisabler disabler;
    //wxBusyCursor busyCursor;
    if (!CTX::ISMOUNTED) return;
    wxArrayString T;
    wxFileDataObject data;
    DirCtrl->GetPaths(T);
    for (size_t x=0; x<T.GetCount();x++) {
        //std::cout << T[x] << "| " << wxFileExists(T[x]) <<"\n";
        if (wxFileExists(T[x])) //filter out folders
            data.AddFile(T[x]);
    }
    wxDropSource dragSource(this);
    dragSource.SetData(data);
    //LogDragResult(dragSource.DoDragDrop());
    dragSource.DoDragDrop();
    RefreshList();
}

void PFSShellBrowser::OnDropFiles(wxDropFilesEvent& event) {
    std::cout << __FUNCTION__<< "\n";
    wxFileDataObject data;
    event.GetNumberOfFiles();
    wxDropSource dragSource(this);
    dragSource.SetData(data);
    //LogDragResult(dragSource.DoDragDrop());
    dragSource.DoDragDrop();
}

void PFSShellBrowser::OnFileListItemRClick(wxListEvent& event)
{
    if (CTX::ISMOUNTED) PopupMenu(&BrowserMenu); //because all of our actions are related to PFS partitions
}

#define INFORM() std::cout << __FUNCTION__ << " '" << CTX::CWD << "'\n"
#define ERRCHECK(z, x, y) if (z < 0) wxMessageBox(x, y, wxICON_ERROR)
void PFSShellBrowser::OnRenameFileFromHDD(wxCommandEvent& event)
{
    wxString NewName, OldName;
    const wxString RenamePrompt = _("Rename");
    long itemIndex = -1;
    int x = 0;
    //traverse the selected Items
    while ((itemIndex = FileList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
        OldName = FileList->GetItemText(itemIndex);
        wxTextEntryDialog* T = new wxTextEntryDialog(this, RenamePrompt + ": " + OldName, RenamePrompt, OldName);
        if (T->ShowModal() == wxID_OK) {
            NewName = T->GetValue();
            if (NewName == OldName) continue; //nonsense!
            std::cout <<"RENAME "<< OldName << " -> " << NewName << "\n";
            PFSSHELL.pfs_rename(CTX::MNT.mb_str(), CTX::CWD.mb_str(), OldName.mb_str(), wxString::Format("pfs0:%s%s", CTX::CWD, NewName).mb_str());
            x++;
        }
        delete T;
    }
    if (x > 0) RefreshList(); //user didnt cancel the op
}

void PFSShellBrowser::OnMkdirFromHDD(wxCommandEvent& event)
{
    INFORM();
    wxTextEntryDialog T(this, _("Write the name of the new folder"));
    if (T.ShowModal() == wxID_OK) {
        wxString NewDir = T.GetValue();
        int x = PFSSHELL.pfs_mkdir(CTX::MNT.mb_str(), CTX::CWD.mb_str(), NewDir.mb_str());
        ERRCHECK(x, _("Failed to create folder!"), "");
        RefreshList();
    }
}

void PFSShellBrowser::OnRecoverFileFromHDD(wxCommandEvent& event)
{
    INFORM();
    int x = 0;
    int ercnt = 0;
    wxDirDialog T(this, _("Choose a folder to dump the files"));
    if (T.ShowModal() == wxID_OK) {
        wxString TargetPath = T.GetPath();
        long itemIndex = -1;
        //traverse the selected Items
        while ((itemIndex = FileList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
            wxString targ = TargetPath + "\\" + FileList->GetItemText(itemIndex);
            wxString source = CTX::CWD + FileList->GetItemText(itemIndex);
            std::cout <<"PULL '"<< CTX::MNT << ":pfs:" << source <<"' -> '"<< targ <<"'\n";
            x = PFSSHELL.recoverfile(CTX::MNT.mb_str(), source.mb_str(), targ);
            if (x < 0) ercnt++;
        }
    }
    if (ercnt > 0 ) wxMessageBox(wxString::Format(_("%d files failed to be recovered")+"\n"+check_terminal_4_detailed_err, ercnt),wxMessageBoxCaptionStr, wxICON_ERROR);
}

void PFSShellBrowser::OnDeleteFileFromHDD(wxCommandEvent& event)
{
    INFORM();
    int cnt = FileList->GetSelectedItemCount();
    int ret, errcnt = 0, unk = 0;
    if (wxMessageBox(wxString::Format(_("Delete %d files?\nThis cannot be undone"), cnt), wxMessageBoxCaptionStr, wxICON_QUESTION|wxYES_NO|wxNO_DEFAULT) == wxNO) {
        return;
    }
        long itemIndex = -1;
        //traverse the selected Items
        while ((itemIndex = FileList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
            wxString targ = FileList->GetItemText(itemIndex);
            int T = GetItemIcon(FileList, itemIndex);
            if (T == XPM::FILE) {
                std::cout <<" DELETE " << CTX::MNT <<":pfs:"<< CTX::CWD << targ <<" Prop "<<T<<"\n";
                ret = PFSSHELL.pfs_rm(CTX::MNT.mb_str(), CTX::CWD.mb_str(), targ);
            } else if (T == XPM::FOLDER) {
                std::cout <<" RMDIR " << CTX::MNT <<":pfs:"<< CTX::CWD << targ <<" Prop "<<T<<"\n";
                ret = PFSSHELL.pfs_rmdir(CTX::MNT.mb_str(), CTX::CWD.mb_str(), targ);
            } else {
                std::cout << "UNKNOWN ITEM TYPE: "<<T<<"\n";
                unk++;
                continue;
            }
            if (ret < 0) errcnt++;
        }
    if (errcnt > 0 || unk >0) {
        wxString condf;
        if (errcnt > 0) condf += wxString::Format(_("%d errors")+"\n", errcnt);
        if (unk > 0) condf += wxString::Format(_("%d unknown entries skipped")+"\n", unk);
        wxMessageBox(condf + check_terminal_4_detailed_err, _("The following problems ocurred during transfer"), wxICON_ERROR);
    }
    RefreshList(); //to avoid adding another variable to count on the while loop
}

static int wxCALLBACK CompareBasedOnIconType(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData) {
    /*wxListCtrl *ctrl = (wxListCtrl*) sortData;
    wxListItem A;
    A.SetMask(wxLIST_MASK_IMAGE);
    A.SetId(item1);
    ctrl->GetItem(A);
    wxListItem B;
    B.SetMask(wxLIST_MASK_IMAGE);
    B.SetId(item2);
    ctrl->GetItem(B);
    if (A.GetImage() == XPM::FOLDER && B.GetImage() == XPM::FOLDER) return 0;
    if (A.GetImage() == XPM::FOLDER && B.GetImage() != XPM::FOLDER) return 1;
    if (A.GetImage() != XPM::FOLDER && B.GetImage() == XPM::FOLDER) return -1;*/
    //std::cout << item1 << "|" << item2 << "|"<< sortData<<"\n";
    if(item1<item2) return -1;
    if(item1>item2) return 1;
    return 0; // if both items are equal...
    return 0;

}

void PFSShellBrowser::OnSort(wxCommandEvent& WXUNUSED(event))
{
    FileList->SortItems(CompareBasedOnIconType, 0);
}
//UNUSED
void PFSShellBrowser::OnWindowClose(wxCloseEvent& event)
{
    PFSSHELL.CloseDevice(); //just in case
}
