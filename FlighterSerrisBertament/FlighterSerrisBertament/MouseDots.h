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
 public:
  enum Type { WEAK, STRONG };

 private:
  /* The coresponding sprite for MouseDot. */
  class DotSprite : public Sprite {
   private:
    MouseDots* parent;
    ID2D1SolidColorBrush* (DeviceResources::*getBrush)(void);
    float radius;

   public:
    DotSprite(MouseDots* parenti, decltype(getBrush) getBrush);
    virtual void update(std::list<std::shared_ptr<Sprite>>& toAdd);
    virtual void draw(DeviceResources& deviceResources);
  };
  /* The coresponding sprite for MouseDot. */
  class FadingDotSprite : public Sprite {
   private:
    ID2D1SolidColorBrush* (DeviceResources::*getBrush)(void);
    float radius;
    const float x;
    const float y;
    const float rate;

   public:
    FadingDotSprite(decltype(getBrush) getBrush, float radius, float x, float y,
                    float rate = 0.9);
    virtual bool isDead() const;
    virtual void update(std::list<std::shared_ptr<Sprite>>& toAdd);
    virtual void draw(DeviceResources& deviceResources);
  };

 private:
  std::shared_ptr<Mouse> mouse;
  std::shared_ptr<DotSprite> sprite;
  MouseDotsManager& manager;
  Vec2 position;
  Type type;

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
