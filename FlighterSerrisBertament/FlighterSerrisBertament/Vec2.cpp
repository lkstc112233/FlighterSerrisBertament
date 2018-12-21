#include "stdafx.h"

#include "Vec2.h"

Vec2::Vec2(float both = 0.0F) : x(both), y(both) {}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

Vec2::~Vec2() {}

Vec2& Vec2::operator*=(const Vec2& op) {
  x *= op.x;
  y *= op.y;
  return *this;
}
