#include "stdafx.h"

#include <windowsx.h>

#include "Application.h"

constexpr static const UINT_PTR TIMER_ID = 0xDEAD;
constexpr static const UINT TIMER_ELAPSE = USER_TIMER_MINIMUM;

LRESULT CALLBACK Application::WndProc(HWND hwnd, UINT message, WPARAM wParam,
                                      LPARAM lParam) {
  LRESULT result = 0;

  if (message == WM_CREATE) {
    LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
    Application *pApplication = (Application *)pcs->lpCreateParams;

    ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pApplication));

    ::SetTimer(hwnd, TIMER_ID, TIMER_ELAPSE, NULL);

    result = 1;
  } else {
    Application *pApplication = reinterpret_cast<Application *>(
        static_cast<LONG_PTR>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)));

    bool wasHandled = false;

    if (pApplication) {
      switch (message) {
        case WM_SIZE: {
          UINT width = LOWORD(lParam);
          UINT height = HIWORD(lParam);
          pApplication->OnResize(width, height);
        }
          result = 0;
          wasHandled = true;
          break;
        case WM_TIMER:
          result = 0;
          if (wasHandled = (wParam == TIMER_ID)) {
            InvalidateRect(hwnd, NULL, FALSE);
          }
          break;
        case WM_DISPLAYCHANGE: {
          InvalidateRect(hwnd, NULL, FALSE);
        }
          result = 0;
          wasHandled = true;
          break;

        case WM_MOUSEMOVE: {
          pApplication->mouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
          InvalidateRect(hwnd, NULL, FALSE);
        }
          result = 0;
          wasHandled = true;
          break;

        case WM_PAINT: {
          pApplication->spriteManager.update();
          pApplication->OnRender();
          ValidateRect(hwnd, NULL);
        }
          result = 0;
          wasHandled = true;
          break;

        case WM_DESTROY: {
          PostQuitMessage(0);
        }
          result = 1;
          wasHandled = true;
          break;
      }
    }

    if (!wasHandled) {
      result = DefWindowProc(hwnd, message, wParam, lParam);
    }
  }

  return result;
}
