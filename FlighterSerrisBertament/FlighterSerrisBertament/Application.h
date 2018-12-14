#pragma once

#include "DeviceIndependentResources.h"
#include "DeviceResources.h"

class Application {
 private:
  HWND m_hwnd;
  std::unique_ptr<DeviceIndependentResources> deviceIndependentResources;
  std::unique_ptr<DeviceResources> deviceResources;

 private:
  int mouseX = 0;
  int mouseY = 0;

 public:
  Application();
  ~Application();

  // Register the window class and call methods for instantiating drawing
  // resources
  HRESULT Initialize();

  // Process and dispatch messages
  void RunMessageLoop();

 private:
  // Initialize device-independent resources.
  HRESULT CreateDeviceIndependentResources();

  // Initialize device-dependent resources.
  HRESULT CreateDeviceResources();

  // Release device-dependent resource.
  void DiscardDeviceResources();

  // Draw content.
  HRESULT OnRender();

  // Resize the render target.
  void OnResize(UINT width, UINT height);

  // Records the mouse position
  void mouseMove(int x, int y) {
    mouseX = x;
    mouseY = y;
  }

  // The windows procedure.
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);
};
