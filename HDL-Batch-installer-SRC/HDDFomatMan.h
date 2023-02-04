#ifndef HDDFOMATMAN_H
#define HDDFOMATMAN_H

//(*Headers(HDDFomatMan)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
//*)

class HDDFomatMan: public wxDialog
{
	public:

		HDDFomatMan(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HDDFomatMan();

		//(*Declarations(HDDFomatMan)
		wxButton* Format;
		wxListCtrl* HDDList;
		//*)

	protected:

		//(*Identifiers(HDDFomatMan)
		static const long ID_LISTCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(HDDFomatMan)
		void OnFormatClick(wxCommandEvent& event);
		void OnHDDListItemSelect(wxListEvent& event);
		void OnHDDListItemDeselect(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
