#ifndef Randomizeri
#define Randomizeri

#include <random>
#include <SDL.h>

class Randomi
{
public:
	Randomi();
	~Randomi();

	void Randomisize(int seed);

	int getRandomInt() { return Value; };

private:
	int Value;
	

};

#endif // !Randomizer
