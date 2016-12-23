#include "Gravitaatio.h"
#include "MainMenu.h"

double Gravitaatio::simtime  = 0.01;
double Gravitaatio::gconst   = 6.67384e-11;
int    Gravitaatio::kplm‰‰r‰ = 0;
double Gravitaatio::m_renderscale = 5.0;
unsigned int Gravitaatio::calccounter = 0;
SDL_Texture *Gravitaatio::m_SpaceBackgroundTexture = NULL;
SDL_Texture *Gravitaatio::m_SimTimeText = NULL;
SDL_Color   Gravitaatio::m_color = {0, 0, 0, 0};
MenuButtons Gravitaatio::m_backbutton;
bool Gravitaatio::ifinitback = true;
bool Gravitaatio::m_stop = false;

Gravitaatio::Gravitaatio()
{
	m_rad = m_mass = m_pos_x = m_pos_y = m_vel_x = m_vel_y = 0.0;
	m_name = "Name";

	m_active = true;

	m_planeetta = SDLCore::loadTexture(SDLCore::GetRespath() + "pallo.png", SDLCore::GetRenderer());

	if (ifinitback)
	{
		m_backbutton.SetButton("Back", 0, 1030, 150, 50, SDLCore::loadTexture(SDLCore::GetRespath() + "back.png", SDLCore::GetRenderer()), SDLCore::loadTexture(SDLCore::GetRespath() + "back_down.png", SDLCore::GetRenderer()));
		m_SpaceBackgroundTexture = SDLCore::loadTexture(SDLCore::GetRespath() + "mainmenu_background.png", SDLCore::GetRenderer());
		ifinitback = false;
	}

	m_color = { 255, 255, 255, 0 };

	std::cout << "Kappale luotu!" << std::endl;
}


Gravitaatio::~Gravitaatio()
{
}

//Kappaleiden alustus funktio
int Gravitaatio::Init(std::string name, double mass, double pos_x, double pos_y, double vel_x, double vel_y , double rad)
{
	m_name  = name;
	m_mass  = mass;
	m_rad   = rad;

	m_pos_x = pos_x;
	m_pos_y = pos_y;

	m_vel_x = vel_x;
	m_vel_y = vel_y;
	return 0;
}

//Et‰isyyden laskenta
double Gravitaatio::Distance(Gravitaatio *kpl1, Gravitaatio *kpl2)
{
	return sqrt(pow((kpl1->m_pos_x - kpl2->m_pos_x), 2) + pow((kpl1->m_pos_y - kpl2->m_pos_y), 2));
}

//Kiihtyvyyden laskenta
double Gravitaatio::Acceleration(Gravitaatio *orgkpl, Gravitaatio *kpl)
{
	return (-1*(((gconst * orgkpl->m_mass * kpl->m_mass) / Distance(orgkpl, kpl)) / orgkpl->m_mass));
}

//Paikan x-komponentin lasku
void Gravitaatio::PosX(Gravitaatio *orgkpl)
{
	orgkpl->m_pos_x += (orgkpl->m_vel_x * simtime);
}

//Paikan y-komponentin lasku
void Gravitaatio::PosY(Gravitaatio *orgkpl)
{
	orgkpl->m_pos_y += (orgkpl->m_vel_y * simtime);
}

//Nopeuden x-komponentin lasku
void Gravitaatio::VelX(Gravitaatio *orgkpl, Gravitaatio *kpl)
{
	double velx = orgkpl->m_vel_x;

	for (int i = 0; i < kplm‰‰r‰; i++)
	{
			if (orgkpl != &kpl[i] && kpl[i].m_active)
			{
				velx += ((cos(acos((orgkpl->m_pos_x - kpl[i].m_pos_x) / pow(Distance(orgkpl, &kpl[i]), 2))) * Acceleration(orgkpl, &kpl[i])) * simtime);
			}
	}
	orgkpl->m_vel_x = velx;
}

//Nopeuden y-komponentin lasku
void Gravitaatio::VelY(Gravitaatio *orgkpl, Gravitaatio *kpl)
{
	double vely = orgkpl->m_vel_y;

	for (int i = 0; i < kplm‰‰r‰; i++)
	{
			if (orgkpl != &kpl[i] && kpl[i].m_active)
			{
				vely += ((sin(asin((orgkpl->m_pos_y - kpl[i].m_pos_y) / pow(Distance(orgkpl, &kpl[i]), 2))) * Acceleration(orgkpl, &kpl[i])) * simtime);
			}
	}
	orgkpl->m_vel_y = vely;
}

//Universumin p‰ivitys
int Gravitaatio::Update(Gravitaatio *kpl)
{
	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (kpl[i].m_active)
		{
			PosX(&kpl[i]);
			PosY(&kpl[i]);
		}
	}

	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (kpl[i].m_active)
		{
			VelX(&kpl[i], kpl);
			VelY(&kpl[i], kpl);
		}
	}

	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (kpl[i].m_active)
		{
			Collision(&kpl[i], kpl);
		}
	}
	return 0;
}

//Universumin luonti
Gravitaatio *Gravitaatio::CreateUniverse(int kplm‰‰r‰2)
{
	kplm‰‰r‰ = kplm‰‰r‰2;
	Gravitaatio *kpl = new Gravitaatio[kplm‰‰r‰];
	return kpl;
}

