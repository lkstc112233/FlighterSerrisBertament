#pragma once
#include <list>
#include "DeviceResources.h"

class Sprite {
 public:
  Sprite() {}
  virtual ~Sprite() {}
  virtual bool isDead() const { return false; }
  virtual float getZ() const { return 0.0F; }
  // Updates the status of the sprite. Return any new sprites.
  virtual std::list<std::shared_ptr<Sprite>> update() { return {}; }
  virtual void draw(DeviceResources& deviceResources) = 0;
};

class SpriteManager {
 private:
  std::list<std::shared_ptr<Sprite>> sprites;

 public:
  SpriteManager() {}
  ~SpriteManager() {}
  void update();
  void addSprite(std::shared_ptr<Sprite> sprite);
  void draw(DeviceResources& deviceResources);
};
