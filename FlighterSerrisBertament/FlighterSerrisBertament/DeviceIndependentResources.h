#pragma once

#include <map>
#include <string>

class DeviceIndependentResources {
 private:
  ID2D1Factory* direct2dFactory;
  IDWriteFactory* directWriteFactory;
  std::map<std::pair<std::wstring, float>, IDWriteTextFormat*> formats;
  bool valid;

 public:
  DeviceIndependentResources();
  ~DeviceIndependentResources();
  ID2D1Factory* getDirect2dFactory() { return direct2dFactory; }
  IDWriteTextFormat* getTextFormat(const wchar_t* font, float size);
};
