#include "stdafx.h"

#include "DeviceIndependentResources.h"

#include "utility.h"

DeviceIndependentResources::DeviceIndependentResources() {
  // Create a Direct2D factory.
  valid = SUCCEEDED(
      D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &direct2dFactory));
  if (valid) {
    // Create a DirectWrite factory.
    valid = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED, __uuidof(directWriteFactory),
        reinterpret_cast<IUnknown**>(&directWriteFactory));
  }
}

DeviceIndependentResources::~DeviceIndependentResources() {
  SafeRelease(&direct2dFactory);
  SafeRelease(&directWriteFactory);
  for (auto format : formats) {
    SafeRelease(&format.second);
  }
}

IDWriteTextFormat* DeviceIndependentResources::getTextFormat(
    const wchar_t* font, float size) {
  auto format = formats.find(std::make_pair(font, size));
  if (format == formats.end()) {
    IDWriteTextFormat* formatToInsert = nullptr;
    // Create a DirectWrite text format object.
    HRESULT operationResult = directWriteFactory->CreateTextFormat(
        font, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, size,
        L"",  // locale
        &formatToInsert);
    if (SUCCEEDED(operationResult)) {
      // Center the text horizontally and vertically.
      formatToInsert->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
      formatToInsert->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
      auto iteratorPair =
          formats.emplace(std::make_pair(font, size), formatToInsert);
      if (iteratorPair.second) {
        format = iteratorPair.first;
      } else {
        valid = false;
      }
    }
  }
  return format->second;
}
