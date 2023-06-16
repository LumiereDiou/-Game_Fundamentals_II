#include "MenuButton.h"
#include "StateManager.h"
#include "States.h"

MenuButton::MenuButton(SDL_Rect source, SDL_FRect destination, const char* textureKey)
	: UI_Button(source, destination, textureKey)
{

}

void MenuButton::Execute()
{
	StateManager::ChangeState(new MenuState());
}