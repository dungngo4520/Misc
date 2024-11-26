#include "WindowsErrorUtils.h"

#include <stdio.h>

std::wstring utils::windows::error::TranslateSystemError(DWORD error)
{
    PVOID pMessage = NULL;
    const auto formatFlag = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM;
    if (FormatMessageW(formatFlag, NULL, error, 0, (LPWSTR)&pMessage, 0, NULL) == 0) {
        printf("%s: Failed to translate error %lu. Error: %lu\n", __func__, error, GetLastError());
    }
    std::wstring ret = (PWCHAR)pMessage;
    LocalFree(pMessage);
    return ret;
}
