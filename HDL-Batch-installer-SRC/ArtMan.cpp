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
const long ArtMan::ID_BUTTON1 = wxNewId();
const long ArtMan::ID_STATICBOX1 = wxNewId();
const long ArtMan::ID_CHECKBOX2 = wxNewId();
const long ArtMan::ID_CHECKBOX1 = wxNewId();
const long ArtMan::ID_CHECKBOX3 = wxNewId();
const long ArtMan::ID_CHECKBOX4 = wxNewId();
const long ArtMan::ID_CHECKBOX5 = wxNewId();
const long ArtMan::ID_CHECKBOX6 = wxNewId();
const long ArtMan::ID_CHECKBOX7 = wxNewId();
const long ArtMan::ID_CHECKBOX8 = wxNewId();
const long ArtMan::ID_TEXTCTRL1 = wxNewId();
const long ArtMan::ID_STATICLINE1 = wxNewId();
const long ArtMan::ID_CHECKBOX9 = wxNewId();
const long ArtMan::ID_STATICLINE2 = wxNewId();
const long ArtMan::ID_STATICLINE3 = wxNewId();
const long ArtMan::ID_STATICLINE4 = wxNewId();
const long ArtMan::ID_STATICLINE5 = wxNewId();
const long ArtMan::ID_STATICLINE6 = wxNewId();
const long ArtMan::ID_STATICLINE7 = wxNewId();
const long ArtMan::ID_STATICLINE8 = wxNewId();
const long ArtMan::ID_STATICLINE9 = wxNewId();
const long ArtMan::ID_STATICBOX2 = wxNewId();
const long ArtMan::ID_CHECKBOX10 = wxNewId();
const long ArtMan::ID_CHECKBOX11 = wxNewId();
const long ArtMan::ID_STATICLINE10 = wxNewId();
const long ArtMan::ID_CHECKBOX12 = wxNewId();
const long ArtMan::ID_STATICLINE11 = wxNewId();
const long ArtMan::ID_STATICLINE12 = wxNewId();
const long ArtMan::ID_CHECKBOX13 = wxNewId();
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
    Create(parent, wxID_ANY, _("Downloads manager"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(398,273));
    SetIcon( wxICON(HDL_BATCH_ICON));
    download = new wxButton(this, ID_BUTTON1, _("Download"), wxPoint(8,240), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Images"), wxPoint(270,24), wxSize(120,240), 0, _T("ID_STATICBOX1"));
    bg = new wxCheckBox(this, ID_CHECKBOX2, _("BG"), wxPoint(302,96), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    bg->SetValue(false);
    cov = new wxCheckBox(this, ID_CHECKBOX1, _("COV"), wxPoint(302,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    cov->SetValue(true);
    cov2 = new wxCheckBox(this, ID_CHECKBOX3, _("COV2"), wxPoint(302,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    cov2->SetValue(false);
    ico = new wxCheckBox(this, ID_CHECKBOX4, _("ICO"), wxPoint(302,144), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    ico->SetValue(false);
    lab = new wxCheckBox(this, ID_CHECKBOX5, _("LAB"), wxPoint(302,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    lab->SetValue(false);
    lgo = new wxCheckBox(this, ID_CHECKBOX6, _("LGO"), wxPoint(302,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    lgo->SetValue(false);
    scr = new wxCheckBox(this, ID_CHECKBOX7, _("SCR"), wxPoint(302,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    scr->SetValue(false);
    scr_2 = new wxCheckBox(this, ID_CHECKBOX8, _("SCR2"), wxPoint(302,240), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    scr_2->SetValue(false);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(8,24), wxSize(120,23), wxTE_READONLY|wxBORDER_SUNKEN, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(284,64), wxSize(2,192), wxLI_VERTICAL, _T("ID_STATICLINE1"));
    markall = new wxCheckBox(this, ID_CHECKBOX9, wxEmptyString, wxPoint(278,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    markall->SetValue(false);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxPoint(286,80), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxPoint(286,104), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxPoint(286,128), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    StaticLine5 = new wxStaticLine(this, ID_STATICLINE5, wxPoint(286,152), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
    StaticLine6 = new wxStaticLine(this, ID_STATICLINE6, wxPoint(286,176), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE6"));
    StaticLine7 = new wxStaticLine(this, ID_STATICLINE7, wxPoint(286,200), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE7"));
    StaticLine8 = new wxStaticLine(this, ID_STATICLINE8, wxPoint(286,224), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE8"));
    StaticLine9 = new wxStaticLine(this, ID_STATICLINE9, wxPoint(286,248), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE9"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Others"), wxPoint(144,24), wxSize(112,112), 0, _T("ID_STATICBOX2"));
    cfg = new wxCheckBox(this, ID_CHECKBOX10, _("CFG"), wxPoint(176,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    cfg->SetValue(false);
    others_markall = new wxCheckBox(this, ID_CHECKBOX11, wxEmptyString, wxPoint(152,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    others_markall->SetValue(false);
    StaticLine10 = new wxStaticLine(this, ID_STATICLINE10, wxPoint(160,80), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE10"));
    cht = new wxCheckBox(this, ID_CHECKBOX12, _("CHT"), wxPoint(176,96), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    cht->SetValue(false);
    cht->SetToolTip(_("Widescreen hacks for OPL"));
    StaticLine11 = new wxStaticLine(this, ID_STATICLINE11, wxPoint(160,104), wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE11"));
    StaticLine12 = new wxStaticLine(this, ID_STATICLINE12, wxPoint(158,64), wxSize(2,48), wxLI_VERTICAL, _T("ID_STATICLINE12"));
    FAST = new wxCheckBox(this, ID_CHECKBOX13, _("Fast Download"), wxPoint(16,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
    FAST->SetValue(false);
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ArtMan::OndownloadClick);
    Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ArtMan::OnmarkallClick);
    Connect(ID_CHECKBOX11,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ArtMan::Onothers_markallClick);
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
    long wget_return_value;
    wxString command = "common\\wget.exe -q --show-progress https://ia801805.us.archive.org/view_archive.php?archive=/26/items/OPLM_ART_2021_01/OPLM_ART_2021_01.zip&file=PS2%2F";
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
    COLOR(0d(FAST->IsChecked()) ? 00 : 0d)
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
            COLOR(0d(FAST->IsChecked()) ? 00 : 0d)
            if (!wxDirExists("Downloads\\CFG"))
            {
                wxMkdir("Downloads\\CFG");
            }
            commnand = "common\\wget.exe -q --show-progress https://raw.githubusercontent.com/israpps/PS2-OPL-CFG-Database/master/CFG_en/" + ELF + ".cfg -O \"Downloads\\CFG\\" + ELF + ".cfg\"";
            /*retcode = */wxExecute(commnand, (FAST->IsChecked()) ? wxEXEC_ASYNC : wxEXEC_SYNC );
            //if (retcode != 0) {wxRemoveFile( wxString::Format("\"%sDownloads\\CFG\\%s.cfg\"", EXEC_PATH, ELF) );}
            COLOR(07)
        }
        if (cht->GetValue())
        {
            COLOR(0d(FAST->IsChecked()) ? 00 : 0d)
            if (!wxDirExists("Downloads\\CHT"))
            {
                wxMkdir("Downloads\\CHT");
            }
            commnand = "common\\wget.exe -q --show-progress https://raw.githubusercontent.com/PS2-Widescreen/OPL-Widescreen-Cheats/main/CHT/" + ELF + ".cht -O \"Downloads\\CHT\\" + ELF + ".cht\"";
            /*retcode = */wxExecute(commnand, (FAST->IsChecked()) ? wxEXEC_ASYNC : wxEXEC_SYNC );
            //if (retcode != 0) {wxRemoveFile( wxString::Format("\"%sDownloads\\CHT\\%s.cht\"", EXEC_PATH, ELF) );}
            COLOR(07)
        }
        if (FAST->IsChecked())
        	wxMilliSleep(3900);
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
    cht->SetValue(others_markall->GetValue());
    cfg->SetValue(others_markall->GetValue());
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
