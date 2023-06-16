#pragma once
#include "UI_Button.h"
class CreditButton : public UI_Button
{
public:
	CreditButton(SDL_Rect source, SDL_FRect destination, const char* textureKey);
private:
	virtual void Execute() override;
};

