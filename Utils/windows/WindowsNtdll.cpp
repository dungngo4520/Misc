#include "WindowsNtdll.h"
#include "../Define.h"


#include <assert.h>

#include <map>
#include <string>
#include <algorithm>

using namespace utils::windows;

using NtQuerySystemInformationPtr = NTSTATUS(NTAPI *)(
    _In_ ntdll::SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Inout_ PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
);
using NtQueryObjectPtr = NTSTATUS(NTAPI *)(
    _In_opt_ HANDLE Handle,
    _In_ ntdll::OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_opt_ PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
);
using NtDuplicateObjectPtr = NTSTATUS(NTAPI *)(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
);
using NtQueryInformationProcessPtr = NTSTATUS(NTAPI *)(
    _In_ HANDLE ProcessHandle,
    _In_ ntdll::PROCESSINFOCLASS ProcessInformationClass,
    _Out_ PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
);

using NtCreateFilePtr = NTSTATUS(NTAPI *)(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ntdll::POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ ntdll::PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_ PVOID EaBuffer,
    _In_ ULONG EaLength
);

HMODULE libNTDLL = NULL;
std::map<std::string, FARPROC> FunctionMap;

// Load can called multiple times
NTSTATUS ntdll::Load()
{
    if (libNTDLL != NULL) {
        UtilsLog("%s: Library ntdll.dll already loaded\n", __func__);
        return STATUS_SUCCESS;
    }

    libNTDLL = LoadLibraryExW(L"ntdll.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (libNTDLL == NULL) {
        UtilsLog("%s: Failed to load library ntdll.dll. Error: %d\n", __func__, GetLastError());
        return STATUS_UNSUCCESSFUL;
    }

    FunctionMap["NtQuerySystemInformation"] = GetProcAddress(libNTDLL, "NtQuerySystemInformation");
    FunctionMap["NtDuplicateObject"] = GetProcAddress(libNTDLL, "NtDuplicateObject");
    FunctionMap["NtQueryObject"] = GetProcAddress(libNTDLL, "NtQueryObject");
    FunctionMap["NtQueryInformationProcess"] = GetProcAddress(libNTDLL, "NtQueryInformationProcess");
    FunctionMap["NtCreateFile"] = GetProcAddress(libNTDLL, "NtCreateFile");

    return std::all_of(FunctionMap.begin(), FunctionMap.end(), [](auto &&pair) { return pair.second != NULL; })
               ? STATUS_SUCCESS
               : STATUS_UNSUCCESSFUL;
}

NTSTATUS ntdll::QuerySystemInformation(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Inout_ PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
)
{
    assert(FunctionMap["NtQuerySystemInformation"] != NULL);
    return ((NtQuerySystemInformationPtr)FunctionMap["NtQuerySystemInformation"])(
        SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength
    );
}

NTSTATUS ntdll::DuplicateObject(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
)
{
    assert(FunctionMap["NtDuplicateObject"] != NULL);
    return ((NtDuplicateObjectPtr)FunctionMap["NtDuplicateObject"])(
        SourceProcessHandle, SourceHandle, TargetProcessHandle, TargetHandle, DesiredAccess, HandleAttributes, Options
    );
}

NTSTATUS ntdll::QueryObject(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_opt_ PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
)
{
    assert(FunctionMap["NtQueryObject"] != NULL);
    return ((NtQueryObjectPtr)FunctionMap["NtQueryObject"])(
        Handle, ObjectInformationClass, ObjectInformation, ObjectInformationLength, ReturnLength
    );
}

NTSTATUS ntdll::QueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_ PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
)
{
    assert(FunctionMap["NtQueryInformationProcess"] != NULL);
    return ((NtQueryInformationProcessPtr)FunctionMap["NtQueryInformationProcess"])(
        ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength
    );
}

NTSTATUS ntdll::CreateFile(
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_ PVOID EaBuffer,
    _In_ ULONG EaLength
)
{
    assert(FunctionMap["NtCreateFile"] != NULL);
    return ((NtCreateFilePtr)FunctionMap["NtCreateFile"])(
        FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        AllocationSize,
        FileAttributes,
        ShareAccess,
        CreateDisposition,
        CreateOptions,
        EaBuffer,
        EaLength
    );
}

VOID utils::windows::ntdll::Initialize(POBJECT_ATTRIBUTES p, PUNICODE_STRING n, ULONG a, HANDLE r, PVOID s)
{
    (p)->Length = sizeof(OBJECT_ATTRIBUTES);
    (p)->ObjectName = n;
    (p)->Attributes = a;
    (p)->RootDirectory = r;
    (p)->SecurityDescriptor = s;
    (p)->SecurityQualityOfService = NULL;
}
