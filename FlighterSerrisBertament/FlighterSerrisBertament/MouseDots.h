#pragma once

#include "Mouse.h"
#include "Sprite.h"

#include "utility.h"

/* A class for physical representation for the dots. */
class MouseDots {
 private:
  /* The coresponding sprite for MouseDot. */
  class DotSprite : public Sprite {
   private:
    MouseDots* parent;
    D2D1::ColorF::Enum color;
    float radius;

   public:
    DotSprite(MouseDots* parenti);
    virtual void draw(DeviceResources& deviceResources);
  };

 private:
  std::shared_ptr<Mouse> mouse;
  std::shared_ptr<DotSprite> sprite;
  float x;
  float y;

 public:
  MouseDots(std::shared_ptr<Mouse> mouse, float xin, float yin);
  ~MouseDots();
  void update(float time);
  std::shared_ptr<Sprite> getSprite();
};

class MouseDotsManager {
 private:
  std::vector<std::shared_ptr<MouseDots>> dots;

 public:
  template <typename... Args>
  std::shared_ptr<MouseDots> addDot(Args&&... arg) {
    dots.emplace_back(arg...);
    return dots.back();
  }
  void update(float time);
};
