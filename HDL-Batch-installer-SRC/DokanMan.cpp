#include "DokanMan.h"
#include <wx/filefn.h>
#include <wx/longlong.h>
#include <wx/volume.h>
#include <iostream>
#include "include/macro-vault.h"
#include <wx/dir.h>
#include <wx/fileconf.h>
#include <wx/msgdlg.h>
//(*InternalHeaders(DokanMan)
#include <wx/intl.h>
#include <wx/string.h>
//*)
bool MOUNTSTATE;
wxLongLong FREE_SPACE;
wxLongLong TOTAL_SPACE;
#define DOKAN_ENV "DokanLibrary1"
#define DOKAN_ENV2 "DokanLibrary2"

/*struct drive_t
{
    char drive;
    bool used = false;
}drives[25];*/
wxString Get_env(wxString ENV);

enum DRIVEMASKS
{
    A=0,
    B,D,E,F,
    G,H,I,J,K,
    L,M,N,O,P,
    Q,R,S,T,U,
    V,W,X,Y,Z,

    DRIVES
};

const char mountpointss[DRIVES] =
{
    'A','B','D','E','F',
    'G','H','I','J','K',
    'L','M','N','O','P',
    'Q','R','S','T','U',
    'V','W','X','Y','Z'
};// C skipped because it will be used for sure
//(*IdInit(DokanMan)
const long DokanMan::ID_CHOICE1 = wxNewId();
const long DokanMan::ID_TEXTCTRL1 = wxNewId();
const long DokanMan::ID_CHOICE2 = wxNewId();
const long DokanMan::ID_STATICTEXT1 = wxNewId();
const long DokanMan::ID_TEXTCTRL2 = wxNewId();
const long DokanMan::ID_STATICTEXT2 = wxNewId();
const long DokanMan::ID_TEXTCTRL3 = wxNewId();
const long DokanMan::ID_GAUGE1 = wxNewId();
const long DokanMan::ID_BUTTON1 = wxNewId();
const long DokanMan::ID_BUTTON2 = wxNewId();
const long DokanMan::ID_BUTTON4 = wxNewId();
const long DokanMan::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DokanMan,wxDialog)
    //(*EventTable(DokanMan)
    //*)
