#include "CreditsMenu.h"

#define BackButton 1

CreditsMenu *CreditsMenu::Creditsmenu = NULL;

CreditsMenu::CreditsMenu()
{
	for (int i = 0; i < ButtonCount_credits; i++)
	{
		int posx = 50;
		int posy = (i * 150 + 50);
		string name[ButtonCount_credits] = { "Start", "Back"};

		buttons[i].SetButton(name[i], posx, posy, (posx + 150), (posy + 50), SDLCore::loadTexture(SDLCore::GetRespath() + name[i] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[i] + "_down.png", SDLCore::GetRenderer()));
	}
	CreditsMenu::m_CreditsMenuBackgroundTexture = SDLCore::loadTexture(SDLCore::GetRespath() + "mainmenu_background.png", SDLCore::GetRenderer());
}


CreditsMenu::~CreditsMenu()
{
}

int CreditsMenu::CreateCreditsMenu()
{
	//Luodaan CreditsMenu
	if (!Creditsmenu)
	{
		CreditsMenu::Creditsmenu = new CreditsMenu();
	}
	//Luodaan CreditsMenun tausta
	renderTexture(Creditsmenu->m_CreditsMenuBackgroundTexture, SDLCore::GetRenderer(), 0, 0);
	//Luodaan CreditsMenun napit
	for (int i = 0; i < ButtonCount_credits; i++)
	{
		renderTexture(Creditsmenu->buttons[i].GetTexture(), SDLCore::GetRenderer(), Creditsmenu->buttons[i].GetPosX(), Creditsmenu->buttons[i].GetPosY());
	}
	//Creditsmenun renderöinti
	SDL_RenderPresent(SDLCore::GetRenderer());
	return 0;
}

int CreditsMenu::ButtonPressed()
{
	//Täällä napin painallus aiheuttaa jotain
	if (SDLCore::GetEvent()->button.x >= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetSizeY())
	{
		switch (Creditsmenu->m_ButtonIndex)
		{
		case 0:

			break;
		case BackButton:
			//Back nappi
			GameLoop::SetMenuIndex(0);
			MainMenu::CreateMainMenu();
			break;
		default:
			break;
		}
	}

	//Jos hiirennappi palautetaan painikkeiden ulkopuollella tekstuurit palautetaan
	if (!(SDLCore::GetEvent()->button.x >= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetSizeY()))
	{
		renderTexture(Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetTexture(), SDLCore::GetRenderer(), Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetPosX(), Creditsmenu->buttons[Creditsmenu->m_ButtonIndex].GetPosY());
		SDL_RenderPresent(SDLCore::GetRenderer());
	}

	return 0;
}

int CreditsMenu::ButtonPressedDown()
{
	for (int i = 0; i < ButtonCount_credits; i++)
	{
		if (SDLCore::GetEvent()->button.x >= Creditsmenu->buttons[i].GetPosX() && SDLCore::GetEvent()->button.y >= Creditsmenu->buttons[i].GetPosY() && SDLCore::GetEvent()->button.x <= Creditsmenu->buttons[i].GetSizeX() && SDLCore::GetEvent()->button.y <= Creditsmenu->buttons[i].GetSizeY())
		{
			renderTexture(Creditsmenu->buttons[i].GetTextureDown(), SDLCore::GetRenderer(), Creditsmenu->buttons[i].GetPosX(), Creditsmenu->buttons[i].GetPosY());
			Creditsmenu->m_ButtonIndex = i;
			break;
		}
	}
	SDL_RenderPresent(SDLCore::GetRenderer());

	return 0;
}
