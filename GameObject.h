#pragma once
#include <SDL.h>

class GameObject
{
public:
	GameObject()
		: m_destinationTransform({0, 0, 0, 0})
	{ }

	GameObject(const SDL_FRect destination)
		: m_destinationTransform(destination)
	{ }
	void Draw(SDL_Renderer* pRenderer);
	void UpdatePositionX(float x);
	void UpdatePositionY(float y);
	SDL_FRect& GetTransform() { return m_Transform; }

protected:
	SDL_FRect m_destinationTransform;
};

