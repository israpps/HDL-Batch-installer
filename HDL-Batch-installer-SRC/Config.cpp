/***************************************************************
 * Name:      Config.cpp
 * Purpose:   Code for Configurations editor
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include "Config.h"

extern std::string DMA_TABLE[8];
extern std::string DMA_ALIAS[8];
#include "include/locale_table.h"
//(*InternalHeaders(Config)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(Config)
const long Config::ID_CHECKBOX3 = wxNewId();
const long Config::ID_COMBOBOX1 = wxNewId();
const long Config::ID_CHECKBOX1 = wxNewId();
const long Config::ID_CHECKBOX2 = wxNewId();
const long Config::ID_CHECKBOX4 = wxNewId();
const long Config::ID_CHECKBOX5 = wxNewId();
const long Config::ID_CHECKBOX6 = wxNewId();
const long Config::ID_RADIOBUTTON1 = wxNewId();
const long Config::ID_RADIOBUTTON2 = wxNewId();
const long Config::ID_DIRPICKERCTRL1 = wxNewId();
const long Config::ID_CHOICE1 = wxNewId();
const long Config::ID_PANEL1 = wxNewId();
const long Config::ID_CHOICE2 = wxNewId();
const long Config::ID_TEXTCTRL1 = wxNewId();
const long Config::ID_PANEL2 = wxNewId();
const long Config::ID_TEXTCTRL2 = wxNewId();
const long Config::ID_PANEL3 = wxNewId();
const long Config::ID_NOTEBOOK1 = wxNewId();
const long Config::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Config,wxDialog)
    //(*EventTable(Config)
    //*)
END_EVENT_TABLE()

Config::Config(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(Config)
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxGridSizer* GridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxStaticBoxSizer* StaticBoxSizer7;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer9;

    Create(parent, wxID_ANY, _("Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SetIcon( wxICON(HDL_BATCH_ICON));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Startup settings"));
    check_updates = new wxCheckBox(Panel1, ID_CHECKBOX3, _("Check for Updates"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    check_updates->SetValue(true);
    StaticBoxSizer2->Add(check_updates, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Language"));
    language_choice = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    for (long long unsigned int x=0; x < WXSIZEOF(langNames) ; x++)
    language_choice->Append(langNames[x]);
    language_choice->SetSelection(0);
    StaticBoxSizer3->Add(language_choice, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer2->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Installation features"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    GridSizer1 = new wxGridSizer(0, 2, 0, 0);
    miniopl_warning = new wxCheckBox(Panel1, ID_CHECKBOX1, _("OPL Launcher warnings"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    miniopl_warning->SetValue(true);
    GridSizer1->Add(miniopl_warning, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    osd_hide_settings = new wxCheckBox(Panel1, ID_CHECKBOX2, _("Hide game"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    osd_hide_settings->SetValue(false);
    osd_hide_settings->SetToolTip(_("When enabled, the program will install games using __. as partition prefix instead of PP.\n\nThis will hide games from HDD-OSD.\n\nAlso, this alternative prefix is required to launch games via OPL Launcher from PSBBN and PSX XMB menu"));
    GridSizer1->Add(osd_hide_settings, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    CUSTOM_ICONS = new wxCheckBox(Panel1, ID_CHECKBOX4, _("Custom Icon Loader"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CUSTOM_ICONS->SetValue(true);
    GridSizer1->Add(CUSTOM_ICONS, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    DATA_COLLECTION = new wxCheckBox(Panel1, ID_CHECKBOX5, _("Data Collection"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    DATA_COLLECTION->SetValue(false);
    DATA_COLLECTION->SetToolTip(_("When this Feature is enabled, the program will send information to it\'s creator every time it installs a game whose region code isn\'t registered in the database"));
    GridSizer1->Add(DATA_COLLECTION, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    AllowExperimental = new wxCheckBox(Panel1, ID_CHECKBOX6, _("Allow unstable/experimental features"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    AllowExperimental->SetValue(false);
    GridSizer1->Add(AllowExperimental, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer4->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Title Database"));
    gndb_intern = new wxRadioButton(Panel1, ID_RADIOBUTTON1, _("Internal"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    gndb_intern->SetValue(true);
    StaticBoxSizer4->Add(gndb_intern, 1, wxALL|wxEXPAND, 5);
    gndb_extern = new wxRadioButton(Panel1, ID_RADIOBUTTON2, _("External"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    StaticBoxSizer4->Add(gndb_extern, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer4->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Default game search path"));
    ISO_PATH_HOLDER = new wxDirPickerCtrl(Panel1, ID_DIRPICKERCTRL1, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
    StaticBoxSizer5->Add(ISO_PATH_HOLDER, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Default DMA"));
    default_dma = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    default_dma->SetToolTip(_("Determines wich DMA mode will be written to game APA Header.\n\nThis feature is only usable for outdated software like HDLoader or MiniOPL"));
    for (int X=0 ; X <=7 ; X++)
    {default_dma->Append(DMA_ALIAS[X]);}

    default_dma->SetSelection(7);
    StaticBoxSizer6->Add(default_dma, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(StaticBoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("Default HDD letter"));
    MountPoint = new wxChoice(Panel2, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    for (int x=0; x<25; x++)
    {MountPoint->Append(mountpoints[x]);}
    MountPoint->SetSelection(22);
    StaticBoxSizer7->Add(MountPoint, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(StaticBoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("Default OPL data partition name"));
    OPLPART = new wxTextCtrl(Panel2, ID_TEXTCTRL1, _("+OPL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticBoxSizer8->Add(OPLPART, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(StaticBoxSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel2);
    FlexGridSizer3->SetSizeHints(Panel2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("NBD Default IP adress"));
    NBDIP = new wxTextCtrl(Panel3, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    StaticBoxSizer9->Add(NBDIP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(StaticBoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(Panel3);
    FlexGridSizer5->SetSizeHints(Panel3);
    Notebook1->AddPage(Panel1, _("General"), false);
    Notebook1->AddPage(Panel2, _("PFSFUSE"), false);
    Notebook1->AddPage(Panel3, _("NBD Server"), false);
    FlexGridSizer1->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Button1 = new wxButton(this, ID_BUTTON1, _("Save Settings"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Config::OnCheckBox1Click);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&Config::OnNotebook1PageChanged);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Config::OnSaveDataRequest);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&Config::OnInit);
    //*)
    wxFileName fname( wxTheApp->argv[0] );
    wxString ini_filename = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "Common\\config.INI";
    std::cout << "> Sync config menu elements with current config values -> ["<<ini_filename<<"]\n";
    wxFileConfig * main_config = new wxFileConfig( wxEmptyString, wxEmptyString, ini_filename);
    config_t CFGT;
    main_config->Read("Game_search/Default_iso_path",   &CFGT.Default_iso_path,"C:\\");
    ISO_PATH_HOLDER->SetPath(CFGT.Default_iso_path);
    main_config->Read("Installation/DataBase_Mode",     &CFGT.DataBase_Mode,false);
    if (CFGT.DataBase_Mode == DB_INTERNAL) gndb_intern->SetValue(true);
    else gndb_extern->SetValue(true);
    main_config->Read("Installation/MiniOPL",           &CFGT.MiniOPL,true);
    miniopl_warning->SetValue(CFGT.MiniOPL);
    main_config->Read("Init/Language",                  &CFGT.Language,0);
    language_choice->SetSelection(CFGT.Language);
    main_config->Read("Installation/Default_dma",       &CFGT.Default_dma,7);
    default_dma->SetSelection(CFGT.Default_dma);
    main_config->Read("Installation/OSD_Hide",          &CFGT.OSD_Hide,false);
    osd_hide_settings->SetValue(CFGT.OSD_Hide);
    main_config->Read("Init/check_for_updates",         &CFGT.check_updates,true);
    check_updates->SetValue(CFGT.check_updates);
    main_config->Read("Installation/Custom_icons",      &CFGT.custom_icons,true);
    CUSTOM_ICONS->SetValue(CFGT.custom_icons);
    main_config->Read("Installation/inform_unknown_ID", &CFGT.collect_onkown_games_ID, false);
    DATA_COLLECTION->SetValue(CFGT.collect_onkown_games_ID);
    main_config->Read("NBD/Default_IP",                 &CFGT.NBD_IP, "");
    main_config->Read("FEATURES/allow_experimental",    &CFGT.allow_experimental, false);
    NBDIP->Clear();
    NBDIP->SetValue(CFGT.NBD_IP);
    delete main_config;
}

Config::~Config()
{
    //(*Destroy(Config)
    //*)
}

void Config::OnInit(wxInitDialogEvent& event)
{}

void Config::OnButton2Click(wxCommandEvent& event)
{}

void Config::OnRadioButton2Select(wxCommandEvent& event)
{}

void Config::Ongndb_internSelect(wxCommandEvent& event)
{}
void Config::OnButton2Click1(wxCommandEvent& event)
{}

void Config::SaveSettings()
{
    wxFileName fname( wxTheApp->argv[0] );
    wxString ini_filename = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "Common\\config.INI";
    std::cout << "> writing config to ["<<ini_filename<<"]\n";
    wxFileConfig * main_config = new wxFileConfig( wxEmptyString, wxEmptyString, ini_filename);

    config_t CFGT;
    //CFGT.debug_level = debug_level->GetValue();
    CFGT.Default_iso_path           = ISO_PATH_HOLDER->GetPath();
    if (gndb_intern->GetValue())
        CFGT.DataBase_Mode              = DB_INTERNAL;
    else CFGT.DataBase_Mode = DB_EXTERNAL;
    CFGT.MiniOPL                    	= miniopl_warning->GetValue();
    CFGT.Language                   	= language_choice->GetSelection();
    CFGT.Default_dma                	= default_dma->GetSelection();
    CFGT.OSD_Hide                   	= osd_hide_settings->GetValue();
    CFGT.check_updates              	= check_updates->GetValue();
    CFGT.custom_icons               	= CUSTOM_ICONS->GetValue();
    CFGT.collect_onkown_games_ID    	= DATA_COLLECTION->GetValue();
    CFGT.FUSE.default_OPLPART       	= OPLPART->GetValue();
    CFGT.FUSE.mountpoint            	= MountPoint->GetString(MountPoint->GetSelection());
    CFGT.NBD_IP                     	= NBDIP->GetValue();
    CFGT.allow_experimental             = AllowExperimental->GetValue();

    //main_config->Write("Init/Debug_level", CFGT.debug_level);                   std::cout <<"debug_level=" << CFGT.debug_level<<std::endl;
    main_config->Write("Game_search/Default_iso_path", CFGT.Default_iso_path);
    std::cout <<"Default_iso_path="<<CFGT.Default_iso_path<<std::endl;
    main_config->Write("Installation/DataBase_Mode", CFGT.DataBase_Mode);
    std::cout <<"DataBase_Mode="<<CFGT.DataBase_Mode<<std::endl;
    main_config->Write("Installation/MiniOPL", CFGT.MiniOPL);
    std::cout <<"MiniOPL="<<CFGT.MiniOPL<<std::endl;
    main_config->Write("Init/Language", CFGT.Language);
    std::cout <<"Language ID="<< CFGT.Language <<std::endl;
    main_config->Write("Installation/Default_dma", CFGT.Default_dma);
    std::cout <<"Default_dma="<< DMA_TABLE[CFGT.Default_dma] <<std::endl;
    main_config->Write("Installation/OSD_Hide", CFGT.OSD_Hide);
    std::cout <<"OSD_Hide="<<CFGT.OSD_Hide<<std::endl;
    main_config->Write("Init/check_for_updates", CFGT.check_updates);
    std::cout <<"check_for_updates="<<CFGT.check_updates<<std::endl;
    main_config->Write("Installation/Custom_icons", CFGT.custom_icons);
    std::cout <<"Custom_icons="<<CFGT.custom_icons<<std::endl;
    main_config->Write("Installation/inform_unknown_ID", CFGT.collect_onkown_games_ID);
    std::cout <<"inform_unknown_ID="<<CFGT.collect_onkown_games_ID<<std::endl;
    main_config->Write("FUSE/opl_partition",CFGT.FUSE.default_OPLPART);
    std::cout <<"FUSE_OPL_partition="<<CFGT.FUSE.default_OPLPART<<std::endl;
    main_config->Write("FUSE/default_mountpoint",CFGT.FUSE.mountpoint);
    std::cout <<"FUSE_default_mountpoint="<<CFGT.FUSE.mountpoint<<std::endl;
    main_config->Write("NBD/Default_IP",CFGT.NBD_IP);
    std::cout <<"Default_IP="<<CFGT.NBD_IP<<std::endl;
    main_config->Write("FEATURES/allow_experimental",CFGT.allow_experimental);
    std::cout <<"allow_experimental_features="<<CFGT.allow_experimental<<std::endl;

    std::cout << "> flushing settings handler and forcing file writing\n";
    main_config->Flush();//force data writing
    wxMessageBox("Restart the program in order to fully apply those settings", "Settings saved...");
}

void Config::OnOSD_HIDE_SETTING_HELPClick(wxCommandEvent& event)
{}

void Config::OnISO_DEFAULT_PATHDirChanged(wxFileDirPickerEvent& event)
{}

void Config::OnHyperlinkCtrl1Click(wxCommandEvent& event)
{}

void Config::Ondefault_dmaSelect(wxCommandEvent& event)
{}

void Config::Onlanguage_choiceSelect(wxCommandEvent& event)
{}

void Config::OnNotebook1PageChanged(wxNotebookEvent& event)
{}

void Config::OnSaveDataRequest(wxCommandEvent& event)
{
    SaveSettings();
}

void Config::OnCheckBox1Click(wxCommandEvent& event)
{}
