#include "stdafx.h"

#include "Mouse.h"

Mouse::Mouse() {}

Mouse::~Mouse() {}

void Mouse::mouseTo(int xin, int yin) {
  x = xin;
  y = yin;
}

Vec2 Mouse::getPosition() {
  return Vec2(static_cast<float>(x), static_cast<float>(y));
}
