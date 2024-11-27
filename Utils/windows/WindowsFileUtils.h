#pragma once
#include "WindowsDef.h"

#include <string>

#define FILE_SHARE_ALL FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE

namespace utils {
    namespace windows {
        namespace file {
            bool FileExists(const std::wstring& path);
            std::wstring NtPathToWin32Path(const std::wstring& path);
        };  // namespace file
    };  // namespace windows
};  // namespace utils
