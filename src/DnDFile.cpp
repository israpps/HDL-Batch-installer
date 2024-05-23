#include "DnDFile.h"


bool DnDFile::OnDropFiles(wxCoord, wxCoord, const wxArrayString& filenames)
{
    size_t nFiles = filenames.GetCount();
    std::cout << nFiles << " files dropped\n";
    if (m_pOwner != nullptr)
    {
        for ( size_t n = 0; n < nFiles; n++ ) {
            //std::cout << filenames[n] << "\n";
            m_pOwner->InsertItem(0, filenames[n]);
            //OnDropFiles_aditional(filenames[n]);
        }
    }

    return true;
}

bool DnDFile::OnDropFiles_aditional(const wxString individual_item) {

}
