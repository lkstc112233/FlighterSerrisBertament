#include "stdafx.h"

#include "MouseDots.h"

#include <random>

static std::default_random_engine randomEngine;
static std::uniform_int_distribution<int> dotTypeDistribution(0, 1);

MouseDots::MouseDots(std::shared_ptr<Mouse> mousein,
                     MouseDotsManager& managerin, float xin, float yin)
    : mouse(mousein),
      manager(managerin),
      position(xin, yin),
      type(dotTypeDistribution(randomEngine) ? WEAK : STRONG) {}

MouseDots::~MouseDots() {}

MouseDots::DotSprite::DotSprite(MouseDots* parenti, D2D1::ColorF::Enum colori)
    : parent(parenti), radius(2), color(colori) {}

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

  // Avoid other dots.
  float repealForceFactor = type == WEAK ? 10.0F : 20.0F;
  Vec2 force;
  auto nearby = manager.getNearbyDots(position, type == WEAK ? 10.0F : 20.0F);
  for (auto& dot : nearby) {
    // Note that I'm comparing dot with this. This is a workaround for the
    // pointer issue. Will be changed soon.
    if (dot.get() == this) {
      continue;
    }
    auto distance = position - dot->getPosition();
    force += normalize(distance) * (repealForceFactor / distance.length());
  }
  position += force;
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
    sprite = std::make_shared<DotSprite>(
        this, type == WEAK ? D2D1::ColorF::Blue : D2D1::ColorF::Red);
  }
  return sprite;
}

void MouseDotsManager::update(float time) {
  for (auto& dot : dots) {
    dot->update(0.1F);
  }
}

std::vector<std::shared_ptr<MouseDots>> MouseDotsManager::getNearbyDots(
    Vec2 position, float distance) {
  std::vector<std::shared_ptr<MouseDots>> result;
  for (auto& dot : dots) {
    if ((dot->getPosition() - position).length() < distance) {
      result.emplace_back(dot);
    }
  }
  return result;
}
