#include "SDLCore.h"

string        SDLCore::m_respath = "";
SDL_Window   *SDLCore::m_win     = NULL;
SDL_Renderer *SDLCore::m_ren     = NULL;
SDL_Event    *SDLCore::m_e       = NULL;
SDL_Thread   *SDLCore::m_thread  = NULL;

void logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture *SDLCore::loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)
	{
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

int SDLCore::SDLCoreInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	
	SDLCore::m_respath = getResourcePath();
	std::cout << "Resource path is: " << m_respath << std::endl;

	SDLCore::m_win = SDL_CreateWindow("Gravitaatio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_MOUSE_FOCUS);
	if (SDLCore::m_win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDLCore::m_ren = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (SDLCore::m_ren == nullptr)
	{
		SDL_DestroyWindow(m_win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	if (TTF_Init() != 0) {

		SDL_Quit();
		return 1;
	}

	SDLCore::m_e      = new SDL_Event;
	

	cout << "SDL Käynnistetty." << endl;
	return 0;
}