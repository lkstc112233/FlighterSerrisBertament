#include "stdafx.h"

#include "MouseFlower.h"

#include "utility.h"

#include <random>

MouseFlower::MouseFlower() : x(0), y(0), generateShadowCountdown(0) {}

MouseFlower::~MouseFlower() {}

void MouseFlower::mouseTo(int xin, int yin) {
  x = xin;
  y = yin;
}
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
          lifeMax(lifein) {}
    bool isDead() { return life <= 0; }
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
          FLOWER_RADIUS, FLOWER_RADIUS);

      // Pick a random color from D2D1::ColorF.
      auto color = getRandomColor();

      auto brush = deviceResources.getBrush(color);
      auto oldOpacity = brush->GetOpacity();
      brush->SetOpacity(alpha);

      // Draw the ellipse following the mouse.
      deviceResources.getRenderTarget()->FillEllipse(&ellipse, brush);
      brush->SetOpacity(oldOpacity);
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
        static_cast<float>(x), static_cast<float>(y),
        speedDistribution(randomEngine), speedDistribution(randomEngine), 0.0F,
        DEFAULT_AY, lifeDistribution(randomEngine))};
  }
  return {};
}
void MouseFlower::draw(DeviceResources& deviceResources) {
  // Draw an ellipse
  D2D1_ELLIPSE ellipse =
      D2D1::Ellipse(D2D1::Point2F(static_cast<FLOAT>(x), static_cast<FLOAT>(y)),
                    FLOWER_RADIUS, FLOWER_RADIUS);

  // Draw the ellipse following the mouse.
  deviceResources.getRenderTarget()->FillEllipse(
      &ellipse, deviceResources.getBrush(D2D1::ColorF::CornflowerBlue));
}
