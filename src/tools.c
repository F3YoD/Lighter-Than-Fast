#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tools.h"

int CreeAlea(int min, int max){
// ce sous programme retourne un entier aleatoire entre min et max
	return rand()%(max - min+1) + min;
}
