#ifndef UPDATEMAN_H
#define UPDATEMAN_H

//(*Headers(UpdateMan)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class UpdateMan: public wxDialog
{
	public:

		UpdateMan(wxWindow* parent, wxString newv, wxString oldv ,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~UpdateMan();

		//(*Declarations(UpdateMan)
		wxButton* CANCEL;
		wxButton* OK;
		wxStaticText* heading;
		wxTextCtrl* UpdateDetails;
		//*)

	protected:

		//(*Identifiers(UpdateMan)
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(UpdateMan)
		void OnOKClick(wxCommandEvent& event);
		void OnCANCELClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
