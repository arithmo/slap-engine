#pragma once

#include <Windows.h>
#include "../CWindow.h"

class CGameWindow : public CWindow {
public:

    struct {

        int m_width{ 0 },
            m_height{ 0 };

    } screen;

    CGameWindow();

    bool DoWindowCycle(void);
    // override basic CWindow WindowProcedure

    LRESULT WindowProcedure(UINT, WPARAM);

};