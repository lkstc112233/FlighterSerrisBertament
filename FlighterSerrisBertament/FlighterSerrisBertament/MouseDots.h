#pragma once

#include "Mouse.h"
#include "Sprite.h"

#include "utility.h"

/* A class for physical representation for the dots. */
class MouseDots {
 private:
  class DotSprite : public Sprite {
   private:
    MouseDots* parent;
    D2D1::ColorF::Enum color;
    float radius;

   public:
    DotSprite(MouseDots* parenti) : parent(parenti), radius(1) {
      color = getRandomColor();
    }
    virtual std::list<std::shared_ptr<Sprite>> update() { return {}; }
    virtual void draw(DeviceResources& deviceResources) {
      // Draw an ellipse
      D2D1_ELLIPSE ellipse =
          D2D1::Ellipse(D2D1::Point2F(parent->x, parent->y), radius, radius);

      // Draw the ellipse following the mouse.
      deviceResources.getRenderTarget()->FillEllipse(
          &ellipse, deviceResources.getBrush(color));
    }
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
