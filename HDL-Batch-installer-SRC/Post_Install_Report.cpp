#include "Post_Install_Report.h"
#include <iostream>
//(*InternalHeaders(Post_Install_Report)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(Post_Install_Report)
const long Post_Install_Report::ID_STATICTEXT1 = wxNewId();
const long Post_Install_Report::ID_LISTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Post_Install_Report,wxDialog)
    //(*EventTable(Post_Install_Report)
    //*)
END_EVENT_TABLE()

Post_Install_Report::Post_Install_Report(wxWindow* parent, wxArrayString filepath, wxArrayString reason, wxArrayString ELF, wxArrayString media, wxWindowID id):
    _filepath(filepath), _reason(reason), _ELF(ELF), _media(media)
{
    //(*Initialize(Post_Install_Report)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE, _T("id"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("The Following games couldn\'t be installed:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    list = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(667,204), wxLC_REPORT|wxLC_VRULES|wxLC_NO_SORT_HEADER|wxBORDER_SUNKEN|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL1"));
    enum listid
    {
    FILE = 0,
    ID,
    MEDIA,
    REASON,
    };

    wxListItem col0;
    col0.SetId(0);
    col0.SetText( _("File ") );
    col0.SetWidth(200);
    list->InsertColumn(FILE , col0);

    // Add second column
    wxListItem col1;
    col1.SetId(1);
    col1.SetText( _("ID") );
    col1.SetWidth(140);
    list->InsertColumn(ID, col1);

    // Add third column
    wxListItem col2;
    col2.SetId(2);
    col2.SetText( _("Error code") );
    col2.SetWidth(50);
    list->InsertColumn(MEDIA, col2);

    // Add 4th column
    wxListItem col3;
    col3.SetId(3);
    col3.SetText( _("Reason") );
    col3.SetWidth(520);
    list->InsertColumn(REASON, col3);
    FlexGridSizer3->Add(list, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&Post_Install_Report::OnlistBeginDrag);
    //*)
    std::cout <<"> Failed installation summary:\n";
    for (size_t x=0; x< _filepath.GetCount(); x++)
    {
        std::cout <<"# "<<x<<"\n";
        long itemIndex =
            list->InsertItem(0, _filepath.Item(x));// col. 1
        std::cout <<  _filepath.Item(x)<<"\n";
        list->SetItem(itemIndex, ID, _ELF.Item(x)     );     // col. 2
        std::cout <<  _ELF.Item(x)<<"\n";
        list->SetItem(itemIndex, MEDIA, _media.Item(x)   );  // col. 2
        std::cout <<  _media.Item(x)<<"\n";
        list->SetItem(itemIndex, REASON, _reason.Item(x)  ); // col. 2
    }
    std::cout <<"-----------------------------\n";
}

Post_Install_Report::~Post_Install_Report()
{
    //(*Destroy(Post_Install_Report)
    //*)
}


void Post_Install_Report::OnlistBeginDrag(wxListEvent& event)
{
}
