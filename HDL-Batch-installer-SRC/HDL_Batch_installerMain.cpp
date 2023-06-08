/***************************************************************
 * Name:      HDL_Batch_installerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-03-31
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
// FRAME & Dialog
#include "HDL_Batch_installerMain.h"
#include "About.h"
#include "Config.h"
#include "Component_error.h"
#include "ArtMan.h"
#include "DokanMan.h"
#include "Post_Install_Report.h"
#include "CopyHDD.h"
#include "NDBMan.h"
#include "HDDManager.h"
#include "HDDFomatMan.h"
#include "MD5Report.h"

#include "hdl-dump-recodes.h"
#include "gamename/parser.h" //includes both database & parser function
#include "MD5Man.h"
#include "PFSShell.h"

#define PFSSHELL_DISABLED_WARNING() wxMessageBox(_("HDD Management features are temporarily disabled on 32bit versions because it can cause HDD corruption"), warning_caption, wxICON_WARNING)
#define PFSSHELL_ALLOWED_INT 0
#define PFSSHELL_ALLOWED ((BITS != 32) || (PFSSHELL_ALLOWED_INT == 1))
using namespace std;
bool first_init = false;

///CONFIG TABLE
namespace CFG
{
int         DBMODE = DB_INTERNAL; //INTERNAL || EXTERNAL (gamename.DB at Program location)
bool        DBENABLE = true;     //if the program should use any database. true=use database,false=arbitrarly use ISO filename
int         DEBUG_LEVEL;          //defines how many data will be written at the log
int         MINIOPL_WARNING;      //1=display warnings if boot.kelf (AKA: MiniOPL) is missing before begining installation
int         OSD_HIDE;             //use or not -hide switch on installation command
wxString    DEFAULT_ISO_PATH;
int         DMA;
bool        LOAD_CUSTOM_ICONS;
wxString    mountpoint;
wxString    default_OPLPART;
wxString    NBD_IP;
bool        SHARE_DATA;
bool        DISPATCH_SYSTEM_NOTIFICATIONS;
bool        ALLOW_EXPERIMENTAL;
//    bool        UPDATE_AVAILABLE = false;
//    bool        UPDATE_WARNINGS;
}
bool CAN_COPY_HDD;
wxString versionTAG;
//wxString gserverTAG;
//Default path for game search event
///CONFIG TABLE

wxString Get_env(wxString ENV)
{
    wxString TMP;
    wxGetEnv(ENV,&TMP);
    return TMP;
}
/// common data declaration:
//wxFileName fname( wxTheApp->argv[0] );
wxFileName fname;
wxString EXEC_PATH = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);
wxString HDL_CACHE;
wxString MBR_CACHE;
wxString MiniOPL;
wxString ICONS_FOLDER;

std::string HDD_TOKEN;
PFSShell PFSSHELL;
bool PFSSHELL_USABLE = false;

extern string DMA_TABLE[8];
extern string DMA_ALIAS[8];
const std::string MiniOPL_URL = "https://github.com/israpps/HDL-Batch-installer/raw/main/Release/boot.kelf";
const wxString error_caption = _("error");
const wxString warning_caption = _("warning");
#define DOKAN_ENV "DokanLibrary1"
#define DOKAN_ENV2 "DokanLibrary2"
wxString HDLBINST_APPDATA;

/*
 * NOTE: lines encased between //(* and //*) are controlled by code::blocks wxwidgets project manager, changing code inside it is useless, and will be erased as sson as anyone changes the front-end
 */
//(*InternalHeaders(HDL_Batch_installerFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)



//(*IdInit(HDL_Batch_installerFrame)
const long HDL_Batch_installerFrame::ID_BUTTON2 = wxNewId();
const long HDL_Batch_installerFrame::ID_selected_hdd = wxNewId();
const long HDL_Batch_installerFrame::ID_TEXTCTRL2 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON14 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON15 = wxNewId();
const long HDL_Batch_installerFrame::ID_TEXTCTRL1 = wxNewId();
const long HDL_Batch_installerFrame::ID_GAUGE1 = wxNewId();
const long HDL_Batch_installerFrame::ID_LISTCTRL1 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON1 = wxNewId();
const long HDL_Batch_installerFrame::ID_STATICLINE3 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON7 = wxNewId();
const long HDL_Batch_installerFrame::ID_STATICLINE1 = wxNewId();
const long HDL_Batch_installerFrame::ID_CHOICE1 = wxNewId();
const long HDL_Batch_installerFrame::ID_STATICLINE2 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON4 = wxNewId();
const long HDL_Batch_installerFrame::ID_STATICLINE4 = wxNewId();
const long HDL_Batch_installerFrame::ID_CHECKBOX2 = wxNewId();
const long HDL_Batch_installerFrame::ID_PANEL1 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON3 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON8 = wxNewId();
const long HDL_Batch_installerFrame::ID_LISTCTRL2 = wxNewId();
const long HDL_Batch_installerFrame::ID_PANEL2 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON10 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON13 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON6 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON9 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON5 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON11 = wxNewId();
const long HDL_Batch_installerFrame::ID_BUTTON16 = wxNewId();
const long HDL_Batch_installerFrame::ID_PANEL3 = wxNewId();
const long HDL_Batch_installerFrame::ID_NOTEBOOK1 = wxNewId();
const long HDL_Batch_installerFrame::ID_PANEL5 = wxNewId();
const long HDL_Batch_installerFrame::idMenuQuit = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM13 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM15 = wxNewId();
const long HDL_Batch_installerFrame::SETTINGS = wxNewId();
const long HDL_Batch_installerFrame::idMenuAbout = wxNewId();
const long HDL_Batch_installerFrame::UPDT = wxNewId();
const long HDL_Batch_installerFrame::ISSUE = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM1 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM2 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM9 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM10 = wxNewId();
const long HDL_Batch_installerFrame::ID_PROGRESSDIALOG1 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM3 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM18 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM4 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM5 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM7 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM14 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM6 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM11 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM12 = wxNewId();
const long HDL_Batch_installerFrame::ID_MENUITEM8 = wxNewId();
const long HDL_Batch_installerFrame::DELETE_GAME_ID = wxNewId();
const long HDL_Batch_installerFrame::ID_PROGRESSDIALOG2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HDL_Batch_installerFrame,wxFrame)
    //(*EventTable(HDL_Batch_installerFrame)
    //*)
END_EVENT_TABLE()

