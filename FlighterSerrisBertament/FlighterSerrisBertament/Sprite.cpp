#include "stdafx.h"

#include "Sprite.h"

void SpriteManager::update() {
  std::list<std::shared_ptr<Sprite>> addedSprites;
  for (const auto& sprite : sprites) {
    auto toAdd = sprite->update();
    addedSprites.insert(addedSprites.end(), toAdd.begin(), toAdd.end());
  }
  sprites.insert(sprites.end(), addedSprites.begin(), addedSprites.end());
  sprites.remove_if([](const auto& s) { return s->isDead(); });
}

void SpriteManager::draw(DeviceResources& deviceResources) {
  for (const auto& sprite : sprites) {
    sprite->draw(deviceResources);
  }
}
