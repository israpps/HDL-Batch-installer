/***************************************************************
 * Name:      Component_error.cpp
 * Purpose:   Code for games ART/CFG/CHT and other files download
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   Not sure lol, take a look at git history
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include "ArtMan.h"

//(*InternalHeaders(ArtMan)
#include <wx/intl.h>
#include <wx/string.h>
//*)
using namespace std;
//(*IdInit(ArtMan)
const long ArtMan::ID_CHECKBOX1 = wxNewId();
const long ArtMan::ID_CHECKBOX2 = wxNewId();
const long ArtMan::ID_CHECKBOX3 = wxNewId();
const long ArtMan::ID_CHECKBOX4 = wxNewId();
const long ArtMan::ID_CHECKBOX5 = wxNewId();
const long ArtMan::ID_CHECKBOX6 = wxNewId();
const long ArtMan::ID_CHECKBOX7 = wxNewId();
const long ArtMan::ID_CHECKBOX9 = wxNewId();
const long ArtMan::ID_CHECKBOX8 = wxNewId();
const long ArtMan::ID_CHECKBOX10 = wxNewId();
const long ArtMan::ID_CHECKBOX11 = wxNewId();
const long ArtMan::ID_CHECKBOX12 = wxNewId();
const long ArtMan::ID_BUTTON1 = wxNewId();
const long ArtMan::ID_CHECKBOX13 = wxNewId();
const long ArtMan::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ArtMan,wxDialog)
    //(*EventTable(ArtMan)
    //*)
END_EVENT_TABLE()

ArtMan::ArtMan(wxWindow* parent,
               wxArrayString ELF,
               wxWindowID id,
               const wxPoint& pos,
               const wxSize& size) : ELF_t(ELF)
{
    /*
    art_map.insert(art_alias_t("BG"     ,"_BG.jpg"));
    art_map.insert(art_alias_t("COV"    ,"_COV.jpg"));
    art_map.insert(art_alias_t("COV2"   ,"_COV2.jpg"));
    art_map.insert(art_alias_t("ICO"    ,"_ICO.png"));
    art_map.insert(art_alias_t("LAB"    ,"_LAB.jpg"));
    art_map.insert(art_alias_t("LGO"    ,"_LGO.png"));
    art_map.insert(art_alias_t("SCR"    ,"_SCR_00.jpg"));
    art_map.insert(art_alias_t("SCR2"   ,"_SCR_01.jpg"));
    */
    //(*Initialize(ArtMan)
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;

    Create(parent, wxID_ANY, _("Downloads manager"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    SetIcon( wxICON(HDL_BATCH_ICON));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Others"));
    cht = new wxCheckBox(this, ID_CHECKBOX1, _("CHT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    cht->SetValue(false);
    cht->SetToolTip(_("Widescreen hacks for OPL"));
    StaticBoxSizer1->Add(cht, 1, wxALL|wxEXPAND, 5);
    cfg = new wxCheckBox(this, ID_CHECKBOX2, _("CFG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    cfg->SetValue(false);
    StaticBoxSizer1->Add(cfg, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Images"));
    markall = new wxCheckBox(this, ID_CHECKBOX3, _("ALL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    markall->SetValue(false);
    StaticBoxSizer2->Add(markall, 1, wxALL|wxEXPAND, 5);
    bg = new wxCheckBox(this, ID_CHECKBOX4, _("BG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    bg->SetValue(false);
    StaticBoxSizer2->Add(bg, 1, wxALL|wxEXPAND, 5);
    cov = new wxCheckBox(this, ID_CHECKBOX5, _("COV"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    cov->SetValue(false);
    StaticBoxSizer2->Add(cov, 1, wxALL|wxEXPAND, 5);
    cov2 = new wxCheckBox(this, ID_CHECKBOX6, _("COV2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    cov2->SetValue(false);
    StaticBoxSizer2->Add(cov2, 1, wxALL|wxEXPAND, 5);
    ico = new wxCheckBox(this, ID_CHECKBOX7, _("ICO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    ico->SetValue(false);
    StaticBoxSizer2->Add(ico, 1, wxALL|wxEXPAND, 5);
    lgo = new wxCheckBox(this, ID_CHECKBOX9, _("LGO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    lgo->SetValue(false);
    StaticBoxSizer2->Add(lgo, 1, wxALL|wxEXPAND, 5);
    lab = new wxCheckBox(this, ID_CHECKBOX8, _("LAB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    lab->SetValue(false);
    StaticBoxSizer2->Add(lab, 1, wxALL|wxEXPAND, 5);
    scr = new wxCheckBox(this, ID_CHECKBOX10, _("SCR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    scr->SetValue(false);
    StaticBoxSizer2->Add(scr, 1, wxALL|wxEXPAND, 5);
    scr_2 = new wxCheckBox(this, ID_CHECKBOX11, _("SCR2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    scr_2->SetValue(false);
    StaticBoxSizer2->Add(scr_2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
    FAST = new wxCheckBox(this, ID_CHECKBOX12, _("Fast Download"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    FAST->SetValue(false);
    FlexGridSizer1->Add(FAST, 1, wxALL|wxEXPAND, 5);
    download = new wxButton(this, ID_BUTTON1, _("Download"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer1->Add(download, 1, wxALL|wxEXPAND, 5);
    CheckCERT = new wxCheckBox(this, ID_CHECKBOX13, _("Artwork certificate fix"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
    CheckCERT->SetValue(false);
    CheckCERT->SetToolTip(_("Attempts connections to archive.org for artwork download without certificate checks"));
    FlexGridSizer1->Add(CheckCERT, 1, wxALL|wxEXPAND, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetMaxLength(32);
    FlexGridSizer1->Add(TextCtrl1, 1, wxALL|wxEXPAND, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ArtMan::OnmarkallClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ArtMan::OndownloadClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&ArtMan::OnInit);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&ArtMan::OnPaint);
    //*)
}

ArtMan::~ArtMan()
{
    //(*Destroy(ArtMan)
    //*)
}
extern wxString EXEC_PATH;


void ArtMan::OnInit(wxInitDialogEvent& event)
{}

void ArtMan::OnPaint(wxPaintEvent& event)
{
    /*
       if (bg->GetValue() || cov->GetValue() || cov2->GetValue() || ico->GetValue() || lab->GetValue() || lgo->GetValue()|| scr->GetValue() || scr_2->GetValue())
       {
           download->Enable();
       }
       else
       {
           download->Disable();
       }*/
}

long ArtMan::Request_art(wxString ELF, wxString suffix)
{
    wxString gauge_switch = (FAST->IsChecked()) ? "" : "--show-progress ";
    wxString cert_switch =  (CheckCERT->IsChecked()) ? "--no-check-certificate " : "";
    long wget_return_value;
    wxString command = "common\\wget.exe -q " + cert_switch + gauge_switch +"https://ia802706.us.archive.org/view_archive.php?archive=/4/items/OPLM_ART_2023_07/OPLM_ART_2023_07.zip&file=PS2%2F";
    command.append(ELF);
    command.append("%2F");
    command.append(ELF);
    if (suffix == "_BG.jpg")
    {
        command.append("_BG_00.jpg");   ///BG is a special case...
    }
    else
    {
        command.append(suffix);
    }
    command.append(" -O \"Downloads\\ART\\");
    command.append(ELF);
    command.append(suffix);
    command.append("\"");
    COLOR(0d)
    wget_return_value = wxExecute(command,(FAST->IsChecked()) ? wxEXEC_ASYNC : wxEXEC_SYNC);
    COLOR(07)
    //if (wget_return_value != 0) {wxRemoveFile( wxString::Format("\"%sDownloads\\ART\\%s%s\"", EXEC_PATH, ELF, suffix) );}
    //cout << "[" << std::string(command.mb_str()) << "]\n";
    return wget_return_value;
}


void ArtMan::OndownloadClick(wxCommandEvent& event)
{
    //long retcode;
    wxString commnand;
    if (!wxDirExists("Downloads"))
    {
        wxMkdir("Downloads");
    }
    if (!wxDirExists("Downloads\\ART"))
    {
        wxMkdir("Downloads\\ART");
    }


    string ELF;
    COLOR(0e) std::cout <<"Downloading...\n";
    COLOR(07)
    wxBeginBusyCursor();
    wxString gauge_switch = (FAST->IsChecked()) ? "" : "--show-progress";
    for (size_t x=0; x<ELF_t.GetCount(); x++)
    {
        ELF = std::string(ELF_t.Item(x).mb_str());
        TextCtrl1->Clear();
        TextCtrl1->AppendText(ELF_t.Item(x));
        COLOR(0f) std::cout <<"             ["<< ELF << "]\n";
        COLOR(07)
        if (bg->GetValue())
        {
            Request_art(wxString(ELF), "_BG.jpg");
        }
        if (cov->GetValue())
        {
            Request_art(ELF, "_COV.jpg");
        }
        if (cov2->GetValue())
        {
            Request_art(ELF, "_COV2.jpg");
        }
        if (ico->GetValue())
        {
            Request_art(ELF, "_ICO.png");
        }
        if (lab->GetValue())
        {
            Request_art(ELF, "_LAB.jpg");
        }
        if (lgo->GetValue())
        {
            Request_art(ELF, "_LGO.png");
        }
        if (scr->GetValue())
        {
            Request_art(ELF, "_SCR_00.jpg");
        }
        if (scr_2->GetValue())
        {
            Request_art(ELF, "_SCR_01.jpg");
        }
        if (cfg->GetValue())
        {
            COLOR(0d)
            if (!wxDirExists("Downloads\\CFG"))
            {
                wxMkdir("Downloads\\CFG");
            }
            commnand = "common\\wget.exe -q " + gauge_switch + " https://raw.githubusercontent.com/israpps/PS2-OPL-CFG-Database/master/CFG_en/" + ELF + ".cfg -O \"Downloads\\CFG\\" + ELF + ".cfg\"";
            /*retcode = */wxExecute(commnand, (FAST->IsChecked()) ? wxEXEC_ASYNC : wxEXEC_SYNC );
            //if (retcode != 0) {wxRemoveFile( wxString::Format("\"%sDownloads\\CFG\\%s.cfg\"", EXEC_PATH, ELF) );}
            COLOR(07)
        }
        if (cht->GetValue())
        {
            COLOR(0d)
            if (!wxDirExists("Downloads\\CHT"))
            {
                wxMkdir("Downloads\\CHT");
            }
            commnand = "common\\wget.exe -q " + gauge_switch + " https://raw.githubusercontent.com/PS2-Widescreen/OPL-Widescreen-Cheats/main/CHT/" + ELF + ".cht -O \"Downloads\\CHT\\" + ELF + ".cht\"";
            /*retcode = */wxExecute(commnand, (FAST->IsChecked()) ? wxEXEC_ASYNC : wxEXEC_SYNC );
            //if (retcode != 0) {wxRemoveFile( wxString::Format("\"%sDownloads\\CHT\\%s.cht\"", EXEC_PATH, ELF) );}
            COLOR(07)
        }
        if (FAST->IsChecked())
            wxMilliSleep(5000);
    }
    cleanup();
    wxEndBusyCursor();
    COLOR(0a) cout << "Download finished!\n";
    COLOR(07)
    wxMessageBox(_("Downloads finished!"),"",wxICON_INFORMATION);
}

void ArtMan::OnmarkallClick(wxCommandEvent& event)
{
    scr_2->SetValue(markall->GetValue());
    scr->SetValue(markall->GetValue());
    lgo->SetValue(markall->GetValue());
    lab->SetValue(markall->GetValue());
    ico->SetValue(markall->GetValue());
    cov2->SetValue(markall->GetValue());
    cov->SetValue(markall->GetValue());
    bg->SetValue(markall->GetValue());
}

void ArtMan::OndownloadClick1(wxCommandEvent& event)
{}

void ArtMan::Onothers_markallClick(wxCommandEvent& event)
{
}

void ArtMan::cleanup(void)
{
    wxString script_contents = "@echo off\r\ncd \"%~dp0\"\r\nREM this is a script of POPS VCD Manager, made to clean files with 0 bytes size from ART sub-folder\r\n\r\n\r\ncall :CLEAN ART\r\ncall :CLEAN CFG\r\ncall :CLEAN CHT\r\n\r\ngoto :BREAK_\r\n:CLEAN\r\nif not exist %1\\ goto :EOF\r\ncd %1\r\nfor /f \"delims=\" %%x in ('dir *.* /B /A:-D') do (\r\necho %%x - %%~zx\r\nif %%~zx == 0 (\r\necho %%x is empty\r\ndel \"%%x\"\r\n)\r\n\r\n)\r\ncd ..\r\ngoto :EOF\r\n\r\n\r\n\r\n:BREAK_\r\nexit";
    wxString script_path = EXEC_PATH+"Downloads\\Clear_broken_images.bat";
    if (!wxFileExists(script_path))
    {
        COLOR(0e)
        std::cerr <<"Missing script file. Writing internal copy...\n";
        wxFile a;
        a.Open(script_path,wxFile::write);
        a.Write(script_contents);
        COLOR(07)
    }
    wxExecute(wxString::Format("cmd.exe /c \"%sDownloads\\Clear_broken_images.bat\"",EXEC_PATH),wxEXEC_SYNC);
}
