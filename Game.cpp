#include <iostream>
#include "Game.h"

Game::Game()
	: m_running(false)
	, m_pWindow(nullptr)
	, m_pRenderer(nullptr)
	, m_RectangleTransform{ kWidth / 2, kHeight / 2, 100, 100 }
	, m_keyStates(nullptr)
{

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
	std::cout << "Initialization successful!!!" << std::endl;
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
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}
	}
}

bool Game::KeyDown(SDL_Scancode key)
{
	if (m_keyStates)
	{
		return m_keyStates[key] == 1;
	}
	return false;
}

void Game::Update(float deltaTime)
{
	if (KeyDown(SDL_SCANCODE_W))
		m_RectangleTransform.y -= kRectangeSpeed * deltaTime;
	if (KeyDown(SDL_SCANCODE_S))
		m_RectangleTransform.y += kRectangeSpeed * deltaTime;
	if (KeyDown(SDL_SCANCODE_A))
		m_RectangleTransform.x -= kRectangeSpeed * deltaTime;
	if (KeyDown(SDL_SCANCODE_D))
		m_RectangleTransform.x += kRectangeSpeed * deltaTime;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 128, 255, 255);
	SDL_RenderClear(m_pRenderer);
	// Any drawing here...

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderFillRectF(m_pRenderer, &m_RectangleTransform);

	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
}

void Game::Clean()
{
	std::cout << "Cleaning engine..." << std::endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}
