#ifndef MKPARTDLG_H
#define MKPARTDLG_H

//(*Headers(mkpartdlg)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class mkpartdlg: public wxDialog
{
	public:

		mkpartdlg(wxWindow* parent, bool* smth_changed=NULL,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~mkpartdlg();

		//(*Declarations(mkpartdlg)
		wxButton* mkpart;
		wxSlider* HDDSize;
		wxStaticText* GB;
		wxStaticText* MB;
		wxTextCtrl* PARTName;
		//*)

	protected:

		//(*Identifiers(mkpartdlg)
		static const long ID_TEXTCTRL1;
		static const long ID_SLIDER1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(mkpartdlg)
		void OnmkpartClick(wxCommandEvent& event);
		void OnSlider1CmdScrollChanged(wxScrollEvent& event);
		void onPartitionNameChange(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
