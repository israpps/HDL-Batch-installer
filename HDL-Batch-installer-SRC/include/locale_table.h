#ifndef LOCALE_TABLE_H_INCLUDED
#define LOCALE_TABLE_H_INCLUDED
#include <wx/string.h>
#include <wx/language.h>
#include <wx/debug.h>
#include <wx/defs.h>

static const wxLanguage langIds[] =
{
    wxLANGUAGE_DEFAULT,
    wxLANGUAGE_ENGLISH_US,
    wxLANGUAGE_SPANISH,
    wxLANGUAGE_ITALIAN,
    wxLANGUAGE_PORTUGUESE_BRAZILIAN,
    wxLANGUAGE_POLISH,
    wxLANGUAGE_KOREAN,
    wxLANGUAGE_RUSSIAN,
};

const wxString langNames[] =
{
    "System default",
    "English",
    "Spanish",
    "Italian",
    "Portuguese (br)",
    "Polish",
    "Korean",
    "Russian",
};
enum LANG_NUMS
{
    AUTO_DETECT = 0,
    ENGLISH,
    SPANISH,
    ITALIAN,
    PORTUGUESE_BR,
    POLISH,
    KOREAN,
    RUSSIAN,

    TOTAL_COUNT
};
// the arrays must be in sync
wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds),
                       LangArraysMismatch );
wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == LANG_NUMS::TOTAL_COUNT,
                       LangArraysMismatch );


#endif // LOCALE_TABLE_H_INCLUDED
