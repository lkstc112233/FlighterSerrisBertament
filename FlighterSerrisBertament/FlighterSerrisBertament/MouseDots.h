#pragma once

#include "Mouse.h"
#include "Sprite.h"

/* A class for physical representation for the dots. */
class MouseDots {
 private:
  std::shared_ptr<Mouse> mouse;
  float x;
  float y;

 public:
  MouseDots(std::shared_ptr<Mouse> mouse, float xin, float yin);
  ~MouseDots();
  void update(float time);
  std::shared_ptr<Sprite> getSprite();
};
