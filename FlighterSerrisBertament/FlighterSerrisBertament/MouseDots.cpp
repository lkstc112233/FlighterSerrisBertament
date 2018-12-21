#include "stdafx.h"

#include "MouseDots.h"

MouseDots::MouseDots(std::shared_ptr<Mouse> mousei, float xin, float yin)
    : mouse(mousei), x(xin), y(yin) {}

MouseDots::~MouseDots() {}

void MouseDots::update(float time) {
  // Move the dot towards the mouse.
  float speed = 1.0F;

  // Calculate direction
  float dx = mouse->getX() - x;
  float dy = mouse->getY() - y;

  // Calculate rate
  float rate = 1 / sqrt((dx * dx + dy * dy)) / speed;

  // Move the dot
  if (rate < 1 / speed) {
    x += dx * rate;
    y += dy * rate;
  } else {
    // If near enough, only half the move is performed.
    x += dx * rate / 2;
    y += dx * rate / 2;
  }
}

std::shared_ptr<Sprite> MouseDots::getSprite() {
  if (!sprite) {
    sprite = std::make_shared<DotSprite>(this);
  }
  return sprite;
}
