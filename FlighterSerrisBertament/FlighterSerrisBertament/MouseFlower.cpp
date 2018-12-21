#include "stdafx.h"

#include "MouseFlower.h"

MouseFlower::MouseFlower(std::shared_ptr<Mouse> mousein) : mouse(mousein) {}

MouseFlower::~MouseFlower() {}

std::shared_ptr<Sprite> MouseFlower::getSprite() {
  if (!sprite) {
    sprite = std::make_shared<Center>(mouse);
  }
  return sprite;
}
