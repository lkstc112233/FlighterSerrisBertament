#pragma once
class Vec2 {
 public:
  float x;
  float y;
  Vec2(float both = 0.0F);
  Vec2(float x, float y);
  ~Vec2();
  // point-wise add.
  Vec2& operator+=(const Vec2& op);
  Vec2 operator+(const Vec2& op) const;
  // point-wise multiply.
  Vec2& operator*=(const Vec2& op);
  Vec2 operator*(const Vec2& op) const;
};
