#include "stdafx.h"

#include "MouseDots.h"

MouseDots::MouseDots(std::shared_ptr<Mouse> mousei) : mouse(mousei) {}

MouseDots::~MouseDots() {}

std::shared_ptr<Sprite> MouseDots::getSprite() {
  throw 0;  // Not implemented
  return std::shared_ptr<Sprite>();
}
