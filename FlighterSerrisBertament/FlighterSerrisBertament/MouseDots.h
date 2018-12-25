#pragma once

#include <vector>

#include "Mouse.h"
#include "Sprite.h"
#include "Vec2.h"

#include "utility.h"

// Predefinition of the dots manager.
class MouseDotsManager;

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
  MouseDotsManager& manager;
  Vec2 position;

 public:
  MouseDots(std::shared_ptr<Mouse> mouse, MouseDotsManager& manager, float xin,
            float yin);
  ~MouseDots();
  Vec2 getPosition() { return position; }
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
  std::vector<std::shared_ptr<MouseDots>> getNearbyDots(Vec2 position,
                                                        float distance = 10);
};
