#pragma once

#include <map>

#include "Brush.h"

class DeviceResources {
 private:
  ID2D1HwndRenderTarget* renderTarget;
  std::map<D2D1::ColorF::Enum, Brush> defaultBrushes;
  bool valid;

 public:
  DeviceResources(HWND hwnd, ID2D1Factory* m_pDirect2dFactory);
  ~DeviceResources();
  ID2D1SolidColorBrush* getBrush(D2D1::ColorF::Enum color);
};
