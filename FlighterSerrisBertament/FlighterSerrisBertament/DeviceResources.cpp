#include "stdafx.h"

#include "DeviceResources.h"

#include "utility.h"

DeviceResources::DeviceResources(HWND hwnd, ID2D1Factory* direct2dFactory) {
  RECT rc;
  GetClientRect(hwnd, &rc);

  D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

  // Create a Direct2D render target.
  valid = SUCCEEDED(direct2dFactory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(hwnd, size), &renderTarget));
}

DeviceResources::~DeviceResources() { SafeRelease(&renderTarget); }

ID2D1SolidColorBrush* DeviceResources::getBrush(D2D1::ColorF::Enum color) {
  auto brush = defaultBrushes.find(color);
  if (brush == defaultBrushes.end()) {
    auto iteratorPair = defaultBrushes.emplace(
        color, std::make_unique<Brush>(renderTarget, D2D1::ColorF(color)));
    if (iteratorPair.second) {
      brush = iteratorPair.first;
    } else {
      valid = false;
    }
  }
  return brush->second->getBrush();
}
