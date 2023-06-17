#pragma once
#include "Sprite.h"
#include <string>
#include <SDL.h>

class BackgroundSprite : public SpriteObject
{
public:
	BackgroundSprite(SDL_Rect source, SDL_FRect destination, const char* textureKey);
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

protected:
	std::string m_textureKey;
};