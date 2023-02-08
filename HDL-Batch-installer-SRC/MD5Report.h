#ifndef MD5REPORT_H
#define MD5REPORT_H

//(*Headers(MD5Report)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class MD5Report: public wxDialog
{
	public:

		MD5Report(wxWindow* parent, wxString _FILEPATH, wxString _HASH,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~MD5Report();

		//(*Declarations(MD5Report)
		wxButton* redumpsearch;
		wxStaticText* FILENAME;
		wxTextCtrl* DHASH;
		//*)

	protected:

		//(*Identifiers(MD5Report)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:
        wxString FILEPATH;
        wxString HASH;
		//(*Handlers(MD5Report)
		void OnredumpsearchClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
