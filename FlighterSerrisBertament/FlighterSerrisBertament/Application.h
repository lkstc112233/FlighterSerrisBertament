#pragma once

#include "DeviceIndependentResources.h"
#include "DeviceResources.h"
#include "MouseDots.h"
#include "Sprite.h"

class Application {
 private:
  HWND m_hwnd;
  std::unique_ptr<DeviceIndependentResources> deviceIndependentResources;
  std::unique_ptr<DeviceResources> deviceResources;
  SpriteManager spriteManager;

 private:
  int fps;
  int fpsSecondRecord;
  int fpsFrameCount;
  std::shared_ptr<Mouse> mouse;
  MouseDotsManager mouseDots;

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

  // updates required status.
  void update();

  // Records the mouse position
  void mouseMove(int x, int y) { mouse->mouseTo(x, y); }

  // The windows procedure.
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);
};
