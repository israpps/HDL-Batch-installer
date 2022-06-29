/***************************************************************
 * Name:      About.cpp
 * Purpose:   Code for Credits window
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#include "About.h"
//(*InternalHeaders(About)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(About)
const long About::ID_STATICTEXT1 = wxNewId();
const long About::ID_HYPERLINKCTRL1 = wxNewId();
const long About::ID_STATICTEXT2 = wxNewId();
const long About::ID_STATICTEXT3 = wxNewId();
const long About::ID_STATICTEXT5 = wxNewId();
const long About::ID_STATICTEXT8 = wxNewId();
const long About::ID_STATICTEXT10 = wxNewId();
const long About::ID_STATICLINE1 = wxNewId();
const long About::ID_STATICLINE2 = wxNewId();
const long About::ID_STATICLINE3 = wxNewId();
const long About::ID_STATICTEXT4 = wxNewId();
const long About::ID_HYPERLINKCTRL2 = wxNewId();
const long About::ID_STATICLINE4 = wxNewId();
const long About::ID_STATICTEXT11 = wxNewId();
//*)

BEGIN_EVENT_TABLE(About,wxDialog)
    //(*EventTable(About)
    //*)
END_EVENT_TABLE()

About::About(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(About)
    Create(parent, wxID_ANY, _("HDL Batch Installer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(400,389));
    wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SetIcon( wxICON(HDL_BATCH_ICON));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Get the Latest Version here:"), wxPoint(8,352), wxSize(176,15), 0, _T("ID_STATICTEXT1"));
    HyperlinkCtrl1 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL1, _("Official Github"), _("https://github.com/israpps/HDL-Batch-installer"), wxPoint(208,344), wxSize(184,14), wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL1"));
    HyperlinkCtrl1->SetHoverColour(wxColour(255,0,0));
    HyperlinkCtrl1->SetVisitedColour(wxColour(40,7,224));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Created by El_isra (AKA: Matias Israelson)"), wxPoint(0,8), wxSize(400,15), wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(9,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Special thanks to:"), wxPoint(8,40), wxSize(376,15), 0, _T("ID_STATICTEXT3"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Rs1n: For the Creation of HDL Batch\n     (that project inspired me to make this GUI)"), wxPoint(8,208), wxSize(384,32), 0, _T("ID_STATICTEXT5"));
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("The Testers:\n\n     HUN7ER | Salamander | My sister | Jtrex | Torres Kadher"), wxPoint(8,72), wxSize(376,56), 0, _T("ID_STATICTEXT8"));
    StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Alex Parrado:\n    For contributing with some Ideas"), wxPoint(8,248), wxSize(384,29), 0, _T("ID_STATICTEXT10"));
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(0,64), wxSize(392,2), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxPoint(8,136), wxSize(384,2), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    StaticLine3 = new wxStaticLine(this, ID_STATICLINE3, wxPoint(8,336), wxSize(384,2), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("SpaceCoyote:\n   He made the default icon that get\'s injected into HDD-OSD"), wxPoint(8,288), wxSize(376,37), 0, _T("ID_STATICTEXT4"));
    HyperlinkCtrl2 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL2, _("PSX-Place Thread"), _("https://www.psx-place.com/resources/hdl-batch-installer.1173/"), wxPoint(208,368), wxSize(184,14), wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL2"));
    StaticLine4 = new wxStaticLine(this, ID_STATICLINE4, wxPoint(8,200), wxSize(384,2), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _("Translators:\n\n     Fabio Gaigher | HardLevel | Haker120 (a youkai of love)"), wxPoint(8,144), wxSize(376,56), 0, _T("ID_STATICTEXT11"));

    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&About::OnInit);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&About::OnPaint);
    //*)
}

About::~About()
{
    //(*Destroy(About)
    //*)
}


void About::OnVersionText(wxCommandEvent& event)
{}

void About::OnBuild_dateText(wxCommandEvent& event)
{}

void About::OnInit(wxInitDialogEvent& event)
{}

void About::OnPaint(wxPaintEvent& event)
{}