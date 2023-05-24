#include "States.h"
#include "Game.h"
#include "StateManager.h"
#include <iostream>

//Begin TitleState
void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;
}

void TitleState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_N))
	{
		std::cout << "Changing to GameState..." << std::endl;
		StateManager::ChangeState(new GameState()); // Change to new GameState
	}
}

void TitleState::Render()
{
	std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 255, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState

// Begin GameState
void GameState::Enter() // Used for initialization
{
	std::cout << "Entering GameState..." << std::endl;
}

void GameState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_X))
	{
		std::cout << "Changing to TitleState..." << std::endl;
		StateManager::ChangeState(new TitleState()); // Change to new TitleState
	}
}

void GameState::Render()
{
	std::cout << "Rendering GameState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;
}


void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;
}
// End GameState