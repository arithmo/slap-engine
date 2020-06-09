#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

// include the Direct3D Library file

#pragma comment(lib, "dwrite.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "d2d1.lib")

class CGraphics {

    LPDIRECT3D9 m_direct3d;
    LPDIRECT3DDEVICE9 m_direct3d_device;

    struct {

        ID2D1Factory* m_factory;
        ID2D1HwndRenderTarget* m_render_target;
        ID2D1SolidColorBrush* m_solid_brush;

    } direct2d;

public:

    CGraphics( HWND );

    void BeginRender(void);
    void PresentFrame(void);

    ~CGraphics();

};