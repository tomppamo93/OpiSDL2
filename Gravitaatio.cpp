#include "Gravitaatio.h"


double Gravitaatio::simtime  = 0.00001;
double Gravitaatio::gconst   = 6.67384e-11;
int    Gravitaatio::kplm‰‰r‰ = 0;
double Gravitaatio::m_renderscale = 5.0;
SDL_Texture *Gravitaatio::m_SpaceBackgroundTexture = NULL;
SDL_Color   Gravitaatio::m_color = {0, 0, 0, 0};


Gravitaatio::Gravitaatio()
{
	m_rad = m_mass = m_pos_x = m_pos_y = m_vel_x = m_vel_y = 0.0;
	m_name = "Name";

	m_active = true;

	m_planeetta = SDLCore::loadTexture(SDLCore::GetRespath() + "pallo.png", SDLCore::GetRenderer());

	if (!m_SpaceBackgroundTexture)
	{
		m_SpaceBackgroundTexture = SDLCore::loadTexture(SDLCore::GetRespath() + "mainmenu_background.png", SDLCore::GetRenderer());
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
		if (kpl[i].m_active == true)
		{
			if (orgkpl != &kpl[i])
			{
				velx += ((cos(acos((orgkpl->m_pos_x - kpl[i].m_pos_x) / pow(Distance(orgkpl, &kpl[i]), 2))) * Acceleration(orgkpl, &kpl[i])) * simtime);
			}
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
		if (kpl[i].m_active == true)
		{
			if (orgkpl != &kpl[i])
			{
				vely += ((sin(asin((orgkpl->m_pos_y - kpl[i].m_pos_y) / pow(Distance(orgkpl, &kpl[i]), 2))) * Acceleration(orgkpl, &kpl[i])) * simtime);
			}
		}
	}
	orgkpl->m_vel_y = vely;
}

//Universumin p‰ivitys
int Gravitaatio::Update(Gravitaatio *kpl)
{
	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (kpl[i].m_active == true)
		{
			PosX(&kpl[i]);
			PosY(&kpl[i]);
		}
	}

	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (kpl[i].m_active == true)
		{
			VelX(&kpl[i], kpl);
			VelY(&kpl[i], kpl);
		}
	}

	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (kpl[i].m_active == true)
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
	while (!GameLoop::GetQuit())
	{

		while (SDL_PollEvent(SDLCore::GetEvent()))
		{
			if (SDLCore::GetEvent()->type == SDL_KEYUP)
			{
				if (SDLCore::GetEvent()->key.keysym.sym == SDLK_ESCAPE)
				{
					GameLoop::SetQuit(true);
				}
			}
		}
		
		renderTexture(m_SpaceBackgroundTexture, SDLCore::GetRenderer(), 0, 0, 1920, 1080);
		//Kappaleiden p‰‰lle renderˆid‰‰n teksti‰
		for (int i = 0; i < kplm‰‰r‰; i++)
		{
			if (kappale[i].m_active == true)
			{
				kappale[i].m_text = renderText("Kappale: " + kappale[i].m_name, "C:\\Windows\\Fonts\\Arial.ttf", m_color, 12, SDLCore::GetRenderer());
				renderTexture(kappale[i].m_text, SDLCore::GetRenderer(), (int)(kappale[i].GetPosX() * m_renderscale) + 920, (int)(kappale[i].GetPosY() * m_renderscale) + 525);
				SDL_DestroyTexture(kappale[i].m_text);
			}
		}
		
		//Renderˆid‰‰n kappaleet
		for (int i = 0; i < kplm‰‰r‰; i++)
		{
			if (kappale[i].m_active == true)
			{
				renderTexture(kappale[i].m_planeetta, SDLCore::GetRenderer(), (int)(kappale[i].GetPosX() * m_renderscale) + 960, (int)(kappale[i].GetPosY() * m_renderscale) + 540);
			}
		}
		
		SDL_RenderPresent(SDLCore::GetRenderer());

		SDL_Delay(25);
	}
	return 0;
}
void Gravitaatio::Collision(Gravitaatio *orgkpl, Gravitaatio *kpl)
{
	for (int i = 0; i < kplm‰‰r‰; i++)
	{
		if (orgkpl != &kpl[i])
		{
			if (CheckCollision(orgkpl, &kpl[i]))
			{
				double m1 = orgkpl->m_mass, m2 = kpl[i].m_mass;

				double LK2X = (m2 * kpl[i].m_vel_x);
				double LK2Y = (m2 * kpl[i].m_vel_y);
				double LK1X = (m1 * orgkpl->m_vel_x);
				double LK1Y = (m1 * orgkpl->m_vel_y);
				double kokM = (m1 + m2);
				double kokVx = (LK1X + LK2X) / kokM;
				double kokVy = (LK1Y + LK2Y) / kokM;

				orgkpl->m_vel_x = kokVx;
				orgkpl->m_vel_y = kokVy;
				orgkpl->m_mass = kokM;

				kpl[i].m_active = false;
			}
		}
	}
}

//Jos kappaleiden s‰teiden summa on pienempi kuin niiden v‰linen et‰isyys on tapahtunut tˆrm‰ys
bool Gravitaatio::CheckCollision(Gravitaatio *kpl1, Gravitaatio *kpl2)
{
	if ((kpl1->m_rad + kpl2->m_rad) > Distance(kpl1, kpl2))
	{
		return true;
	}
		return false;
}