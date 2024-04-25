#ifndef PFSSHELLBROWSER_H
#define PFSSHELLBROWSER_H

//(*Headers(PFSShellBrowser)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/listctrl.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
//*)

class PFSShellBrowser: public wxDialog
{
	public:

		PFSShellBrowser(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PFSShellBrowser();

		//(*Declarations(PFSShellBrowser)
		wxButton* CloseHDD;
		wxButton* OpenHDD;
		wxChoice* HDDRealDLG;
		wxFilePickerCtrl* HDDFileDLG;
		wxListCtrl* FileList;
		wxRadioButton* HDDFileRadio;
		wxRadioButton* HDDRealRadio;
		//*)

	protected:

		//(*Identifiers(PFSShellBrowser)
		static const long ID_RADIOBUTTON1;
		static const long ID_CHOICE1;
		static const long ID_RADIOBUTTON2;
		static const long ID_FILEPICKERCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_LISTCTRL1;
		//*)

	private:
        void RefreshList(void);

		//(*Handlers(PFSShellBrowser)
		void OnHDDRealRadioSelect(wxCommandEvent& event);
		void OnHDDFileRadioSelect(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnFileListItemActivated(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
