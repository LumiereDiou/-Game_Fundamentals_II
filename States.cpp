#include "States.h"
#include "Game.h"
#include "StateManager.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "AnimatedSprite.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "TiledLevel.h"
#include <iostream>


//Begin TitleState
void TitleState::Enter()
{
	std::cout << "Entering TitleState..." << std::endl;
	m_pDeveloperTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/profile.jpg");
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
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	SDL_Rect srcRect{ 0, 0, 826, 842 };
	SDL_Rect dstRect{ (1024/2) - 200,(768/2) - 200,400, 400};
	SDL_RenderCopy(pRenderer, m_pDeveloperTexture, &srcRect, &dstRect);
}

void TitleState::Exit()
{
	std::cout << "Exiting TitleState..." << std::endl;
	SDL_DestroyTexture(m_pDeveloperTexture);
}
// End TitleState

// Begin MenuState
void MenuState::Enter() // Used for initialization
{
	std::cout << "Entering MenuState..." << std::endl;
	m_pBackGroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/background.bmp");
	m_pGameNameTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/gamename.jpg");
	m_pKeyInputTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/kInput.png");

	m_pMusic = Mix_LoadMUS("assets/MainMenu.mp3");

	Mix_PlayMusic(m_pMusic, -1);
}

void MenuState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (EventManager::KeyPressed(SDL_SCANCODE_C))
	{
		std::cout << "Changing to CreditState..." << std::endl;
		StateManager::ChangeState(new CreditState());
		
	}
	else if (EventManager::KeyPressed(SDL_SCANCODE_G))
	{
		std::cout << "Changing to GameState..." << std::endl;
		StateManager::ChangeState(new GameState());
	}
}


void MenuState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	//std::cout << "Rendering MenuState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 0, 128, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());


	SDL_Rect srcRect{ 0, 0, 998, 562 };
	SDL_Rect dstRect{ 0, 0, 1024, 768 };
	SDL_RenderCopy(pRenderer, m_pBackGroundTexture, &srcRect, &dstRect);

	srcRect = { 0, 0, 284, 177 };
	dstRect = { (1024 / 2) - 200,(768 / 2) - 200,200, 200 };
	SDL_RenderCopy(pRenderer, m_pGameNameTexture, &srcRect, &dstRect);


	srcRect = { 0, 0, 1316, 1316 };
	dstRect = { 1024/2,368,400, 400 };
	SDL_RenderCopy(pRenderer, m_pKeyInputTexture, &srcRect, &dstRect);
}

void MenuState::Exit()
{
	std::cout << "Exiting MenuState..." << std::endl;
	SDL_DestroyTexture(m_pBackGroundTexture);
	SDL_DestroyTexture(m_pGameNameTexture);
	SDL_DestroyTexture(m_pKeyInputTexture);
	Mix_FreeMusic(m_pMusic);
	m_pMusic = nullptr;
}
// End MenuState

// Begin CreditState
void CreditState::Enter() // Used for initialization
{
	std::cout << "Entering CreditState..." << std::endl;
	m_pTitleTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/title.jpg");
	m_pNameTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/myName.png");
	m_pKeyInputTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/kInput1.png");

	m_pMusic = Mix_LoadMUS("assets/MainMenu.mp3");

	Mix_PlayMusic(m_pMusic, -1);
}

void CreditState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (EventManager::KeyPressed(SDL_SCANCODE_ESCAPE))
	{
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}


void CreditState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	//std::cout << "Rendering CreditState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 225, 192, 203, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	SDL_Rect srcRect{ 0, 0, 255, 255 };
	SDL_Rect dstRect{ (1024 / 2) - 100,(768 / 2) - 300,400, 400 };
	SDL_RenderCopy(pRenderer, m_pTitleTexture, &srcRect, &dstRect);

	srcRect = { 0, 0, 2000, 2000 };
	dstRect = { 0, 0, 400, 400 };
	SDL_RenderCopy(pRenderer, m_pNameTexture, &srcRect, &dstRect);


	srcRect = { 0, 0, 2000, 2000 };
	dstRect = { (1024 / 2) - 400,(768 / 2) - 200,400, 400 };
	SDL_RenderCopy(pRenderer, m_pKeyInputTexture, &srcRect, &dstRect);
}

void CreditState::Exit()
{
	std::cout << "Exiting CreditState..." << std::endl;
	SDL_DestroyTexture(m_pTitleTexture);
	SDL_DestroyTexture(m_pNameTexture);
	SDL_DestroyTexture(m_pKeyInputTexture);
	Mix_FreeMusic(m_pMusic);
	m_pMusic = nullptr;
}
// End CreditState

// Begin GameState
void GameState::Enter() // Used for initialization
{
	std::cout << "Entering GameState..." << std::endl;
	
	TextureManager::Load("assets/Images/Tiles.png", "tiles");

	m_pLevel = new TiledLevel(24, 32, 32, 32, "assets/Data/Tiledata.txt", "assets/Data/Level1.txt", "tiles");

	m_pMusic = Mix_LoadMUS("assets/music.wav");
	m_pSoundEffect = Mix_LoadWAV("assets/jump.wav");

	Mix_PlayMusic(m_pMusic, -1);

}

