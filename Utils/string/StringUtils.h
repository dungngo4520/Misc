#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace utils {
    namespace string {
        std::vector<uint8_t> StringToByteArray(const std::string& str);
        std::vector<uint8_t> StringToByteArray(const std::wstring& str);
    };  // namespace string
};  // namespace utils
