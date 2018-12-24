#include "stdafx.h"

#include "MouseDots.h"

MouseDots::MouseDots(std::shared_ptr<Mouse> mousein,
                     MouseDotsManager& managerin, float xin, float yin)
    : mouse(mousein), manager(managerin), position(xin, yin) {}

MouseDots::~MouseDots() {}

MouseDots::DotSprite::DotSprite(MouseDots* parenti)
    : parent(parenti), radius(2) {
  color = getRandomColor();
}

void MouseDots::update(float time) {
  // Move the dot towards the mouse.
  float speed = 1.0F;

  // Calculate direction
  Vec2 diff = mouse->getPosition() - position;
  float distance = diff.length();
  diff.normalize() *= speed;

  // Move the dot, unless the dot is near enough.
  if (distance > 5 * speed) {
    position += diff;
  }
}

void MouseDots::DotSprite::draw(DeviceResources& deviceResources) {
  // Draw an ellipse
  D2D1_ELLIPSE ellipse = D2D1::Ellipse(
      D2D1::Point2F(parent->position.x, parent->position.y), radius, radius);

  // Draw the ellipse following the mouse.
  deviceResources.getRenderTarget()->FillEllipse(
      &ellipse, deviceResources.getBrush(color));
}

std::shared_ptr<Sprite> MouseDots::getSprite() {
  if (!sprite) {
    sprite = std::make_shared<DotSprite>(this);
  }
  return sprite;
}

void MouseDotsManager::update(float time) {
  for (auto& dot : dots) {
    dot->update(0.1F);
  }
}
