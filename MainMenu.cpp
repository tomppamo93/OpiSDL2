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
	kappale = NULL;
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
		Gravitaatio::SetCalcCounter(Gravitaatio::GetCalcCounter()+1);

		while (!GameLoop::GetQuit() && Gravitaatio::GetStop())
		{
			SDL_Delay(100);
		}
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
			Gravitaatio::SetStop(false);

			if (kappale == NULL)
			{
				kappale = Gravitaatio::CreateUniverse(OptionsMenu::GetKpl());

				kappale[0].Init("Sun", 1.98855e12, 0.0, 0.0, 0.0, 0.0, 1000.0);
				kappale[1].Init("Pallo1", 1.98855e8, 2000.0, 0.0, 0.0, 0.25, 100.0);
				kappale[2].Init("Pallo2", 1.98855e8, -2000.0, 0.0, 0.0, -0.35, 100.0);
			}
			
			//kappale[0].Init("Sun", 1.98855e30, 0.0, 0.0, 0.0, 0.0, 6.957e8);
			//kappale[1].Init("Earth", 5.97237e24, 0.0, 152100000.0e3, 29.78e3, 0.0, 6371.0e3);
			//kappale[2].Init("Moon", 7.342e22, 0.0, (362600e3+152100000.0e3), (29.78e3+1.022e3), 0.0, 1738.1e3);
			//kappale[3].Init("Asteroid1", 5.0, -40.0, 0.0, 0.0, -2.5, 0.3);
			//kappale[4].Init("Asteroid2", 5.0, -20.0, 0.0, 0.0, -2.5, 0.3);
			//kappale[5].Init("Asteroid3", 5.0, -50.0, 0.0, 0.0, -1.5, 0.3);

			if (!threadluotu)
			{
				SDLCore::SetThread(SDL_CreateThread(Universe_ThreadFunction, "UpdateUniverse", (void*)kappale));
				threadluotu = true;
			}

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