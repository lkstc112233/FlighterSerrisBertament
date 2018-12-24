#pragma once
#include "Sprite.h"

// A sprite for displaying fps.
class FpsSprite : public Sprite {
 public:
  FpsSprite();
  ~FpsSprite();
  // Updates the status of the sprite. Return any new sprites.
  virtual std::list<std::shared_ptr<Sprite>> update();
  virtual void draw(DeviceResources& deviceResources);
};
