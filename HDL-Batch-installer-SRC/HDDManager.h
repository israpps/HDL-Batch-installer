#ifndef HDDMANAGER_H
#define HDDMANAGER_H
#include "iomanX_port.h"
#include <vector>
//(*Headers(HDDManager)
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
//*)

class HDDManager: public wxDialog
{
	public:

		HDDManager(wxWindow* parent, std::string HDDTOK,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HDDManager();

		//(*Declarations(HDDManager)
		wxListCtrl* PARTList;
		//*)

	protected:

		//(*Identifiers(HDDManager)
		static const long ID_LISTCTRL1;
		//*)

	private:
        std::string HDD_TOKEN;
        std::vector<iox_dirent_t> PART_LIST;
		//(*Handlers(HDDManager)
		void OnPARTListBeginDrag(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
