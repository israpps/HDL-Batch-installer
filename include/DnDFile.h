#ifndef DNDFILE_H
#define DNDFILE_H
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/arrstr.h>
#include <wx/dnd.h>




class DnDFile : public wxFileDropTarget
{
public:
    DnDFile(wxListCtrl *pOwner = nullptr) { m_pOwner = pOwner; }

    virtual bool OnDropFiles(wxCoord x, wxCoord y,
                             const wxArrayString& filenames) override;
    bool OnDropFiles_aditional(const wxString individual_item);

private:
    wxListCtrl *m_pOwner;
};
#define DND_CONNECT(x) \
    x->SetDropTarget(new DnDFile(x));
//x->SetDropTarget(new DnDFile<y>(&y::OnDropFiles, this));


#endif // DNDFILE_H
