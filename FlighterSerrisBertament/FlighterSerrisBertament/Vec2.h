#pragma once
class Vec2 {
 public:
  float x;
  float y;
  Vec2(float both = 0.0F);
  Vec2(float x, float y);
  ~Vec2();
  // point-wise add and minus.
  Vec2& operator+=(const Vec2& op);
  Vec2 operator+(const Vec2& op) const;
  Vec2& operator-=(const Vec2& op);
  Vec2 operator-(const Vec2& op) const;
  // point-wise multiply.
  Vec2& operator*=(const Vec2& op);
  Vec2 operator*(const Vec2& op) const;
  Vec2& operator*=(float op);
  Vec2 operator*(float op) const;
  // negative
  Vec2 operator-() const;
  float length() const;
  Vec2& normalize();
};

Vec2 operator*(float op, const Vec2& vec);
float dot(const Vec2& op, const Vec2& op2);
