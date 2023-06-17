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
#include "MenuButton.h"
#include "PauseButton.h"
#include "ResumeButton.h"
#include "ExitButton.h"
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
	if (!Mix_PlayingMusic())
	{
		SoundManager::LoadMusic("assets/Sound/Music/Menu.mp3", "MainMenuMusic");
		SoundManager::PlayMusic("MainMenuMusic");
	}

	SoundManager::ResumeMusic();

	TextureManager::Load("assets/Images/menuScreen.jpg", "menu");

	SDL_Rect source{ 0, 0, 1280 , 720 };
	SDL_FRect destination{ 0, 0, Game::GetInstance().kWidth, Game::GetInstance().kHeight };

	m_pBackground = new BackgroundSprite(source, destination, "menu");

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
	m_pBackground->Render();
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
	TextureManager::Unload("credit");
	TextureManager::Unload("play");

	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}

	delete m_pBackground;
	m_pBackground = nullptr;
	m_objects.clear();
}
// End MenuState

// Begin CreditState
void CreditState::Enter() // Used for initialization
{
	std::cout << "Entering CreditState..." << std::endl;
	
	SoundManager::ResumeMusic();

	TextureManager::Load("assets/Images/creditScreen.png", "credit");

	SDL_Rect source{ 0, 0, 1306 , 737 };
	SDL_FRect destination{ 0, 0, Game::GetInstance().kWidth, Game::GetInstance().kHeight };

	m_pBackground = new BackgroundSprite(source, destination, "credit");

	TextureManager::Load("assets/Images/Buttons/menu.png", "menu");

	int srcWidth = 399;
	int srcHeight = 82;
	int dstWidth = 250;
	int dstHeight = 50;
	float buttonX = Game::GetInstance().kWidth / 2.0f - dstWidth / 2.0f;
	float buttonY = Game::GetInstance().kHeight / 2.0f + dstHeight / 2.0f;

	SDL_Rect cSource{ 0, 0, srcWidth , srcHeight };
	SDL_FRect cDestination{ buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("menu", new MenuButton(cSource, cDestination, "menu"));
}

void CreditState::Update(float deltaTime)
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

void CreditState::Render()
{
	m_pBackground->Render();
	for (auto object : m_objects)
	{
		object.second->Render();
	}
}

void CreditState::Exit()
{
	std::cout << "Exiting CreditState..." << std::endl;
	
	SoundManager::PauseMusic();

	TextureManager::Unload("menu");
	TextureManager::Unload("credit");

	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}

	delete m_pBackground;
	m_pBackground = nullptr;
	m_objects.clear();
}
// End CreditState

// Begin GameState
void GameState::Enter() // Used for initialization
{
	std::cout << "Entering GameState..." << std::endl;
	
	SoundManager::StopMusic();
	SoundManager::UnloadMusic("MainMenuMusic");
	SoundManager::LoadMusic("assets/Sound/Music/level.mp3", "levelMusic");
	SoundManager::PlayMusic("levelMusic");

	TextureManager::Load("assets/Images/Tiles.png", "tiles");
	TextureManager::Load("assets/Images/Player.png", "player");
	TextureManager::Load("assets/Images/Buttons/pause.png", "pause");

	int srcWidth = 400;
	int srcHeight = 85;
	int dstWidth = 250;
	int dstHeight = 50;
	float buttonX = Game::GetInstance().kWidth - dstWidth;
	float buttonY = 10;
	SDL_Rect cSource{ 0, 0, srcWidth , srcHeight };
	SDL_FRect cDestination{ buttonX, buttonY, (float)dstWidth, (float)dstHeight };
	
	m_objects.emplace("level", new TiledLevel(24, 32, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Level1.txt", "tiles"));
	m_objects.emplace("player", new PlatformPlayer({0, 0, 128, 128}, {288, 480, 64, 64}));
	m_objects.emplace("pause", new PauseButton(cSource, cDestination, "pause"));

}

void GameState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= 20.0f)
	{
		StateManager::ChangeState(new WinState());
	}
	else
	{
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

		for (unsigned int i = 0; i < static_cast<TiledLevel*> (m_objects["level"])->GetHazards().size(); i++)
		{
			SDL_FRect* obstacleColliderTransfrom = static_cast<TiledLevel*>(m_objects["level"])->GetHazards()[i]->GetDestinationTransform();

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
					pPlayer->Dead();
					break;

				}
				if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
				{
					pPlayer->Dead();
					break;
				}
				if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
				{
					pPlayer->Dead();
					break;
				}
				if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision)
				{
					pPlayer->Dead();
					break;
				}
			}
		}
		PlatformPlayer* pPlayer = static_cast<PlatformPlayer*>(m_objects["player"]);
		if (pPlayer->IsDead())
		{
			if (timer >= 4.0f)
			{
				StateManager::ChangeState(new LoseState());
			}
			
		}

	}
	
}

