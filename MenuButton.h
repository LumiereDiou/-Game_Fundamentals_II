#pragma once
#include "UI_Button.h"
class MenuButton :
    public UI_Button
{
public:
	MenuButton(SDL_Rect source, SDL_FRect destination, const char* textureKey);
private:
	virtual void Execute() override;
};

