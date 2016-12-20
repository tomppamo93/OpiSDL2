#include "MainMenu.h"

#define NothingPressed -1
#define StartButton 0
#define OptionsButton 1
#define CreditsButton 2
#define QuitButton 3

MainMenu *MainMenu::Mainmenu = NULL;

MainMenu::MainMenu()
{
	for (int i = 0; i < ButtonCount_main; i++)
	{
		int posx = 50;
		int posy = (i * 150 + 50);
		string name[ButtonCount_main] = {"Start", "Options", "Credits", "Quit"};

		buttons[i].SetButton(name[i], posx, posy, (150), (50), SDLCore::loadTexture(SDLCore::GetRespath() + name[i] + ".png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + name[i] + "_down.png", SDLCore::GetRenderer()));
	}
	MainMenu::m_MainMenuBackgroundTexture = SDLCore::loadTexture(SDLCore::GetRespath() + "mainmenu_background.png", SDLCore::GetRenderer());
}


MainMenu::~MainMenu()
{

}

int MainMenu::CreateMainMenu()
{
	//Luodaan MainMenu
	if (!Mainmenu)
	{
		MainMenu::Mainmenu = new MainMenu();
	}
	//Luodaan MainMenun tausta
	renderTexture(Mainmenu->m_MainMenuBackgroundTexture, SDLCore::GetRenderer(), 0, 0, 1920, 1080);
	//Luodaan MainMenun napit
	for (int i = 0; i < ButtonCount_main; i++)
	{
		renderTexture(Mainmenu->buttons[i].GetTexture(), SDLCore::GetRenderer(), Mainmenu->buttons[i].GetPosX(), Mainmenu->buttons[i].GetPosY());
	}
	//Mainmenun renderöinti
	SDL_RenderPresent(SDLCore::GetRenderer());
	return 0;
}
// Loop Thread
int Universe_ThreadFunction(void* data)
{
	while (!GameLoop::GetQuit()) 
	{
		Gravitaatio::Update((Gravitaatio*)data);
		//SDL_Delay(1);
	}
	return 0;
}

int MainMenu::ButtonPressed()
{
	if (MainMenu::m_ButtonIndex == NothingPressed)
	{
		return 0;
	}
			//Täällä napin painallus aiheuttaa jotain
	if (SDLCore::GetEvent()->button.x >= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetSizeY())
	{
		switch (Mainmenu->m_ButtonIndex)
		{
		case StartButton:			
			kappale = Gravitaatio::CreateUniverse(OptionsMenu::GetKpl());

			kappale[0].Init("Planeetta1", 1.0e13, 0.0, 0.0, 0.0, 0.0);
			kappale[1].Init("Pallo1", 1.0e11, 9.0, 0.0, 0.0, 11.61125878);
			kappale[2].Init("Pallo2", 5.0, 15.0, 0.0, 0.0, 5.61125878);
			kappale[3].Init("Pallo3", 5.0, -40.0, 0.0, 0.0, -2.5);
			kappale[4].Init("Pallo4", 5.0, -20.0, 0.0, 0.0, -2.5);

			SDLCore::SetThread(SDL_CreateThread(Universe_ThreadFunction, "UpdateUniverse", (void*)kappale));
			Gravitaatio::RenderUniverse(kappale);
			break;
		case OptionsButton:
			GameLoop::SetMenuIndex(1);
			OptionsMenu::CreateOptionsMenu();
			break;
		case CreditsButton:
			GameLoop::SetMenuIndex(2);
			CreditsMenu::CreateCreditsMenu();
			break;
		case QuitButton:
			//Poistutaan
			GameLoop::SetQuit(true);
			break;
		default:
			break;
		}
	}
		//Jos hiirennappi palautetaan painikkeiden ulkopuollella tekstuurit palautetaan
		if (!(SDLCore::GetEvent()->button.x >= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetSizeY()))
		{
			renderTexture(Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetTexture(), SDLCore::GetRenderer(), Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetPosX(), Mainmenu->buttons[Mainmenu->m_ButtonIndex].GetPosY());
			SDL_RenderPresent(SDLCore::GetRenderer());
		}
	return 0;
}

int MainMenu::ButtonPressedDown()
{
	for (int i = 0; i < ButtonCount_main; i++)
	{
		if (SDLCore::GetEvent()->button.x >= Mainmenu->buttons[i].GetPosX() && SDLCore::GetEvent()->button.y >= Mainmenu->buttons[i].GetPosY() && SDLCore::GetEvent()->button.x <= Mainmenu->buttons[i].GetSizeX() && SDLCore::GetEvent()->button.y <= Mainmenu->buttons[i].GetSizeY())
		{
			renderTexture(Mainmenu->buttons[i].GetTextureDown(), SDLCore::GetRenderer(), Mainmenu->buttons[i].GetPosX(), Mainmenu->buttons[i].GetPosY());
			Mainmenu->m_ButtonIndex = i;
			break;
		}
	}

	if (!(SDLCore::GetEvent()->button.x >= Mainmenu->buttons[m_ButtonIndex].GetPosX() && SDLCore::GetEvent()->button.y >= Mainmenu->buttons[m_ButtonIndex].GetPosY() && SDLCore::GetEvent()->button.x <= Mainmenu->buttons[m_ButtonIndex].GetSizeX() && SDLCore::GetEvent()->button.y <= Mainmenu->buttons[m_ButtonIndex].GetSizeY()))
	{
		Mainmenu->m_ButtonIndex = NothingPressed;
		return 0;
	}

	SDL_RenderPresent(SDLCore::GetRenderer());
	return 0;
}