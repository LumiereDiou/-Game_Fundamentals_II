#include <iostream>
#include "Game.h"
#include "StateManager.h"
#include "States.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "SoundManager.h"


Game::Game()
	: m_running(false)
	, m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, m_keyStates(nullptr)
{

}

Game& Game::GetInstance()
{
	static Game* pInstance = new Game();
	return *pInstance;
}

int Game::Init(const char* title, int xPos, int yPos)
{
	std::cout << "Initializing engine..." << std::endl;
	//Call to SDL_Init(). Initialize SDL and video subsystem
	int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
	if (errorCode == 0)
	{
		std::cout << "SDL_Init() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_Init() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		system("pause");
		return errorCode;
	}

	//Attempt to create a maximized window that can be restored to a kWidthxkHeight, centered window.
	m_pWindow = SDL_CreateWindow("GAME 1017",            //title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  //x, y
		kWidth, kHeight,								 //w, h
		0);												 // flags
	if (m_pWindow != nullptr)
	{
		std::cout << "SDL_CreateWindow() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//Attempts to create a hardware-accelerated renderer for our window.
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer != nullptr)
	{
		std::cout << "SDL_CreateRenderer() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateRenderer() failed. Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		std::cout << "Mix_OpenAudio() succeeded." << std::endl;
	}
	else
	{
		std::cout << "Mix_OpenAudio() failed. Error: " << SDL_GetError() << std::endl;
	}
	
	if (SoundManager::Init())
	{
		std::cout << "SoundManager::Init() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SoundManager::Init() failed. Error: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		return -1;
	}

	std::cout << "Initialization successful!!!" << std::endl;
	
	EventManager::Init();

	StateManager::PushState(new TitleState());
	
	m_keyStates = SDL_GetKeyboardState(nullptr);
	
	m_running = true;
	return 0;
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::HandleEvents()
{
	EventManager::HandleEvents();
}

void Game::Update(float deltaTime)
{
	StateManager::Update(deltaTime);
}

void Game::Render()
{
	StateManager::Render();
	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
}

void Game::Quit()
{
	m_running = false;
}

void Game::Clean()
{
	std::cout << "Cleaning engine..." << std::endl;
	StateManager::Quit();
	TextureManager::Quit();
	EventManager::Quit();
	SoundManager::Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();

	delete this;
}
