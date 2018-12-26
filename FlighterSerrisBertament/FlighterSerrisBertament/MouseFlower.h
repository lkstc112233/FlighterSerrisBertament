#pragma once

#include <random>

#include "Mouse.h"
#include "Sprite.h"
#include "utility.h"

class MouseFlower {
 private:
  std::shared_ptr<Mouse> mouse;
  std::shared_ptr<Sprite> sprite;
  class Center : public Sprite {
   private:
    int generateShadowCountdown;
    std::shared_ptr<Mouse> mouse;

   protected:
    float x;
    float y;

   public:
    Center(std::shared_ptr<Mouse> mousein)
        : mouse(mousein), generateShadowCountdown(0) {}
    virtual std::list<std::shared_ptr<Sprite>> update() {
      x = static_cast<float>(mouse->getX());
      y = static_cast<float>(mouse->getY());
      if (--generateShadowCountdown < 0) {
        static std::default_random_engine randomEngine;
        static std::uniform_int_distribution<int> countdownDistribution(
            MIN_COUNTDOWN_SPAWN_SHADOW, MAX_COUNTDOWN_SPAWN_SHADOW);
        static std::uniform_int_distribution<int> lifeDistribution(
            MIN_LIFE_SPAWN_SHADOW, MAX_LIFE_SPAWN_SHADOW);
        static std::normal_distribution<float> speedDistribution(0, 1);
        generateShadowCountdown = countdownDistribution(randomEngine);
        return {std::make_shared<Shadow>(
            x, y, speedDistribution(randomEngine) * 10,
            speedDistribution(randomEngine) * 10, 0.0F, DEFAULT_AY,
            lifeDistribution(randomEngine))};
      }
      return {};
    }
    virtual void draw(DeviceResources& deviceResources) {
      // Draw an ellipse
      D2D1_ELLIPSE ellipse =
          D2D1::Ellipse(D2D1::Point2F(x, y), FLOWER_RADIUS, FLOWER_RADIUS);

      // Draw the ellipse following the mouse.
      deviceResources.getRenderTarget()->FillEllipse(
          &ellipse, deviceResources.getBrush(D2D1::ColorF::CornflowerBlue));
    }
  };
  class Shadow : public Sprite {
   private:
    float x;
    float y;
    float vx;
    float vy;
    float ax;
    float ay;
    float alpha;
    int life;
    int lifeMax;
    D2D1::ColorF::Enum color;

   public:
    Shadow(float xin, float yin, float vxin, float vyin, float axin, float ayin,
           int lifein)
        : x(xin),
          y(yin),
          vx(vxin),
          vy(vyin),
          ax(axin),
          ay(ayin),
          alpha(1.0),
          life(lifein),
          lifeMax(lifein) {
      // Pick a random color from D2D1::ColorF.
      color = getRandomColor();
    }
    virtual bool isDead() const { return life <= 0; }
    virtual std::list<std::shared_ptr<Sprite>> update() {
      x += vx;
      y += vy;
      vx += ax;
      vy += ay;
      life -= 1;
      alpha = static_cast<float>(life) / lifeMax;
      return {};
    }
    virtual void draw(DeviceResources& deviceResources) {
      // Draw an ellipse
      D2D1_ELLIPSE ellipse = D2D1::Ellipse(
          D2D1::Point2F(static_cast<FLOAT>(x), static_cast<FLOAT>(y)),
          FLOWER_RADIUS / 3, FLOWER_RADIUS / 3);

      auto brush = deviceResources.getBrush(color);
      auto oldOpacity = brush->GetOpacity();
      brush->SetOpacity(alpha);

      deviceResources.getRenderTarget()->FillEllipse(&ellipse, brush);
      brush->SetOpacity(oldOpacity);
      deviceResources.getRenderTarget()->DrawEllipse(
          &ellipse, deviceResources.getBrush(D2D1::ColorF::Black));
    }
  };

 public:
  constexpr static const float FLOWER_RADIUS = 10.0F;
  constexpr static const int MIN_COUNTDOWN_SPAWN_SHADOW = 1;
  constexpr static const int MAX_COUNTDOWN_SPAWN_SHADOW = 1;
  constexpr static const int MIN_LIFE_SPAWN_SHADOW = 40;
  constexpr static const int MAX_LIFE_SPAWN_SHADOW = 70;
  constexpr static const float DEFAULT_AY = 1.0F;
  MouseFlower(std::shared_ptr<Mouse> mouse);
  ~MouseFlower();
  std::shared_ptr<Sprite> getSprite();
};
