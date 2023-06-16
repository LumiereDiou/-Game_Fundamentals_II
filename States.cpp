#include "States.h"
#include "Game.h"
#include "StateManager.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "AnimatedSprite.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "TiledLevel.h"
#include "Tile.h"
#include "PlatformingPlayer.h"
#include "BackgroundSprite.h"
#include "PlayButton.h"
#include "CreditButton.h"
#include <iostream>


//Begin TitleState
void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;

	SoundManager::LoadMusic("assets/Sound/Music/Menu.mp3", "MainMenuMusic");
	SoundManager::PlayMusic("MainMenuMusic");

	TextureManager::Load("assets/Images/titleScreen.jpg", "title");

	SDL_Rect source{ 0, 0, 1280 , 720 };
	SDL_FRect destination{ 0, 0, Game::GetInstance().kWidth, Game::GetInstance().kHeight };

	m_objects.emplace("title", new BackgroundSprite(source, destination, "title"));

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
	for (auto object : m_objects)
	{
		object.second->Render();
	}
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;

	SoundManager::PauseMusic();

	TextureManager::Unload("title");

	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}
	m_objects.clear();
}
// End TitleState

// Begin MenuState
void MenuState::Enter() // Used for initialization
{
	std::cout << "Entering MenuState..." << std::endl;

	SoundManager::ResumeMusic();

	TextureManager::Load("assets/Images/menuScreen.jpg", "menu");

	SDL_Rect source{ 0, 0, 1280 , 720 };
	SDL_FRect destination{ 0, 0, Game::GetInstance().kWidth, Game::GetInstance().kHeight };

	m_pMenuBackground = new BackgroundSprite(source, destination, "menu");
	//m_objects.emplace("menu", new BackgroundSprite(source, destination, "menu"));

	TextureManager::Load("assets/Images/Buttons/credit.png", "credit");
	
	int srcWidth = 399;
	int srcHeight = 82;
	int dstWidth = 250;
	int dstHeight = 50;
	float buttonX = Game::GetInstance().kWidth / 2.0f + dstWidth / 2.0f - 100.0f;
	float buttonY = Game::GetInstance().kHeight / 2.0f - dstHeight / 2.0f;
	
	SDL_Rect cSource{ 0, 0, srcWidth , srcHeight };
	SDL_FRect cDestination{ buttonX, buttonY, (float)dstWidth, (float)dstHeight };
	
	m_objects.emplace("credit", new CreditButton(cSource, cDestination, "credit"));

	TextureManager::Load("assets/Images/Buttons/play.png", "play");

	srcWidth = 400;
	srcHeight = 100;
	dstWidth = 250;
	dstHeight = 50;
	buttonX = Game::GetInstance().kWidth / 2.0f - dstWidth;
	buttonY = Game::GetInstance().kHeight / 2.0f - dstHeight / 2.0f;

	cSource = { 0, 0, srcWidth , srcHeight };
	cDestination = { buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("play", new PlayButton(cSource, cDestination, "play"));

	//TextureManager::Load("assets/Images/Buttons/play.png", "play");
	//
	//int buttonWidth = 400;
	//int buttonHeight = 100;
	//float buttonX = Game::GetInstance().kWidth / 2.0f - buttonWidth / 2.0f;
	//float buttonY = Game::GetInstance().kHeight / 2.0f - buttonHeight / 2.0f;
	//
	//SDL_Rect source{ 0, 0, buttonWidth , buttonHeight };
	//SDL_FRect destination{ buttonX, buttonY, (float)buttonWidth, (float)buttonHeight };
	//
	//m_objects.emplace("play", new PlayButton(source, destination, "play"));
}

void MenuState::Update(float deltaTime)
{
	for (auto object : m_objects)
	{
		object.second->Update(deltaTime);
		if (StateManager::IsStateChanging())
		{
			return;
		}
	}
}

void MenuState::Render()
{
	m_pMenuBackground->Render();
	for (auto object : m_objects)
	{
		object.second->Render();
	}
}

void MenuState::Exit()
{
	std::cout << "Exiting MenuState..." << std::endl;
	
	SoundManager::PauseMusic();

	TextureManager::Unload("menu");

	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}
	m_objects.clear();
}
// End MenuState

// Begin CreditState
void CreditState::Enter() // Used for initialization
{
	std::cout << "Entering CreditState..." << std::endl;
}

void CreditState::Update(float deltaTime)
{

}


