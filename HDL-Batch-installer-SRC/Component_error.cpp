/***************************************************************
 * Name:      Component_error.cpp
 * Purpose:   Code for warning dialog displayed if important files are missing
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   Not sure lol, take a look at git history
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#include "Component_error.h"

//(*InternalHeaders(Component_error)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(Component_error)
const long Component_error::ID_STATICTEXT1 = wxNewId();
const long Component_error::ID_HYPERLINKCTRL1 = wxNewId();
const long Component_error::ID_HYPERLINKCTRL2 = wxNewId();
const long Component_error::ID_HYPERLINKCTRL3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Component_error,wxDialog)
    //(*EventTable(Component_error)
    //*)
END_EVENT_TABLE()

Component_error::Component_error(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(Component_error)
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, id, _("FATAL ERROR"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,222));
    Move(wxDefaultPosition);
    wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Some Core components are Missing.\nDownload the program again from the official github. \n\nIf the error persists:\nContact the Developer or open a new issue at github"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HyperlinkCtrl1 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL1, _("Official Repository"), _("https://github.com/israpps/HDL-Batch-installer"), wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL1"));
    FlexGridSizer1->Add(HyperlinkCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HyperlinkCtrl2 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL2, _("Discord server"), _("https://discord.gg/tc9G7zewvh"), wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL2"));
    FlexGridSizer1->Add(HyperlinkCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HyperlinkCtrl3 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL3, _("Download Latest version"), _("https://github.com/israpps/HDL-Batch-installer/releases/tag/Latest"), wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL3"));
    FlexGridSizer1->Add(HyperlinkCtrl3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    SetSizer(FlexGridSizer1);
    Layout();
    Center();

    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&Component_error::OnInit);
    //*)
}

Component_error::~Component_error()
{
    //(*Destroy(Component_error)
    //*)
}


void Component_error::OnInit(wxInitDialogEvent& event)
{
}

void Component_error::OnHyperlinkCtrl1Click(wxCommandEvent& event)
{
}
