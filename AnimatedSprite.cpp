#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(int angle, float frameRate, int maxSprites, SDL_Rect sourceTransform, SDL_FRect destinationTransform)
	: Sprite(sourceTransform, destinationTransform, angle)
	, m_currentSpriteIndex {0}
	, m_maxSprites { maxSprites }
	, m_currentTime {0}
	, m_frameRate {frameRate}
{

}
void AnimatedSprite::Animate(float deltatime)
{
	m_currentTime += deltatime;
	if (m_currentTime > m_frameRate)
	{
		m_currentTime = m_frameRate - m_currentTime;
		m_currentSpriteIndex++;
		if (m_currentSpriteIndex == m_maxSprites)
		{
			m_currentSpriteIndex = 0;
		}
	}

	m_sourceTransform.x = m_sourceTransform.x * m_currentSpriteIndex;
}