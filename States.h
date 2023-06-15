#pragma once
#include "SDL.h"
#include <vector>
#include <SDL_image.h>
#include <SDL_mixer.h>

class GameObject;
class AnimatedSprite;
class TiledLevel;

class State // This is the abstract base class for all states
{
public:
	State() = default;
	virtual ~State() = default; // Modern alternative to {}

	virtual void Enter() = 0; // 0 means pure virtual - must be defined in subclass
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void Resume() { };
};

class TitleState : public State
{
	SDL_Texture* m_pDeveloperTexture;
	float timer = 0.0f;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class MenuState : public State
{
	SDL_Texture* m_pBackGroundTexture;
	SDL_Texture* m_pGameNameTexture;
	SDL_Texture* m_pKeyInputTexture;

	Mix_Music* m_pMusic;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class CreditState : public State
{
	SDL_Texture* m_pTitleTexture;
	SDL_Texture* m_pNameTexture;
	SDL_Texture* m_pKeyInputTexture;

	Mix_Music* m_pMusic;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class GameState : public State
{
	static const int kPlayerSpeed = 400;
	float timer = 0.0f;
	TiledLevel* m_pLevel;
	Mix_Music* m_pMusic;
	Mix_Chunk* m_pSoundEffect;

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
};

class PauseState : public State
{
	SDL_Texture* m_pTitleTexture;
	SDL_Texture* m_pBackGroundTexture;
	SDL_Texture* m_pKeyInputTexture;

	Mix_Music* m_pMusic;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class WinState : public State
{
	SDL_Texture* m_pTitleTexture;
	SDL_Texture* m_pBackGroundTexture;
	SDL_Texture* m_pKeyInputTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LoseState : public State
{
	SDL_Texture* m_pTitleTexture;
	SDL_Texture* m_pBackGroundTexture;
	SDL_Texture* m_pKeyInputTexture;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};