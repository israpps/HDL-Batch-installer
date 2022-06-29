/***************************************************************
 * Name:      HDL_Batch_installerApp.h
 * Purpose:   Defines Application Class
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-03-31
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/

#ifndef HDL_BATCH_INSTALLERAPP_H
#define HDL_BATCH_INSTALLERAPP_H
//<>
#include <wx/splash.h>
#include <wx/filefn.h>
#include <wx/file.h>
#include <wx/app.h>
#include <wx/cmdline.h>
#include <iostream>
//""
#include "version.h"

class HDL_Batch_installerApp : public wxApp
{
public:
    HDL_Batch_installerApp()
    {
        m_lang = wxLANGUAGE_UNKNOWN;
    }
    virtual bool OnInit();
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
protected:
    wxLanguage m_lang;  // language specified by user
    wxLocale m_locale;  // locale we'll be using
};
//
static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
    {
        wxCMD_LINE_SWITCH, "h", "help", "displays help on the command line parameters",
        wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP
    },
    { wxCMD_LINE_SWITCH, "sot", "stay-on-top", "forces the GUI to stay on top of every program"},
    { wxCMD_LINE_SWITCH, "rdl", "redirect-text", "redirects log messages from console into two text files found inside log/ folder"},
    { wxCMD_LINE_SWITCH, "fmd", "force-max-debug", "forces the debug level to it's max value"},
    { wxCMD_LINE_NONE }
};

#endif // HDL_BATCH_INSTALLERAPP_H
