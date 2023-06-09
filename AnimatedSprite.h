#pragma once
#include "Sprite.h"

class AnimatedSpriteObject : public SpriteObject
{
public:
	virtual void Render() = 0;

protected:

	int m_currentSpriteIndex;
	int m_startingSpriteIndex;
	int m_totalSprites;

	float m_currentTime;
	float m_frameRate;

protected:
	AnimatedSpriteObject(const SDL_Rect source, SDL_FRect destination);
	
	void SetAnimation(float frameRate, int startingSpriteIndex, int totalSprite, int sourceY = 0);
	
	virtual void Update(float deltaTime) override;
};