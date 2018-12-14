#pragma once
#include "Sprite.h"

class MouseFlower : public Sprite {
 private:
  int x;
  int y;

 public:
  MouseFlower();
  ~MouseFlower();
  void mouseTo(int x, int y);
  // Updates the status of the sprite. Return any new sprites.
  virtual std::list<std::unique_ptr<Sprite>> update() = 0;
  virtual void draw(ID2D1HwndRenderTarget* renderTarget) = 0;
};
