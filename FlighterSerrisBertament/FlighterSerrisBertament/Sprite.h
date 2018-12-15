#pragma once
#include <list>

class Sprite {
 public:
  Sprite() {}
  virtual ~Sprite() {}
  virtual bool isDead() { return false; }
  // Updates the status of the sprite. Return any new sprites.
  virtual std::list<std::shared_ptr<Sprite>> update() = 0;
  virtual void draw(ID2D1HwndRenderTarget* renderTarget) = 0;
};

class SpriteManager {
 private:
  std::list<std::shared_ptr<Sprite>> sprites;

 public:
  SpriteManager() {}
  ~SpriteManager() {}
  void update();
  void draw(ID2D1HwndRenderTarget* renderTarget);
};
