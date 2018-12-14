#include "stdafx.h"

#include <string>

#include "Application.h"
#include "utility.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

Application::Application()
    : m_hwnd(NULL), m_pDirect2dFactory(NULL), m_pRenderTarget(NULL) {}

Application::~Application() {
  SafeRelease(&m_pDirect2dFactory);
  SafeRelease(&m_pDWriteFactory);
  SafeRelease(&m_pTextFormat);
  SafeRelease(&m_pRenderTarget);
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

  if (!m_pRenderTarget) {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    // Create a Direct2D render target.
    hr = m_pDirect2dFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size), &m_pRenderTarget);

    if (SUCCEEDED(hr)) {
      // Create a gray brush.
      lightSlateGrayBrush = std::make_unique<Brush>(
          m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::LightSlateGray));
    }
    if (lightSlateGrayBrush->isValid()) {
      // Create a blue brush.
      cornflowerBlueBrush = std::make_unique<Brush>(
          m_pRenderTarget, D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
    }
    if (cornflowerBlueBrush->isValid()) {
      // Create a black brush.
      blackBrush = std::make_unique<Brush>(m_pRenderTarget,
                                           D2D1::ColorF(D2D1::ColorF::Black));
    }
  }

  return hr;
}

void Application::DiscardDeviceResources() {
  SafeRelease(&m_pRenderTarget);
  lightSlateGrayBrush.reset();
  cornflowerBlueBrush.reset();
  blackBrush.reset();
}

HRESULT Application::OnRender() {
  HRESULT hr = S_OK;

  hr = CreateDeviceResources();
  if (SUCCEEDED(hr)) {
    static const WCHAR sc_helloWorld[] = L"Hello, World!";

    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

    // Draw a grid background.
    int width = static_cast<int>(rtSize.width);
    int height = static_cast<int>(rtSize.height);

    for (int x = 0; x < width; x += 10) {
      m_pRenderTarget->DrawLine(
          D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
          D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
          lightSlateGrayBrush->getBrush(), 0.5f);
    }

    for (int y = 0; y < height; y += 10) {
      m_pRenderTarget->DrawLine(
          D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
          D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
          lightSlateGrayBrush->getBrush(), 0.5f);
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
    m_pRenderTarget->FillRectangle(&rectangle1,
                                   lightSlateGrayBrush->getBrush());

    // Draw the outline of a rectangle.
    m_pRenderTarget->DrawRectangle(&rectangle2,
                                   cornflowerBlueBrush->getBrush());

    // Draw the ellipse following the mouse.
    m_pRenderTarget->FillEllipse(&ellipse, cornflowerBlueBrush->getBrush());

    SYSTEMTIME time;
    GetSystemTime(&time);
    std::wstring timeString = std::to_wstring(time.wMilliseconds);

    m_pRenderTarget->DrawText(
        timeString.c_str(), timeString.size(), m_pTextFormat,
        D2D1::RectF(0, 0, rtSize.width, rtSize.height), blackBrush->getBrush());

    std::wstring mouseString =
        L"X: " + std::to_wstring(mouseX) + L"\nY: " + std::to_wstring(mouseY);

    m_pRenderTarget->DrawText(
        mouseString.c_str(), mouseString.size(), m_pTextFormat,
        D2D1::RectF(0, 0, rtSize.width / 3, rtSize.height / 3),
        blackBrush->getBrush());

    hr = m_pRenderTarget->EndDraw();
  }

  if (hr == D2DERR_RECREATE_TARGET) {
    hr = S_OK;
    DiscardDeviceResources();
  }

  return hr;
}

void Application::OnResize(UINT width, UINT height) {
  if (m_pRenderTarget) {
    // Note: This method can fail, but it's okay to ignore the
    // error here, because the error will be returned again
    // the next time EndDraw is called.
    m_pRenderTarget->Resize(D2D1::SizeU(width, height));
  }
}
