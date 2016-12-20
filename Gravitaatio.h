#pragma once

#include <math.h>
#include <string>
#include <iostream>
#include "SDLCore.h"
#include "GameLoop.h"

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Texture *renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);

class Gravitaatio
{
public:
	Gravitaatio();
	~Gravitaatio();
	
	int Init(std::string name, double mass, double pos_x, double pos_y, double vel_x, double vel_y);

	double GetPosX() { return m_pos_x; };
	double GetPosY() { return m_pos_y; };

	double GetVelX() { return m_vel_x; };
	double GetVelY() { return m_vel_y; };

	static double Distance(Gravitaatio *orgkpl, Gravitaatio *kpl);
	static double Acceleration(Gravitaatio *orgkpl, Gravitaatio *kpl);
	static void   VelX(Gravitaatio *orgkpl, Gravitaatio *kpl), VelY(Gravitaatio *orgkpl, Gravitaatio *kpl);
	static void   PosX(Gravitaatio *orgkpl), PosY(Gravitaatio *orgkpl);

	static int Update(Gravitaatio*);
	static Gravitaatio *CreateUniverse(int);
	static int RenderUniverse(Gravitaatio *kappale);
private:
	std::string m_name;
	double m_mass;
	double m_pos_x, m_pos_y;
	double m_vel_x, m_vel_y;
	SDL_Texture *m_planeetta;
	SDL_Texture *m_text;

	static double simtime;
	static double gconst;
	static int kplm��r�;
	static SDL_Texture *m_SpaceBackgroundTexture;
	static SDL_Color m_color;
};