HDL_Batch_installerFrame::HDL_Batch_installerFrame(wxWindow* parent, wxLocale& locale, long Custom_Styles, long ctor_flags_ctor, wxWindowID id)
    :  m_locale(locale) ///Initialize Translations
    , CTOR_FLAGS(ctor_flags_ctor) ///Pass init flags into class member
{
    COLOR(0f)
    cout << "welcome to HDL Batch Installer [" << versionTAG <<"]\n";
    COLOR(07)
#ifdef RELEASE
    Create(parent, wxID_ANY, "HDL Batch Installer | By Matias Israelson (El_isra)", wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER|Custom_Styles|wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("wxID_ANY"));
#endif
    //(*Initialize(HDL_Batch_installerFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer9;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenu* Menu3;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem3;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, wxID_ANY, _("HDL Batch Installer"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("wxID_ANY"));
    SetClientSize(wxSize(537,651));
    Move(wxPoint(-1,-1));
    SetMinSize(wxSize(537,681));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    wxFont thisFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SetIcon( wxICON(HDL_BATCH_ICON));
    Panel5 = new wxPanel(this, ID_PANEL5, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    Panel5->SetMinSize(wxSize(557,691));
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(2);
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
    Button1 = new wxButton(Panel5, ID_BUTTON2, _("Search ps2 HDD\'s"), wxDefaultPosition, wxSize(144,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button1->SetFocus();
    FlexGridSizer10->Add(Button1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer10->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    selected_hdd = new wxChoice(Panel5, ID_selected_hdd, wxDefaultPosition, wxSize(148,24), 0, 0, 0, wxDefaultValidator, _T("ID_selected_hdd"));
    FlexGridSizer10->Add(selected_hdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer1->Add(FlexGridSizer10, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer2->Add(BoxSizer1, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer9->AddGrowableRow(0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel5, _("WNBD Server"));
    NBD4IP = new wxTextCtrl(Panel5, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    NBD4IP->SetMaxLength(15);
    StaticBoxSizer1->Add(NBD4IP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    NBDConnect = new wxButton(Panel5, ID_BUTTON14, _("Connect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON14"));
    NBDConnect->Disable();
    StaticBoxSizer1->Add(NBDConnect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    NBDDisconnect = new wxButton(Panel5, ID_BUTTON15, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON15"));
    StaticBoxSizer1->Add(NBDDisconnect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    hdd_used_space = new wxTextCtrl(Panel5, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(400,23), wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer3->Add(hdd_used_space, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Gauge1 = new wxGauge(Panel5, ID_GAUGE1, 100, wxDefaultPosition, wxSize(464,24), wxGA_SMOOTH, wxDefaultValidator, _T("ID_GAUGE1"));
    FlexGridSizer3->Add(Gauge1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    FlexGridSizer4 = new wxFlexGridSizer(1, 3, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(0);
    Notebook1 = new wxNotebook(Panel5, ID_NOTEBOOK1, wxPoint(-1,-1), wxSize(520,440), 0, _T("ID_NOTEBOOK1"));
    Notebook1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 3, 3, 4);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(0);
    game_list__ = new wxListCtrl(Panel1, ID_LISTCTRL1, wxDefaultPosition, wxSize(370,405), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxBORDER_SUNKEN|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL1"));
    game_list__->SetMinSize(wxSize(377,415));
    wxListItem _col0;
    _col0.SetId(0);
    _col0.SetText( _("Game ") );
    _col0.SetWidth(350);
    game_list__->InsertColumn(0, _col0);
    FlexGridSizer6->Add(game_list__, 0, wxALL|wxEXPAND, 0);
    FlexGridSizer6->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
    SEARCH_ISO = new wxButton(Panel1, ID_BUTTON1, _("Search Games"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    SEARCH_ISO->Disable();
    FlexGridSizer7->Add(SEARCH_ISO, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticLine3 = new wxStaticLine(Panel1, ID_STATICLINE3, wxDefaultPosition, wxSize(0,0), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    FlexGridSizer7->Add(StaticLine3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    clear_iso_list = new wxButton(Panel1, ID_BUTTON7, _("Clear list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    clear_iso_list->Disable();
    FlexGridSizer7->Add(clear_iso_list, 0, wxLEFT|wxRIGHT|wxEXPAND, 0);
    StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    FlexGridSizer7->Add(StaticLine1, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer7->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    dma_choice = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    dma_choice->Disable();
    for (int X=0 ; X <=7 ; X++)
    { dma_choice->Append(DMA_ALIAS[X]); }
    dma_choice->SetSelection(7);
    FlexGridSizer7->Add(dma_choice, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticLine2 = new wxStaticLine(Panel1, ID_STATICLINE2, wxDefaultPosition, wxSize(0,0), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    FlexGridSizer7->Add(StaticLine2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer7->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    install = new wxButton(Panel1, ID_BUTTON4, _("Install"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    install->Disable();
    FlexGridSizer7->Add(install, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    StaticLine4 = new wxStaticLine(Panel1, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    FlexGridSizer7->Add(StaticLine4, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer7->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    use_database = new wxCheckBox(Panel1, ID_CHECKBOX2, _("Use Database"), wxDefaultPosition, wxSize(110,20), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    use_database->SetValue(true);
    use_database->SetToolTip(_("When enabled, the program will try to automatically assign the original title for the games by searching the game ID on a database with more than 14700 titles"));
    FlexGridSizer7->Add(use_database, 0, wxLEFT|wxRIGHT|wxEXPAND, 9);
    FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(Panel1);
    FlexGridSizer6->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer8->AddGrowableCol(0);
    FlexGridSizer8->AddGrowableRow(1);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Parse_hdl_toc = new wxButton(Panel2, ID_BUTTON3, _("Get List"), wxDefaultPosition, wxSize(80,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Parse_hdl_toc->Disable();
    BoxSizer2->Add(Parse_hdl_toc, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Button3 = new wxButton(Panel2, ID_BUTTON8, _("\?"), wxDefaultPosition, wxSize(16,23), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer2->Add(Button3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer8->Add(BoxSizer2, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    Installed_game_list = new wxListCtrl(Panel2, ID_LISTCTRL2, wxDefaultPosition, wxSize(509,378), wxLC_REPORT|wxLC_AUTOARRANGE|wxLC_SORT_ASCENDING|wxLC_HRULES|wxLC_VRULES|wxLC_NO_SORT_HEADER|wxBORDER_SUNKEN|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL2"));
    Installed_game_list->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX));
    wxListItem col0;
    col0.SetId(0);
    col0.SetText( _("Game ") );
    col0.SetWidth(200);//180
    Installed_game_list->InsertColumn(0, col0);

    // Add second column
    wxListItem col1;
    col1.SetId(1);
    col1.SetText( _("ID") );
    col1.SetWidth(110);
    Installed_game_list->InsertColumn(1, col1);

    // Add third column
    wxListItem col2;
    col2.SetId(2);
    col2.SetText( _("size (MB)") );
    col2.SetWidth(90);
    Installed_game_list->InsertColumn(2, col2);

    // Add 4th column
    wxListItem col3;
    col3.SetId(3);
    col3.SetText( _("Media") );
    col3.SetWidth(50);
    Installed_game_list->InsertColumn(3, col3);
    FlexGridSizer8->Add(Installed_game_list, 0, wxEXPAND, 0);
    Panel2->SetSizer(FlexGridSizer8);
    FlexGridSizer8->Fit(Panel2);
    FlexGridSizer8->SetSizeHints(Panel2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetMaxSize(wxSize(-1,-1));
    FlexGridSizer5 = new wxFlexGridSizer(0, 0, 5, 5);
    FlexGridSizer5->AddGrowableCol(0);
    FlexGridSizer5->AddGrowableRow(0);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    HDDManagerButton = new wxButton(Panel3, ID_BUTTON10, _("HDD Manager"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    HDDManagerButton->Disable();
    BoxSizer10->Add(HDDManagerButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(BoxSizer10, 1, wxALL|wxEXPAND, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    mass_header_injection = new wxButton(Panel3, ID_BUTTON13, _("Inject OPL Launcher"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    mass_header_injection->Disable();
    mass_header_injection->SetToolTip(_("This will inject OPL Launcher (boot.kelf on program folder) into every PS2 game found on this HDD.\nUsefull to install/update OPL Launcher into your games"));
    BoxSizer9->Add(mass_header_injection, 0, wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(BoxSizer9, 1, wxALL|wxEXPAND, 5);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    modify_header_event = new wxButton(Panel3, ID_BUTTON6, _("Modify Header"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    modify_header_event->Disable();
    BoxSizer8->Add(modify_header_event, 0, wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(BoxSizer8, 1, wxALL|wxEXPAND, 5);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    MBRExtractRequest = new wxButton(Panel3, ID_BUTTON9, _("Recover MBR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    MBRExtractRequest->Disable();
    BoxSizer7->Add(MBRExtractRequest, 0, wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(BoxSizer7, 1, wxALL|wxEXPAND, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    MBR_EVENT = new wxButton(Panel3, ID_BUTTON5, _("Inject MBR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    MBR_EVENT->Disable();
    BoxSizer6->Add(MBR_EVENT, 0, wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(BoxSizer6, 1, wxALL|wxEXPAND, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    FUSE = new wxButton(Panel3, ID_BUTTON11, _("Mount hdd Partition"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    FUSE->Disable();
    BoxSizer5->Add(FUSE, 0, wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(BoxSizer5, 1, wxALL|wxEXPAND, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    Button4 = new wxButton(Panel3, ID_BUTTON16, _("NBD Driver manager"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON16"));
    BoxSizer4->Add(Button4, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer5->Add(BoxSizer3, 1, wxALL|wxEXPAND, 5);
    Panel3->SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(Panel3);
    FlexGridSizer5->SetSizeHints(Panel3);
    Notebook1->AddPage(Panel1, _("Install"), false);
    Notebook1->AddPage(Panel2, _("Browse"), false);
    Notebook1->AddPage(Panel3, _("HDD Management"), false);
    FlexGridSizer4->Add(Notebook1, 0, wxEXPAND, 0);
    FlexGridSizer1->Add(FlexGridSizer4, 4, wxALL|wxEXPAND, 5);
    Panel5->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel5);
    FlexGridSizer1->SetSizeHints(Panel5);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    COPYHDD = new wxMenuItem(Menu1, ID_MENUITEM13, _("Massive game transfer"), _("Transfer all games installed on currently selected HDD into another one"), wxITEM_NORMAL);
    Menu1->Append(COPYHDD);
    COPYHDD->Enable(false);
    MenuHDDFormat = new wxMenuItem(Menu1, ID_MENUITEM15, _("Format HDD"), _("Format any device into PS2 HDD"), wxITEM_NORMAL);
    Menu1->Append(MenuHDDFormat);
    MenuBar1->Append(Menu1, _("&Main"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, SETTINGS, _("Settings\tF2"), _("configure program"), wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuBar1->Append(Menu3, _("Config"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show version and credits"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuItem5 = new wxMenuItem(Menu2, UPDT, _("Update Program"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu2, ISSUE, _("Report Issue"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem6);
    MenuBar1->Append(Menu2, _("About"));
    Menu4 = new wxMenu();
    MenuItem4 = new wxMenuItem(Menu4, ID_MENUITEM1, _("Update OPL Launcher"), _("update OPL Launcher KELF"), wxITEM_NORMAL);
    Menu4->Append(MenuItem4);
    MenuItem7 = new wxMenuItem(Menu4, ID_MENUITEM2, _("Update HDL-Dump"), _("Update the game installation tool"), wxITEM_NORMAL);
    Menu4->Append(MenuItem7);
    MenuItem14 = new wxMenuItem(Menu4, ID_MENUITEM9, _("Update game title database"), _("Update game title database"), wxITEM_NORMAL);
    Menu4->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu4, ID_MENUITEM10, _("Download Icons Package"), _("Update HDD-OSD icons package"), wxITEM_NORMAL);
    Menu4->Append(MenuItem15);
    MenuBar1->Append(Menu4, _("Downloads"));
    SetMenuBar(MenuBar1);
    MBR_search = new wxFileDialog(this, _("Search MBR.KELF"), wxEmptyString, _("MBR.KELF"), _("*.KELF"), wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    //nedeaaa
    MenuItem8 = new wxMenuItem((&about_2_install_menu), ID_MENUITEM3, _("Open File location"), wxEmptyString, wxITEM_NORMAL);
    about_2_install_menu.Append(MenuItem8);
    Redump_search = new wxMenuItem((&about_2_install_menu), ID_MENUITEM18, _("Calculate MD5 Hash"), wxEmptyString, wxITEM_NORMAL);
    about_2_install_menu.Append(Redump_search);
    MenuItem9 = new wxMenuItem((&about_2_install_menu), ID_MENUITEM4, _("Remove from List"), wxEmptyString, wxITEM_NORMAL);
    about_2_install_menu.Append(MenuItem9);
    MenuItem10 = new wxMenuItem((&Browser_menu), ID_MENUITEM5, _("Extract Game(s)"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem10);
    MenuItem12 = new wxMenuItem((&Browser_menu), ID_MENUITEM7, _("Download assets"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem12);
    MenuItem18 = new wxMenuItem((&Browser_menu), ID_MENUITEM14, _("Transfer game(s) to another PS2 HDD"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem18);
    Browser_menu.AppendSeparator();
    MenuItem11 = new wxMenuItem((&Browser_menu), ID_MENUITEM6, _("Rename"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem11);
    MenuItem16 = new wxMenuItem((&Browser_menu), ID_MENUITEM11, _("Inject OPL Launcher"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem16);
    MenuItem17 = new wxMenuItem((&Browser_menu), ID_MENUITEM12, _("Load Custom Icon"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem17);
    Browser_menu.AppendSeparator();
    MenuItem13 = new wxMenuItem((&Browser_menu), ID_MENUITEM8, _("Information"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(MenuItem13);
    DeleteGameMenuItem = new wxMenuItem((&Browser_menu), DELETE_GAME_ID, _("Delete game"), wxEmptyString, wxITEM_NORMAL);
    Browser_menu.Append(DeleteGameMenuItem);
    DeleteGameMenuItem->Enable(false);
    Center();

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnButton1Click);
    Connect(ID_selected_hdd,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::Onselected_hddSelect);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnIP4NBDUpdate);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnNBDConnectClick);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnNBDDisconnectClick);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnTextCtrl1Text);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnListCtrl1BeginDrag);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&HDL_Batch_installerFrame::onItemRightClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnSEARCH_ISOClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::Onclear_iso_listClick);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::Ondma_choiceSelect);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OninstallClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnCheckBox1Click1);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnParse_hdl_tocClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnButton3Click1);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnListCtrl1BeginDrag1);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::Selected_games);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::UnSelected_games);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnInstalled_game_listItemRClick1);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnButton2Click3);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::Onmass_header_injectionClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnButton2Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnMBRExtractRequestClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnMBR_EVENTClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnButton4Click);
    Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnButton4Click1);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnNotebook1PageChanged);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnQuit);
    Connect(ID_MENUITEM13,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnCOPYHDDSelected);
    Connect(ID_MENUITEM15,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnHDDFormatMenuRequest);
    Connect(SETTINGS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnSettings);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnAbout);
    Connect(UPDT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnUpdateRequest);
    Connect(ISSUE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnIssueReport);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::On_MiniOPL_Update_request);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnHDL_DumpUpdateRequest);
    Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::On_GameNameDatabaseDownloadRequest);
    Connect(ID_MENUITEM10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnIconsPackageRequest);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnItemListShowRequest);
    Connect(ID_MENUITEM18,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnCalculateMD5Selected);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::RemoveISOfromList);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnExtractInstalledGameRequest);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnInstalledGameAssetsDownloadRequest);
    Connect(ID_MENUITEM14,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnSelectiveGameMigration);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnInstalledGameRenameRequest);
    Connect(ID_MENUITEM11,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnManualInjectionRequest);
    Connect(ID_MENUITEM12,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnLoadCustomIcon2InstalledGameRequest);
    Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnGameInfoRequest);
    Connect(DELETE_GAME_ID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnGameDeletionRequest);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnClose);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&HDL_Batch_installerFrame::OnPaint);
    //*)
}

void cache_cleanup(void)
{
    if(wxFileExists(HDL_CACHE))
    {
        COLOR(08) std::cout << "> Cleaning HDL Cache\n";
        COLOR(07) wxRemoveFile("./info.sys");
    }
    if(wxFileExists(MBR_CACHE))
    {
        COLOR(08) std::cout << "> Cleaning MBR Cache\n";
        COLOR(07) wxRemoveFile("./MBR.KELF");
    }
}

HDL_Batch_installerFrame::~HDL_Batch_installerFrame()
{
    //(*Destroy(HDL_Batch_installerFrame)
    //*)
}

void HDL_Batch_installerFrame::OnQuit(wxCommandEvent& event)
{
    cache_cleanup();
    exit(0);
}


bool HDL_Batch_installerFrame::is_PS2(wxString path)
{
    wxString CMD = wxString::Format("HDL.EXE cdvd_info \"%s\"",path), result_;
    wxArrayString result, errorBuffer;
    std::string couterr;
    long program_return_value = wxExecute(CMD,result,errorBuffer);
    if (program_return_value == 0)
    {
        if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
        {
            for (size_t x=0; x<result.GetCount(); x++)
            {
                result_ += result.Item(x);   //pass contents of array into a single string
            }
            COLOR(08)
            cout << ">\t["<< result_ << "]\n";
        }
        COLOR(0a)
        cout << "is a PS2 Game\n";
        COLOR(07)
        return true;
    }
    else
    {
        COLOR(0c) std::cerr << " Error\n";
        for (size_t x=0; x<errorBuffer.GetCount(); x++)
        {
            couterr += errorBuffer.Item(x);
        }
        cerr <<"\t" << couterr <<"\n";
        COLOR(07)
        return false;
    }
}

void HDL_Batch_installerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf("version %i.%i.%i [%s]-[%s]\n\n Revision: %i\n build date: %s-%s-%s",
               AutoVersion::MAJOR,
               AutoVersion::MINOR,
               AutoVersion::BUILD,
               AutoVersion::STATUS,
#if (BITS == 32)
               "32 bits",
#elif (BITS == 64)
               "64 bits",
#endif
               AutoVersion::REVISION,
               AutoVersion::DATE,
               AutoVersion::MONTH,
               AutoVersion::YEAR
              );
    wxMessageBox(msg, "HDL Batch Installer");
    About About_DLG(this);
    About_DLG.ShowModal();
}

void HDL_Batch_installerFrame::OnRadioButton1Select(wxCommandEvent& event)
{
    cout << "selected Local HDD\n";
    selected_hdd->Enable();
}

void HDL_Batch_installerFrame::OnNotebook1PageChanged(wxNotebookEvent& event)
{}

void HDL_Batch_installerFrame::OnTextCtrl1Text(wxCommandEvent& event)
{}

void HDL_Batch_installerFrame::OnListBox1Select(wxCommandEvent& event)
{}

void HDL_Batch_installerFrame::OnCheckListBox1Toggled(wxCommandEvent& event)
{}

void HDL_Batch_installerFrame::OnListCtrl1BeginDrag(wxListEvent& event)
{}

void HDL_Batch_installerFrame::OnSEARCH_ISOClick(wxCommandEvent& event)
{
    if((wxFileExists(MiniOPL)==false) && (CFG::MINIOPL_WARNING==1))
    {
        wxMessageBox(_("OPL Launcher is missing.\n you must get a copy of MiniOPL from the GitHub repo and place it back with the program before Installing games,\n otherwise... your PS2 games won't be executed from HDD-OSD"), warning_caption, wxICON_WARNING);
        COLOR(0e) cout << "> WARNING, boot.kelf is Missing...\n";
        COLOR(07)
    }
    wxBeginBusyCursor();

    COLOR(0f) cout << "Loading ISO's------------------------\n";
    COLOR(07)
    ISO_SEARCH_DIALOG = new wxFileDialog(this,
                                         _("Select your PS2 games"),
                                         CFG::DEFAULT_ISO_PATH,
                                         "",
                                         wxString::Format("%s|*.ISO;*.CUE;*.NRG;*.GI;*.IML;*.ZSO|%s|*.ISO|%s|*.cue|%s|*.nrg|%s|*.gi|%s|*.iml|%s|*.zso",
                                                 _("All supported formats (*.ISO;*.CUE;*.NRG;*.GI;*.IML;*.ZSO)"),
                                                 _("ISO 9660 (*.ISO)"),
                                                 _("CDRWIN cuesheets (*.cue)"),
                                                 _("Nero images (*.nrg)"),
                                                 _("Global images (*.gi)"),
                                                 _("IML files (*.iml)"),
                                                 _("lz4 Compressed Image Files (*.zso)") ),
                                         wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE,
                                         wxDefaultPosition,
                                         wxDefaultSize,
                                         _T("wxFileDialog")
                                        );
    wxArrayString ISO_PATHS;
    int valid_gamecount = 0, invalid_gamecount = 0;
    wxString path;
    if (ISO_SEARCH_DIALOG->ShowModal() == wxID_OK)
    {
        ISO_SEARCH_DIALOG->GetPaths(ISO_PATHS);
        std::cout << "loaded ISO's: " << ISO_PATHS.GetCount() <<std::endl;
        for (size_t game_count = 0; game_count < ISO_PATHS.GetCount(); game_count++ )
        {
            path = ISO_PATHS.Item(game_count);
            std::cout << path << "\n";
            if (is_PS2(path))
            {
                game_list__->InsertItem(0,path);
                valid_gamecount++;
            }
            else
            {
                invalid_gamecount++;
            }
        }
        wxString msg;
        if (valid_gamecount > 0)
        {
            msg.append(_("Loaded:"));
            msg.append(wxString::Format(" %i ", valid_gamecount) );
            msg.append(_("PS2 Games"));
        }
        msg.append("\n");
        if (invalid_gamecount > 0)
        {
            msg.append(_("discarded"));
            msg.append(wxString::Format(" %i ", invalid_gamecount) );
            msg.append(_("invalid ISO's"));
        }
        wxMessageBox(msg, _("Information:"));
    }
    COLOR(0f) cout << "Loaded ISO's------------------------\n";
    COLOR(07)
    wxEndBusyCursor();
}

void HDL_Batch_installerFrame::OnTextCtrl1Text1(wxCommandEvent& event)
{
}

void HDL_Batch_installerFrame::OnClose(wxCloseEvent& event)
{
    cache_cleanup();
    exit(0);
}
void HDL_Batch_installerFrame::Onselected_hddSelect(wxCommandEvent& event)
{
    Update_hdd_data();
}

void HDL_Batch_installerFrame::OnButton1Click(wxCommandEvent& event)
{
    const wxString command = "HDL.EXE query";
    wxArrayString result;
    wxString line, hdd_number;
    wxFileName fname( wxTheApp->argv[0] );
    wxString HDL_DUMP = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "HDL.EXE";

    if(!wxFileExists(HDL_DUMP))
    {
        Component_error error_dlg(this);
        error_dlg.ShowModal();
    }
    wxBeginBusyCursor();

    selected_hdd->Clear();
    int HDDCount = 0;
    wxExecute(command,result);
    for (size_t index = 0; index < result.GetCount(); index++)
    {
        line = result.Item(index);
        if (line.find("hdd") == NOT_FOUND) continue;
        hdd_number = line.Mid(4,1);
        if (!(line.find("Playstation") == NOT_FOUND)) // if "playstation" found, we've encountered a ps2 hdd
        {
            selected_hdd->Append(line.substr(1,line.find_first_of(':')));

            COLOR(0a) cout << line <<endl;
            COLOR(07)

            HDDCount++;
        }
        else
        {
            cout << line <<endl;
        }
    }
    wxEndBusyCursor();

    if (HDDCount == 0)
    {
        wxMessageBox(_("no PS2 HDD's Found"),_("warning"),wxICON_EXCLAMATION);
    }
    if (selected_hdd->GetCount() == 1)
    {
        selected_hdd->SetSelection(0);
        Update_hdd_data();
    }
    if (HDDCount > 1)
    {
        CAN_COPY_HDD = true;
        COPYHDD->Enable();
    }
    COPYHDD->Enable();
}

void HDL_Batch_installerFrame::OnListCtrl1BeginDrag1(wxListEvent& event) {}

void HDL_Batch_installerFrame::OnParse_hdl_tocClick(wxCommandEvent& event)
{
    List_refresh_request();
}

void HDL_Batch_installerFrame::OninstallClick(wxCommandEvent& event)
{
    int not_enough_space_count = 0;
    wxString messagebuffer, HIDE_SWITCH, strr, msg, command1;
    wxString hddd = selected_hdd->GetString(selected_hdd->GetSelection());
    long original_item_count = game_list__->GetItemCount();
    long installation_retcode;

    wxBeginBusyCursor();

    HIDE_SWITCH = (CFG::OSD_HIDE) ? " -hide" : "";
    if (original_item_count == 0)// IF gamelist is empty, get out
    {
        wxMessageBox(_("no games selected for installation"), error_caption,wxICON_EXCLAMATION);
        wxEndBusyCursor();
        return;
    }

    if ( (!wxFileExists(EXEC_PATH+"Common\\Icons.INI")) && (CFG::LOAD_CUSTOM_ICONS))
    {
        wxEndBusyCursor();
        ask_2_download_icons();
        wxBeginBusyCursor();
    }
#if PFSSHELL_ALLOWED
    PFSSHELL.CloseDevice(); //PFSShell with device attached will make HDL Dump write features crash
#endif
    std::cout <<"game count: "<< original_item_count<<std::endl;
    cout << "> begining installation...\n";
    install_progress = new wxProgressDialog(_("Installing"), wxEmptyString, original_item_count, this, wxPD_APP_MODAL|wxPD_ELAPSED_TIME|wxPD_SMOOTH|wxPD_AUTO_HIDE);
    /// /////////////////////////////////MAIN INSTALL LOOP///////////////////////////////// ///
    //for (int current_index = 0; current_index < game_list__->GetItemCount(); current_index++)
    int report_counter = 0;
    wxArrayString _filepath,
                  _reason,
                  _ELF,
                  _media
//                   _DBA,
                  ;

    while (game_list__->GetItemCount() > 0)
    {
        command1.clear();
        if (install_progress->WasCancelled()) break;
        int current_index = (original_item_count - game_list__->GetItemCount());
        strr = game_list__->GetItemText(0,0);
        wxString resultt;
        std::cout << "\n>index: " << current_index <<std::endl;
        msg = _("installing: ");
        msg.append(strr);
        install_progress->Update(current_index, msg.substr(msg.find_last_of("\\")+1));
        wxString ELF, title;
        std::string inject_mode;
        ///-------------------------------PULL DATA
        wxArrayString result;
        wxString command0;
        command0.clear();
        command0.Printf("HDL.EXE cdvd_info2 \"%s\"",strr);
        result.Clear();
        wxExecute(command0,result);
        ///------------------------------/PULL DATA
        resultt.clear();//clear buffer
        cout << result.Item(0) << endl;    ///write output to log
        resultt = result.Item(0); //pass data from array to single string
        if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) ) cout << "count(cdvd_info2): " << result.GetCount()<<std::endl;

        inject_mode = (resultt.StartsWith("CD")) ? "inject_cd " : "inject_dvd ";
        std::cout << "media: " << inject_mode <<std::endl;
        ///ID
        size_t z;
        z = resultt.find_first_of("\""); //1st one
        z = resultt.find_first_of("\"",z + 1); //2nd one
        z = resultt.find_first_of("\"",z + 1); //3rd one
        ELF = resultt.Mid(z+1); ///DEJO ACAz
        ELF = ELF.substr(0,ELF.find_last_of("\""));
        /// READ DATABASE
        title = get_gamename(std::string(ELF.mb_str()), CFG::DBMODE, CFG::DBENABLE); //retrieve gamename from Database
        if (title == NO_MATCH) //if not found || databse usage disabled
        {
            title = strr.substr(strr.find_last_of("\\") + 1); //use Filename instead
            title = title.substr(0, title.find_last_of('.') ); //cut extension
        }
        while (title.EndsWith(' '))
            title.RemoveLast(1); //clean trailing whitespaces
        int DD = dma_choice->GetSelection();
        ///           hdl_dump    !disctype!   !hdlhdd!      "!title!"         "!filename!"  !gameid!       *u4             -hide
        //command1 = "HDL.EXE " + inject_mode + hddd + " \"" + title + "\" \"" + strr + "\" " + ELF + " " + DMA_TABLE[DD] + HIDE_SWITCH;
        if (CFG::LOAD_CUSTOM_ICONS)
            Load_custom_icon(ELF);
        command1.Printf("HDL.EXE %s %s \"%s\" \"%s\" %s %s %s",
                        inject_mode, hddd, title, strr, ELF, DMA_TABLE[DD], HIDE_SWITCH);
        COLOR(0f )std::cout << "---\n"
                            << " inject_mode: [" << inject_mode
                            << "]\n hdd_target: [" << hddd
                            << "]\n title: [" << title << "]"
                            << "\n ISO_PATH: ["<< strr << "] "
                            << "\n ELF ["<< ELF <<"]"
                            << "\n DMA: "<< DMA_TABLE[DD]
                            << "\n Hide_switch: " << HIDE_SWITCH
                            << "\n---\n"
                            << command1 <<"\n";
        COLOR(0d)
        installation_retcode = wxExecute(command1.ToUTF8(),wxEXEC_SYNC);
        COLOR(08)
        //if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
        cout << "\n>returned value [" << installation_retcode <<"]\n";
        COLOR(07)

        if (installation_retcode != 0 && installation_retcode != -1073741819)
        {
            report_counter++;
            _filepath.Add(strr);
            _ELF.Add(ELF);
            _media.Add(wxString::Format("%il",installation_retcode));
            if( installation_retcode == RET_NO_SPACE)
            {
                _reason.Add(_("There is not enough space on the HDD to install this game"));
                not_enough_space_count++;
            }
            else if( installation_retcode == RET_NO_MEM)
                _reason.Add(_("HDL-Dump reported \"Out of memory\"."));

            else if( installation_retcode == RET_NOT_APA)
                _reason.Add(_("not a PlayStation 2 HDD."));

            else if ( installation_retcode == RET_PART_EXISTS)
                _reason.Add(_("A game with this name is already installed"));

            else if ( installation_retcode == RET_BAD_SYSCNF)
                _reason.Add(_("The game has a corrupt SYSTEM.CNF file"));

            else if ( installation_retcode == RET_FILE_NOT_FOUND)
                _reason.Add(_("File could not be found (or accesed?)"));

            else if ( installation_retcode == RET_BROKEN_LINK)
                _reason.Add(_("CUE or IML have a missing linked file"));

            else if ( installation_retcode == RET_MULTITRACK)
                _reason.Add(_("bin/cue with multiple .bin files are not supported, combine them into a single bin"));

            else
                _reason.Add("Unhandled error...");
        }
        game_list__->DeleteItem(0);

        if (not_enough_space_count > 3)
        {
            wxMessageBox(_("Installation process aborted, HDD is running out of space"), warning_caption, wxICON_WARNING);
            break;
        }

    }/// /////////////////////////////////MAIN INSTALL LOOP///////////////////////////////// ///
    COLOR(08) std::cout << endl << "> installation process finished.\n";
    delete install_progress;
    COLOR(07)
    ///
    if (report_counter != 0)
    {
        Post_Install_Report* REPORT = new Post_Install_Report(this,_filepath,_reason,_ELF,_media);
        REPORT->ShowModal();
        delete REPORT;
    }
    std::cout << "> Updating HDD information...\n";
    Update_hdd_data();
    if (wxFileExists(HDL_CACHE))//Clean BBNav cache
    {
        COLOR(08) cout << "> erasing \"info.sys\" \n";
        COLOR(07)
        wxRemoveFile(HDL_CACHE);
    }
    if (wxFileExists(EXEC_PATH + "list.ico"))
    {
        COLOR(08) cout << "> erasing \"list.ico\" \n";
        COLOR(07)
        wxRemoveFile(EXEC_PATH + "list.ico");
    }
    wxEndBusyCursor();
    wxBell();
}

void HDL_Batch_installerFrame::OnCheckBox1Click(wxCommandEvent& event)
{}

void HDL_Batch_installerFrame::OnSettings(wxCommandEvent& event)
{
    Config configmenu(this);
    configmenu.ShowModal();
}

void HDL_Batch_installerFrame::OnPaint(wxPaintEvent& event)
{
    if (first_init==true)
    {
        return;
    }
    else
    {
        ACTIVATE_DEBUG_LOG()
        wxFileName fname( wxTheApp->argv[0] );
        wxString config_file = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "Common\\config.INI";
        wxFileConfig * main_config = new wxFileConfig( wxEmptyString, wxEmptyString, config_file);
        if(wxFileExists(config_file))
        {
            COLOR(08) cout << "> Config File Loaded!\n";
        }
        else
        {
            COLOR(0c) cerr << "Can't load config file!\n  Loading default values\n";
        }
        main_config->Read("Installation/DataBase_Mode", &CFG::DBMODE, DB_INTERNAL);
        main_config->Read("Init/Debug_level", &CFG::DEBUG_LEVEL, 5);
        main_config->Read("Installation/MiniOPL", &CFG::MINIOPL_WARNING, 1);
        main_config->Read("Installation/OSD_Hide", &CFG::OSD_HIDE, 0);
        main_config->Read("Game_search/Default_iso_path", &CFG::DEFAULT_ISO_PATH, "C:\\");
        main_config->Read("Installation/Default_dma", &CFG::DMA, 7);
        main_config->Read("Installation/Custom_icons", &CFG::LOAD_CUSTOM_ICONS, true);
        main_config->Read("FUSE/default_mountpoint", &CFG::mountpoint, "X");
        main_config->Read("FUSE/opl_partition", &CFG::default_OPLPART, "+OPL");
        main_config->Read("Installation/inform_unknown_ID", &CFG::SHARE_DATA, false);
        main_config->Read("NBD/Default_IP", &CFG::NBD_IP, "");
        main_config->Read("FEATURES/allow_experimental", &CFG::ALLOW_EXPERIMENTAL, false);
        NBD4IP->Clear();
        NBD4IP->SetValue(CFG::NBD_IP);
//        main_config->Read("Init/Check_for_Updates",&CFG::UPDATE_WARNINGS,false);
        COLOR(08)
        cout <<"database mode="     << CFG::DBMODE                                     <<endl;
        cout <<"debug level="       << CFG::DEBUG_LEVEL                                <<endl;
        cout <<"MiniOPL="           << CFG::MINIOPL_WARNING                            <<endl;
        cout <<"OSD_Hide="          << CFG::OSD_HIDE                                   <<endl;
        cout <<"Default_iso_path="  << std::string(CFG::DEFAULT_ISO_PATH.mb_str())     <<endl;
        cout <<"Default DMA Mode="  << DMA_TABLE[CFG::DMA]                             <<endl;
        cout <<"Custom Icon Loader="<< CFG::LOAD_CUSTOM_ICONS                          <<endl;
        cout <<"Report Unknown Game ID's="<< CFG::SHARE_DATA                                 <<endl;
        cout <<"Game Title Database, "<<GAME_AMOUNT<<" ID's registered\n";
        COLOR(07)
        delete main_config;
        fname = wxTheApp->argv[0];

        EXEC_PATH   = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR);
        HDL_CACHE   = EXEC_PATH + "info.sys";
        MBR_CACHE   = EXEC_PATH + "MBR.KELF";
        MiniOPL     = EXEC_PATH + "boot.kelf";
        ICONS_FOLDER= EXEC_PATH + "Common\\ICNS\\";
        first_init = true;
        if (!wxDirExists(ICONS_FOLDER)) wxMkDir(ICONS_FOLDER);
    }
}

void HDL_Batch_installerFrame::OnCheckBox1Click1(wxCommandEvent& event)
{
    CFG::DBENABLE = use_database->IsChecked();
    std::cout <<"> use database ="<<CFG::DBENABLE<<std::endl;
}

void HDL_Batch_installerFrame::OnMBR_EVENTClick(wxCommandEvent& event)
{
    wxString MBR_PATH, command, output_string;
    wxArrayString output;
    wxFileName fname( wxTheApp->argv[0] );
    wxString MBR_HOME = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "MBR.KELF";
    wxString label = selected_hdd->GetString(selected_hdd->GetSelection());
    if (MBR_search->ShowModal() == wxID_OK)
    {
        MBR_PATH = MBR_search->GetPath();
        cout << "copying\n" << MBR_PATH <<"\n to:\n" <<MBR_HOME<<"\n";
        if (wxCopyFile(MBR_PATH,MBR_HOME,true)==false) //if copy failed...
            wxMessageBox(_("can't Load MBR.KELF"), "ERROR", wxICON_ERROR);
        else
        {
            command = "HDL.EXE inject_mbr " + label + " MBR.KELF";
            wxExecute(command,output);
            for (size_t x=0; x< output.GetCount(); x++)
            {
                output_string += output.Item(x);
                output_string += "\n";
            }
            cout << output_string << "\n";
        }
    }
    else
    {
        COLOR(08) cout<<"> operation cancelled\n";
    }

    if (wxFileExists("./MBR.KELF"))
        {
            COLOR(08) cout <<"> Cleaning MBR.KELF cache.\n";
            wxRemoveFile("./MBR.KELF");
        }
    COLOR(07)
}

void HDL_Batch_installerFrame::OnButton2Click(wxCommandEvent& event)
{
    wxMessageBox(_("work in progress"),"sorry",wxICON_WARNING);
    // modify_header mhw(this);
    // mhw.ShowModal();
}

void HDL_Batch_installerFrame::Onclear_iso_listClick(wxCommandEvent& event)
{
    if (game_list__->GetItemCount() == 0)// IF gamelist is empty, get out
    {
        wxMessageBox(_("Game list is already empty"),"",wxICON_EXCLAMATION);
        return;
    }
    else
    {
        if(wxMessageBox("",_("Clear List??"),wxICON_QUESTION | wxYES_NO) ==wxYES)
        {
            game_list__->DeleteAllItems();
            COLOR(08) cout<<"> cleaning game list\n";
            COLOR(07)
        }
    }
}

void HDL_Batch_installerFrame::OnUpdateRequest(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://github.com/israpps/HDL-Batch-installer/releases");
}

void HDL_Batch_installerFrame::OnIssueReport(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://github.com/israpps/HDL-Batch-installer/issues");
}


void HDL_Batch_installerFrame::Selected_games(wxListEvent& event)
{
}

void HDL_Batch_installerFrame::UnSelected_games(wxListEvent& event)
{
}

void HDL_Batch_installerFrame::Onpull_isoClick(wxCommandEvent& event)
{
}

void HDL_Batch_installerFrame::Ondma_choiceSelect(wxCommandEvent& event)
{
    if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
    {
        int X = dma_choice->GetSelection();
        COLOR(08) cout << "> Selected DMA Mode "<< X <<" ["<< DMA_TABLE[X] <<"]\n";
        COLOR(07)
    }
}
void HDL_Batch_installerFrame::Enable_HDD_dependant_objects(bool WTF_should_I_do)
{
    if (WTF_should_I_do)
    {
        Parse_hdl_toc->Enable();
        SEARCH_ISO->Enable();
        install->Enable();
        clear_iso_list->Enable();
        MBR_EVENT->Enable();
        dma_choice->Enable();
        mass_header_injection->Enable();
        MBRExtractRequest->Enable();
        FUSE->Enable();
#if PFSSHELL_ALLOWED
        HDDManagerButton->Enable(PFSSHELL_USABLE);
#else
        HDDManagerButton->Enable(true);
#endif
        ///this one has nothing to do
        Installed_game_list->DeleteAllItems();
    }
    else
    {
        Parse_hdl_toc->Disable();
        SEARCH_ISO->Disable();
        install->Disable();
        clear_iso_list->Disable();
        MBR_EVENT->Disable();
        dma_choice->Disable();
        mass_header_injection->Disable();
        MBRExtractRequest->Disable();
        FUSE->Disable();
        HDDManagerButton->Disable();
    }
}

void HDL_Batch_installerFrame::Update_hdd_data(void)
{
    Enable_HDD_dependant_objects(false);///Temporarly disble just in case data parsing fails
    ///MAKE SURE TO RE-ENABLE EVERYTHING THAT WAS DISABLEd HERE INSIDE THE 'if (toc_ret == 0)' BLOCK
    wxString command;
    wxString label = selected_hdd->GetString(selected_hdd->GetSelection());
    HDD_TOKEN = wxString::Format("\\\\.\\PHYSICALDRIVE%s", label.SubString(3, label.find(':')-1));
    cout << "selected "<< label <<endl;
    command.Printf("HDL.EXE toc %s",label);
    wxArrayString result,std_error;
    long toc_ret = wxExecute(command,result,std_error);
    wxString line, TMP;
    long int size_total, size_used, size_free;
    if (toc_ret == 0)
    {
        for(size_t x=0; x < result.GetCount(); x++) //Parse line-to-line :D
        {
            line = result.Item(x);


            if (line.find(", used") == NOT_FOUND)
                continue;
            else
            {
                if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
                    cout << line <<"\n";
                TMP =  line.SubString(line.find_first_of(":") + 2,line.find_first_of("MB") - 1);
                TMP.ToLong(&size_total);
                TMP.clear();
                int A = line.find_first_of(",") + 8,
                    B = line.find_first_of("MB",A)-1;
                TMP  = line.SubString(A, B);
                TMP.ToLong(&size_used);
                TMP.clear();
                TMP  = line.SubString(line.find_last_of(":") + 2,line.find_last_of("MB") - 2);
                TMP.ToLong(&size_free);
            }
        }
        std::cout << "total: ["<<size_total<<"]\nused:  ["<<size_used<<"]\nfree:  ["<<size_free<<"]\n";
        Gauge1->SetRange(size_total);
        Gauge1->SetValue(size_used);

        hdd_used_space->Clear();
        hdd_used_space->AppendText( wxString::Format(_("Total: %dGb | Used: %d%s | Free: %d%s"),
                                    (size_total / 1024),
                                    (size_used > 1024) ? (size_used / 1024) : size_used,
                                    (size_used > 1024) ? ("Gb") : "Mb",
                                    (size_free > 1024) ? (size_free / 1024) : size_free,
                                    (size_free > 1024) ? ("Gb") : "Mb"
                                                    ));
#if PFSSHELL_ALLOWED
        std::cout << "initializing libPS2HDD...\n";
        if (!PFSSHELL.SelectDevice(HDD_TOKEN.c_str()))
        {
            PFSSHELL_USABLE = true;
        } else {
            PFSSHELL_USABLE = false;
            wxMessageBox(("Error initializing libps2hdd service\n\nCheck log for more details\n\nHDD formatting and HDD Manager disabled"), wxMessageBoxCaptionStr, wxICON_WARNING);
        }
        PFSSHELL.CloseDevice();
        MenuHDDFormat->Enable(PFSSHELL_USABLE);
#endif
        Enable_HDD_dependant_objects(true); //re-enable & clean installed game list
    }
    else
    {
        COLOR(0c)
        cerr << "ERROR ---\n";
        for (size_t x = 0; x < std_error.GetCount(); x++)
            cerr << std::string(std_error.Item(x)) << "\n";
        cerr << "---------"<<std::endl;
        COLOR(07)
        if (toc_ret == RET_BAD_APA)
            wxMessageBox(_("The HDD is corrupted or your hard drive connection has issues"), _("APA Partition is broken"), wxICON_ERROR);
    }
}

void HDL_Batch_installerFrame::OnButton2Click1(wxCommandEvent& event)
{
}

void HDL_Batch_installerFrame::List_refresh_request()
{
    Installed_game_list->DeleteAllItems();
    wxArrayString result;
    wxString command = "HDL.EXE hdl_toc ";
    command.append(selected_hdd->GetString(selected_hdd->GetSelection()));

    std::cout << "listing games of "<< selected_hdd->GetString(selected_hdd->GetSelection()) << "\n\n";

    wxExecute(command,result);

    for(size_t x = 0; x < result.GetCount(); x++)
    {
        cout << result.Item(x) << "\n";
    }

    int media = MEDIA_DVD;
    std::string Gamename;
    long int gamesize;
    std::string ELF;
    wxString line;
    for(size_t x = 0; x < result.GetCount(); x++)
    {
        line = result.Item(x);
        if (line.Mid(0,1) =='t') continue;//if this is the first line then skip it


        if (line.Mid(0,1) =='C') media = MEDIA_CD;
        if (line.Mid(0,1) =='D') media = MEDIA_DVD;
        gamesize = wxAtoi(line.Mid(4,line.find_first_of("B") - 5));

        if (line.find('*') == NOT_FOUND)///if DMA mode is found use it to locate ELF and game title, ensuring compatibility with HDLGI
        {
            ELF = line.SubString(34, line.find_first_of(" ",34)-1);
            Gamename = line.substr( line.find_first_of(" ",34) +2 );
        }
        else     ///No DMA found, use hardcoded offsets that SHOULD ensure compatibility with winhiip
        {
            ELF = line.SubString(line.find('*') + 4, line.find_first_of(" ",line.find('*') + 4)-1);
            Gamename = line.substr( line.find_first_of(" ",line.find('*') + 4) +2 );
        }
        ///VALUE ASSINGMENT
        long itemIndex = Installed_game_list->InsertItem(0, Gamename);// col. 1
        Installed_game_list->SetItem(itemIndex, 1, ELF); // col. 2
        Installed_game_list->SetItem(itemIndex, 2, wxString::Format(wxT("%i"),gamesize / 1024)); //col. 3
        if (media == MEDIA_CD)
            Installed_game_list->SetItem(itemIndex, 3, "CD"); //col. 4
        else
            Installed_game_list->SetItem(itemIndex, 3, "DVD"); //col. 4
    }
    if (result.GetCount() <= 2) wxMessageBox(_("This HDD has no PS2 Games inside"), error_caption);
}

void HDL_Batch_installerFrame::On_MiniOPL_Update_request(wxCommandEvent& event)
{
    wxString cmd = "common\\wget.exe -q --show-progress " + MiniOPL_URL + " -O \"" + MiniOPL + "\"";
    COLOR(0d)
    if (wxExecute(wxString::Format("common\\wget.exe -q --spider --no-cache \"%s\"", MiniOPL_URL)) == 0)
        wxExecute(cmd,wxEXEC_SYNC);
    COLOR(07)
}

void HDL_Batch_installerFrame::OnButton2Click3(wxCommandEvent& event)
{
#if PFSSHELL_ALLOWED
    HDDManager *MANAGER = new HDDManager(this, HDD_TOKEN);
    MANAGER->ShowModal();
    delete MANAGER;
#else
    PFSSHELL_DISABLED_WARNING();
#endif
}

void HDL_Batch_installerFrame::OnHDL_DumpUpdateRequest(wxCommandEvent& event)
{
    wxString HDL_DUMP       = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "HDL.EXE";
    wxString HDL_DUMP_URL   = "https://github.com/israpps/hdl-dump/releases/download/hdlinst/HDL.EXE";
    wxString cmd = "common\\wget.exe -q --show-progress " + HDL_DUMP_URL + " -O \"" + HDL_DUMP + "\"";
    COLOR(0d)
    if (wxExecute(wxString::Format("common\\wget.exe -q --spider --no-cache \"%s\"", HDL_DUMP_URL)) == 0)
        wxExecute(cmd,wxEXEC_SYNC);
    COLOR(07)
}

void HDL_Batch_installerFrame::Onart_requestClick(wxCommandEvent& event)
{}

void HDL_Batch_installerFrame::Onprint_partition_tableClick(wxCommandEvent& event)
{
}


void HDL_Batch_installerFrame::Onmass_header_injectionClick(wxCommandEvent& event)
{
    wxString system_cnf  = EXEC_PATH + "system.cnf";
    wxString icon_sys    = EXEC_PATH + "icon.sys";
    wxString icon_icn    = EXEC_PATH + "list.ico";
    wxString logo_raw    = EXEC_PATH + "logo.raw";
    wxString boot_kirx   = EXEC_PATH + "boot.kirx";
    wxString boot_elf    = EXEC_PATH + "boot.elf";
    wxString boot_kelf   = EXEC_PATH + "boot.kelf";
    wxString partition, inject_header_cmd;
    int partcount = 0;

    if(!wxFileExists(boot_kelf))
    {
        COLOR(0c)
        wxMessageBox( _("Warning\n\tCan't find boot.kelf\n\nAborting APA Injection"), error_caption,wxICON_WARNING);
        cerr << "no boot.kelf to inject\n";
        COLOR(07)
        return;
    }

    long KELF_size;
    if (wxFileExists(boot_kelf))  /// IF boot.kelf exists check if it's size is ok
    {
        KELF_size = GetFileSize("boot.kelf");
        if (KELF_size >= 2031616)///Size limitation taken from HDL-Dump readme [https://github.com/israpps/hdl-dump#modify_header]
        {
            COLOR(0c)
            wxMessageBox(_("file boot.kelf is too big!\n\nit's size can't be larger than 2,031,616 bytes"), error_caption, wxICON_ERROR);
            cerr << "boot.kelf is too big!\n\tExpected file to be smaller than 2031616 bytes\n\tprovided file is[" << KELF_size << "] bytes in length\n";
            COLOR(07)
            return;
        }
    }
    if( wxFileExists(system_cnf) )
    {
        wxRemoveFile(system_cnf);
    }
    if( wxFileExists(icon_sys)   )
    {
        wxRemoveFile(icon_sys);
    }
    if( wxFileExists(logo_raw)   )
    {
        wxRemoveFile(logo_raw);
    }
    if( wxFileExists(boot_kirx)  )
    {
        wxRemoveFile(boot_kirx);
    }
    if( wxFileExists(boot_elf)   )
    {
        wxRemoveFile(boot_elf);
    }
    if( wxFileExists(icon_icn)   )
    {
        wxRemoveFile(icon_icn);
    }

    wxBeginBusyCursor();
    wxString command = "HDL.EXE toc " + selected_hdd->GetString( selected_hdd->GetSelection() );
    wxString line,partname;
    wxString HDD = selected_hdd->GetString( selected_hdd->GetSelection() );
    wxArrayString output,partitions;
    COLOR(08) cout << "> Obtaining partition table...\n";
    COLOR(07)
    wxExecute(command,output,wxEXEC_SYNC);
    for (size_t x=0; x<output.GetCount(); x++)//parse partition table looking for HDL Partitions (AKA: games)
    {
        line = output.Item(x);
        if ( line.find("0x1337") != NOT_FOUND)
        {
            if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
            {
                cout << "found game\n";
            }
            partname = line.substr( line.find_first_of("B") +2);   ///get partition name, it should be two chars after the 'B', it needs testing
            /*           while (partname.EndsWith(' '))///strip whitespaces
                       {
                           partname.RemoveLast(1);
                       }*/ // not needed now since I made a PR to hdl-dump that removes the whitespace filling from partition listing
            partitions.Add(partname);
            partcount++;
        }
        else
        {
            if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
            {
                std::cout << "skipping [" << line << "]\n";
            }
        }
    }
    wxProgressDialog* DLG = new wxProgressDialog(_("Injecting OPL Launcher to..."), wxEmptyString, partcount, this);
    COLOR(08) cout <<"> writing headers...\n";
    COLOR(07)
    //DLG->ShowModal();
    for (size_t x=0; x<partitions.GetCount(); x++)//traverse the list of partitions to inject
    {
        partition = partitions.Item(x);
        DLG->Update(x, partition);
        cout << "\t[" <<partition <<"]\n";
        inject_header_cmd = "HDL.EXE modify_header " + HDD + " \"" + partition + "\"";
        if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
        {
            COLOR(08)
            cout << inject_header_cmd << endl;
        }
        COLOR(0d)
        wxExecute(inject_header_cmd, wxEXEC_SYNC);
        COLOR(07)
    }
    wxEndBusyCursor();
    delete DLG;
    wxMessageBox( _("Header Injection finished"),"",wxICON_INFORMATION );
}

void HDL_Batch_installerFrame::OnmodifyClick(wxCommandEvent& event)
{
}

void HDL_Batch_installerFrame::onItemRightClick(wxListEvent& event)
{
    //wxContextMenuEvent();
    //wxContextMenuEvent()

    PopupMenu(&about_2_install_menu);
}

void HDL_Batch_installerFrame::OnGoToFileLocationRequest(wxString victim)
{
    wxExecute( wxString::Format("explorer.exe \"/select,%s\"", victim) );
}

void HDL_Batch_installerFrame::OnItemListShowRequest(wxCommandEvent& event)
{
    long itemIndex = -1;
    if ( (itemIndex = game_list__->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        OnGoToFileLocationRequest( game_list__->GetItemText(itemIndex));
}

void HDL_Batch_installerFrame::OnTakeOutFromTheListRequest(wxListCtrl* ListCtrl, long itemIndex)
{
    ListCtrl->DeleteItem(itemIndex);
}

void HDL_Batch_installerFrame::RemoveISOfromList(wxCommandEvent& event)
{
    long itemIndex = -1;
    if ( (itemIndex = game_list__->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        OnTakeOutFromTheListRequest(game_list__, itemIndex);
}

void HDL_Batch_installerFrame::OnExtractInstalledGameRequest(wxCommandEvent& event)
{
    long itemIndex = -1;
    int ripcount = 0, currrip=0;
    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        ripcount++;
    itemIndex = -1;//reset index counter for the real iteration

    wxString game_title, game_title2,extraction_path, full_extraction_path;
    wxString hdd = selected_hdd->GetString(selected_hdd->GetSelection());
    wxString command;

    dump_folder = new wxDirDialog(this, _("Choose path to extract selected games"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));

    if (dump_folder->ShowModal() == wxID_OK)
    {
        wxProgressDialog* DLG = new wxProgressDialog(_("extracting game..."), "", ripcount, this);
        extraction_path = dump_folder->GetPath();
        cout << std::string(extraction_path.mb_str()) <<"\n";
        while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        {
            full_extraction_path.clear();
            game_title.clear();
            game_title = Installed_game_list->GetItemText(itemIndex);// Got the selected item index
            if (game_title[0]==' ') game_title = game_title.Mid(1);
            DLG->Update(currrip++, game_title);
            cout <<"\nExtracting game ["<< game_title <<"]\n";
            game_title2 = game_title;
            COLOR(08) cout << "> Filtering illegal characters...\n";
            ///Filter windows illegal characters for filename
            game_title2.Replace(':', '_',true);
            game_title2.Replace('/', '_',true);
            game_title2.Replace('\\','_',true);
            game_title2.Replace('<', '_',true);
            game_title2.Replace('>', '_',true);
            game_title2.Replace('*', '_',true);
            game_title2.Replace('"', '_',true);
            game_title2.Replace('|', '_',true);
            game_title2.Replace('?', '_',true);
            // wxString::Replace(
            //-----------------------------------
            full_extraction_path = extraction_path + "\\" + game_title2 + ".ISO";
            cout <<"  to: ["<< full_extraction_path <<"]\n";
            command = "HDL.EXE dump \"" + std::string(game_title.mb_str()) + "@" + std::string(hdd.mb_str()) + "\" \"" + std::string(full_extraction_path.mb_str()) + "\"";
            if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
            {
                COLOR(08)cout <<command<<"\n";
                COLOR(07)
            }
            COLOR(0d)
            wxExecute(command,wxEXEC_SYNC);
            //crude_SystemCapture(command);
            COLOR(07)
        }
        delete DLG;
    }

}

void HDL_Batch_installerFrame::OnInstalledGameRenameRequest(wxCommandEvent& event)
{
    long itemIndex = -1;
    wxString title,title_backup;
    wxString game_title, game_title2,extraction_path, full_extraction_path;
    wxString hdd = selected_hdd->GetString(selected_hdd->GetSelection());
    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        title = Installed_game_list->GetItemText(itemIndex);
        title_backup = title;
        rename_game = new wxTextEntryDialog(this, title_backup, "Rename game2",title_backup );
        if (rename_game->ShowModal() == wxID_OK)
        {
            title = rename_game->GetValue();
            wxArrayString stdout_,stderr_;
            wxString command = "HDL.EXE modify " + hdd + " \"" + title_backup + "\" \"" + title + "\"" ;
            COLOR(08) cout << command <<endl;
            COLOR(07)
            long ret = wxExecute(command, stdout_, stderr_);
            if (ret == 0)
            {
                for (size_t x=0; x < stdout_.GetCount(); x++)
                {
                    cout << stdout_.Item(x) <<endl;
                }
            }
            else
            {
                for (size_t x=0; x < stderr_.GetCount(); x++)
                {
                    cout << stderr_.Item(x) <<endl;
                }
            }
        }
        delete rename_game;
    }
    List_refresh_request();
}

void HDL_Batch_installerFrame::OnInstalledGameAssetsDownloadRequest(wxCommandEvent& event)
{
    long itemIndex = -1;
    wxArrayString ELF;
    wxString CURRENT_ELF;
    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        CURRENT_ELF = Installed_game_list->GetItemText(itemIndex,1);
        if (CURRENT_ELF.EndsWith(' '))
        {
            CURRENT_ELF.RemoveLast(1);
        }
        ELF.Add(CURRENT_ELF);// populate array with selected ELF's
    }
    ArtMan artman_dlg(this,ELF);///Create instance of download manager outside loop, the dialog will iterate the list on it's own
    artman_dlg.ShowModal();
}

void HDL_Batch_installerFrame::OnInstalled_game_listItemRClick1(wxListEvent& event)
{
    Browser_menu.Enable(DELETE_GAME_ID, CFG::ALLOW_EXPERIMENTAL);
    PopupMenu(&Browser_menu);
}

void HDL_Batch_installerFrame::OnButton3Click1(wxCommandEvent& event)
{
    wxMessageBox(_("Game related operations can be used by selecting games from the list and right clicking them..."),"",wxICON_INFORMATION);
}


void HDL_Batch_installerFrame::OnGameHashReques(wxCommandEvent& event)
{

}

long HDL_Batch_installerFrame::GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void HDL_Batch_installerFrame::OnGameInfoRequest(wxCommandEvent& event)
{
    wxString command, title, game_information;
    wxArrayString output;
    long itemIndex = wxNOT_FOUND;
    itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex != wxNOT_FOUND)
    {
        title = Installed_game_list->GetItemText(itemIndex);
        command = wxString::Format("HDL.EXE info %s \"%s\"",
                                   selected_hdd->GetString(selected_hdd->GetSelection()), title );
        wxExecute(command, output, wxEXEC_SYNC);
        for (size_t x=0; x<output.GetCount(); x++)
        {
            game_information << output.Item(x) << "\n";
        }
        wxMessageBox(game_information, wxString::Format(_("Report for [%s]"), title), wxICON_INFORMATION);
    }
}

void HDL_Batch_installerFrame::OnMBRExtractRequestClick(wxCommandEvent& event)
{
    long KELF_size, retcode;
    if (!wxDirExists("Extracted_MBR"))
        wxMkdir("Extracted_MBR");

    wxString kelfpath = "RECOVERED_MBR.KELF", command;
    if (wxFileExists(kelfpath)) kelfpath = wxString::Format("%dRECOVERED_MBR.KELF",rand());
    command = wxString::Format("HDL.EXE dump_mbr %s \"%s\"",
                               selected_hdd->GetString(selected_hdd->GetSelection()),kelfpath);
    cout << "saving MBR.KELF to ["<<kelfpath<<"]\n";
    retcode = wxExecute(command, wxEXEC_SYNC);
    if (retcode != 0)
    {
        wxMessageBox(_("MBR extraction failed!!\n\nsee console log to see error code..."),error_caption,wxICON_ERROR);
        return;
    }
    KELF_size = GetFileSize(std::string(kelfpath));
    if (KELF_size == 0)
        wxMessageBox(_("KELF size is 0 bytes!\nIt seems that this HDD had no MBR program installed...\n\n(or something went wrong)"),error_caption,wxICON_WARNING);
    else
        wxCopyFile(kelfpath, wxString::Format("Extracted_MBR\\%s", kelfpath));
    wxRemoveFile(kelfpath);
    cout << "Kelf size was: "<<KELF_size<<"\n";
}

void HDL_Batch_installerFrame::On_GameNameDatabaseDownloadRequest(wxCommandEvent& event)
{
    int database_mode;
    if (wxFileExists("gamename.DB"))
    {
        if (wxMessageBox(_("A local database already exists.\nDownloading the database from the repository will delete the old one...\n\n Continue?"),warning_caption,wxICON_WARNING|wxYES_NO) == wxNO)
            return;
    }

    if (wxFileExists("gamename.DB"))
        wxRemoveFile("gamename.DB");

    if (wxExecute("common\\wget.exe -q --spider --no-cache https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/Database/gamename.csv",wxEXEC_SYNC)==0)
        wxExecute("common\\wget.exe -q --show-progress https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/Database/gamename.csv -O gamename.DB",wxEXEC_SYNC);

    wxFileName fname( wxTheApp->argv[0] );
    wxString ini_filename = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "Common\\config.INI";
    wxFileConfig * main_config = new wxFileConfig( wxEmptyString, wxEmptyString, ini_filename);
    main_config->Read("Installation/DataBase_Mode", &database_mode, DB_INTERNAL);
    if (database_mode == DB_INTERNAL)
        wxMessageBox( _("The program is currently configured to use it's internal database.\nChange it on the settings menu in order to use the database you just downloaded"), warning_caption, wxICON_WARNING);
}
bool HDL_Batch_installerFrame::Load_custom_icon(wxString ELF)
{
    if (!wxFileExists(EXEC_PATH+"Common\\Icons.INI"))
    {
        ask_2_download_icons();
    }
    std::cout << "Searching custom icon: ";
    wxFileConfig* CNF = new wxFileConfig(wxEmptyString, wxEmptyString, EXEC_PATH+"Common\\Icons.INI");
    const wxString icon_icn = EXEC_PATH + "list.ico";
    if (wxFileExists(icon_icn)) wxRemoveFile(icon_icn);
    wxString icon_from_database;
    CNF->Read(wxString::Format("ICONS/%s",ELF),&icon_from_database,"NOT_FOUND");
    if (icon_from_database == "NOT_FOUND")
    {
        COLOR(0c)
        std::cout << "No custom icon found\n";
        if (CFG::DEBUG_LEVEL > 6 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL))
            std::cout <<"["<< ELF<<"]\n";
        COLOR(07)
        return false;
    }
    else
    {
        std::cout << "Found Custom icon!\n";
    }

    if (wxFileExists(ICONS_FOLDER+icon_from_database))
    {
        COLOR(0a)
        std::cout << "Loading icon ["<<icon_from_database<<"]\n";
        COLOR(07)
        wxCopyFile(ICONS_FOLDER+icon_from_database,icon_icn);
    }
    else
    {
        COLOR(0c) std::cerr << wxString::Format("> WARNING: Couldn't find icon specified by database\nELF:%s\nFILE:%s\n",ELF, icon_from_database);
        COLOR(07) return false;
    }
    delete CNF;
    return true;
}

void HDL_Batch_installerFrame::OnICONS_DOWNLOAD(void)
{
    wxArrayString unused_buffer;
    long ping = -1;
    ping = wxExecute("ping google.com", unused_buffer, wxEXEC_SYNC);
    if (ping != 0)
    {
        wxMessageBox(_("No internet connection!"), "", wxICON_WARNING);
        std::cerr << "PING Result ["<<ping<<"]\n";
        return;
    }
    const wxString DOWNLOAD_COMMAND    = "Common\\wget -q --show-progress https://github.com/israpps/HDL-Batch-installer/raw/main/svr/_ICN.7z -O Common\\_ICN.7z",
                   EXTRACTION_COMMAND = "Common\\7z.exe x -oCommon -bso0 -y -pPDPA Common\\_ICN.7z";
    COLOR(0e)
    std::cout << "Downloading package...\n";
    COLOR(0d)
    long retcode = wxExecute(DOWNLOAD_COMMAND,wxEXEC_SYNC);
    if (retcode != 0)
    {
        COLOR(0c)
        wxMessageBox(_("The download of the icons package failed!"), "", wxICON_ERROR);
        COLOR(07)
        return;
    }
    COLOR(07)
    retcode = wxExecute(EXTRACTION_COMMAND, wxEXEC_SYNC);
    if (retcode != 0)
    {
        wxMessageBox(_("The package extraction failed!"), "", wxICON_ERROR);
    }
    return;
}

void HDL_Batch_installerFrame::OnIconsPackageRequest(wxCommandEvent& event)
{
    OnICONS_DOWNLOAD();
}

void HDL_Batch_installerFrame::ask_2_download_icons(void)
{
    if(wxMessageBox(_("Can't find custom icons package\n\nDownload now?"),"",wxICON_QUESTION|wxYES_NO)==wxYES)
        OnICONS_DOWNLOAD();
}

bool Dokan_is_installed(void)
{
    return wxGetEnv(DOKAN_ENV, NULL) || wxGetEnv(DOKAN_ENV2, NULL);
}

void HDL_Batch_installerFrame::OnButton4Click(wxCommandEvent& event)
{
    if (!wxFileExists(HDLBINST_APPDATA+"\\dokan_and_fuse.ini"))
    {
        wxMessageBox(_("This is the first time you use PFSFUSE\n\nPLEASE, Keep in mind that, if you mount a partition you must unmount it when you finish using this program, otherwise, you could corrupt the mounted partition or the whole HDD"),
                     warning_caption,
                     wxICON_INFORMATION);
    }
    if (!Dokan_is_installed())
    {
        if(
            wxMessageBox(
                wxString::Format(_("Can't find the enviroment variables \"%s\" or \"%s\" used to locate the Dokan Library\n\n It seems like Dokan was unproperly installed (or it isn't installed)\n\nGo to Dokan download website?"),DOKAN_ENV, DOKAN_ENV2)
                ,error_caption,
                wxICON_ERROR|wxYES_NO
            )==wxYES) wxLaunchDefaultBrowser("https://github.com/dokan-dev/dokany/releases");

        return;
    }
    wxBeginBusyCursor();
    wxString HDD = selected_hdd->GetString( selected_hdd->GetSelection() );
    wxString command = "HDL.EXE toc " + HDD;
    wxString winapi_device_token = wxString::Format("\\\\.\\PHYSICALDRIVE%s", HDD.substr(3,HDD.find_first_of(':')-3));
    wxString line,partname;
    wxArrayString output,pfs_partitions;
    if (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL)
        std::cout <<"winapi_device_token["<<winapi_device_token<<"]\n";
    COLOR(08) cout << "Obtaining partition table...\n";
    COLOR(07)
    wxExecute(command,output,wxEXEC_SYNC);
    for (size_t x=0; x<output.GetCount(); x++)//parse partition table looking for HDL Partitions (AKA: games)
    {
        line = output.Item(x);
        if ( line.find("0x0100") != NOT_FOUND) //If PFS partition identifier detected, process data and load partition to array
        {
            partname = line.substr( line.find_first_of("B") +2,32);   ///get partition name, it should be two chars after the 'B', it needs testing
            /*while (partname.EndsWith(' '))///strip whitespaces
            {
                partname.RemoveLast(1);
            }*/ //not needed since I made a PR to hdl-dump to remove whitespace filling
            cout << "found Partition\n\t["<<partname<<"]\n";
            ///                      from B+2                  up to       1st whitespace after B+2
            pfs_partitions.Add(partname);
        }
        else
        {
            if (CFG::DEBUG_LEVEL > 5 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL) )
            {
                std::cout << "skipping this [" << line << "]\n";
            }
        }
    }
    wxEndBusyCursor();

    if (pfs_partitions.GetCount() < 1)
    {
        wxMessageBox(_("You need at least one PFS partition to use this menu"), _("Could not find PFS Partitions"), wxICON_WARNING);
        return;
    }

    DokanMan* DOKAN_WIZARD = new DokanMan(this, pfs_partitions, winapi_device_token);
    DOKAN_WIZARD->ShowModal();
    delete DOKAN_WIZARD;
}

void HDL_Batch_installerFrame::OnIP4NBDUpdate(wxCommandEvent& event)
{
    wxRegEx regxIPAddr("^(([0-9]{1}|[0-9]{2}|[0-1][0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]{1}|[0-9]{2}|[0-1][0-9]{2}|2[0-4][0-9]|25[0-5])$");
    wxString TMP = NBD4IP->GetValue();
    if (regxIPAddr.Matches(TMP))
    {
        NBDConnect->Enable();
    }
    else
    {
        NBDConnect->Disable();
    }
}

void HDL_Batch_installerFrame::OnNBDConnectClick(wxCommandEvent& event)
{
    if (!wxFileExists(HDLBINST_APPDATA+"\\NBD.ini"))
    {
        wxMessageBox(
            _("This is the first time you try to use NBD Server\nKeep in mind that you must disconnect the server when you finish using the Device\nOtherwise... There might be risk of HDD Damage")
            ,""
            ,wxICON_WARNING
        );
    }
    wxBeginBusyCursor();
    wxString command;
    command.Printf("Common\\WNBD\\wnbd-client.exe map PS2HDD %s", NBD4IP->GetValue());
    wxExecute(command,wxEXEC_SYNC);
    wxEndBusyCursor();
}

void HDL_Batch_installerFrame::OnNBDDisconnectClick(wxCommandEvent& event)
{
    wxString command = "Common\\WNBD\\wnbd-client.exe unmap PS2HDD";
    wxExecute(command);
}

void HDL_Batch_installerFrame::OnButton4Click1(wxCommandEvent& event)
{
    NDBMan* NBDManager= new NDBMan(this);
    NBDManager->ShowModal();
    delete NBDManager;
}

void HDL_Batch_installerFrame::OnManualInjectionRequest(wxCommandEvent& event)
{
    wxString HDD = selected_hdd->GetString( selected_hdd->GetSelection() );
    wxString system_cnf  = EXEC_PATH + "system.cnf";
    wxString icon_sys    = EXEC_PATH + "icon.sys";
    wxString icon_icn    = EXEC_PATH + "list.ico";
    wxString logo_raw    = EXEC_PATH + "logo.raw";
    wxString boot_kirx   = EXEC_PATH + "boot.kirx";
    wxString boot_elf    = EXEC_PATH + "boot.elf";
    wxString boot_kelf   = EXEC_PATH + "boot.kelf";

    if( wxFileExists(system_cnf) )
    {
        wxRemoveFile(system_cnf);
    }
    if( wxFileExists(icon_sys)   )
    {
        wxRemoveFile(icon_sys);
    }
    if( wxFileExists(logo_raw)   )
    {
        wxRemoveFile(logo_raw);
    }
    if( wxFileExists(boot_kirx)  )
    {
        wxRemoveFile(boot_kirx);
    }
    if( wxFileExists(boot_elf)   )
    {
        wxRemoveFile(boot_elf);
    }
    if( wxFileExists(icon_icn)   )
    {
        wxRemoveFile(icon_icn);
    }


    long itemIndex = -1, retcode;
    int prevcount = 0, x = 0;
    wxString title, command;
    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        prevcount++;
    itemIndex = -1;//reset counter for the real iteration
    wxProgressDialog* DLG = new wxProgressDialog(_("Injecting OPL Launcher to..."), wxEmptyString, prevcount, this);
    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        title = Installed_game_list->GetItemText(itemIndex);
        DLG->Update(x, title);
        command.clear();
        command.Printf("HDL.EXE modify_header %s \"%s\"", HDD, title);
        std::cout << "injecting ["<<title<<"]\n";
        COLOR(0d);
        retcode = wxExecute(command,wxEXEC_SYNC);
        COLOR(07);
        if (CFG::DEBUG_LEVEL > 6 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL))
            std::cout << "injection result: "<<retcode<<"\n";
        x++;
    }
    delete DLG;
}

void HDL_Batch_installerFrame::OnLoadCustomIcon2InstalledGameRequest(wxCommandEvent& event)
{
    wxString HDD = selected_hdd->GetString( selected_hdd->GetSelection() );
    wxString system_cnf  = EXEC_PATH + "system.cnf";
    wxString icon_sys    = EXEC_PATH + "icon.sys";
    wxString icon_icn    = EXEC_PATH + "list.ico";
    wxString logo_raw    = EXEC_PATH + "logo.raw";
    wxString boot_kirx   = EXEC_PATH + "boot.kirx";
    wxString boot_elf    = EXEC_PATH + "boot.elf";
    wxString boot_kelf   = EXEC_PATH + "boot.kelf";

    if( wxFileExists(system_cnf) )
    {
        wxRemoveFile(system_cnf);
    }
    if( wxFileExists(icon_sys)   )
    {
        wxRemoveFile(icon_sys);
    }
    if( wxFileExists(logo_raw)   )
    {
        wxRemoveFile(logo_raw);
    }
    if( wxFileExists(boot_kirx)  )
    {
        wxRemoveFile(boot_kirx);
    }
    if( wxFileExists(boot_elf)   )
    {
        wxRemoveFile(boot_elf);
    }
    if( wxFileExists(icon_icn)   )
    {
        wxRemoveFile(icon_icn);
    }


    long itemIndex = -1, retcode;
    int prevcount = 0, x = 0;
    wxString title, ELF, command;

    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        prevcount++;
    itemIndex = -1;//reset counter for the real iteration
    wxProgressDialog* DLG = new wxProgressDialog(_("Injecting custom icon to..."), wxEmptyString, prevcount, this);

    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        title = Installed_game_list->GetItemText(itemIndex,0);
        DLG->Update(x, title);
        ELF = Installed_game_list->GetItemText(itemIndex,1);
        if( wxFileExists(icon_icn)   )
        {
            wxRemoveFile(icon_icn);
        }
        if (Load_custom_icon(ELF))
        {
            command.clear();
            command.Printf("HDL.EXE modify_header %s \"%s\"", HDD, title);
            std::cout << "injecting ["<<title<<"] @"<<ELF<<"\n";
            COLOR(0d);
            retcode = wxExecute(command,wxEXEC_SYNC);
            COLOR(07);
            if (CFG::DEBUG_LEVEL > 6 || (CTOR_FLAGS & FORCE_HIGH_DEBUG_LEVEL))
                std::cout << "injection result: "<<retcode<<"\n";
        }
        x++;
    }
    delete DLG;
    if( wxFileExists(icon_icn)   )
    {
        std::cout << "> Cleaning stray icon\n";
        wxRemoveFile(icon_icn);
    }
    wxMessageBox(_("Injection Finished!"),"",wxICON_INFORMATION);
}

void HDL_Batch_installerFrame::OnMD5HashRequest(wxCommandEvent& event)
{
    wxBeginBusyCursor();
    std::string HASH, FILEPATH;
    long itemIndex = -1;
    if((itemIndex = game_list__->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        FILEPATH = std::string(game_list__->GetItemText(itemIndex).mb_str());
    }
    std::cout << "Collecting MD5 hash for ["<<FILEPATH<<"]\n";
    HASH = MD5digest_file(FILEPATH);
    std::cout << "\tCollected hash: ["<<HASH<<"]\n";
    wxEndBusyCursor();
    wxMessageBox(HASH, _("Collected hash:"),wxICON_INFORMATION);
}

void HDL_Batch_installerFrame::OnCOPYHDDSelected(wxCommandEvent& event)
{
    if (selected_hdd->GetCount() < 2)
    {
        wxMessageBox(_("You need at least two PlayStation 2 formatted HDDs to use this operation!"),"", wxICON_WARNING);
        return;
    }
    wxArrayString HDDS;
    for (size_t x=0; x < selected_hdd->GetCount(); x++)
        HDDS.Add(selected_hdd->GetString(x));

    CopyHDD* HDDCOPYER = new CopyHDD(this, HDDS, -1, wxEmptyString);

    HDDCOPYER->ShowModal();
    delete HDDCOPYER;
}

void HDL_Batch_installerFrame::OnSelectiveGameMigration(wxCommandEvent& event)
{
    if (selected_hdd->GetCount() < 2)
    {
        wxMessageBox(_("You need at least two PlayStation 2 formatted HDDs to use this operation!"),"", wxICON_WARNING);
        return;
    }

    wxString FLAGS;
    long itemIndex = -1;

    while ((itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != wxNOT_FOUND)
    {
        FLAGS.append( (Installed_game_list->GetItemState(itemIndex, wxLIST_STATE_SELECTED)) ? "y":"n");
    }
    std::cout <<"The command string is: ["<<FLAGS<<"]\n";
    wxArrayString HDDS;
    for (size_t x=0; x < selected_hdd->GetCount(); x++)
        HDDS.Add(selected_hdd->GetString(x));

    CopyHDD* HDDCOPYER = new CopyHDD(this, HDDS, selected_hdd->GetSelection(), FLAGS);

    HDDCOPYER->ShowModal();
    delete HDDCOPYER;
}

void HDL_Batch_installerFrame::OnGameDeletionRequest(wxCommandEvent& event)
{
    if (wxMessageBox(_("This feature is unstable, untested and potentially dangerous.\n"
                       "It has been confirmed that it corrupts the HDD format.\n"
                       "Are you certain that you want to delete this game?"),
                     _("IMPORTANT WARNING"),
                     wxICON_WARNING|wxYES_NO|wxNO_DEFAULT, this) == wxNO)
        return;

    long itemIndex = -1, retcode;
    wxString title, HDD;
    if ( (itemIndex = Installed_game_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        HDD = selected_hdd->GetString(selected_hdd->GetSelection());
        title = Installed_game_list->GetItemText(itemIndex);
        retcode = wxExecute(wxString::Format("HDL.EXE delete %s \"%s\"", HDD, title), wxEXEC_SYNC);
        std::cout << __func__<<": returned "<< retcode << "\n";
        if (retcode != 0)
        {
            wxMessageBox(wxString::Format(_("Failed with error code %ld"), retcode),error_caption, wxICON_ERROR);
        }
        List_refresh_request();
    }
}

void HDL_Batch_installerFrame::OnFrameResize(wxSizeEvent& event)
{
    /* // TODO: FIND A WAY TO MAKE THIS WORK WITHOUT FUCKING THE *sizer objects auto resizing
    int listwidth = Installed_game_list->GetSize().x;
    int listwidth2 = game_list__->GetSize().x;

    Installed_game_list->SetColumnWidth(0, listwidth);
    game_list__->SetColumnWidth(0, listwidth2); */
}

int wxCALLBACK hdlbinst_listctrl_compare(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    if(item1<item2) return -1;
    if(item1>item2) return 1;
    return 0; // if both items are equal...
}

void HDL_Batch_installerFrame::OnHDDFormatMenuRequest(wxCommandEvent& event)
{
#if PFSSHELL_ALLOWED
    HDDFomatMan *MAN = new HDDFomatMan(this);
    MAN->ShowModal();
    delete MAN;
#else
    PFSSHELL_DISABLED_WARNING();
#endif
}

void HDL_Batch_installerFrame::OnRedump_searchSelected(wxCommandEvent& event)
{
}

void HDL_Batch_installerFrame::OnCalculateMD5Selected(wxCommandEvent& event)
{
    long itemIndex = -1;
    if ( (itemIndex = game_list__->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
        {
            wxString HASH = MD5digest_file(game_list__->GetItemText(itemIndex).ToStdString());
            MD5Report *REPORT = new MD5Report(this, game_list__->GetItemText(itemIndex), HASH);
            REPORT->ShowModal();
            delete REPORT;
        }
}
