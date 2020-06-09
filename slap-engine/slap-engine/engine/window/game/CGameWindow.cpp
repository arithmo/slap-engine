#include "CGameWindow.h"
#include "../../other/CGlobals.h"
#include "../../CGame.h"

CGameWindow::CGameWindow( ) : CWindow(L"slap-engine",  WS_EX_TOPMOST | WS_POPUP ) {

    const HWND desktop = GetDesktopWindow();

    RECT res{};
    GetWindowRect(desktop, &res);

    this->screen.m_width = res.right;
    this->screen.m_height = res.bottom;

}

LRESULT CGameWindow::WindowProcedure(UINT msg, WPARAM param) {

    // game window's procedure
    // handle input etc from here
    if (msg == WM_PAINT)
        g_Game.DoRender();

    return ERROR_SUCCESS;

}

bool CGameWindow::DoWindowCycle(void) {

    if (!this->m_window || !GetWindowLongPtrW(this->m_window, GWLP_USERDATA))
        return false;

    MSG msg{};

    LARGE_INTEGER frequency;        // ticks per second
    LARGE_INTEGER t1, t2;           // ticks

    g_Globals.m_curtime = { 0.f };

    static float m_next_frame_time = 0.f;

    // get ticks per second
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&t1);

    while (msg.message != WM_QUIT) {

        while (PeekMessageW(&msg, this->m_window, NULL, NULL, PM_REMOVE) > 0) {

            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }

        if (g_Globals.m_curtime >= m_next_frame_time) {

            this->WindowProcedure(WM_PAINT, 0);
            m_next_frame_time = g_Globals.m_curtime + (1000.f / 60.f);

        }

        QueryPerformanceCounter(&t2);

        g_Globals.m_curtime += static_cast<float>(t2.QuadPart - t1.QuadPart) / static_cast<float>(frequency.QuadPart);

        t1 = t2;

    }

    return true;

}