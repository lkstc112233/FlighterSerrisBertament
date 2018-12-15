#include "stdafx.h"

#include "MouseFlower.h"

MouseFlower::MouseFlower() : x(0), y(0) {}

MouseFlower::~MouseFlower() {}

void MouseFlower::mouseTo(int xin, int yin) {
  x = xin;
  y = yin;
}
// Updates the status of the sprite. Return any new sprites.
std::list<std::shared_ptr<Sprite>> MouseFlower::update() { return {}; }
void MouseFlower::draw(DeviceResources& deviceResources) {
  // Draw an ellipse
  D2D1_ELLIPSE ellipse =
      D2D1::Ellipse(D2D1::Point2F(static_cast<FLOAT>(x), static_cast<FLOAT>(y)),
                    FLOWER_RADIUS, FLOWER_RADIUS);

  // Draw the ellipse following the mouse.
  deviceResources.getRenderTarget()->FillEllipse(
      &ellipse, deviceResources.getBrush(D2D1::ColorF::CornflowerBlue));
}
