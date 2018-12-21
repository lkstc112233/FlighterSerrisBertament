#include "stdafx.h"

#include "MouseDots.h"

MouseDots::MouseDots(std::shared_ptr<Mouse> mousei, float xin, float yin)
    : mouse(mousei), x(xin), y(yin) {}

MouseDots::~MouseDots() {}

std::shared_ptr<Sprite> MouseDots::getSprite() {
  throw 0;  // Not implemented
  return std::shared_ptr<Sprite>();
}
