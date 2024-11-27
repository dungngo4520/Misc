#include "WindowsUserUtils.h"
#include "../Define.h"

#include <memory>

bool utils::windows::user::IsElevated()
{
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) == FALSE) {
        UtilsLog("%s: Failed to open process token. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    TOKEN_ELEVATION Elevation = {};
    DWORD cbSize = sizeof(TOKEN_ELEVATION);
    if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize) == FALSE) {
        UtilsLog("%s: Failed to get token information. Error: %lu\n", __func__, GetLastError());
    }
    CloseHandle(hToken);
    return Elevation.TokenIsElevated;
}

bool utils::windows::user::IsRunningAsAdministrator()
{
    BOOL IsRunAsAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID pAdministratorsGroup = NULL;

    if (AllocateAndInitializeSid(
            &NtAuthority,                 //pIdentifierAuthority
            2,                            //nSubAuthorityCount
            SECURITY_BUILTIN_DOMAIN_RID,  //nSubAuthority0
            DOMAIN_ALIAS_RID_ADMINS,      //nSubAuthority1
            0,                            //nSubAuthority2
            0,                            //nSubAuthority3
            0,                            //nSubAuthority4
            0,                            //nSubAuthority5
            0,                            //nSubAuthority6
            0,                            //nSubAuthority7
            &pAdministratorsGroup         //pSid
        )) {
        CheckTokenMembership(NULL, pAdministratorsGroup, &IsRunAsAdmin);
        FreeSid(pAdministratorsGroup);
    }
    return IsRunAsAdmin == TRUE;
}

bool utils::windows::user::IsPrivilegeEnabled(const std::wstring& privilegeName)
{
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) == FALSE) {
        UtilsLog("%s: Failed to open process token. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    LUID luid;
    if (LookupPrivilegeValueW(NULL, privilegeName.c_str(), &luid) == FALSE) {
        UtilsLog("%s: Failed to lookup privilege value. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    DWORD sizeNeeded = 0;
    GetTokenInformation(hToken, TokenPrivileges, NULL, 0, &sizeNeeded);
    UtilsLog("%s: Size needed: %lu\n", __func__, sizeNeeded);
    if (sizeNeeded == 0) return false;

    std::unique_ptr<byte[]> privilegesBuffer(new byte[sizeNeeded]);
    if (GetTokenInformation(hToken, TokenPrivileges, privilegesBuffer.get(), sizeNeeded, &sizeNeeded) == FALSE) {
        UtilsLog("%s: Failed to get token information. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    auto privileges = reinterpret_cast<TOKEN_PRIVILEGES*>(privilegesBuffer.get());
    for (unsigned int i = 0; i < privileges->PrivilegeCount; i++) {
        if (luid.LowPart == privileges->Privileges[i].Luid.LowPart &&
            luid.HighPart == privileges->Privileges[i].Luid.HighPart) {
            return privileges->Privileges[i].Attributes & SE_PRIVILEGE_ENABLED;
        }
    }
    return false;
}

bool utils::windows::user::SetPrivilege(const std::wstring& privilegeName, bool enable)
{
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken) == FALSE) {
        UtilsLog("%s: Failed to open process token. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    TOKEN_PRIVILEGES tokenPrivileges;
    LUID luid;
    if (LookupPrivilegeValueW(NULL, privilegeName.c_str(), &luid) == FALSE) {
        UtilsLog("%s: Failed to lookup privilege value. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Luid = luid;
    tokenPrivileges.Privileges[0].Attributes = enable ? SE_PRIVILEGE_ENABLED : 0;
    if (AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(tokenPrivileges), NULL, NULL) == FALSE) {
        UtilsLog("%s: Failed to adjust token privileges. Error: %lu\n", __func__, GetLastError());
    }

    return GetLastError() == ERROR_SUCCESS;
}
