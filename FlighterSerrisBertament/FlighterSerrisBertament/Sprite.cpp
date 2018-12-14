#include "stdafx.h"

#include "Sprite.h"

void SpriteManager::update() {
  for (const auto& sprite : sprites) {
    sprite->update();
  }
  sprites.remove_if([](const auto& s) { return s->isDead(); });
}

void SpriteManager::draw(ID2D1HwndRenderTarget* renderTarget) {
  for (const auto& sprite : sprites) {
    sprite->draw(renderTarget);
  }
}
