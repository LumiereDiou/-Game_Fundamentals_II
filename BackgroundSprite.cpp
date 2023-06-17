#include "BackgroundSprite.h"
#include "Game.h"
#include "TextureManager.h"
#include "EventManager.h"

BackgroundSprite::BackgroundSprite(SDL_Rect source, SDL_FRect destination, const char* textureKey)
	: SpriteObject(source, destination)
	, m_textureKey(textureKey)
{

}

void BackgroundSprite::Render()
{
	SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(m_textureKey), &m_sourceTransfrom, &m_destinationTransform);
}

void BackgroundSprite::Update(float deltaTime) {}