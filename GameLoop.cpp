#include "GameLoop.h"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "CreditsMenu.h"

#define MainMenuIndex 0
#define OptionsMenuIndex 1
#define CreditsMenuIndex 2

bool GameLoop::quit = false;
int GameLoop::MenuIndex = 0;


GameLoop::GameLoop()
{
	if (SDLCore::SDLCoreInit() != 0)
	{
		quit = true;
	}

	StartGame();
}


GameLoop::~GameLoop()
{

}

int GameLoop::StartGame()
{
	
	
	if (MainMenu::CreateMainMenu() != 0)
	{
		quit = true;
	}
	

	while (!quit)
	{
		SDL_Delay(20);
		while (SDL_PollEvent(SDLCore::GetEvent()))
		{
			if (SDLCore::GetEvent()->type == SDL_KEYUP)
			{
				//Kun käyttäjä painaa pakene nappia niin ikkuna menee kiinni
				if (SDLCore::GetEvent()->key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
			}
			//If user closes the window
			if (SDLCore::GetEvent()->type == SDL_QUIT)
			{
				quit = true;
			}

			//Onko hiiren vasentanappia painettu?
			if (SDLCore::GetEvent()->button.button == SDL_BUTTON_LEFT)
			{
				//Kumpi napin painalluksen tyyppi
				switch (SDLCore::GetEvent()->button.type)
				{

				case SDL_MOUSEBUTTONUP:

					//Missä menussa painettu?
					switch (MenuIndex)
					{
					case MainMenuIndex:
						MainMenu::Mainmenu->ButtonPressed();
						break;
					case OptionsMenuIndex:
						OptionsMenu::Optionsmenu->ButtonPressed();
						break;
					case CreditsMenuIndex:
						CreditsMenu::Creditsmenu->ButtonPressed();
						break;
					default:
						break;
					}					
					break;

				case SDL_MOUSEBUTTONDOWN:

					//Missä menussa painettu?
					switch (MenuIndex)
					{
					case MainMenuIndex:
						MainMenu::Mainmenu->ButtonPressedDown();
						break;
					case OptionsMenuIndex:
						OptionsMenu::Optionsmenu->ButtonPressedDown();
						break;
					case CreditsMenuIndex:
						CreditsMenu::Creditsmenu->ButtonPressedDown();
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}

			}

		}


		
	}

	if (MainMenu::Mainmenu)
	{
		delete MainMenu::Mainmenu;
		MainMenu::Mainmenu = NULL;
	}

	if (OptionsMenu::Optionsmenu)
	{
		delete OptionsMenu::Optionsmenu;
		OptionsMenu::Optionsmenu = NULL;
	}

	if (CreditsMenu::Creditsmenu)
	{
		delete CreditsMenu::Creditsmenu;
		CreditsMenu::Creditsmenu = NULL;
	}
	
	return 0;
}