#include "Sprite.h"

Sprite::Sprite()
	: m_sourceTransform { 0, 0, 0, 0}
	, m_destinationTransform{ 0, 0, 0, 0 }
	, m_angle {0}
{

}


Sprite::Sprite(SDL_Rect m_sourceTransform, SDL_FRect m_destinationTransform, int m_angle)
	:m_sourceTransform{ m_sourceTransform }
	, m_destinationTransform{ m_destinationTransform }
	, m_angle{ m_angle }
{

}