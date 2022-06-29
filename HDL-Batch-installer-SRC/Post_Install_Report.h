#ifndef POST_INSTALL_REPORT_H
#define POST_INSTALL_REPORT_H

//(*Headers(Post_Install_Report)
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

class Post_Install_Report: public wxDialog
{
public:

    Post_Install_Report(wxWindow* parent, wxArrayString filepath, wxArrayString reason, wxArrayString ELF, wxArrayString media, wxWindowID id=wxID_ANY);
    virtual ~Post_Install_Report();

    //(*Declarations(Post_Install_Report)
    wxListCtrl* list;
    wxStaticText* StaticText1;
    //*)

protected:

    //(*Identifiers(Post_Install_Report)
    static const long ID_STATICTEXT1;
    static const long ID_LISTCTRL1;
    //*)

private:
    wxArrayString _filepath;
    wxArrayString _reason;
    wxArrayString _ELF;
    wxArrayString _media;
    //(*Handlers(Post_Install_Report)
    void OnlistBeginDrag(wxListEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
