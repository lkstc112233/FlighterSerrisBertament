#pragma once
class SolidColorBrush {
 private:
  ID2D1SolidColorBrush* brush;
  bool valid;

 public:
  template <typename... Args>
  SolidColorBrush(ID2D1HwndRenderTarget* renderTarget, const Args&... args) {
    valid = SUCCEEDED(renderTarget->CreateSolidColorBrush(args..., &brush));
  }
  ~SolidColorBrush();
  bool isValid() { return valid; }
  ID2D1SolidColorBrush* getBrush() { return brush; }
};

// Define an alias for Brush
typedef SolidColorBrush Brush;
