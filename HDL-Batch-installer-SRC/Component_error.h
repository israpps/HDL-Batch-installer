/***************************************************************
 * Name:      Component_error.h
 * Purpose:   Code for warning dialog displayed if important files are missing
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef COMPONENT_ERROR_H
#define COMPONENT_ERROR_H

//(*Headers(Component_error)
#include <wx/dialog.h>
#include <wx/hyperlink.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class Component_error: public wxDialog
{
public:

    Component_error(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~Component_error();

    //(*Declarations(Component_error)
    wxHyperlinkCtrl* HyperlinkCtrl1;
    wxHyperlinkCtrl* HyperlinkCtrl2;
    wxHyperlinkCtrl* HyperlinkCtrl3;
    wxStaticLine* StaticLine1;
    wxStaticText* StaticText1;
    //*)

protected:

    //(*Identifiers(Component_error)
    static const long ID_STATICTEXT1;
    static const long ID_HYPERLINKCTRL1;
    static const long ID_HYPERLINKCTRL2;
    static const long ID_HYPERLINKCTRL3;
    static const long ID_STATICLINE1;
    //*)

private:

    //(*Handlers(Component_error)
    void OnInit(wxInitDialogEvent& event);
    void OnHyperlinkCtrl1Click(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
