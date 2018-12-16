#include "stdafx.h"

#include "MouseFlower.h"

#include "utility.h"

#include <random>

MouseFlower::MouseFlower(std::shared_ptr<Mouse> mousein)
    : mouse(mousein), generateShadowCountdown(0) {}

MouseFlower::~MouseFlower() {}

// Updates the status of the sprite. Return any new sprites.
std::list<std::shared_ptr<Sprite>> MouseFlower::update() {
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
    float getZ() const { return -1; }
    bool isDead() const { return life <= 0; }
    std::list<std::shared_ptr<Sprite>> update() {
      x += vx;
      y += vy;
      vx += ax;
      vy += ay;
      life -= 1;
      alpha = static_cast<float>(life) / lifeMax;
      return {};
    }
    void draw(DeviceResources& deviceResources) {
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
  if (--generateShadowCountdown < 0) {
    static std::default_random_engine randomEngine;
    static std::uniform_int_distribution<int> countdownDistribution(
        MIN_COUNTDOWN_SPAWN_SHADOW, MAX_COUNTDOWN_SPAWN_SHADOW);
    static std::uniform_int_distribution<int> lifeDistribution(
        MIN_LIFE_SPAWN_SHADOW, MAX_LIFE_SPAWN_SHADOW);
    static std::normal_distribution<float> speedDistribution(0, 1);
    generateShadowCountdown = countdownDistribution(randomEngine);
    return {std::make_shared<Shadow>(
        static_cast<float>(mouse->getX()), static_cast<float>(mouse->getY()),
        speedDistribution(randomEngine) * 10,
        speedDistribution(randomEngine) * 10, 0.0F, DEFAULT_AY,
        lifeDistribution(randomEngine))};
  }
  return {};
}
void MouseFlower::draw(DeviceResources& deviceResources) {
  // Draw an ellipse
  D2D1_ELLIPSE ellipse =
      D2D1::Ellipse(D2D1::Point2F(static_cast<FLOAT>(mouse->getX()),
                                  static_cast<FLOAT>(mouse->getY())),
                    FLOWER_RADIUS, FLOWER_RADIUS);

  // Draw the ellipse following the mouse.
  deviceResources.getRenderTarget()->FillEllipse(
      &ellipse, deviceResources.getBrush(D2D1::ColorF::CornflowerBlue));
}
