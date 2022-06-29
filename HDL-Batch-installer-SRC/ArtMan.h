/***************************************************************
 * Name:      Component_error.h
 * Purpose:   Code for art manager frame
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#ifndef ARTMAN_H

#define ARTMAN_H

//(*Headers(ArtMan)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
//*)

#include <wx/arrstr.h>
#include <iostream>
#include "include/macro-vault.h"
#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/file.h>
//#include <map>

class ArtMan: public wxDialog
{
public:

    ArtMan(wxWindow* parent,
           wxArrayString ELF,
           wxWindowID id=wxID_ANY,
           const wxPoint& pos=wxDefaultPosition,
           const wxSize& size=wxDefaultSize);
    virtual ~ArtMan();
    wxArrayString ELF_t;
    //(*Declarations(ArtMan)
    wxButton* download;
    wxCheckBox* FAST;
    wxCheckBox* bg;
    wxCheckBox* cfg;
    wxCheckBox* cht;
    wxCheckBox* cov2;
    wxCheckBox* cov;
    wxCheckBox* ico;
    wxCheckBox* lab;
    wxCheckBox* lgo;
    wxCheckBox* markall;
    wxCheckBox* others_markall;
    wxCheckBox* scr;
    wxCheckBox* scr_2;
    wxStaticBox* StaticBox1;
    wxStaticBox* StaticBox2;
    wxStaticLine* StaticLine10;
    wxStaticLine* StaticLine11;
    wxStaticLine* StaticLine12;
    wxStaticLine* StaticLine1;
    wxStaticLine* StaticLine2;
    wxStaticLine* StaticLine3;
    wxStaticLine* StaticLine4;
    wxStaticLine* StaticLine5;
    wxStaticLine* StaticLine6;
    wxStaticLine* StaticLine7;
    wxStaticLine* StaticLine8;
    wxStaticLine* StaticLine9;
    wxTextCtrl* TextCtrl1;
    //*)

protected:

    //(*Identifiers(ArtMan)
    static const long ID_BUTTON1;
    static const long ID_STATICBOX1;
    static const long ID_CHECKBOX2;
    static const long ID_CHECKBOX1;
    static const long ID_CHECKBOX3;
    static const long ID_CHECKBOX4;
    static const long ID_CHECKBOX5;
    static const long ID_CHECKBOX6;
    static const long ID_CHECKBOX7;
    static const long ID_CHECKBOX8;
    static const long ID_TEXTCTRL1;
    static const long ID_STATICLINE1;
    static const long ID_CHECKBOX9;
    static const long ID_STATICLINE2;
    static const long ID_STATICLINE3;
    static const long ID_STATICLINE4;
    static const long ID_STATICLINE5;
    static const long ID_STATICLINE6;
    static const long ID_STATICLINE7;
    static const long ID_STATICLINE8;
    static const long ID_STATICLINE9;
    static const long ID_STATICBOX2;
    static const long ID_CHECKBOX10;
    static const long ID_CHECKBOX11;
    static const long ID_STATICLINE10;
    static const long ID_CHECKBOX12;
    static const long ID_STATICLINE11;
    static const long ID_STATICLINE12;
    static const long ID_CHECKBOX13;
    //*)

private:

    //(*Handlers(ArtMan)
    void OnInit(wxInitDialogEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OndownloadClick(wxCommandEvent& event);
    void OnmarkallClick(wxCommandEvent& event);
    void OndownloadClick1(wxCommandEvent& event);
    void Onothers_markallClick(wxCommandEvent& event);
    //*)
    long Request_art(wxString ELF, wxString suffix);
    void cleanup(void);
    //typedef std::pair<std::string, std::string> art_alias_t;
    //std::map<std::string, std::string> art_map;
    DECLARE_EVENT_TABLE()
};

#endif
