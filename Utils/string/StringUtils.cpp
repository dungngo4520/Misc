#include "StringUtils.h"
#include <cstdint>

std::vector<uint8_t> utils::string::StringToByteArray(const std::string& str)
{
    return std::vector<uint8_t>(str.begin(), str.end());
}

#pragma warning(push, 1)
#pragma warning(disable : 4244)  // conversion from 'wchar_t' to 'uint8_t', possible loss of data
std::vector<uint8_t> utils::string::StringToByteArray(const std::wstring& str)
{
    return std::vector<uint8_t>(str.begin(), str.end());
}
#pragma warning(pop)
