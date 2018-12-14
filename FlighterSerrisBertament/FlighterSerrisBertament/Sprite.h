#pragma once

class Sprite {
 public:
  Sprite() {}
  virtual ~Sprite() {}

 private:
  virtual bool isDead() { return false; }
  virtual void update() = 0;
  virtual void draw(ID2D1HwndRenderTarget *renderTarget) = 0;
};
