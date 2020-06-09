#include "CWindow.h"

// xref: https://docs.microsoft.com/en-gb/previous-versions/windows/desktop/legacy/ms633573(v=vs.85)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    const auto window_class = reinterpret_cast<CWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    const auto result = window_class ? window_class->WindowProcedure(uMsg, wParam) : ERROR_SUCCESS;

    if (SUCCEEDED(result))
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);

    return result;

}

CWindow::CWindow(std::wstring window_name, DWORD style, DWORD style_ex) {

    WNDCLASSEXW wnd_class{};
    memset(&wnd_class, 0x0, sizeof(wnd_class));

    const auto class_name = window_name + L"_class";

    wnd_class.cbSize = sizeof(wnd_class);
    wnd_class.lpfnWndProc = WindowProc;
    wnd_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wnd_class.lpszClassName = class_name.c_str();

    RegisterClassExW(&wnd_class);

    this->m_window = CreateWindowExW(style_ex, class_name.c_str(), window_name.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, NULL,
        NULL, NULL, nullptr);

    SetWindowLongPtr(this->m_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

}


bool CWindow::DoWindowCycle(void) {

    if (!this->m_window || !GetWindowLongPtrW(this->m_window, GWLP_USERDATA))
        return false;

    MSG msg{};

    while (msg.message != WM_QUIT) {

        while (PeekMessageW(&msg, this->m_window, NULL, NULL, PM_REMOVE) > 0) {

            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }

    }

    return true;

}

void CWindow::Close(void) {

    DestroyWindow(this->m_window);

}