/***************************************************************
 * Name:      Config.h
 * Purpose:   Code for Configurations editor
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

//(*Headers(Config)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
//*)
#include <wx/msgdlg.h>
#include <string>
#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/app.h>

#include "include/macro-vault.h"

class Config: public wxDialog
{
public:

    Config(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~Config();

    //(*Declarations(Config)
    wxButton* Button1;
    wxCheckBox* AllowExperimental;
    wxCheckBox* CUSTOM_ICONS;
    wxCheckBox* DATA_COLLECTION;
    wxCheckBox* HDDManagerGPD;
    wxCheckBox* HDDManagerSubPartDSP;
    wxCheckBox* check_updates;
    wxCheckBox* miniopl_warning;
    wxCheckBox* osd_hide_settings;
    wxChoice* MountPoint;
    wxChoice* default_dma;
    wxComboBox* language_choice;
    wxDirPickerCtrl* ISO_PATH_HOLDER;
    wxNotebook* Notebook1;
    wxPanel* Panel1;
    wxPanel* Panel2;
    wxRadioButton* gndb_extern;
    wxRadioButton* gndb_intern;
    wxTextCtrl* OPLPART;
    //*)

protected:

    //(*Identifiers(Config)
    static const long ID_CHECKBOX3;
    static const long ID_COMBOBOX1;
    static const long ID_CHECKBOX1;
    static const long ID_CHECKBOX2;
    static const long ID_CHECKBOX4;
    static const long ID_CHECKBOX6;
    static const long ID_CHECKBOX7;
    static const long ID_CHECKBOX8;
    static const long ID_CHECKBOX5;
    static const long ID_RADIOBUTTON1;
    static const long ID_RADIOBUTTON2;
    static const long ID_DIRPICKERCTRL1;
    static const long ID_CHOICE1;
    static const long ID_PANEL1;
    static const long ID_CHOICE2;
    static const long ID_TEXTCTRL1;
    static const long ID_PANEL2;
    static const long ID_NOTEBOOK1;
    static const long ID_BUTTON1;
    //*)

private:

    //(*Handlers(Config)
    void OnInit(wxInitDialogEvent& event);
    void OnButton2Click(wxCommandEvent& event);
    void OnRadioButton2Select(wxCommandEvent& event);
    void Ongndb_internSelect(wxCommandEvent& event);
    void OnButton2Click1(wxCommandEvent& event);
    void OnOSD_HIDE_SETTING_HELPClick(wxCommandEvent& event);
    void OnISO_DEFAULT_PATHDirChanged(wxFileDirPickerEvent& event);
    void OnHyperlinkCtrl1Click(wxCommandEvent& event);
    void Ondefault_dmaSelect(wxCommandEvent& event);
    void Onlanguage_choiceSelect(wxCommandEvent& event);
    void OnNotebook1PageChanged(wxNotebookEvent& event);
    void OnSaveDataRequest(wxCommandEvent& event);
    void OnCheckBox1Click(wxCommandEvent& event);
    //*)
    void SaveSettings(void);
    DECLARE_EVENT_TABLE()
};

const char mountpoints[25] =
{
    'A','B','D','E','F',
    'G','H','I','J','K',
    'L','M','N','O','P',
    'Q','R','S','T','U',
    'V','W','X','Y','Z'
};// C skipped because it will be used for sure
struct fuse_t
{
    wxString mountpoint;
    wxString default_OPLPART;
};

struct config_t
{
    int         debug_level;
    wxString    Default_iso_path;
    bool        DataBase_Mode;
    bool        MiniOPL;
    int         Language;
    int         Default_dma;
    bool        OSD_Hide;
    bool        check_updates;
    bool        custom_icons;
    bool        collect_onkown_games_ID;
    bool        allow_experimental;
    bool        HDDManagerGameTitleDISP;
    bool        HDDManagerDisplaySubpart;
    fuse_t      FUSE;
    wxString    NBD_IP;
};
#endif
