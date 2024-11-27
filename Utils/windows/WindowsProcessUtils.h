#pragma once
#include "WindowsDef.h"

#include <vector>
#include <string>

namespace utils {
    namespace windows {
        namespace process {
            bool KillProcess(DWORD pid);
            bool WriteProcess(DWORD pid, const std::vector<byte>& buffer);
            HANDLE DuplicateProcessToken(DWORD pid);
            std::vector<DWORD> FindProcess(const std::wstring& name);
            std::wstring GetProcessPathWithoutOpen(DWORD pid);
            std::wstring GetProcessPath(DWORD pid);
            std::wstring GetProcessCommandLine(DWORD pid);
        };  // namespace process
    };  // namespace windows
};  // namespace utils
