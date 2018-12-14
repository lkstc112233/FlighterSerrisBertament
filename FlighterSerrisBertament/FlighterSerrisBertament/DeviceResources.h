#pragma once

#include <map>

#include "Brush.h"
#include "DeviceIndependentResources.h"

class DeviceResources {
 private:
  ID2D1HwndRenderTarget* renderTarget;
  std::map<D2D1::ColorF::Enum, std::unique_ptr<Brush>> defaultBrushes;
  bool valid;

 public:
  DeviceResources(HWND hwnd, DeviceIndependentResources& indepentResources);
  ~DeviceResources();
  bool isValid() { return valid; }
  ID2D1HwndRenderTarget* getRenderTarget() { return renderTarget; }
  ID2D1SolidColorBrush* getBrush(D2D1::ColorF::Enum color);
};
