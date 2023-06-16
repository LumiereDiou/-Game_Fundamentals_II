#include "AnimatedSprite.h"

AnimatedSpriteObject::AnimatedSpriteObject(const SDL_Rect source, SDL_FRect destination)
	: SpriteObject(source, destination)
	, m_currentSpriteIndex(0)
	, m_startingSpriteIndex(0)
	, m_totalSprites(0)
	, m_currentTime(0)
	, m_frameRate(0)
{

}

void AnimatedSpriteObject::SetAnimation(float frameRate, int startingSpriteIndex, int totalSprites, int sourceY)
{
	m_currentTime = 0;
	m_frameRate = frameRate;
	m_currentSpriteIndex = 0;
	m_startingSpriteIndex = startingSpriteIndex;
	m_totalSprites = totalSprites;
	m_sourceTransfrom.x = m_sourceTransfrom.w * startingSpriteIndex;
	m_sourceTransfrom.y = sourceY;
}

void AnimatedSpriteObject::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameRate)
	{
		m_currentTime = m_frameRate - m_currentTime;
		m_currentSpriteIndex++;
		if (m_currentSpriteIndex == m_totalSprites)
		{
			m_currentSpriteIndex = 0;
		}
	}
	m_sourceTransfrom.x = m_sourceTransfrom.w * (m_startingSpriteIndex + m_currentSpriteIndex);
}