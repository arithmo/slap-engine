#pragma once

#include <Windows.h>
#include "window/game/CGameWindow.h"
#include "graphics/CGraphics.h"

class CGame {

    // seems awkward to put graphics in the 
    // window class... 

    CGraphics* m_graphics;
    CGameWindow* m_window;

public:

    bool RunGame(void);
    void DoRender(void);

};

extern CGame g_Game;