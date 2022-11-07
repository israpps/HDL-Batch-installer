#include "CopyHDD.h"

//(*InternalHeaders(CopyHDD)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/arrstr.h>
#include <iostream>
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include "include/macro-vault.h"

//(*IdInit(CopyHDD)
const long CopyHDD::ID_CHOICE1 = wxNewId();
const long CopyHDD::ID_STATICTEXT1 = wxNewId();
const long CopyHDD::ID_CHOICE2 = wxNewId();
const long CopyHDD::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CopyHDD,wxDialog)
    //(*EventTable(CopyHDD)
    //*)
END_EVENT_TABLE()

CopyHDD::CopyHDD(wxWindow* parent, wxArrayString HDDs, int selectedHDD, wxString COPY_LIST, wxWindowID id,const wxPoint& pos,const wxSize& size):
    HDDS(HDDs), SELECTED_HDD(selectedHDD), INSTALL_LIST(COPY_LIST)
{
    //(*Initialize(CopyHDD)
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Source"));
    Source = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    StaticBoxSizer1->Add(Source, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("---->"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
    BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Destination"));
    Destination = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    StaticBoxSizer2->Add(Destination, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND, 5);
    Transfer = new wxButton(this, ID_BUTTON1, _("Transfer games"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Transfer->Disable();
    FlexGridSizer1->Add(Transfer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&CopyHDD::OnHDDsSelection);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&CopyHDD::OnHDDsSelection);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CopyHDD::OnTransferClick);
    //*)
    std::cout << "HDD Game massive copying tool\n"<<HDDS.GetCount()<<" HDDs available\n";
    for (size_t x=0; x < HDDS.GetCount(); x++)
    {
        std::cout << "\t"<<HDDS.Item(x)<<"\n";
        Source->Append(HDDS.Item(x));
        Destination->Append(HDDS.Item(x));
    }
    if (selectedHDD > -1)
    {
        Source->SetSelection(selectedHDD);
        Source->Disable();
    }
}

CopyHDD::~CopyHDD()
{
    //(*Destroy(CopyHDD)
    //*)
}


void CopyHDD::OnTransferClick(wxCommandEvent& event)
{
    if (Source->GetString(Source->GetSelection()) == Destination->GetString(Destination->GetSelection()))
    {
        wxMessageBox(_("You can't transfer games from one HDD into the same HDD!"), "",wxICON_WARNING);
        return;
    }
    wxString COMMAND;
    COMMAND.Printf("HDL.EXE copy_hdd %s %s %s",
                   Source->GetString(Source->GetSelection()),
                   Destination->GetString(Destination->GetSelection()),
                   INSTALL_LIST
                  );
    wxProgressDialog* DLG = new wxProgressDialog(_("Transfering games..."), _("Please wait, this might take a while."));
    DLG->Update(99);
    COLOR(0d)
    wxExecute(COMMAND, wxEXEC_SYNC);
    COLOR(07)
    delete DLG;
    std::cout << "\nFinished!\n";
    wxMessageBox(_("Transfer Completed!"), "", wxICON_INFORMATION);
}

void CopyHDD::OnHDDsSelection(wxCommandEvent& event)
{
    Transfer->Enable((Source->GetSelection() != wxNOT_FOUND ) && (Destination->GetSelection() != wxNOT_FOUND ));
}
