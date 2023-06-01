#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(int angle, float frameRate, int maxSprites, 
	SDL_Rect sourceTranform, SDL_FRect destinationTransfrom)
	: Sprite(sourceTranform, destinationTransfrom, angle)
	, m_currentSpriteIndex {0}
	, m_maxSprite { maxSprites }
	, m_currentTime {0}
	, m_framRate {frameRate}
{ }

void AnimatedSprite::Animate(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_framRate)
	{
		m_currentTime = m_framRate - m_currentTime;
		m_currentSpriteIndex++;
		if (m_currentSpriteIndex == m_maxSprite)
		{
			m_currentSpriteIndex = 0;
		}
	}

	m_sourceTransfrom.x = m_sourceTransfrom.w * m_currentSpriteIndex;
}