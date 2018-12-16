#include "stdafx.h"

#include "FpsSprite.h"

FpsSprite::FpsSprite() {}

FpsSprite::~FpsSprite() {}

std::list<std::shared_ptr<Sprite>> FpsSprite::update() {
  return std::list<std::shared_ptr<Sprite>>();
}

void FpsSprite::draw(DeviceResources& deviceResources) {}
