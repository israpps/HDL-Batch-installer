/***************************************************************
 * Name:      About.h
 * Purpose:   Code for Credits window
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef ABOUT_H
#define ABOUT_H
#include "version.h"
//(*Headers(About)
#include <wx/dialog.h>
#include <wx/hyperlink.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class About: public wxDialog
{
public:

    About(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~About();

    //(*Declarations(About)
    wxHyperlinkCtrl* HyperlinkCtrl1;
    wxHyperlinkCtrl* HyperlinkCtrl2;
    wxStaticLine* StaticLine1;
    wxStaticLine* StaticLine2;
    wxStaticLine* StaticLine3;
    wxStaticLine* StaticLine4;
    wxStaticText* StaticText10;
    wxStaticText* StaticText11;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticText3;
    wxStaticText* StaticText4;
    wxStaticText* StaticText5;
    wxStaticText* StaticText8;
    //*)

protected:

    //(*Identifiers(About)
    static const long ID_STATICTEXT1;
    static const long ID_HYPERLINKCTRL1;
    static const long ID_STATICTEXT2;
    static const long ID_STATICTEXT3;
    static const long ID_STATICTEXT5;
    static const long ID_STATICTEXT8;
    static const long ID_STATICTEXT10;
    static const long ID_STATICLINE1;
    static const long ID_STATICLINE2;
    static const long ID_STATICLINE3;
    static const long ID_STATICTEXT4;
    static const long ID_HYPERLINKCTRL2;
    static const long ID_STATICLINE4;
    static const long ID_STATICTEXT11;
    //*)

private:

    //(*Handlers(About)
    void OnVersionText(wxCommandEvent& event);
    void OnBuild_dateText(wxCommandEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnPaint(wxPaintEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
