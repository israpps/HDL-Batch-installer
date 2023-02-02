#include "HDDManager.h"

//(*InternalHeaders(HDDManager)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(HDDManager)
//*)

BEGIN_EVENT_TABLE(HDDManager,wxDialog)
	//(*EventTable(HDDManager)
	//*)
END_EVENT_TABLE()

HDDManager::HDDManager(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(HDDManager)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	//*)
}

HDDManager::~HDDManager()
{
	//(*Destroy(HDDManager)
	//*)
}

