#pragma once

#include "MenuButtons.h"
#include "GameLoop.h"
#include "MainMenu.h"
#define ButtonCount_options 6

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

class OptionsMenu
{
public:
	OptionsMenu();
	~OptionsMenu();
	int ButtonPressed();
	int ButtonPressedDown();
	static int CreateOptionsMenu();
	static OptionsMenu *Optionsmenu;
	static unsigned int GetKpl() { return m_kplm‰‰r‰; };
private:
	int m_ButtonIndex = 0;
	MenuButtons buttons[ButtonCount_options];
	SDL_Texture *m_OptionsMenuBackgroundTexture;
	SDL_Texture *m_text;
	SDL_Color color = { 255, 255, 255, 0 };
	static unsigned int m_kplm‰‰r‰;
};

