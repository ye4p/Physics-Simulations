
#include <display.h>

void InitFramebuffer()
{
    gPixels = new uint32_t[W * H];

    gBmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    gBmi.bmiHeader.biWidth = W;
    gBmi.bmiHeader.biHeight = -H;
    gBmi.bmiHeader.biPlanes = 1;
    gBmi.bmiHeader.biBitCount = 32;
    gBmi.bmiHeader.biCompression = BI_RGB;
}

void ShutdownFramebuffer()
{
    delete[] gPixels;
    gPixels = nullptr;
}

void Clear(uint32_t color)
{
    for (int i = 0; i < W * H; i++)
    {
        gPixels[i] = color;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_TIMER:
    {
        // velYm+= g*dt;
        // ballXm += velXm * dt;
        // ballYm += velYm * dt;
        // if (ballXm - r < 0)
        // {
        //     ballXm = r;
        //     velXm = -velXm;
        // }
        // if (ballXm + r > maxWm)
        // {
        //     ballXm = maxWm - r;
        //     velXm = -velXm;
        // }
        // if (ballYm - r < 0)
        // {
        //     ballYm = r;
        //     velYm = -velYm;
        // }
        // if (ballYm + r > maxHm)
        // {
        //     ballYm = maxHm - r;
        //     velYm = -velYm;
        // }

        Clear(0x00000000);
        // drawSquare();
        // drawBall(ballXm, ballYm, 0x00FFFFFF);
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        StretchDIBits(
            hdc,
            0, 0, W, H,
            0, 0, W, H,
            gPixels,
            &gBmi,
            DIB_RGB_COLORS,
            SRCCOPY);
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void display()
{
    InitFramebuffer();
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"MySimWindowClass";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        wc.lpszClassName,
        L"Simulation",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        W, H,
        nullptr, nullptr,
        wc.hInstance, nullptr);
    ShowWindow(hwnd, SW_SHOW);
    SetTimer(hwnd, 1, 16, nullptr);
    MSG msg;
    // drawSquare();
    InvalidateRect(hwnd, nullptr, FALSE);
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    ShutdownFramebuffer();
}
