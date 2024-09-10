/***************************************************************
 * Name:      HDL_Batch_installerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    matias israelson (aka: El_isra) (tatochin-m@hotmail.com)
 * Created:   2021-03-31
 * Copyright: matias israelson (aka: El_isra) (https://github.com/israpps)
 * License:   GPL-3.0
 **************************************************************/
#include "HDL_Batch_installerApp.h"
#include "UpdateMan.h"
#include "flags.h"
#include <wx/snglinst.h>

//(*AppHeaders
#include "HDL_Batch_installerMain.h"
#include <wx/image.h>
//*)
extern wxString versionTAG;
extern wxString HDLBINST_APPDATA;
IMPLEMENT_APP(HDL_Batch_installerApp);
//wxIMPLEMENT_APP_CONSOLE(HDL_Batch_installerApp);
wxString Get_env(wxString ENV);
bool HDL_Batch_installerApp::OnInit()
{

    wxSingleInstanceChecker* instance_chk = new wxSingleInstanceChecker;
    if (instance_chk->IsAnotherRunning() && (!wxFileExists("Common\\multi_instance.opt")) )
    {
        wxLogError(_("Another program instance is already running, aborting."));

        delete instance_chk; // OnExit() won't be called if we return false
        instance_chk = nullptr;

        return false;
    }
    bool first_time = false;
    const wxString DOWNLOAD_COMMAND    = "Common\\wget -q --show-progress https://github.com/israpps/HDL-Batch-installer/raw/main/svr/_ICN.7z -O Common\\_ICN.7z",
                   EXTRACTION_COMMAND = "Common\\7z.exe x -oCommon -bso0 -pPDPA -y Common\\_ICN.7z";

    if (!wxApp::OnInit()) return false;
    wxInitAllImageHandlers();
    wxBitmap BANNER = wxBITMAP_PNG(MAIN_BANNER);

    wxSplashScreen *SPLASH_SCREEN = new wxSplashScreen(BANNER, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,2500, NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFRAME_NO_TASKBAR|wxSIMPLE_BORDER|wxSTAY_ON_TOP);

    HDLBINST_APPDATA = wxString::Format("%s\\HDLBInst",Get_env("appdata"));
    std::cout <<"HDLBINST_APPDATA ["<< HDLBINST_APPDATA <<"]\n";
    if (!wxDirExists(HDLBINST_APPDATA))
        wxMkDir(HDLBINST_APPDATA);

    first_time = (!wxFileExists("Common\\tinmft.sys"));

    int fake_argc = wxTheApp->argc;
    wxString fake_argv[fake_argc], svr_ver;
    wxArrayString unused_buffer;
    long ping = -1, custom_styles = 0, scoped_flags = 0, ctor_flags = 0;
    bool wxsOK = true, check_updates, new_ver_available = false;
    COLOR(07)///normalize console color
    ///---------------------construct-version-string----------------------///
    versionTAG = "v";
    versionTAG.append(wxString::Format(wxT("%i"),AutoVersion::MAJOR));
    versionTAG.append(".");
    versionTAG.append(wxString::Format(wxT("%i"),AutoVersion::MINOR));
    versionTAG.append(".");
    versionTAG.append(wxString::Format(wxT("%i"),AutoVersion::BUILD));
    versionTAG.append(" - Revision ");
    versionTAG.append(wxString::Format(wxT("%i"),AutoVersion::REVISION));
    ///-------------------------------------------------------------------///

    wxFileName fname( wxTheApp->argv[0] );
    wxString config_file = fname.GetPath(wxPATH_GET_VOLUME|wxPATH_GET_SEPARATOR) + "Common\\config.INI";
    wxFileConfig * main_config = new wxFileConfig( wxEmptyString, wxEmptyString, config_file);
    main_config->Read("Init/check_for_updates",&check_updates,true);
    /// Lang init

    if ( m_lang == wxLANGUAGE_UNKNOWN )
    {
        int lng;
        main_config->Read("Init/language",&lng,0);
        m_lang = lng == -1 ? wxLANGUAGE_DEFAULT : langIds[lng];
        std::cout <<"Loading lang ID ["<< lng <<"]\n";
    }
    if ( !m_locale.Init(m_lang, wxLOCALE_DONT_LOAD_DEFAULT) )
        wxLogWarning(_("This language is not supported by the system."));
    ///-lang init
    ///catalog init and search:
    wxLocale::AddCatalogLookupPathPrefix("./Lang");
    const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(m_lang);
    if (!m_locale.AddCatalog("HDLBinst"))///add program specific catalog
    {
        COLOR(0c)
        std::cout << wxString::Format(_("Couldn't find/load the 'HDLBinst' catalog for locale '%s'.\nThe translation file must be placed here: \"Lang\\%s\\HDLBinst.mo\"\n"),
                                      pInfo ? pInfo->GetLocaleName() : _("unknown"),
                                      m_locale.GetCanonicalName());
        COLOR(07)
    }
    if (!m_locale.AddCatalog("wxstd"))///add wxwidgets standard catalog
        std::cerr << "can't find wxstd.mo\n";
    if (fake_argc > 1)
    {
        COLOR(0e)
        std::cout << "init arguments detected...\n";
        COLOR(07)
        for (int x=0; x<fake_argc; x++)
        {
            fake_argv[x] = wxTheApp->argv[x];   ///populate scoped variable with argv[]
        }

        for (int x=1; x<fake_argc; x++)
        {
            if (fake_argv[x].IsSameAs("--force-max-debug") || fake_argv[x].IsSameAs("-fmd"))
            {
                std::cout << "\t arguments passed to program are:\n";
                ctor_flags |= FORCE_HIGH_DEBUG_LEVEL;
                COLOR(0f)
                for (int x=0; x < wxTheApp->argc; x++)
                {
                    std::cout << "argv[" << x <<"] = [" << fake_argv[x] << "]\n";
                }
                COLOR(0e)
                std::cout << " -- Forcing high debug data...\n";
                COLOR(07)
            }
            if (fake_argv[x].IsSameAs("--stay-on-top") || fake_argv[x].IsSameAs("-sot"))
            {
                COLOR(0e)
                std::cout << " -- GUI will stay on top...\n";
                COLOR(07)
                custom_styles |= wxSTAY_ON_TOP;
            }
            if (fake_argv[x].IsSameAs("--skip-update") || fake_argv[x].IsSameAs("-nup"))
            {
                COLOR(0e)
                std::cout << " -- skipping updates...\n";
                COLOR(07)
                check_updates = false;
            }
            if (fake_argv[x].IsSameAs("--redirect-text") || fake_argv[x].IsSameAs("-rdl"))
            {
                COLOR(0e)
                std::cout << " -- Redirecting text from console into log files...\n";
                COLOR(07)
                scoped_flags |= REDIRECT_OUTPUT;
            }
        }
    }
    if (scoped_flags & REDIRECT_OUTPUT)
    {
        if (!wxDirExists("logs")) wxMkdir("logs");
        freopen("logs/stdout.log","a",stdout);
        std::cout <<"---stdout redirection init---\n";
        freopen("logs/stderr.log","a",stderr);
        std::cerr <<"---stdeer redirection init---\n";
    }

    ping = wxExecute("ping google.com",unused_buffer,wxEXEC_SYNC);

    if (ping == 0)
    {
        if (!wxFileExists("Common\\_ICN.7z"))
        {
            std::cout << "icon package is missing. pulling copy from svr...\n";
            wxExecute(DOWNLOAD_COMMAND, wxEXEC_SYNC);
        }

        if ((!wxFileExists("Common\\Icons.INI") || !wxDirExists("Common\\ICNS")) && wxFileExists("Common\\_ICN.7z"))
        {
            std::cout << "icon manifest is missing. unpacking icons...\n";
            wxExecute(EXTRACTION_COMMAND, wxEXEC_SYNC);
        }
    }

    if (check_updates)
    {
        printf("Checking for updates...\n");
        long ping2 = -1;
        if (ping == 0)
        {
            printf("we have internet! Checking for Updates...\n");
            unused_buffer.clear();
            ping2 = wxExecute("Common\\WGET.EXE -q https://raw.githubusercontent.com/israpps/HDL-Batch-installer/main/svr/VERSION -O -",unused_buffer,wxEXEC_SYNC);
            if (ping2 == 0)
            {
                //for (size_t x = 0 ; x<unused_buffer.GetCount() ; x++) {svr_ver << unused_buffer.Item(x);}
                svr_ver = unused_buffer.Item(0);
                if (svr_ver[0] == 'v')
                {
                    printf("sucessfully recovered version tag from github\n");
                    if (svr_ver != versionTAG)
                    {
                        printf("New version available\n");
                        new_ver_available = true;
                    }
                    else
                    {
                        COLOR(0a)
                        printf("this version is the latest release!\n");
                        COLOR(07)
                    }
                }
                else
                {
                    COLOR(0c) printf("invalid data recovered from github, skipping update check...\n");
                    COLOR(07)
                }
            }
            else
            {
                printf("Failed to connect to github repository (%ld)\n",ping2);
                new_ver_available = false;
            }
        }
        else
        {
            printf("No interned connection (%ld)\n",ping);
            new_ver_available = false;
        }
    }
    else
    {
        new_ver_available = false;
    }

    SPLASH_SCREEN->Hide();
    HDL_Batch_installerFrame* Frame = new HDL_Batch_installerFrame(nullptr ,m_locale,custom_styles,ctor_flags);
    delete SPLASH_SCREEN;
    if (new_ver_available)
    {
        UpdateMan* A = new UpdateMan(nullptr, svr_ver, versionTAG);
        if (A->ShowModal() == wxYES)
            wxLaunchDefaultBrowser("https://github.com/israpps/HDL-Batch-installer/releases");
    }
    if (first_time)
    {
        wxFile A("Common\\tinmft.sys",wxFile::write);
        A.Write("What are you looking for?\n");
        A.Close();
        wxExecute("wmic os get Caption", unused_buffer, wxEXEC_ASYNC);
        for (size_t x = 0; x < unused_buffer.GetCount(); x++)
        {
            if (unused_buffer.Item(x).Contains("Windows 11"))
            {
                COLOR(0c)
                std::cout << "-- winver: " << unused_buffer.Item(x) << "\n";
                COLOR(07)
                wxMessageBox(_("Windows 11 and some anti-virus software will detect HDL-Batch-Installer and underlying tools as ransomware "
                            "due to accessing PS2 HDDs via RAW I/O (Because windows does not understand their format)\n"
                            "If game installation gives error 5, some issue related with permissions or \"disk is not ready\" "
                            "please consider whitelisting on your defender/AV the HDL batch installer exe, along with HDL.EXE and pfsfuse.exe "
                            "from program folder."), _("Windows 11 detected"), wxICON_WARNING);
                break;
            }
        }
    }
    delete main_config;
    Frame->Show();
    SetTopWindow(Frame);
    return wxsOK;
}

void HDL_Batch_installerApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}

bool HDL_Batch_installerApp::OnCmdLineParsed(wxCmdLineParser& parser)
{

    // to get at your unnamed parameters use
    wxArrayString files;
    for (size_t i = 0; i < parser.GetParamCount(); i++)
    {
        files.Add(parser.GetParam(i));
    }

    // and other command line parameters

    // then do what you need with them.

    return true;
}
