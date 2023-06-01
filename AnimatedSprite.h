#pragma once
#include "Sprite.h"
class AnimatedSprite : public Sprite
{
protected:
	int m_currentSpriteIndex;
	int m_maxSprite;
	float m_currentTime;
	float m_framRate;

public:
	AnimatedSprite(int angle, float frameRate, int maxSprites,
		SDL_Rect sourceTranform, SDL_FRect destinationTransfrom);
	void Animate(float deltaTime);
};

