#include "CreditButton.h"
#include "StateManager.h"
#include "States.h"

CreditButton::CreditButton(SDL_Rect source, SDL_FRect destination, const char* textureKey)
	: UI_Button(source, destination, textureKey)
{

}

void CreditButton::Execute()
{
	StateManager::ChangeState(new CreditState());
}