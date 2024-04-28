#include "fn_random.hpp"


// fonction générant un entier aléatoire dans [min ; max]
int rand_int(int min, int max)
{
    return rand()%(max-min+1) + min;
}

float rand_float(float min, float max)
{
    return rand()/ (float) RAND_MAX * (max-min) + min;
}

int rand_without(int min, int max, int exclu){
    if(min==max) //Si il l'intervalle donné ne contient qu'un élément, on le renvoit...Même si c'est celui exclu.
        return exclu;

    int r = rand_int(min,max-1);
    if(r>=exclu)
        ++r;
    return r;
}

// fonction générant un booléen aléatoire
bool rand_bool()
{
    return (bool) rand()%2;
}
