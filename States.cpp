#include "States.h"
#include "Game.h"
#include "StateManager.h"
#include "GameObject.h"
#include <iostream>
#include "CollisionManager.h"



//Begin TitleState
void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;
}

void TitleState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= 4.0f)
	{
		StateManager::ChangeState(new MenuState());
	}
	
}

void TitleState::Render()
{
	std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState

// Begin MenuState
void MenuState::Enter() // Used for initialization
{
	std::cout << "Entering MenuState..." << std::endl;
}

void MenuState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_C))
	{
		std::cout << "Changing to CreditState..." << std::endl;
		StateManager::ChangeState(new CreditState());
	}
	else if (GameInstance.KeyDown(SDL_SCANCODE_G))
	{
		std::cout << "Changing to GameState..." << std::endl;
		StateManager::PushState(new GameState());
	}
}


void MenuState::Render()
{
	//std::cout << "Rendering MenuState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 0, 128, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void MenuState::Exit()
{
	std::cout << "Exiting MenuState..." << std::endl;
}
// End MenuState

// Begin CreditState
void CreditState::Enter() // Used for initialization
{
	std::cout << "Entering CreditState..." << std::endl;
}

void CreditState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_ESCAPE))
	{
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}


void CreditState::Render()
{
	//std::cout << "Rendering CreditState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 225, 192, 203, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void CreditState::Exit()
{
	std::cout << "Exiting CreditState..." << std::endl;
}
// End CreditState

// Begin GameState
void GameState::Enter() // Used for initialization
{
	std::cout << "Entering GameState..." << std::endl;
	m_gameObjects.push_back(new GameObject(100, 100,30, 30));
	m_gameObjects.push_back(new GameObject(400, 100,30, 30));
	m_gameObjects.push_back(new GameObject(700, 100,30, 30));

	m_pPlayer = new GameObject(Game::kWidth / 2, Game::kHeight / 2, 100, 100, 255, 255, 255, 255);
	m_gameObjects.push_back(m_pPlayer);

}

void GameState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= 20.0f)
	{
		StateManager::ChangeState(new WinState());
	}

	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState..." << std::endl;
		StateManager::PushState(new PauseState()); // Add new PauseState
	}
	else
	{
		if (GameInstance.KeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->UpdatePositionY(-kPlayerSpeed * deltaTime);
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_S))
		{
			m_pPlayer->UpdatePositionY(kPlayerSpeed * deltaTime);
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->UpdatePositionX(-kPlayerSpeed * deltaTime);
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->UpdatePositionX(kPlayerSpeed * deltaTime);
		}

		// Check for collision
		for (GameObject* pObject : m_gameObjects)
		{
			if (pObject != m_pPlayer)
			{
				if (CollisionManager::AABBCheck(m_pPlayer->GetTransform(), pObject->GetTransform()))
				{
					std::cout << "Player Object Collision" << std::endl;
					StateManager::PushState(new LoseState());
				}
			}
		}
	}
	
}

void GameState::Render()
{
	//std::cout << "Rendering GameState..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255); //blue
	SDL_RenderClear(pRenderer);
	
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Draw(pRenderer);
	}
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;
	
	for (GameObject* pObject : m_gameObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
}


void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;
}
// End GameState

// Begin PauseState
void PauseState::Enter()
{
	std::cout << "Entering PauseState..." << std::endl;
}

void PauseState::Update(float deltaTime)
{
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE))
	{
		StateManager::PopState();
	}
}

void PauseState::Render()
{
	//std::cout << "Rendering PauseState..." << std::endl;
	// First render the GameSate
	// Now render rest of PauseState
	//SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
	//StateManager::GetStates().front()->Render();
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);
}

void PauseState::Exit()
{
	std::cout << "Exiting PauseState..." << std::endl;
}
// End PauseState

// Begin WinState
void WinState::Enter() // Used for initialization
{
	std::cout << "Entering WinState..." << std::endl;
}

void WinState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_SPACE))
	{
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}


void WinState::Render()
{
	//std::cout << "Rendering WinState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 225, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void WinState::Exit()
{
	std::cout << "Exiting WinState..." << std::endl;
}
// End WinState

// Begin LoseState
void LoseState::Enter() // Used for initialization
{
	std::cout << "Entering LoseState..." << std::endl;
}

void LoseState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_SPACE))
	{
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}


void LoseState::Render()
{
	//std::cout << "Rendering LoseState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 225, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState..." << std::endl;
}
// End LoseState