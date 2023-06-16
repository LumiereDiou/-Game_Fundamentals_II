#pragma once
#include "SDL.h"
#include <vector>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

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
	virtual void Pause() { };

	std::map<std::string, GameObject*> m_objects;

};

class TitleState : public State
{
	float timer = 0.0f;
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class MenuState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class CreditState : public State
{
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

public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Resume() override;
	virtual void Pause() override;
};

class PauseState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class WinState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};

class LoseState : public State
{
public:
	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
};