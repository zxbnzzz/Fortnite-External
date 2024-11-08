#pragma once

#include <windows.h>
#include <iostream>

#include <unordered_map>

class utils_t
{
public:
    void left_click()
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
}; utils_t utils;