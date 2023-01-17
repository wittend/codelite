#include "LSPNetworkSTDIO.h"

#include "ChildProcess.h"
#include "JSON.h"
#include "LSP/basic_types.h" // needed for the debugging macros
#include "asyncprocess.h"
#include "cl_exception.h"
#include "clcommandlineparser.h"
#include "dirsaver.h"
#include "file_logger.h"
#include "processreaderthread.h"
#include "sftp_settings.h"

#include <sstream>

static const char separator_str[] = "\n************\n";
static size_t separator_str_len = sizeof(separator_str) - 1;

LSPNetworkSTDIO::LSPNetworkSTDIO() { LSP::Initialise(); }

LSPNetworkSTDIO::~LSPNetworkSTDIO() { Close(); }

void LSPNetworkSTDIO::Close() { wxDELETE(m_server); }

void LSPNetworkSTDIO::Open(const LSPStartupInfo& siInfo)
{
    m_startupInfo = siInfo;

    // Start the LSP server first
    Close();
    DoStartLocalProcess();
}

void LSPNetworkSTDIO::Send(const std::string& data)
{
    if(m_server) {
        m_server->Write(data);
        LSP_DEBUG() << data << endl;
    } else {
        LSP_WARNING() << "LSPNetworkSTDIO: no process !?" << endl;
    }
}

bool LSPNetworkSTDIO::IsConnected() const { return m_server != nullptr; }

void LSPNetworkSTDIO::OnProcessTerminated(clProcessEvent& event)
{
    wxDELETE(m_server);
    LSP_DEBUG() << "LSPNetworkSTDIO: program terminated:" << m_startupInfo.GetLspServerCommand() << endl;
    LSP_DEBUG() << "LSPNetworkSTDIO:" << event.GetString() << endl;
    clCommandEvent evt(wxEVT_LSP_NET_ERROR);
    AddPendingEvent(evt);
}

void LSPNetworkSTDIO::OnProcessOutput(clProcessEvent& event)
{
    const wxString& dataRead = event.GetOutput();
    clCommandEvent evt(wxEVT_LSP_NET_DATA_READY);
    evt.SetString(dataRead);

    LSP_DEBUG() << dataRead << endl;

    AddPendingEvent(evt);
}

void LSPNetworkSTDIO::OnProcessStderr(clProcessEvent& event)
{
    LSP_DEBUG() << "[**STDERR**]" << event.GetOutput() << endl;
}

void LSPNetworkSTDIO::DoStartLocalProcess()
{
    m_server = new ChildProcess();
    BindEvents();

    DirSaver ds;
    if(!m_startupInfo.GetWorkingDirectory().IsEmpty() && wxFileName::DirExists(m_startupInfo.GetWorkingDirectory())) {
        ::wxSetWorkingDirectory(m_startupInfo.GetWorkingDirectory());
    }

    wxArrayString args = m_startupInfo.GetLspServerCommand();
    try {
        m_server->Start(args);

    } catch(clException& e) {
        clERROR() << "failed to execute LSP proceess with args:" << args << endl;
        clERROR() << e.What() << endl;
        clCommandEvent eventError(wxEVT_LSP_NET_ERROR);
        eventError.SetString(e.What());
        AddPendingEvent(eventError);
        return;
    }

    clCommandEvent evtReady(wxEVT_LSP_NET_CONNECTED);
    AddPendingEvent(evtReady);
    LSP_DEBUG() << wxString("\n\n  =============== Process Started ===============  \n\n") << endl;
}

void LSPNetworkSTDIO::BindEvents()
{
    m_server->Bind(wxEVT_ASYNC_PROCESS_OUTPUT, &LSPNetworkSTDIO::OnProcessOutput, this);
    m_server->Bind(wxEVT_ASYNC_PROCESS_STDERR, &LSPNetworkSTDIO::OnProcessStderr, this);
    m_server->Bind(wxEVT_ASYNC_PROCESS_TERMINATED, &LSPNetworkSTDIO::OnProcessTerminated, this);
}