#include "MenuButtons.h"

MenuButtons::MenuButtons()
{
	m_name = "Nimi";
	m_pos_x = m_pos_y = m_size_x = m_size_y = 0;
	m_ButtonTexture = m_ButtonTextureDown = NULL;
}


MenuButtons::~MenuButtons()
{
}


int MenuButtons::SetButton(string name, int posx, int posy, int sizex, int sizey, SDL_Texture *texture, SDL_Texture *texturedown)
{
	m_name				= name;
	m_pos_x				= posx;
	m_pos_y				= posy;
	m_size_x			= sizex + posx;
	m_size_y			= sizey + posy;
	m_ButtonTexture     = texture;
	m_ButtonTextureDown = texturedown;
	return 0;
}
