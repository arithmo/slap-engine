#include <Windows.h>
#include "engine/CGame.h"

// global entry point...
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int showcmd) {
    
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (!g_Game.RunGame()) 
        MessageBoxW(NULL, L"Game failed to run.", L"the game failed to run.", MB_OK);

    return 0;

}