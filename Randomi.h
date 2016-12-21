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

	double getRandomInt() { return Value; };

private:
	double Value;
	

};

#endif // !Randomizer
