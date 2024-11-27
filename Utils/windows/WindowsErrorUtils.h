#pragma once
#include "WindowsDef.h"

#include <string>

namespace utils {
    namespace windows {
        namespace error {
            std::wstring TranslateSystemError(DWORD error);
        };
    };  // namespace windows
};  // namespace utils
