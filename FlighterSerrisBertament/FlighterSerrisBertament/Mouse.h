#pragma once
#include "Vec2.h"

class Mouse {
 private:
  int x = 0;
  int y = 0;

 public:
  Mouse();
  ~Mouse();
  void mouseTo(int x, int y);
  int getX() { return x; }
  int getY() { return y; }
  Vec2 getPosition();
};