int Gravitaatio::RenderUniverse(Gravitaatio *kappale)
{
	while (!GameLoop::GetQuit() && !m_stop)
	{
		while (SDL_PollEvent(SDLCore::GetEvent()))
		{
			if (SDLCore::GetEvent()->type == SDL_KEYUP)
			{
				if (SDLCore::GetEvent()->key.keysym.sym == SDLK_ESCAPE)
				{
					MainMenu::CreateMainMenu();
					m_stop = true;
					break;
				}
			}
		}

		if (m_stop)
		{
			break;
		}

		renderTexture(m_SpaceBackgroundTexture, SDLCore::GetRenderer(), 0, 0, 1920, 1080);
		//Kappaleiden p‰‰lle renderˆid‰‰n teksti‰
		for (int i = 0; i < kplm‰‰r‰; i++)
		{
			if (kappale[i].m_active)
			{
				kappale[i].m_text = renderText("Kappale: " + kappale[i].m_name, "C:\\Windows\\Fonts\\Arial.ttf", m_color, 12, SDLCore::GetRenderer());
				renderTexture(kappale[i].m_text, SDLCore::GetRenderer(), (int)((kappale[i].m_pos_x * m_renderscale) + 920 - kappale[i].m_rad * m_renderscale), (int)((kappale[i].m_pos_y * m_renderscale) + 525 - kappale[i].m_rad * m_renderscale));
				SDL_DestroyTexture(kappale[i].m_text);
				kappale[i].m_text = renderText("Massa::: " + to_string(kappale[i].m_mass), "C:\\Windows\\Fonts\\Arial.ttf", m_color, 12, SDLCore::GetRenderer());
				renderTexture(kappale[i].m_text, SDLCore::GetRenderer(), (int)((kappale[i].m_pos_x * m_renderscale) + 920 - kappale[i].m_rad * m_renderscale), (int)((kappale[i].m_pos_y * m_renderscale) + 513 - kappale[i].m_rad * m_renderscale));
				SDL_DestroyTexture(kappale[i].m_text);
			}
		}	

		//Renderˆid‰‰n simulaation aika n‰ytˆn reunaan
		m_SimTimeText = renderText("Sim Time[h]:: " + to_string(((int)(simtime * calccounter))/3600), "C:\\Windows\\Fonts\\Arial.ttf", m_color, 24, SDLCore::GetRenderer());
		renderTexture(m_SimTimeText, SDLCore::GetRenderer(), 0, 0);
		SDL_DestroyTexture(m_SimTimeText);
		m_SimTimeText = renderText("Calculations: " + to_string(calccounter), "C:\\Windows\\Fonts\\Arial.ttf", m_color, 24, SDLCore::GetRenderer());
		renderTexture(m_SimTimeText, SDLCore::GetRenderer(), 0, 24);
		SDL_DestroyTexture(m_SimTimeText);
		renderTexture(m_backbutton.GetTexture(), SDLCore::GetRenderer(), m_backbutton.GetPosX(), m_backbutton.GetPosY());

		//Renderˆid‰‰n kappaleet
		for (int i = 0; i < kplm‰‰r‰; i++)
		{
			if (kappale[i].m_active)
			{
				renderTexture(kappale[i].m_planeetta, SDLCore::GetRenderer(), (int)((kappale[i].m_pos_x * m_renderscale) + 960 - kappale[i].m_rad * m_renderscale), (int)((kappale[i].m_pos_y * m_renderscale) + 540 - kappale[i].m_rad * m_renderscale), (int)(kappale[i].m_rad * 2.0 * m_renderscale), (int)(kappale[i].m_rad * 2.0 * m_renderscale));
			}
		}
		
		SDL_RenderPresent(SDLCore::GetRenderer());
		SDL_Delay(20);
	}
	return 0;
}

//Kappaleiden yhteentˆrm‰yksess‰ tuhotaan toinen kappaleista mutta liikem‰‰r‰ s‰ilyy niiden yhdistelm‰ss‰
void Gravitaatio::Collision(Gravitaatio *orgkpl, Gravitaatio *kpl)
{
	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (orgkpl != &kpl[i] && kpl[i].m_active && CheckCollision(orgkpl, &kpl[i]))
		{
					double m1 = orgkpl->m_mass, m2 = kpl[i].m_mass;
					orgkpl->m_vel_x = ((m1 / (m1 + m2))*(orgkpl->m_vel_x - kpl[i].m_vel_x));
					orgkpl->m_vel_y = ((m1 / (m1 + m2))*(orgkpl->m_vel_y - kpl[i].m_vel_y));
					orgkpl->m_mass = (m1 + m2);
					kpl[i].m_active = false;
		}
	}
}

//Jos kappaleiden s‰teiden summa on suurempi kuin niiden v‰linen et‰isyys on tapahtunut tˆrm‰ys
bool Gravitaatio::CheckCollision(Gravitaatio *kpl1, Gravitaatio *kpl2)
{
	if ((kpl1->m_rad + kpl2->m_rad) >= Distance(kpl1, kpl2))
	{
		return true;
	}
		return false;
}