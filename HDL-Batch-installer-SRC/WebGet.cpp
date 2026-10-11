/***************************************************************
 * Name:      WebGet.cpp
 * Purpose:   Cross-platform replacements for the "Common\WGET.EXE ..." /
 *            "ping google.com" wxExecute() calls. See WebGet.h.
 **************************************************************/
#include "WebGet.h"

#include <wx/webrequest.h>
#include <wx/evtloop.h>
#include <wx/timer.h>
#include <wx/tokenzr.h>

namespace {

struct SyncResult
{
    bool done = false;
    bool gotResponse = false; // true as soon as ANY HTTP response came back, even an error one
    int httpStatus = 0;
    wxString body;
};

// wxWebRequest is asynchronous-only; this pumps the event loop ourselves until the request
// reaches a terminal state, which is what the old synchronous wxExecute(..., wxEXEC_SYNC)
// call used to give us directly. 15s is generous for the small text files this is used for.
const long kTimeoutMs = 15000;

SyncResult RunRequestSync(const wxString& url)
{
    SyncResult result;

    // wxWebRequest only drives its curl/WinHTTP/etc backend from an active wx event loop, so
    // when this is called before one exists yet (e.g. a startup check in OnInit(), before
    // MainLoop() has started) nothing would ever service the request and it would just sit
    // there until our own timeout below gave up. Running (and owning) a small event loop of
    // our own for the duration of this one request is the standard way to get a synchronous
    // wait out of an async-only wx API.
    wxEventLoop loop;
    wxEventLoopActivator activateLoop(&loop);

    // wxWebRequest delivers its events to a wxEvtHandler passed into CreateRequest() - it is
    // not an event source itself, so a plain local handler is enough to catch them.
    wxEvtHandler handler;
    handler.Bind(wxEVT_WEBREQUEST_STATE, [&result, &loop](wxWebRequestEvent& evt) {
        switch (evt.GetState())
        {
            case wxWebRequest::State_Completed:
            case wxWebRequest::State_Failed:
            case wxWebRequest::State_Cancelled:
            {
                const wxWebResponse& response = evt.GetResponse();
                // response.IsOk() alone isn't enough: it stays true even for a hard
                // connection failure (bad host, no route, TLS error, ...), where
                // GetStatus() is 0. A nonzero status is what actually proves a server
                // answered, even if that answer was an HTTP error.
                if (response.IsOk() && response.GetStatus() != 0)
                {
                    result.gotResponse = true;
                    result.httpStatus = response.GetStatus();
                    result.body = response.AsString();
                }
                result.done = true;
                loop.Exit();
                break;
            }
            default:
                break; // Idle / Unauthorized / Active: not terminal, keep waiting
        }
    });

    wxWebRequest request = wxWebSession::GetDefault().CreateRequest(&handler, url);
    if (!request.IsOk())
        return result;

    request.Start();

    // Backstop against a request that never reaches a terminal state at all: give up and
    // stop the loop after kTimeoutMs regardless (the small text files this is used for should
    // never legitimately take anywhere near this long).
    wxTimer timeoutTimer(&handler);
    handler.Bind(wxEVT_TIMER, [&loop](wxTimerEvent&) { loop.Exit(); });
    timeoutTimer.StartOnce(kTimeoutMs);

    loop.Run();

    return result;
}

} // namespace

bool WebGetLines(const wxString& url, wxArrayString& lines)
{
    const SyncResult result = RunRequestSync(url);
    if (!result.gotResponse || result.httpStatus != 200)
        return false;

    // Split on "\n" only (not "\r\n" as a delimiter set) so that a genuinely empty line still
    // produces exactly one empty entry - UpdateMan.cpp relies on that to find section breaks
    // in the changelog. Trim() below then drops the trailing '\r' a CRLF line leaves behind.
    lines = wxStringTokenize(result.body, "\n", wxTOKEN_RET_EMPTY_ALL);
    for (wxString& line : lines)
        line.Trim(); // trailing only: drop a leftover '\r', keep leading whitespace intact
    return true;
}

bool WebIsReachable(const wxString& url)
{
    // Any HTTP response at all - even a 4xx/5xx one - proves the network, DNS and TLS stack
    // are working, which is all the old "ping google.com" check was really verifying.
    return RunRequestSync(url).gotResponse;
}
