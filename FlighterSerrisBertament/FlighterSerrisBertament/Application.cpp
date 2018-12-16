#include "stdafx.h"

#include <string>

#include "Application.h"
#include "utility.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

Application::Application() : m_hwnd(NULL), fps(0) {
  mouse = std::make_shared<Mouse>();
  mouseFlower = std::make_shared<MouseFlower>(mouse);
  spriteManager.addSprite(mouseFlower);
}

Application::~Application() {}

void Application::RunMessageLoop() {
  MSG msg;

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

HRESULT Application::Initialize() {
  HRESULT hr;

  // Initialize device-indpendent resources, such
  // as the Direct2D factory.
  hr = CreateDeviceIndependentResources();

  if (SUCCEEDED(hr)) {
    const char *WINDOW_CLASS_NAME = "D2DDemoApplication";
    const char *WINDOW_DEFAULT_TITLE = "Direct2D Practice";

    // Register the window class.
    WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Application::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wcex.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClassEx(&wcex);

    // Because the CreateWindow function takes its size in pixels,
    // obtain the system DPI and use it to scale the window size.
    FLOAT dpiX, dpiY;

    // The factory returns the current system DPI. This is also the value it
    // will use to create its own windows.
    deviceIndependentResources->getDirect2dFactory()->GetDesktopDpi(&dpiX,
                                                                    &dpiY);

    // Create the window.
    m_hwnd = CreateWindow(WINDOW_CLASS_NAME, WINDOW_DEFAULT_TITLE,
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
                          static_cast<UINT>(ceil(480.f * dpiY / 96.f)), NULL,
                          NULL, HINST_THISCOMPONENT, this);
    hr = m_hwnd ? S_OK : E_FAIL;
    if (SUCCEEDED(hr)) {
      ShowWindow(m_hwnd, SW_SHOWNORMAL);
      UpdateWindow(m_hwnd);
    }
  }

  return hr;
}

HRESULT Application::CreateDeviceIndependentResources() {
  HRESULT hr = S_OK;
  deviceIndependentResources = std::make_unique<DeviceIndependentResources>();
  return hr;
}

HRESULT Application::CreateDeviceResources() {
  HRESULT hr = S_OK;

  if (!deviceResources) {
    deviceResources =
        std::make_unique<DeviceResources>(m_hwnd, *deviceIndependentResources);
  }

  return hr;
}

void Application::DiscardDeviceResources() { deviceResources.reset(); }

HRESULT Application::OnRender() {
  static const WCHAR msc_fontName[] = L"Verdana";
  static const FLOAT msc_fontSize = 20;

  HRESULT hr = S_OK;

  hr = CreateDeviceResources();

  if (deviceResources->isValid()) {
    static const WCHAR sc_helloWorld[] = L"Hello, World!";
    auto renderTarget = deviceResources->getRenderTarget();

    renderTarget->BeginDraw();

    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    D2D1_SIZE_F rtSize = renderTarget->GetSize();

    // Draw a grid background.
    int width = static_cast<int>(rtSize.width);
    int height = static_cast<int>(rtSize.height);

    for (int x = 0; x < width; x += 10) {
      renderTarget->DrawLine(
          D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
          D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
          deviceResources->getBrush(D2D1::ColorF::LightSlateGray), 0.5f);
    }

    for (int y = 0; y < height; y += 10) {
      renderTarget->DrawLine(
          D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
          D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
          deviceResources->getBrush(D2D1::ColorF::LightSlateGray), 0.5f);
    }

    // Draw two rectangles.
    D2D1_RECT_F rectangle1 =
        D2D1::RectF(rtSize.width / 2 - 50.0f, rtSize.height / 2 - 50.0f,
                    rtSize.width / 2 + 50.0f, rtSize.height / 2 + 50.0f);

    D2D1_RECT_F rectangle2 =
        D2D1::RectF(rtSize.width / 2 - 100.0f, rtSize.height / 2 - 100.0f,
                    rtSize.width / 2 + 100.0f, rtSize.height / 2 + 100.0f);

    spriteManager.draw(*deviceResources);

    // Draw a filled rectangle.
    renderTarget->FillRectangle(
        &rectangle1, deviceResources->getBrush(D2D1::ColorF::LightSlateGray));

    // Draw the outline of a rectangle.
    renderTarget->DrawRectangle(
        &rectangle2, deviceResources->getBrush(D2D1::ColorF::CornflowerBlue));

    std::wstring timeString = L"FPS: " + std::to_wstring(fps);

    renderTarget->DrawText(
        timeString.c_str(), timeString.size(),
        deviceIndependentResources->getTextFormat(msc_fontName, msc_fontSize),
        D2D1::RectF(0, 0, rtSize.width, rtSize.height),
        deviceResources->getBrush(D2D1::ColorF::Black));

    hr = renderTarget->EndDraw();
  }

  if (hr == D2DERR_RECREATE_TARGET) {
    hr = S_OK;
    DiscardDeviceResources();
  }

  return hr;
}

void Application::OnResize(UINT width, UINT height) {
  if (deviceResources) {
    // Note: This method can fail, but it's okay to ignore the
    // error here, because the error will be returned again
    // the next time EndDraw is called.
    deviceResources->getRenderTarget()->Resize(D2D1::SizeU(width, height));
  }
}
