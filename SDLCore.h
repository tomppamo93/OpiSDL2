#pragma once

#include "includes.h"
#include "SDL_thread.h"
#include "Gravitaatio.h"

using namespace std;

class SDLCore
{
public:
	static string GetRespath()         { return SDLCore::m_respath; };
	static SDL_Window *GetWindow()     { return SDLCore::m_win; };
	static SDL_Renderer *GetRenderer() { return SDLCore::m_ren; };
	static SDL_Event *GetEvent()       { return SDLCore::m_e; };
	static SDL_Thread *GetThread()     { return SDLCore::m_thread; }
	
	static void SetThread(SDL_Thread *th) { m_thread = th; };

	static SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren);

	static int SDLCoreInit();
private:
	static string m_respath;
	static SDL_Window *m_win;
	static SDL_Renderer *m_ren;
	static SDL_Event *m_e;
	static SDL_Thread *m_thread;
};

