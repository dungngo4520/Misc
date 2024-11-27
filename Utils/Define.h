#pragma once
#include <stdio.h>

template <typename... Args>
void UtilsLog(const char* format, Args... args)
{
#if defined(_DEBUG)
    printf(format, args...);
#endif
}
