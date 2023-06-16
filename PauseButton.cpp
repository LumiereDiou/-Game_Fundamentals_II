#include "PauseButton.h"
#include "StateManager.h"
#include "States.h"

PauseButton::PauseButton(SDL_Rect source, SDL_FRect destination, const char* textureKey)
	: UI_Button(source, destination, textureKey)
{

}

void PauseButton::Execute()
{
	StateManager::PushState(new PauseState());
}