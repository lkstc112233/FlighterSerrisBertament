#pragma once
#include "Sprite.h"

class MouseFlower : public Sprite {
 private:
  int x;
  int y;
  int generateShadowCountdown;

 public:
  constexpr static const float FLOWER_RADIUS = 10.0F;
  constexpr static const int MIN_COUNTDOWN_SPAWN_SHADOW = 10;
  constexpr static const int MAX_COUNTDOWN_SPAWN_SHADOW = 40;
  constexpr static const int MIN_LIFE_SPAWN_SHADOW = 40;
  constexpr static const int MAX_LIFE_SPAWN_SHADOW = 70;
  constexpr static const float DEFAULT_AY = 1.0F;
  MouseFlower();
  ~MouseFlower();
  void mouseTo(int x, int y);
  // Updates the status of the sprite. Return any new sprites.
  virtual std::list<std::shared_ptr<Sprite>> update();
  virtual void draw(DeviceResources& deviceResources);
};
