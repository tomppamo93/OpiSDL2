#pragma once

#include <math.h>
#include <string>
#include <iostream>
#include "SDLCore.h"
#include "GameLoop.h"
#include "MenuButtons.h"


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Texture *renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);

class Gravitaatio
{
public:
	Gravitaatio();
	~Gravitaatio();

	int Init(std::string name, double mass, double pos_x, double pos_y, double vel_x, double vel_y, double rad);

	double GetPosX() { return m_pos_x; }
	double GetPosY() { return m_pos_y; }

	double GetVelX() { return m_vel_x; }
	double GetVelY() { return m_vel_y; }

	static double GetSimtime() { return simtime; }
	static unsigned int GetCalcCounter() { return calccounter; }
	static void   SetSimtime(double time) { simtime = time; }
	static void   SetCalcCounter(unsigned int counter) { calccounter = counter; }

	static double Distance(Gravitaatio *orgkpl, Gravitaatio *kpl);
	static double Acceleration(Gravitaatio *orgkpl, Gravitaatio *kpl);
	static void   VelX(Gravitaatio *orgkpl, Gravitaatio *kpl), VelY(Gravitaatio *orgkpl, Gravitaatio *kpl);
	static void   PosX(Gravitaatio *orgkpl), PosY(Gravitaatio *orgkpl);
	static bool   CheckCollision(Gravitaatio *kpl1, Gravitaatio *kpl2);

	static int Update(Gravitaatio*);
	static Gravitaatio *CreateUniverse(int);
	static int RenderUniverse(Gravitaatio *kappale);
	static void Collision(Gravitaatio*, Gravitaatio*);

	static void   SetRenderScale(double scale) { m_renderscale = scale; }
	static double GetRenderScale()             { return m_renderscale; }
	static bool GetStop()                      { return m_stop; };
	static void SetStop(bool stop) { m_stop = stop; };
private:
	std::string m_name;
	double m_mass, m_rad;
	double m_pos_x, m_pos_y;
	double m_vel_x, m_vel_y;
	SDL_Texture *m_planeetta;
	SDL_Texture *m_text;
	bool m_active;

	static double simtime;
	static double gconst;
	static int kplm‰‰r‰;
	static SDL_Texture *m_SpaceBackgroundTexture;
	static SDL_Texture *m_SimTimeText;
	static unsigned int calccounter;
	static SDL_Color m_color;
	static double m_renderscale;
	static MenuButtons m_backbutton;
	static bool ifinitback;
	static bool m_stop;
};