void GameState::Render()
{
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
	TextureManager::Unload("pause");

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

	TextureManager::Load("assets/Images/Buttons/resume.png", "resume");

	int srcWidth = 200;
	int srcHeight = 80;
	int dstWidth = 250;
	int dstHeight = 50;
	float buttonX = Game::GetInstance().kWidth / 2.0f + dstWidth / 2.0f - 100.0f;
	float buttonY = Game::GetInstance().kHeight / 2.0f - dstHeight / 2.0f;

	SDL_Rect cSource{ 0, 0, srcWidth , srcHeight };
	SDL_FRect cDestination{ buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("resume", new ResumeButton(cSource, cDestination, "resume"));

	TextureManager::Load("assets/Images/Buttons/exit.png", "exit");

	srcWidth = 400;
	srcHeight = 100;
	dstWidth = 250;
	dstHeight = 50;
	buttonX = Game::GetInstance().kWidth / 2.0f - dstWidth;
	buttonY = Game::GetInstance().kHeight / 2.0f - dstHeight / 2.0f;

	cSource = { 0, 0, srcWidth , srcHeight };
	cDestination = { buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("exit", new ExitButton(cSource, cDestination, "exit"));
}

void PauseState::Update(float deltaTime)
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

void PauseState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	// First render the GameSate
	StateManager::GetStates().front()->Render();
	// Now render rest of PauseState
	SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
	//SDL_SetRenderDrawColor(pRenderer, 128, 128, 128, 128);
	//SDL_Rect rect = { 256, 128, 512, 512 };
	//SDL_RenderFillRect(pRenderer, &rect);
	for (auto object : m_objects)
	{
		object.second->Render();
	}

}

void PauseState::Exit()
{
	std::cout << "Exiting PauseState..." << std::endl;
	
	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}

	m_objects.clear();

	TextureManager::Unload("exit");
	TextureManager::Unload("resume");

}
// End PauseState

// Begin WinState
void WinState::Enter() // Used for initialization
{
	std::cout << "Entering WinState..." << std::endl;

	SoundManager::LoadMusic("assets/Sound/Music/winOrLose.mp3", "winOrLose");
	SoundManager::PlayMusic("winOrLose");

	TextureManager::Load("assets/Images/winScreen.png", "win");

	SDL_Rect source{ 0, 0, 1275 , 722 };
	SDL_FRect destination{ 0, 0, Game::GetInstance().kWidth, Game::GetInstance().kHeight };

	m_pBackground = new BackgroundSprite(source, destination, "win");

	TextureManager::Load("assets/Images/Buttons/menu.png", "menu");

	int srcWidth = 399;
	int srcHeight = 82;
	int dstWidth = 250;
	int dstHeight = 50;
	float buttonX = Game::GetInstance().kWidth / 2.0f + dstWidth / 2.0f - 100.0f;
	float buttonY = Game::GetInstance().kHeight / 2.0f + dstHeight / 2.0f;

	SDL_Rect cSource{ 0, 0, srcWidth , srcHeight };
	SDL_FRect cDestination{ buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("menu", new MenuButton(cSource, cDestination, "menu"));

	TextureManager::Load("assets/Images/Buttons/exit.png", "exit");

	srcWidth = 400;
	srcHeight = 100;
	dstWidth = 250;
	dstHeight = 50;
	buttonX = Game::GetInstance().kWidth / 2.0f - dstWidth;
	buttonY = Game::GetInstance().kHeight / 2.0f + dstHeight / 2.0f;

	cSource = { 0, 0, srcWidth , srcHeight };
	cDestination = { buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("exit", new ExitButton(cSource, cDestination, "exit"));
}

void WinState::Update(float deltaTime)
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


void WinState::Render()
{
	m_pBackground->Render();
	for (auto object : m_objects)
	{
		object.second->Render();
	}
}

void WinState::Exit()
{
	std::cout << "Exiting WinState..." << std::endl;
	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}

	m_objects.clear();
	delete m_pBackground;
	m_pBackground = nullptr;
	TextureManager::Unload("exit");
	TextureManager::Unload("menu");
	SoundManager::StopMusic();
	SoundManager::UnloadMusic("winOrLose");

}
// End WinState

// Begin LoseState
void LoseState::Enter() // Used for initialization
{
	std::cout << "Entering LoseState..." << std::endl;

	SoundManager::LoadMusic("assets/Sound/Music/winOrLose.mp3", "winOrLose");
	SoundManager::PlayMusic("winOrLose");

	TextureManager::Load("assets/Images/loseScreen.png", "lose");

	SDL_Rect source{ 0, 0, 1277 , 718 };
	SDL_FRect destination{ 0, 0, Game::GetInstance().kWidth, Game::GetInstance().kHeight };

	m_pBackground = new BackgroundSprite(source, destination, "lose");

	TextureManager::Load("assets/Images/Buttons/menu.png", "menu");

	int srcWidth = 399;
	int srcHeight = 82;
	int dstWidth = 250;
	int dstHeight = 50;
	float buttonX = Game::GetInstance().kWidth / 2.0f + dstWidth / 2.0f - 100.0f;
	float buttonY = Game::GetInstance().kHeight / 2.0f + dstHeight / 2.0f;

	SDL_Rect cSource{ 0, 0, srcWidth , srcHeight };
	SDL_FRect cDestination{ buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("menu", new MenuButton(cSource, cDestination, "menu"));

	TextureManager::Load("assets/Images/Buttons/exit.png", "exit");

	srcWidth = 400;
	srcHeight = 100;
	dstWidth = 250;
	dstHeight = 50;
	buttonX = Game::GetInstance().kWidth / 2.0f - dstWidth;
	buttonY = Game::GetInstance().kHeight / 2.0f + dstHeight / 2.0f;

	cSource = { 0, 0, srcWidth , srcHeight };
	cDestination = { buttonX, buttonY, (float)dstWidth, (float)dstHeight };

	m_objects.emplace("exit", new ExitButton(cSource, cDestination, "exit"));
}

void LoseState::Update(float deltaTime)
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

void LoseState::Render()
{
	m_pBackground->Render();
	for (auto object : m_objects)
	{
		object.second->Render();
	}
}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState..." << std::endl;
	for (auto object : m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}

	m_objects.clear();
	delete m_pBackground;
	m_pBackground = nullptr;
	TextureManager::Unload("exit");
	TextureManager::Unload("menu");

	SoundManager::StopMusic();
	SoundManager::UnloadMusic("winOrLose");
}
// End LoseState