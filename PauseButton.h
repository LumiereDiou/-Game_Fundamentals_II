#pragma once
#include "UI_Button.h"
class PauseButton :
    public UI_Button
{
public:
	PauseButton(SDL_Rect source, SDL_FRect destination, const char* textureKey);
private:
	virtual void Execute() override;
};

