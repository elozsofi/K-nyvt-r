#ifndef STRUKT_H_INCLUDED
#define STRUKT_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Konyv{
    char szerzo[30+1];
    char cim[50+1];
    int kiadasiev;
    char tema[20+1];
    char kinelvan[30+1];
    struct Konyv* kovetkezo;
}Konyv;

#endif // STRUKT_H_INCLUDED
