#ifndef HDDMANAGER_H
#define HDDMANAGER_H
#include "iomanX_port.h"
#include <vector>
//(*Headers(HDDManager)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/sizer.h>
//*)

class HDDManager: public wxDialog
{
	public:

		HDDManager(wxWindow* parent, std::string HDDTOK,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HDDManager();

		//(*Declarations(HDDManager)
		wxButton* MKPart;
		wxListCtrl* PARTList;
		wxMenu HDDManagerMenu;
		wxMenuItem* MenuItem1;
		//*)

	protected:

		//(*Identifiers(HDDManager)
		static const long ID_LISTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_MENUITEM1;
		//*)

	private:
        std::string HDD_TOKEN;
        std::vector<iox_dirent_t> PART_LIST;
		//(*Handlers(HDDManager)
		void OnPARTListBeginDrag(wxListEvent& event);
		void OnPARTListItemRClick(wxListEvent& event);
		void OnPartitionDeleteRequest(wxCommandEvent& event);
		void OnMKPartClick(wxCommandEvent& event);
		//*)
        void UpdateList(void);

		DECLARE_EVENT_TABLE()
};

#endif
