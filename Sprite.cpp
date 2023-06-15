#include "Sprite.h"

Sprite::Sprite()
	: m_sourceTransfrom {0, 0, 0, 0}
	, m_destinationTransfrom {0, 0, 0, 0}
	, m_angle {0}
{ }

Sprite::Sprite(SDL_Rect sourceTransform, SDL_FRect destinationTransfrom, int angle)
	: m_sourceTransfrom{ sourceTransform }
	, m_destinationTransfrom{ destinationTransfrom }
	, m_angle{ angle }
{ }