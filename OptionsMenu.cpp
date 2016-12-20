#include "OptionsMenu.h"

#define NothingPressed -1

OptionsMenu *OptionsMenu::Optionsmenu = NULL;
unsigned int OptionsMenu::m_kplmäärä = 5;

OptionsMenu::OptionsMenu()
{
	string name[ButtonCount_options] = { "Start", "Back", "Plus", "Miinus", "Plus","Miinus"};

	buttons[0].SetButton(name[0], 50, 50, 150, 50, SDLCore::loadTexture(SDLCore::GetRespath() + name[0] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[0] + "_down.png", SDLCore::GetRenderer()));
	buttons[1].SetButton(name[1], 50, 150, 150, 50, SDLCore::loadTexture(SDLCore::GetRespath() + name[1] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[1] + "_down.png", SDLCore::GetRenderer()));
	buttons[2].SetButton(name[2], 250, 50, 50, 50, SDLCore::loadTexture(SDLCore::GetRespath() + name[2] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[2] + "_down.png", SDLCore::GetRenderer()));
	buttons[3].SetButton(name[3], 250, 100, 50, 50, SDLCore::loadTexture(SDLCore::GetRespath() + name[3] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[3] + "_down.png", SDLCore::GetRenderer()));
	buttons[4].SetButton(name[4], 250, 200, 50, 50, SDLCore::loadTexture(SDLCore::GetRespath() + name[4] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[4] + "_down.png", SDLCore::GetRenderer()));
	buttons[5].SetButton(name[5], 250, 250, 50, 50, SDLCore::loadTexture(SDLCore::GetRespath() + name[5] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[5] + "_down.png", SDLCore::GetRenderer()));
																								//Placeholder tekstuuri
	OptionsMenu::m_OptionsMenuBackgroundTexture = SDLCore::loadTexture(SDLCore::GetRespath() + "mainmenu_background.png", SDLCore::GetRenderer());
	
	OptionsMenu::m_text = renderText("Kappaleiden lukumäärä: " + to_string(m_kplmäärä), "C:\\Windows\\Fonts\\Arial.ttf", color, 12, SDLCore::GetRenderer());
}

OptionsMenu::~OptionsMenu()
{
}

int OptionsMenu::CreateOptionsMenu()
{
	//Luodaan OptionsMenu
	if (!Optionsmenu)
	{
		OptionsMenu::Optionsmenu = new OptionsMenu();
	}
	//Luodaan OptionsMenun tausta
	renderTexture(Optionsmenu->m_OptionsMenuBackgroundTexture, SDLCore::GetRenderer(), 0, 0, 1920, 1080);
	//Luodaan OptionsMenun napit
	for (int i = 0; i < ButtonCount_options; i++)
	{
		renderTexture(Optionsmenu->buttons[i].GetTexture(), SDLCore::GetRenderer(), Optionsmenu->buttons[i].GetPosX(), Optionsmenu->buttons[i].GetPosY());
	}
	//Optionsmenun renderöinti
	SDL_RenderPresent(SDLCore::GetRenderer());
	return 0;
}

int OptionsMenu::ButtonPressed()
{
	if (OptionsMenu::m_ButtonIndex == NothingPressed)
	{
		return 0;
	}
	//Täällä napin painallus aiheuttaa jotain
	if (SDLCore::GetEvent()->button.x >= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetSizeY())
	{
		switch (Optionsmenu->m_ButtonIndex)
		{
		case 0:

			break;
		case 1:
			GameLoop::SetMenuIndex(0);
			MainMenu::CreateMainMenu();
			break;
		case 2:
			OptionsMenu::CreateOptionsMenu();
			SDL_DestroyTexture(m_text);
			m_kplmäärä++;
			OptionsMenu::m_text = renderText("Kappaleiden lukumäärä: " + to_string(m_kplmäärä), "C:\\Windows\\Fonts\\Arial.ttf", color, 24, SDLCore::GetRenderer());
			renderTexture(m_text, SDLCore::GetRenderer(), 300, 75);
			SDL_RenderPresent(SDLCore::GetRenderer());
			break;
		case 3:
			if (m_kplmäärä != 1)
			{
				OptionsMenu::CreateOptionsMenu();
				SDL_DestroyTexture(m_text);
				m_kplmäärä--;
				OptionsMenu::m_text = renderText("Kappaleiden lukumäärä: " + to_string(m_kplmäärä), "C:\\Windows\\Fonts\\Arial.ttf", color, 24, SDLCore::GetRenderer());
				renderTexture(m_text, SDLCore::GetRenderer(), 300, 75);
				SDL_RenderPresent(SDLCore::GetRenderer());
			}
			break;
		default:
			break;
		}
	}

	//Jos hiirennappi palautetaan painikkeiden ulkopuollella tekstuurit palautetaan
	if (!(SDLCore::GetEvent()->button.x >= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetSizeY()))
	{
		renderTexture(Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetTexture(), SDLCore::GetRenderer(), Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetPosX(), Optionsmenu->buttons[Optionsmenu->m_ButtonIndex].GetPosY());
		SDL_RenderPresent(SDLCore::GetRenderer());
	}

	return 0;
}

int OptionsMenu::ButtonPressedDown()
{
		for (int i = 0; i < ButtonCount_options; i++)
		{
			if (SDLCore::GetEvent()->button.x >= Optionsmenu->buttons[i].GetPosX() && SDLCore::GetEvent()->button.y >= Optionsmenu->buttons[i].GetPosY() && SDLCore::GetEvent()->button.x <= Optionsmenu->buttons[i].GetSizeX() && SDLCore::GetEvent()->button.y <= Optionsmenu->buttons[i].GetSizeY())
			{
				renderTexture(Optionsmenu->buttons[i].GetTextureDown(), SDLCore::GetRenderer(), Optionsmenu->buttons[i].GetPosX(), Optionsmenu->buttons[i].GetPosY());
				Optionsmenu->m_ButtonIndex = i;
				break;
			}
		}

		if (!(SDLCore::GetEvent()->button.x >= Optionsmenu->buttons[m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Optionsmenu->buttons[m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Optionsmenu->buttons[m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Optionsmenu->buttons[m_ButtonIndex].GetSizeY()))
		{
			Optionsmenu->m_ButtonIndex = NothingPressed;
			return 0;
		}

		SDL_RenderPresent(SDLCore::GetRenderer());
	return 0;
}
