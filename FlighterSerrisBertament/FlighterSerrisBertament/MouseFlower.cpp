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
void MouseFlower::draw(ID2D1HwndRenderTarget* renderTarget) {}
