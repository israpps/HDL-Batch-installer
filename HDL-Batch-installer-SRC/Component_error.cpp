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
const long Component_error::ID_STATICLINE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Component_error,wxDialog)
    //(*EventTable(Component_error)
    //*)
END_EVENT_TABLE()

Component_error::Component_error(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(Component_error)
    Create(parent, id, _("FATAL ERROR"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,222));
    Move(wxDefaultPosition);
    wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Some Core components are Missing.\n  Download the program again from the official github. \n    If the error persists:\n      Contact the Developer or open a new issue at github"), wxPoint(16,32), wxSize(368,80), wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
    HyperlinkCtrl1 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL1, _("Official Github"), _("https://github.com/israpps/HDL-Batch-installer"), wxPoint(16,128), wxSize(96,14), wxHL_CONTEXTMENU, _T("ID_HYPERLINKCTRL1"));
    HyperlinkCtrl2 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL2, _("Contact the developer"), _("https://github.com/israpps"), wxPoint(16,152), wxSize(114,14), wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL2"));
    HyperlinkCtrl3 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL3, _("Download the program again"), _("https://github.com/israpps/HDL-Batch-installer/releases"), wxPoint(16,176), wxSize(147,14), wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE, _T("ID_HYPERLINKCTRL3"));
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxPoint(8,120), wxSize(376,2), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    Center();

    Connect(ID_HYPERLINKCTRL1,wxEVT_COMMAND_HYPERLINK,(wxObjectEventFunction)&Component_error::OnHyperlinkCtrl1Click);
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