END_EVENT_TABLE()
DokanMan::DokanMan(wxWindow* parent, wxArrayString PARTITIONS_, wxString HDD, wxWindowID id): PARTITION_LIST(PARTITIONS_), CURR_HDD(HDD)
{
    //(*Initialize(DokanMan)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxGridSizer* GridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;

    Create(parent, wxID_ANY, _("Dokan Manager"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Available partitions"));
    partyselector = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxSize(161,28), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    StaticBoxSizer1->Add(partyselector, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Current HDD"));
    currhdd = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticBoxSizer2->Add(currhdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Mount point"));
    Drive_selector = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    Drive_selector->Disable();
    Drive_selector->SetToolTip(_("Choose device letter to mount  partition"));
    StaticBoxSizer3->Add(Drive_selector, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1 = new wxGridSizer(0, 1, 0, 0);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Free"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PART_FREE = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer3->Add(PART_FREE, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("total"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PART_TOTAL = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer4->Add(PART_TOTAL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Gauge1 = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxSize(391,28), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    GridSizer1->Add(Gauge1, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Mount  = new wxButton(this, ID_BUTTON1, _("Mount "), wxDefaultPosition, wxSize(105,28), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Mount ->Disable();
    BoxSizer2->Add(Mount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Unmount = new wxButton(this, ID_BUTTON2, _("Unmount"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Unmount->Disable();
    BoxSizer2->Add(Unmount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    ART_TRANSFER = new wxButton(this, ID_BUTTON4, _("Transfer OPL files"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    ART_TRANSFER->Disable();
    BoxSizer3->Add(ART_TRANSFER, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    call_explorer_exe = new wxButton(this, ID_BUTTON5, _("Open in explorer"), wxDefaultPosition, wxSize(155,28), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    call_explorer_exe->Disable();
    BoxSizer3->Add(call_explorer_exe, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DokanMan::OnpartyselectorSelect);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&DokanMan::OnDrive_selectorSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DokanMan::Mount_Partition);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DokanMan::OnUnmountClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DokanMan::OnART_TRANSFERClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DokanMan::Oncall_explorer_exeClick);
    //*)
    for (size_t x=0; x< PARTITIONS_.GetCount(); x++)
        partyselector->Append(PARTITIONS_.Item(x));

    currhdd->Clear();
    currhdd->AppendText(HDD);

    wxArrayString VOLS = wxFSVolume::GetVolumes();
    bool found_conflict = false;
    for (int z=0; z<25; z++)
    {
        //std::cout<<"Iterating on["<<mountpointss[z]<<"]\n";
        wxString TMP;
        for (size_t x=0; x< VOLS.GetCount(); x++)
        {
            TMP = VOLS.Item(x)[0];
            //std::cout <<"> "<<TMP<<" Drive is in use, exlcluding from options...\n";
            //if (TMP==mountpointss[z])
            if (TMP.IsSameAs(mountpointss[z],true))
            {
                std::cout <<"found conflict\n";
                found_conflict = true;
                break;
            }

        }
        if (found_conflict)
        {
            COLOR(0c)
            //std::cout << mountpointss[z]<<"|\n";
        }
        else
        {
            COLOR(0a)
            //std::cout <<mountpointss[z]<<",|\n";
            Drive_selector->Append(mountpointss[z]);
        }
        COLOR(07)
        found_conflict = false; ///reset to original state before iteration continues
    }
    HDLBINST_APPDATA_2 = wxString::Format("%s\\HDLBInst",Get_env("appdata"));

}

DokanMan::~DokanMan()
{
    //(*Destroy(DokanMan)
    //*)
}

void DokanMan::Mount_Partition(wxCommandEvent& event)
{
    EnableCloseButton(false);
    Mount->Disable();
    Drive_selector->Disable();
    partyselector->Disable();
    Unmount->Enable();
    ART_TRANSFER->Enable();
    call_explorer_exe->Enable();
    wxString PART = partyselector->GetString(partyselector->GetCurrentSelection());
    wxString MOUNTPOINT = Drive_selector->GetString(Drive_selector->GetCurrentSelection());
    wxString MOUNT_COMMAND = wxString::Format("Common\\pfsfuse.exe --partition=%s %s %s -o volname=%s",
                             PART, CURR_HDD, MOUNTPOINT, PART);
    std::cout <<"> Calling PFSFUSE to mount partition\n\t";
    COLOR(0e)
    std::cout <<"Command: ["<<MOUNT_COMMAND<<"]\n";
    COLOR(07)
    wxExecute(MOUNT_COMMAND);
    wxDiskspaceSize_t FREE,TOT;
    wxGetDiskSpace(wxString::Format("%s",MOUNTPOINT)
                   ,&TOT,&FREE);
    PART_FREE->Clear();
    PART_FREE->AppendText(wxString::Format("%lli",FREE));
    PART_TOTAL->Clear();
    PART_TOTAL->AppendText(wxString::Format("%lli",TOT));
}

void DokanMan::OnpartyselectorSelect(wxCommandEvent& event)
{
    //wxString PARTY = partyselector->GetString(partyselector->GetCurrentSelection());
    Drive_selector->Enable();
}

void DokanMan::OnDrive_selectorSelect(wxCommandEvent& event)
{
    Mount->Enable();
}

void DokanMan::OnUnmountClick(wxCommandEvent& event)
{
    wxString DOKAN_ENV_TMP;
    if (wxDirExists(HDLBINST_APPDATA_2))
    {
        if (!wxFileExists(HDLBINST_APPDATA_2+"\\dokan_and_fuse.ini"))
        {
            wxFileConfig * DUMM = new wxFileConfig( wxEmptyString, wxEmptyString, HDLBINST_APPDATA_2+"\\dokan_and_fuse.ini");
            DUMM->Write("PFSFUSE/has_been_used",true);
            DUMM->Flush();
            delete DUMM;
        }
    }
    else
    {
        wxMkDir(HDLBINST_APPDATA_2);
    }
    if (!wxGetEnv(DOKAN_ENV, &DOKAN_ENV_TMP))
        if (!wxGetEnv(DOKAN_ENV2, &DOKAN_ENV_TMP))
        {
            wxMessageBox(_("impossible to find dokan enviroment variables.\nunmount the drive manually by calling:\ndokanctl.exe /u {"+_("Mount point")+"}"), wxEmptyString, wxICON_ERROR);
            return;
        };
    std::cout <<"> Unmounting partition\n";
    wxString MOUNTPOINT = Drive_selector->GetString(Drive_selector->GetCurrentSelection());

    wxString UNMOUNT_COMMAND = wxString::Format("%s\\dokanctl.exe /u %s",DOKAN_ENV_TMP,MOUNTPOINT);

    wxExecute(UNMOUNT_COMMAND,wxEXEC_SYNC);

    Drive_selector->Enable();
    partyselector->Enable();
    Mount ->Enable();
    ART_TRANSFER->Enable(false);
    call_explorer_exe->Enable(false);
    EnableCloseButton(true);
    Unmount->Disable();
}

void DokanMan::Oncall_explorer_exeClick(wxCommandEvent& event)
{
    wxString MOUNTPOINT = Drive_selector->GetString(Drive_selector->GetCurrentSelection());
    wxExecute(wxString::Format("explorer.exe %s:\\",MOUNTPOINT));
}

void DokanMan::Onmanual_ExitClick(wxCommandEvent& event)
{

}

void DokanMan::OnART_TRANSFERClick(wxCommandEvent& event)
{
    wxString MOUNTBASE, TMP;
    wxString MOUNTPOINT = Drive_selector->GetString(Drive_selector->GetCurrentSelection());
    wxString PART = partyselector->GetString(partyselector->GetCurrentSelection());
    extern wxString EXEC_PATH;
    wxDir *curdir_handler = new wxDir();
    wxArrayString filelist;
    //-----------------------------------ART
    if (wxDirExists(EXEC_PATH+"Downloads\\ART"))
    {
        curdir_handler->GetAllFiles(EXEC_PATH+"Downloads\\ART",&filelist,"*.*",wxDIR_FILES);
        MOUNTBASE = MOUNTPOINT+":\\";
        if (!PART.StartsWith("+")) MOUNTBASE.append("OPL\\");
        if (!wxDirExists(MOUNTBASE)) wxMkDir(MOUNTBASE);
        MOUNTBASE.append("ART\\");
        if (!wxDirExists(MOUNTBASE)) wxMkDir(MOUNTBASE);
        COLOR(0d)
        for (size_t x = 0 ; x < filelist.GetCount() ; x++)
        {
            TMP = filelist.Item(x);
            TMP = TMP.substr(TMP.find_last_of('\\')+1);
            std::cout <<"copying: ["<<filelist.Item(x)<<"] -> ["<<MOUNTBASE<<TMP<<"]\n";
            wxCopyFile(filelist.Item(x), MOUNTBASE+ TMP);
            if (wxFileExists(MOUNTBASE+TMP)) wxRemoveFile(filelist.Item(x));
        }
    }
    COLOR(07)
    //-----------------------------------CHEATS
    if (wxDirExists(EXEC_PATH+"Downloads\\CHT"))
    {
        filelist.clear();
        curdir_handler->GetAllFiles(EXEC_PATH+"Downloads\\CHT",&filelist,"*.cht",wxDIR_FILES);
        MOUNTBASE = MOUNTPOINT+":\\";
        if (!PART.StartsWith("+")) MOUNTBASE.append("OPL\\");
        MOUNTBASE.append("CHT\\");
        if (!wxDirExists(MOUNTBASE)) wxMkDir(MOUNTBASE);
        COLOR(0d)
        for (size_t x = 0 ; x < filelist.GetCount() ; x++)
        {
            TMP = filelist.Item(x);
            TMP = TMP.substr(TMP.find_last_of('\\')+1);
            std::cout <<"copying: ["<<filelist.Item(x)<<"] -> ["<<MOUNTBASE<<TMP<<"]\n";
            wxCopyFile(filelist.Item(x), MOUNTBASE+ TMP);
            if (wxFileExists(MOUNTBASE+TMP)) wxRemoveFile(filelist.Item(x));
        }
    }
    COLOR(07)
    //-----------------------------------Config files
    if (wxDirExists(EXEC_PATH+"Downloads\\CFG"))
    {
        filelist.clear();
        curdir_handler->GetAllFiles(EXEC_PATH+"Downloads\\CFG",&filelist,"*.cfg",wxDIR_FILES);
        MOUNTBASE = MOUNTPOINT+":\\";
        if (!PART.StartsWith("+")) MOUNTBASE.append("OPL\\");
        MOUNTBASE.append("CFG\\");
        if (!wxDirExists(MOUNTBASE)) wxMkDir(MOUNTBASE);
        COLOR(0d)
        for (size_t x = 0 ; x < filelist.GetCount() ; x++)
        {
            TMP = filelist.Item(x);
            TMP = TMP.substr(TMP.find_last_of('\\')+1);
            std::cout <<"copying: ["<<filelist.Item(x)<<"] -> ["<<MOUNTBASE<<TMP<<"]\n";
            wxCopyFile(filelist.Item(x), MOUNTBASE+ TMP);
            if (wxFileExists(MOUNTBASE+TMP)) wxRemoveFile(filelist.Item(x));
        }
    }
    COLOR(07)
    //-----------------------------------VIRTUAL MEMRY CARDS
    if (wxDirExists(EXEC_PATH+"Downloads\\VMC"))
    {
        filelist.clear();
        curdir_handler->GetAllFiles(EXEC_PATH+"Downloads\\VMC",&filelist,"*.bin",wxDIR_FILES);
        MOUNTBASE = MOUNTPOINT+":\\";
        if (!PART.StartsWith("+")) MOUNTBASE.append("OPL\\");
        MOUNTBASE.append("VMC\\");
        if (!wxDirExists(MOUNTBASE)) wxMkDir(MOUNTBASE);
        COLOR(0d)
        for (size_t x = 0 ; x < filelist.GetCount() ; x++)
        {
            TMP = filelist.Item(x);
            TMP = TMP.substr(TMP.find_last_of('\\')+1);
            std::cout <<"copying: ["<<filelist.Item(x)<<"] -> ["<<MOUNTBASE<<TMP<<"]\n";
            wxCopyFile(filelist.Item(x), MOUNTBASE+ TMP);
            if (wxFileExists(MOUNTBASE+TMP)) wxRemoveFile(filelist.Item(x));
        }
    }
    COLOR(07)

}
