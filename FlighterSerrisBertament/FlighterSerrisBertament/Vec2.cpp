#include "stdafx.h"

#include "Vec2.h"

Vec2::Vec2(float both) : x(both), y(both) {}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

Vec2& Vec2::operator+=(const Vec2& op) {
  x += op.x;
  y += op.y;
  return *this;
}

Vec2 Vec2::operator+(const Vec2& op) const {
  Vec2 result = *this;
  return result += op;
}

Vec2& Vec2::operator-=(const Vec2& op) {
  x -= op.x;
  y -= op.y;
  return *this;
}

Vec2 Vec2::operator-(const Vec2& op) const {
  Vec2 result = *this;
  return result -= op;
}

Vec2& Vec2::operator*=(const Vec2& op) {
  x *= op.x;
  y *= op.y;
  return *this;
}

Vec2 Vec2::operator*(const Vec2& op) const {
  Vec2 result = *this;
  return result *= op;
}

Vec2& Vec2::operator*=(float op) {
  x *= op;
  y *= op;
  return *this;
}

Vec2 Vec2::operator*(float op) const {
  Vec2 result = *this;
  return result *= op;
}

Vec2 Vec2::operator-() const {
  Vec2 result;
  result.x = -this->x;
  result.y = -this->y;
  return result;
}

float Vec2::length() const { return sqrt(x * x + y * y); }
float Vec2::lengthSquared() const { return x * x + y * y; }

Vec2& Vec2::normalize() {
  float len = length();
  x /= len;
  y /= len;
  return *this;
}

Vec2 operator*(float op, const Vec2& vec) { return vec * op; }

float dot(const Vec2& op, const Vec2& op2) {
  return op.x * op2.x + op.y * op2.y;
}

Vec2 normalize(const Vec2& op) {
  Vec2 result(op);
  return result.normalize();
}
