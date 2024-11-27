#include "windowsFileUtils.h"
#include "WindowsNtdll.h"
#include "../Define.h"

#include <memory>

using namespace utils::windows;

bool file::FileExists(const std::wstring& path)
{
    auto hFile = CreateFileW(path.c_str(), FILE_READ_ATTRIBUTES, FILE_SHARE_ALL, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;
    CloseHandle(hFile);
    return true;
}

std::wstring file::NtPathToWin32Path(const std::wstring& path)
{
    HANDLE hFile = INVALID_HANDLE_VALUE;
    ntdll::IO_STATUS_BLOCK IoStatusBlock = {};
    ntdll::OBJECT_ATTRIBUTES ObjectAttributes = {};
    NTSTATUS status = STATUS_SUCCESS;
    ntdll::UNICODE_STRING FileName = { (USHORT)(path.size() * sizeof(wchar_t)),
                                       (USHORT)(path.size() * sizeof(wchar_t)),
                                       (PWSTR)path.c_str() };

    if (ntdll::Load() != STATUS_SUCCESS) {
        UtilsLog("%s: Failed to load ntdll.dll\n", __func__);
        return path;
    }

    ntdll::Initialize(&ObjectAttributes, &FileName, OBJ_CASE_INSENSITIVE, NULL, NULL);
    status = ntdll::CreateFile(
        &hFile, FILE_READ_ATTRIBUTES, &ObjectAttributes, &IoStatusBlock, {}, 0, FILE_SHARE_ALL, FILE_OPEN, 0, NULL, 0
    );
    if (!NT_SUCCESS(status)) {
        UtilsLog("%s: Failed to open file. Error: %x\n", __func__, status);
        return path;
    }

    DWORD RequireSize = MAX_PATH;
    auto Buffer = std::make_unique<wchar_t[]>(RequireSize);
    RequireSize = GetFinalPathNameByHandleW(hFile, Buffer.get(), RequireSize, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
    if (GetLastError() == ERROR_NOT_ENOUGH_MEMORY) {
        Buffer = std::make_unique<wchar_t[]>(RequireSize);
        GetFinalPathNameByHandleW(hFile, Buffer.get(), RequireSize, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
    }
    CloseHandle(hFile);
    return std::wstring(Buffer.get(), RequireSize);
}
