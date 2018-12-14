#include "stdafx.h"

#include "MouseFlower.h"

MouseFlower::MouseFlower() {}

MouseFlower::~MouseFlower() {}

void MouseFlower::mouseTo(int xin, int yin) {
  x = xin;
  y = yin;
}
// Updates the status of the sprite. Return any new sprites.
std::list<std::unique_ptr<Sprite>> MouseFlower::update() {}
void MouseFlower::draw(ID2D1HwndRenderTarget* renderTarget) {}
