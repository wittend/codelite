#include "fmtClangFormat.hpp"

#include "Platform.hpp"

fmtClangFormat::fmtClangFormat()
{
    SetName("clang-format");
    SetFileTypes({ FileExtManager::TypeSourceCpp, FileExtManager::TypeSourceC, FileExtManager::TypeHeader,
                   FileExtManager::TypeJava, FileExtManager::TypeJS });
    SetDescription(_("A tool to format C/C++/Java/JavaScript/JSON/Objective-C/Protobuf/C# code"));
    SetHasConfigFile(true);
    SetConfigFilepath("$(WorkspacePath)/.clang-format");

    // local command
    wxString clang_format_exe;
    Platform::Which("clang-format", &clang_format_exe);
    SetCommand({ clang_format_exe, "$(CurrentFileFullPath)" });

    // remote command
    wxString remote_command = "\"";
    if(!GetWorkingDirectory().empty()) {
        remote_command << "cd " << GetWorkingDirectory() << " && ";
    }
    remote_command << "clang-format $(CurrentFileFullPath)\"";
    SetRemoteCommand({ "ssh", "$(SSH_User)@$(SSH_Host)", remote_command });
}

fmtClangFormat::~fmtClangFormat() {}