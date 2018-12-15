#pragma once
#include "Sprite.h"

class MouseFlower : public Sprite {
 private:
  int x;
  int y;

 public:
  constexpr static const float FLOWER_RADIUS = 10.0F;
  MouseFlower();
  ~MouseFlower();
  void mouseTo(int x, int y);
  // Updates the status of the sprite. Return any new sprites.
  virtual std::list<std::shared_ptr<Sprite>> update();
  virtual void draw(DeviceResources& deviceResources);
};
