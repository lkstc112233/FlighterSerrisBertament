#include "stdafx.h"

#include <string>

#include "Application.h"
#include "utility.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

Application::Application() : m_hwnd(NULL), m_pDirect2dFactory(NULL) {}

Application::~Application() {
  SafeRelease(&m_pDirect2dFactory);
  SafeRelease(&m_pDWriteFactory);
  SafeRelease(&m_pTextFormat);
}

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
    m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

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
  static const WCHAR msc_fontName[] = L"Verdana";
  static const FLOAT msc_fontSize = 50;
  HRESULT hr = S_OK;

  // Create a Direct2D factory.
  hr =
      D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

  if (SUCCEEDED(hr)) {
    // Create a DirectWrite factory.
    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                             __uuidof(m_pDWriteFactory),
                             reinterpret_cast<IUnknown **>(&m_pDWriteFactory));
    if (SUCCEEDED(hr)) {
      // Create a DirectWrite text format object.
      hr = m_pDWriteFactory->CreateTextFormat(
          msc_fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL,
          DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, msc_fontSize,
          L"",  // locale
          &m_pTextFormat);
    }
    if (SUCCEEDED(hr)) {
      // Center the text horizontally and vertically.
      m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
      m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
  }

  return hr;
}

HRESULT Application::CreateDeviceResources() {
  HRESULT hr = S_OK;

  if (!deviceResources) {
    deviceResources =
        std::make_unique<DeviceResources>(m_hwnd, m_pDirect2dFactory);
  }

  return hr;
}

void Application::DiscardDeviceResources() { deviceResources.reset(); }

HRESULT Application::OnRender() {
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

    // And an ellipse
    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(static_cast<FLOAT>(mouseX), static_cast<FLOAT>(mouseY)),
        10.0F, 10.0F);

    // Draw a filled rectangle.
    renderTarget->FillRectangle(
        &rectangle1, deviceResources->getBrush(D2D1::ColorF::LightSlateGray));

    // Draw the outline of a rectangle.
    renderTarget->DrawRectangle(
        &rectangle2, deviceResources->getBrush(D2D1::ColorF::CornflowerBlue));

    // Draw the ellipse following the mouse.
    renderTarget->FillEllipse(
        &ellipse, deviceResources->getBrush(D2D1::ColorF::CornflowerBlue));

    SYSTEMTIME time;
    GetSystemTime(&time);
    std::wstring timeString = std::to_wstring(time.wMilliseconds);

    renderTarget->DrawText(timeString.c_str(), timeString.size(), m_pTextFormat,
                           D2D1::RectF(0, 0, rtSize.width, rtSize.height),
                           deviceResources->getBrush(D2D1::ColorF::Black));

    std::wstring mouseString =
        L"X: " + std::to_wstring(mouseX) + L"\nY: " + std::to_wstring(mouseY);

    renderTarget->DrawText(
        mouseString.c_str(), mouseString.size(), m_pTextFormat,
        D2D1::RectF(0, 0, rtSize.width / 3, rtSize.height / 3),
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
