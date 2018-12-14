#pragma once
#include <list>

class Sprite {
 public:
  Sprite() {}
  virtual ~Sprite() {}
  virtual bool isDead() { return false; }
  virtual void update() = 0;
  virtual void draw(ID2D1HwndRenderTarget* renderTarget) = 0;
};

class SpriteManager {
 private:
  std::list<std::unique_ptr<Sprite>> sprites;

 public:
  SpriteManager() {}
  ~SpriteManager() {}
  void update();
  void draw(ID2D1HwndRenderTarget* renderTarget);
};
