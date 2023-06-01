#pragma once
#include "Sprite.h"
class AnimatedSprite : public Sprite
{
protected:
	int m_currentSpriteIndex, m_maxSprites;
	float m_currentTime, m_frameRate;

public:
	AnimatedSprite(int angle, float frameRate, int maxSprites, SDL_Rect sourceTransform, SDL_FRect destinationTransform);
	void Animate(float deltatime);
};

