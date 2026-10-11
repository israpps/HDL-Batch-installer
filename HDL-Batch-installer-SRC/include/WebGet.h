/***************************************************************
 * Name:      WebGet.h
 * Purpose:   Cross-platform replacements for the "Common\WGET.EXE ..." /
 *            "ping google.com" wxExecute() calls, which only work on Windows
 *            and depend on a bundled wget.exe. Implemented with wxWebRequest,
 *            which ships with wxWidgets itself on every platform.
 **************************************************************/
#ifndef HDLBINST_WEBGET_H
#define HDLBINST_WEBGET_H

#include <wx/string.h>
#include <wx/arrstr.h>

/// Fetches `url` synchronously and splits the response body into lines, the same shape
/// the old "WGET.EXE -q <url> -O -" + wxExecute(..., data, wxEXEC_SYNC) call produced in
/// its output array. Returns true only on a successful (HTTP 200) response.
bool WebGetLines(const wxString& url, wxArrayString& lines);

/// Replacement for the old "ping google.com" connectivity check. Returns true as soon as
/// any HTTP response (even an error status) comes back from `url`, since that's enough to
/// prove the network/DNS/TLS stack is working; only a hard failure (no connection, DNS
/// failure, timeout) counts as "offline". Defaults to a small, reliable endpoint.
bool WebIsReachable(const wxString& url = "https://github.com");

#endif // HDLBINST_WEBGET_H
