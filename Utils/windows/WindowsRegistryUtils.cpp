#include "WindowsRegistryUtils.h"
#include "../Define.h"

#pragma comment(lib, "Advapi32.lib")

bool utils::windows::registry::RenameKey(HKEY rootKey, const std::wstring& source, const std::wstring& target)
{
    auto status = RegRenameKey(rootKey, source.c_str(), target.c_str());
    if (status != ERROR_SUCCESS) {
        UtilsLog("%s: Failed to rename key. Error: %ld\n", __func__, status);
        return false;
    }
    return true;
}
