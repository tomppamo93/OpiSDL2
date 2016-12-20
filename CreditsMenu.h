#pragma once
#include "MenuButtons.h"
#include "SDLCore.h"
#include "GameLoop.h"
#include "MainMenu.h"

#define ButtonCount_credits 2

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

class CreditsMenu
{
public:
	CreditsMenu();
	~CreditsMenu();
	int ButtonPressed();
	int ButtonPressedDown();
	static int CreateCreditsMenu();
	static CreditsMenu *Creditsmenu;
private:
	int m_ButtonIndex = 0;
	MenuButtons buttons[ButtonCount_credits];
	SDL_Texture *m_CreditsMenuBackgroundTexture;
};

