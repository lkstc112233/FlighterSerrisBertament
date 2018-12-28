#include "stdafx.h"

#include "DeviceResources.h"

#include "utility.h"

DeviceResources::DeviceResources(
    HWND hwnd, DeviceIndependentResources& indepentResources) {
  RECT rc;
  GetClientRect(hwnd, &rc);

  D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

  // Create a Direct2D render target.
  valid =
      SUCCEEDED(indepentResources.getDirect2dFactory()->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(hwnd, size), &renderTarget));
}

DeviceResources::~DeviceResources() { SafeRelease(&renderTarget); }
