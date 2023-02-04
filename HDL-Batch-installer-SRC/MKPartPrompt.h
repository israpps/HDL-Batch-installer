#ifndef MKPARTPROMPT_H
#define MKPARTPROMPT_H

//(*Headers(MKPartPrompt)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
//*)

class MKPartPrompt: public wxDialog
{
	public:

		MKPartPrompt(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~MKPartPrompt();

		//(*Declarations(MKPartPrompt)
		wxButton* Create;
		wxChoice* FileSystem;
		wxSpinCtrl* SizeSpinCtrl;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(MKPartPrompt)
		static const long ID_TEXTCTRL1;
		static const long ID_CHOICE1;
		static const long ID_SPINCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(MKPartPrompt)
		void OnCreateClick(wxCommandEvent& event);
		void OnSizeSpinCtrlChange(wxSpinEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
