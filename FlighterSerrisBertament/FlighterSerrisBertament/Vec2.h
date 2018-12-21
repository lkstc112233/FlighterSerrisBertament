#pragma once
class Vec2 {
 public:
  float x;
  float y;
  Vec2(float both = 0.0F);
  Vec2(float x, float y);
  ~Vec2();
  // point-wise multiply.
  Vec2& operator*=(const Vec2& op);
};
