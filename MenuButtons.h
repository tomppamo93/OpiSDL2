#pragma once

#include "includes.h"

using namespace std;

class MenuButtons
{
public:
	MenuButtons();
	~MenuButtons();
	int SetButton(string name, int posx, int posy, int sizex, int sizey, SDL_Texture *texture, SDL_Texture *texturedown);

	int GetPosX() { return m_pos_x; };
	int GetPosY() { return m_pos_y; };

	int GetSizeX() { return m_size_x; };
	int GetSizeY() { return m_size_y; };

	SDL_Texture *GetTexture()     { return m_ButtonTexture; };
	SDL_Texture *GetTextureDown() { return m_ButtonTextureDown; };
private:
	string m_name;
	int m_pos_x, m_pos_y;
	int m_size_x, m_size_y;
	SDL_Texture *m_ButtonTexture, *m_ButtonTextureDown;
};

