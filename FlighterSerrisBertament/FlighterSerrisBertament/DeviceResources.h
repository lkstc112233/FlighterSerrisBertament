#pragma once

#include <map>

#include "Brush.h"
#include "DeviceIndependentResources.h"

#define BRUSH_DEFINITION(color) std::unique_ptr<Brush> m_##color##Brush

#define GET_BRUSH_IMPLEMENTATION(color)                     \
  ID2D1SolidColorBrush* get##color##Brush() {               \
    if (!m_##color##Brush) {                                \
      m_##color##Brush = std::make_unique<Brush>(           \
          renderTarget, D2D1::ColorF(D2D1::ColorF::color)); \
      if (!m_##color##Brush->isValid()) {                   \
        valid = false;                                      \
      }                                                     \
    }                                                       \
    return m_##color##Brush->getBrush();                    \
  }

class DeviceResources {
 private:
  ID2D1HwndRenderTarget* renderTarget;
  BRUSH_DEFINITION(Red);
  BRUSH_DEFINITION(Blue);
  BRUSH_DEFINITION(Black);
  BRUSH_DEFINITION(LightSlateGray);
  BRUSH_DEFINITION(CornflowerBlue);
  bool valid;

 public:
  DeviceResources(HWND hwnd, DeviceIndependentResources& indepentResources);
  ~DeviceResources();
  bool isValid() { return valid; }
  ID2D1HwndRenderTarget* getRenderTarget() { return renderTarget; }
  GET_BRUSH_IMPLEMENTATION(Red);
  GET_BRUSH_IMPLEMENTATION(Blue);
  GET_BRUSH_IMPLEMENTATION(Black);
  GET_BRUSH_IMPLEMENTATION(LightSlateGray);
  GET_BRUSH_IMPLEMENTATION(CornflowerBlue);
};
