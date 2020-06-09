#pragma once

#include <Windows.h>
#include <functional>
#include <string>

class CWindow {

public:

    // handle to window
    HWND m_window{ };

    CWindow(std::wstring, DWORD = WS_OVERLAPPEDWINDOW |
        WS_VISIBLE, DWORD = 0 );
    
    // abstract WindowProcedure overwritten
    // by parent class
    virtual LRESULT WindowProcedure(UINT, WPARAM) = 0;

    // starts window cycle loop
    virtual bool DoWindowCycle(void);

    // closes window and closes thread if is one
    void Close(void);

};