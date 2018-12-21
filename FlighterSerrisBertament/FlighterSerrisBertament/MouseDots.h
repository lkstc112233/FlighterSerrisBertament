#pragma once

#include "Mouse.h"
#include "Sprite.h"

/* A class for physical representation for the dots. */
class MouseDots {
 private:
  std::shared_ptr<Mouse> mouse;

 public:
  MouseDots(std::shared_ptr<Mouse> mouse);
  ~MouseDots();
  std::shared_ptr<Sprite> getSprite();
};
