#pragma once

#include "SDLCore.h"

class GameLoop
{
public:
	GameLoop();
	~GameLoop();
	static void SetQuit(bool exit) { quit = exit; };
	static void SetMenuIndex(int Index) { MenuIndex = Index; };
	static bool GetQuit() { return GameLoop::quit; };
private:
	static int MenuIndex;
	static bool quit;
	int StartGame();
};