void CreditState::Render()
{
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
	
	SoundManager::StopMusic();
	SoundManager::UnloadMusic("MainMenuMusic");

	TextureManager::Load("assets/Images/Tiles.png", "tiles");
	TextureManager::Load("assets/Images/Player.png", "player");

	SoundManager::LoadMusic("assets/Sound/Music/level.mp3", "levelMusic");
	SoundManager::PlayMusic("levelMusic");

	m_objects.emplace("level", new TiledLevel(24, 32, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Level1.txt", "tiles"));
	m_objects.emplace("player", new PlatformPlayer({0, 0, 128, 128}, {288, 480, 64, 64}));

}

void GameState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= 20.0f)
	{
		StateManager::ChangeState(new WinState());
	}
	else if (EventManager::KeyPressed(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState..." << std::endl;
		StateManager::PushState(new PauseState()); // Add new PauseState
		Mix_PauseMusic();
	}
	else
	{
		//m_pLevel->Update(deltaTime);
		for (auto const& object : m_objects)
		{
			object.second->Update(deltaTime);
		}

		for (unsigned int i = 0; i < static_cast<TiledLevel*> (m_objects["level"])->GetObstacles().size(); i++)
		{
			SDL_FRect* obstacleColliderTransfrom = static_cast<TiledLevel*>(m_objects["level"])->GetObstacles()[i]->GetDestinationTransform();

			float obstacleLeft = obstacleColliderTransfrom->x;
			float obstacleRight = obstacleColliderTransfrom->x + obstacleColliderTransfrom->w;

			float obstacleTop = obstacleColliderTransfrom->y;
			float obstacleBottom = obstacleColliderTransfrom->y + obstacleColliderTransfrom->h;

			SDL_FRect* playerColliderTransfrom = m_objects["player"]->GetDestinationTransform();

			float playerLeft = playerColliderTransfrom->x;
			float playerRight = playerColliderTransfrom->x + playerColliderTransfrom->w;

			float playerTop = playerColliderTransfrom->y;
			float playerBottom = playerColliderTransfrom->y + playerColliderTransfrom->h;

			bool xOverlap = playerLeft < obstacleRight&& playerRight > obstacleLeft;
			bool yOverlap = playerTop < obstacleBottom&& playerBottom > obstacleTop;

			float bottomCollision = obstacleBottom - playerColliderTransfrom->y;
			float topCollision = playerBottom - obstacleColliderTransfrom->y;
			float leftCollision = playerRight - obstacleColliderTransfrom->x;
			float rightCollision = obstacleRight - playerColliderTransfrom->x;

			if (xOverlap && yOverlap)
			{
				PlatformPlayer* pPlayer = static_cast<PlatformPlayer*>(m_objects["player"]);
				if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
				{
					pPlayer->StopY();
					pPlayer->SetY(playerColliderTransfrom->y - topCollision);
					pPlayer->SetGrounded(true);
				}
				if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
				{
					pPlayer->StopY();
					pPlayer->SetY(playerColliderTransfrom->y + bottomCollision);
				}
				if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
				{
					pPlayer->StopX();
					pPlayer->SetX(playerColliderTransfrom->x - leftCollision);
				}
				if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision)
				{
					pPlayer->StopX();
					pPlayer->SetX(playerColliderTransfrom->x + rightCollision);
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
	
	for (auto object : m_objects)
	{
		object.second->Render();
	}
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;

	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}

	m_objects.clear();

	TextureManager::Unload("tiles");
	TextureManager::Unload("player");

	SoundManager::StopMusic();
	SoundManager::UnloadMusic("levelMusic");

}

void GameState::Pause()
{
	std::cout << "Pausing GameState..." << std::endl;
	SoundManager::PauseMusic();
}

void GameState::Resume()
{
	std::cout << "Resuming GameState..." << std::endl;
	SoundManager::ResumeMusic();
}
// End GameState

// Begin PauseState
void PauseState::Enter()
{
	std::cout << "Entering PauseState..." << std::endl;
}

void PauseState::Update(float deltaTime)
{
	if (EventManager::KeyPressed(SDL_SCANCODE_ESCAPE))
	{
		StateManager::PopState();
		Mix_ResumeMusic();
	}
}

void PauseState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	// First render the GameSate
	StateManager::GetStates().front()->Render();
	// Now render rest of PauseState
	SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(pRenderer, 128, 128, 128, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(pRenderer, &rect);
	

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

}


void WinState::Render()
{
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

}

void LoseState::Render()
{
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState..." << std::endl;
}
// End LoseState