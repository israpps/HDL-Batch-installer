#ifndef PFSSHELLBROWSER_H
#define PFSSHELLBROWSER_H

//(*Headers(PFSShellBrowser)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
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
		wxMenu BrowserMenu;
		wxMenuItem* MenuItem1;
		wxMenuItem* MenuItem2;
		wxMenuItem* MenuItem3;
		wxMenuItem* MenuItem4;
		wxRadioButton* HDDFileRadio;
		wxRadioButton* HDDRealRadio;
		//*)

	protected:
        wxImageList *IMGLIST;

		//(*Identifiers(PFSShellBrowser)
		static const long ID_RADIOBUTTON1;
		static const long ID_CHOICE1;
		static const long ID_RADIOBUTTON2;
		static const long ID_FILEPICKERCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_LISTCTRL1;
		static const long ID_MENUITEM1;
		static const long ID_MENUITEM2;
		static const long ID_MENUITEM3;
		static const long ID_MENUITEM4;
		//*)

	private:
        void RefreshList(void);
        void OnDropFiles(wxDropFilesEvent& event);

		//(*Handlers(PFSShellBrowser)
		void OnHDDRealRadioSelect(wxCommandEvent& event);
		void OnHDDFileRadioSelect(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnFileListItemActivated(wxListEvent& event);
		void OnFileListItemRClick(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
