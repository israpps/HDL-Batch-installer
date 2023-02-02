#ifndef HDDMANAGER_H
#define HDDMANAGER_H

//(*Headers(HDDManager)
#include <wx/dialog.h>
//*)

class HDDManager: public wxDialog
{
	public:

		HDDManager(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~HDDManager();

		//(*Declarations(HDDManager)
		//*)

	protected:

		//(*Identifiers(HDDManager)
		//*)

	private:

		//(*Handlers(HDDManager)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