void GameState::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= 20.0f)
	{
		StateManager::ChangeState(new WinState());
	}

	Game& GameInstance = Game::GetInstance();

	if (EventManager::KeyPressed(SDL_SCANCODE_P))
	{
		std::cout << "Changing to PauseState..." << std::endl;
		StateManager::PushState(new PauseState()); // Add new PauseState
		Mix_PauseMusic();
	}
	else
	{
		m_pLevel->Update(deltaTime);
	}
	
}

void GameState::Render()
{
	//std::cout << "Rendering GameState..." << std::endl;
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255); //blue
	SDL_RenderClear(pRenderer);
	
	m_pLevel->Render();
}

void GameState::Exit()
{
	std::cout << "Exiting GameState..." << std::endl;

	delete m_pLevel;
	m_pLevel = nullptr;

	TextureManager::Unload("tiles");

	Mix_FreeMusic(m_pMusic);
	m_pMusic = nullptr;

	Mix_FreeChunk(m_pSoundEffect);
	m_pSoundEffect = nullptr;

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
	m_pBackGroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/background.bmp");
	m_pTitleTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/title.jpg");
	m_pKeyInputTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/kInput1.png");
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
	
	SDL_Rect srcRect{ 0, 0, 998, 562 };
	SDL_Rect dstRect{ 0, 0, 1024, 768 };
	
	srcRect = { 0, 0, 2000, 2000 };
	dstRect = { 0, 0, 400, 400 };
	SDL_RenderCopy(pRenderer, m_pKeyInputTexture, &srcRect, &dstRect);

}

void PauseState::Exit()
{
	std::cout << "Exiting PauseState..." << std::endl;
	SDL_DestroyTexture(m_pBackGroundTexture);
	SDL_DestroyTexture(m_pTitleTexture);
	SDL_DestroyTexture(m_pKeyInputTexture);
}
// End PauseState

// Begin WinState
void WinState::Enter() // Used for initialization
{
	std::cout << "Entering WinState..." << std::endl;
	m_pBackGroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/background.bmp");
	m_pTitleTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/title.jpg");
	m_pKeyInputTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/kInput3.png");
}

void WinState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (EventManager::KeyPressed(SDL_SCANCODE_SPACE))
	{
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}


void WinState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	//std::cout << "Rendering WinState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 225, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	SDL_Rect srcRect{ 0, 0, 998, 562 };
	SDL_Rect dstRect{ 0, 0, 1024, 768 };
	SDL_RenderCopy(pRenderer, m_pBackGroundTexture, &srcRect, &dstRect);

	srcRect = { 0, 0, 255, 255 };
	dstRect = { (1024 / 2) - 200,(768 / 2) - 200,400, 400 };
	SDL_RenderCopy(pRenderer, m_pTitleTexture, &srcRect, &dstRect);

	srcRect = { 0, 0, 2000, 2000 };
	dstRect = { 0, 0, 400, 400 };
	SDL_RenderCopy(pRenderer, m_pKeyInputTexture, &srcRect, &dstRect);
}

void WinState::Exit()
{
	std::cout << "Exiting WinState..." << std::endl;
	SDL_DestroyTexture(m_pBackGroundTexture);
	SDL_DestroyTexture(m_pTitleTexture);
	SDL_DestroyTexture(m_pKeyInputTexture);
}
// End WinState

// Begin LoseState
void LoseState::Enter() // Used for initialization
{
	std::cout << "Entering LoseState..." << std::endl;
	m_pBackGroundTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/background.bmp");
	m_pTitleTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/title.jpg");
	m_pKeyInputTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), "assets/kInput3.png");
}

void LoseState::Update(float deltaTime)
{
	Game& GameInstance = Game::GetInstance();

	if (EventManager::KeyPressed(SDL_SCANCODE_SPACE))
	{
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}

void LoseState::Render()
{
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();
	//std::cout << "Rendering LoseState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 225, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());

	SDL_Rect srcRect{ 0, 0, 998, 562 };
	SDL_Rect dstRect{ 0, 0, 1024, 768 };
	SDL_RenderCopy(pRenderer, m_pBackGroundTexture, &srcRect, &dstRect);

	srcRect = { 0, 0, 255, 255 };
	dstRect = { (1024 / 2) - 200,(768 / 2) - 200,400, 400 };
	SDL_RenderCopy(pRenderer, m_pTitleTexture, &srcRect, &dstRect);

	srcRect = { 0, 0, 2000, 2000 };
	dstRect = {0, 0, 400, 400 };
	SDL_RenderCopy(pRenderer, m_pKeyInputTexture, &srcRect, &dstRect);
}

void LoseState::Exit()
{
	std::cout << "Exiting LoseState..." << std::endl;
	SDL_DestroyTexture(m_pBackGroundTexture);
	SDL_DestroyTexture(m_pTitleTexture);
	SDL_DestroyTexture(m_pKeyInputTexture);
}
// End LoseState