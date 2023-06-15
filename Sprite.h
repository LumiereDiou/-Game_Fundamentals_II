#pragma once
#include "GameObject.h"

class SpriteObject : public GameObject
{
protected:
	SDL_Rect m_sourceTransfrom;

public:
	SpriteObject(const SDL_Rect source, const SDL_FRect destination)
		: GameObject(destination)
		, m_sourceTransfrom(source)
	{

	}
	SDL_Rect* GetSourceTransform() { return &m_sourceTransfrom; }
	
};

