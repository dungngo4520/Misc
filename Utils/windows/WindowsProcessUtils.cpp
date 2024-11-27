#include "WindowsProcessUtils.h"
#include "../Define.h"
#include "WindowsNtdll.h"

#include <memory>

using namespace utils::windows;

bool process::KillProcess(DWORD pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        UtilsLog("%s: Failed to open process. Error: %lu\n", __func__, GetLastError());
        return false;
    }
    if (TerminateProcess(hProcess, 0) == FALSE) {
        UtilsLog("%s: Failed to terminate process. Error: %lu\n", __func__, GetLastError());
        CloseHandle(hProcess);
        return false;
    }
    CloseHandle(hProcess);
    return true;
}

bool process::WriteProcess(DWORD pid, const std::vector<byte>& buffer)
{
    auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        UtilsLog("%s: Failed to open process. Error: %lu\n", __func__, GetLastError());
        return false;
    }

    auto StartAddress = VirtualAllocEx(hProcess, NULL, buffer.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (StartAddress == NULL) {
        UtilsLog("%s: Failed to allocate memory. Error: %lu\n", __func__, GetLastError());
        CloseHandle(hProcess);
        return false;
    }

    if (WriteProcessMemory(hProcess, StartAddress, buffer.data(), buffer.size(), NULL) == FALSE) {
        UtilsLog("%s: Failed to write process memory. Error:%lu\n", __func__, GetLastError());
        CloseHandle(hProcess);
        return false;
    }
    CloseHandle(hProcess);
    return true;
}

HANDLE process::DuplicateProcessToken(DWORD pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        UtilsLog("%s: Failed to open process. Error: %lu\n", __func__, GetLastError());
        return NULL;
    }
    HANDLE hToken = NULL;
    if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken) == FALSE) {
        UtilsLog("%s: Failed to open process token. Error:%lu\n", __func__, GetLastError());
        CloseHandle(hProcess);
        return NULL;
    }

    HANDLE hDupToken = NULL;
    if (DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &hDupToken) == FALSE) {
        UtilsLog("%s: Failed to duplicate token. Error: %lu\n", __func__, GetLastError());
        CloseHandle(hToken);
        CloseHandle(hProcess);
        return NULL;
    }
    CloseHandle(hToken);
    CloseHandle(hProcess);
    return hDupToken;
}

std::vector<DWORD> process::FindProcess(const std::wstring& name)
{
    std::vector<DWORD> result;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (name == std::wstring(entry.szExeFile)) {
                result.push_back(entry.th32ProcessID);
            }
        } while (Process32NextW(snapshot, &entry));
    }
    CloseHandle(snapshot);
    return result;
}

std::wstring process::GetProcessPathWithoutOpen(DWORD pid)
{
    if (ntdll::Load() != STATUS_SUCCESS) {
        UtilsLog("%s: Failed to load ntdll.dll\n", __func__);
        return L"";
    }

    ULONG RequiredLength = 1024;
    std::unique_ptr<byte[]> Buffer = std::make_unique<byte[]>(RequiredLength);
    auto processIdInfo = reinterpret_cast<ntdll::PSYSTEM_PROCESS_ID_INFORMATION>(Buffer.get());
    processIdInfo->ProcessId = (HANDLE)(DWORD_PTR)pid;
    processIdInfo->ImageName.Buffer = (PWSTR)((char*)Buffer.get() + sizeof(ntdll::SYSTEM_PROCESS_ID_INFORMATION));
    processIdInfo->ImageName.Length = 0;
    processIdInfo->ImageName.MaximumLength = (USHORT)(RequiredLength - sizeof(ntdll::SYSTEM_PROCESS_ID_INFORMATION));

    auto status = STATUS_SUCCESS;
    while ((status = QuerySystemInformation(
                ntdll::SystemProcessIdInformation, Buffer.get(), sizeof(ntdll::SYSTEM_PROCESS_ID_INFORMATION), NULL
            )) == STATUS_INFO_LENGTH_MISMATCH) {
        Buffer = std::make_unique<byte[]>(RequiredLength);
        processIdInfo = reinterpret_cast<ntdll::PSYSTEM_PROCESS_ID_INFORMATION>(Buffer.get());
        processIdInfo->ProcessId = (HANDLE)(DWORD_PTR)pid;
        processIdInfo->ImageName.Buffer = (PWSTR)((char*)Buffer.get() + sizeof(ntdll::SYSTEM_PROCESS_ID_INFORMATION));
        processIdInfo->ImageName.Length = processIdInfo->ImageName.MaximumLength =
            (USHORT)(RequiredLength - sizeof(ntdll::SYSTEM_PROCESS_ID_INFORMATION));
    }
    if (!NT_SUCCESS(status)) {
        UtilsLog("%s: Failed to get process path. Error: %x\n", __func__, status);
        return L"";
    }

    return std::wstring(processIdInfo->ImageName.Buffer, processIdInfo->ImageName.Length / sizeof(wchar_t));
}

std::wstring process::GetProcessPath(DWORD pid)
{
    if (ntdll::Load() != STATUS_SUCCESS) return L"";

    auto hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (hProcess == NULL) hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProcess == NULL) {
        UtilsLog("%s: Failed to open process. Error: %lu\n", __func__, GetLastError());
        UtilsLog("Fallback to GetProcessPathWithoutOpen\n");
        return GetProcessPathWithoutOpen(pid);
    }

    ULONG RequiredLength = 1024;
    std::unique_ptr<wchar_t[]> Buffer = std::make_unique<wchar_t[]>(RequiredLength);
    while (QueryFullProcessImageNameW(hProcess, 0, Buffer.get(), &RequiredLength) &&
           GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        Buffer = std::make_unique<wchar_t[]>(RequiredLength);
    }
    if (GetLastError() != ERROR_SUCCESS) {
        UtilsLog("%s: Failed to get process path. Error: %lu\n", __func__, GetLastError());
        CloseHandle(hProcess);
        return L"";
    }

    CloseHandle(hProcess);
    return std::wstring(Buffer.get(), RequiredLength);
}

std::wstring utils::windows::process::GetProcessCommandLine(DWORD pid)
{
    if (ntdll::Load() != STATUS_SUCCESS) return L"";

    auto hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (hProcess == NULL) hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProcess == NULL) {
        UtilsLog("%s: Failed to open process. Error: %lu\n", __func__, GetLastError());
        return L"";
    }

    DWORD RequiredLength = 1024;
    std::unique_ptr<byte[]> Buffer = std::make_unique<byte[]>(RequiredLength);

    NTSTATUS status = STATUS_SUCCESS;
    while ((status = ntdll::QueryInformationProcess(
                hProcess, ntdll::ProcessCommandLineInformation, Buffer.get(), RequiredLength, &RequiredLength
            )) == STATUS_INFO_LENGTH_MISMATCH) {
        Buffer = std::make_unique<byte[]>(RequiredLength);
    }
    if (!NT_SUCCESS(status)) {
        UtilsLog("%s: Failed to get process command line. Error: %x\n", __func__, status);
        CloseHandle(hProcess);
        return L"";
    }

    CloseHandle(hProcess);
    auto pCmdLineInfo = reinterpret_cast<ntdll::PUNICODE_STRING>(Buffer.get());
    return std::wstring(pCmdLineInfo->Buffer, pCmdLineInfo->Length / sizeof(wchar_t));
}
