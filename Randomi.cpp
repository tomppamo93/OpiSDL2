
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
	while (!(seed <= 1024) && !(seed >= 100))
	{
		std::srand(seed);
		Value = seed;
		continue;
	}
}
