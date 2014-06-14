#include "fn_random.hpp"


// fonction générant un entier aléatoire dans [min ; max]
int rand_int(int min, int max)
{
    return rand()%(max-min+1) + min;
}
