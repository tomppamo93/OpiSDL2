#pragma once

#include "MenuButtons.h"
#include "GameLoop.h"
#include "OptionsMenu.h"
#include "CreditsMenu.h"
#include "Gravitaatio.h"

#define ButtonCount_main 4

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	int ButtonPressed();
	int ButtonPressedDown();
	static int CreateMainMenu();
	static MainMenu *Mainmenu;
private:
	int m_ButtonIndex = 0;
	MenuButtons buttons[ButtonCount_main];
	SDL_Texture *m_MainMenuBackgroundTexture;
	Gravitaatio *kappale;
	bool threadluotu = false;
};

