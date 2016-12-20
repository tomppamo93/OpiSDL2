#include "OptionsMenu.h"

OptionsMenu *OptionsMenu::Optionsmenu = NULL;

OptionsMenu::OptionsMenu()
{
	for (int i = 0; i < ButtonCount_options; i++)
	{
		int posx = 50;
		int posy = (i * 150 + 50);
		string name[ButtonCount_options] = { "Start", "Back"};

		buttons[i].SetButton(name[i], posx, posy, (posx + 150), (posy + 50), SDLCore::loadTexture(SDLCore::GetRespath() + name[i] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[i] + "_down.png", SDLCore::GetRenderer()));
	}
	OptionsMenu::m_OptionsMenuBackgroundTexture = SDLCore::loadTexture(SDLCore::GetRespath() + "mainmenu_background.png", SDLCore::GetRenderer());
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
	renderTexture(Optionsmenu->m_OptionsMenuBackgroundTexture, SDLCore::GetRenderer(), 0, 0);
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
	SDL_RenderPresent(SDLCore::GetRenderer());
	return 0;
}
