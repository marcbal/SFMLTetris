#include "fn_random.h"


// fonction générant un entier aléatoire dans [min ; max]
int rand_int(int min, int max)
{
	return rand()%(max-min+1) + min;
}

float rand_float(float min, float max)
{
    float v = rand()+rand()/(float) rand();
    v = fmod(v, max-min);
	return v+min;
}

// fonction générant un booléen aléatoire
bool rand_bool()
{
	return (bool) rand()%2;
}
