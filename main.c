#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "strukt.h"
#include "fajlkezeles.h"
#include "lancoltlistakezeles.h"
#include "keresesek.h"

int main()
{
    int valasztas;
    Konyv* eleje = listaba_beolvas();
    printf("Udvozlunk az InfoC konyvtarban!\n");

    do{
        lehetosegek_kiir();
        scanf("%d", &valasztas);

        switch(valasztas){
            case 1:
                kereses_szerzo(eleje);
                break;
            case 2:
                kereses_cim(eleje);
                break;
            case 3:
                kereses_kiadasiev(eleje);
                break;
            case 4:
                kereses_tema(eleje);
                break;
            case 5:
                olvaso_konyvei(eleje);
                break;
            case 6:
                hozza_ad(eleje);
                break;
            case 7:
                listat_kiir(eleje);
                break;
        }

    }while(valasztas != 0);

    listat_lement_es_felszabadit(eleje);
    printf("Varjuk vissza!\n");

    return 0;
}
