
#include "Randomi.h"

Randomi::Randomi()
{
	SDL_TimerCallback Callback;
	void *seed;
	Value = 0;
	SDL_TimerID TimeID;
	TimeID = SDL_AddTimer(1,Callback,seed);
	Randomisize(TimeID);
	
}
void Randomi::Randomisize(int seed)
{
	while (!(seed <= 1024 * 100000) && !(seed >= 100 * 100000))
	{
		std::srand(seed);
		Value = seed/100000;
		continue;
	}
}
