#include "CGraphics.h"
#include "../window/game/CGameWindow.h"

CGraphics::CGraphics(HWND window) {

    this->m_direct3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    const auto klass = reinterpret_cast<CGameWindow*>(GetWindowLongPtrW(window, GWLP_USERDATA));

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = FALSE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = window;    // set the window to be used by Direct3D
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;    // set the back buffer format to 32-bit
    d3dpp.BackBufferWidth = klass->screen.m_width;    // set the width of the buffer
    d3dpp.BackBufferHeight = klass->screen.m_height;

    // create a device class using this information and information from the d3dpp stuct
    this->m_direct3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &this->m_direct3d_device);

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->direct2d.m_factory);

    this->direct2d.m_factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(window, D2D1::SizeU(klass->screen.m_width, klass->screen.m_height)),
        &this->direct2d.m_render_target
    );

    this->direct2d.m_render_target->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &this->direct2d.m_solid_brush
    );

}

CGraphics::~CGraphics(void) {

    this->m_direct3d_device->Release();
    this->m_direct3d->Release();

    for (unsigned int i = 0; i < sizeof(this->direct2d) / sizeof(IUnknown*); i++) {

        const auto& v = reinterpret_cast<IUnknown**>(&this->direct2d)[i];

        v->Release();

    }
 
}

void CGraphics::BeginRender(void) {

    this->m_direct3d_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    this->m_direct3d_device->BeginScene();

    this->direct2d.m_render_target->DrawLine(D2D1::Point2F(0.f, 0.f), D2D1::Point2F(600, 600), this->direct2d.m_solid_brush);

}

void CGraphics::PresentFrame(void) {

    this->m_direct3d_device->EndScene();
    this->m_direct3d_device->Present(0, 0, 0, 0);

}