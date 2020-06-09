#include "CGame.h"

bool CGame::RunGame(void) {

    this->m_window = new CGameWindow();

    this->m_graphics = new CGraphics(this->m_window->m_window);

    if (!this->m_window->DoWindowCycle())
        return false;

    return true;

}

void CGame::DoRender(void) {

    this->m_graphics->BeginRender();

    // render in here

    this->m_graphics->PresentFrame();

}

CGame g_Game{};