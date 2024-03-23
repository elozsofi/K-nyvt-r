#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "strukt.h"
#include "lancoltlistakezeles.h"


//menü elején megjeleníti a választható opciókat
void lehetosegek_kiir(){
    printf("\n1) Kereses *szerzo* alapjan\n2) Kereses *cim* alapjan\n3) Kereses *kiadasi ev* alapjan\n4) Kereses *tema* alapjan\n5) Adott olvasonal levo konyv(ek)\n6) Uj konyv bejegyzese\n7) Adatbazisban levo konyvek kilistazasa\n0) Kilepes\n");
}


/*kb. az összes keresõ fgv ugyanúgy mûködik, beolvassa a keresett
kulcsszót, majd while-lal végigmegy a láncolt listán
egy temp pointer segítségével, amíg nem talál hasonlóságot a beírt szó
és a keresett attribútum között. majd meghívja a törlõ vagy módosító fgv-eket */
void kereses_szerzo(Konyv* eleje){
    bool talalt = false;

    printf("\nIrja be a keresett szerzo nevet: ");
    char* nev = (char*) malloc((30+1)*sizeof(char));

    fflush(stdin);
    scanf("%[^\n]", nev);

    Konyv* temp = eleje;

    int szamlalo = 1;

    while(temp){
        Konyv* ideiglenes = temp->kovetkezo;
        if (!(strstr(temp->szerzo, nev)==NULL)){
            talalt = true;
            printf("%d. %s: %s    (%d), tema: %s.\n", szamlalo, temp->szerzo, temp->cim, temp->kiadasiev, temp->tema);
            szamlalo += 1;
            int valasz;
            printf("\n1) modositas\n2) torles\n3) tovabb\n");
            scanf("%d", &valasz);

            if(valasz==1)
                modositas(temp);
            else if(valasz==2)
                torles(&eleje, temp->cim);
        }
        temp = ideiglenes;
    }
    free(nev);

    if (!talalt){
        printf("\n***Nincsen az adatbazisban ettol a szerzotol konyv***\n");
    }
}

void kereses_cim(Konyv* eleje){
    bool talalt = false;

    printf("\nIrja be a keresett konyv cimet: ");
    char* kerescim = (char*) malloc((50+1)*sizeof(char));

    fflush(stdin);
    scanf("%[^\n]", kerescim);

    Konyv* temp = eleje;

    int szamlalo = 1;

    while(temp){
        Konyv* ideiglenes = temp->kovetkezo;
        if (!(strstr(temp->cim, kerescim)==NULL)){
            talalt = true;
            printf("%d. %s: %s    (%d), tema: %s.\n", szamlalo, temp->szerzo, temp->cim, temp->kiadasiev, temp->tema);
            szamlalo += 1;
            int valasz;
            printf("\n1) modositas\n2) torles\n3) tovabb\n");
            scanf("%d", &valasz);

            if(valasz==1)
                modositas(temp);
            else if(valasz==2)
                torles(&eleje, temp->cim);
        }
        temp = ideiglenes;
    }
    free(kerescim);

    if (!talalt){
        printf("\n***Nincsen az adatbazisban ilyen cimu konyv***\n");
    }
}


void kereses_kiadasiev(Konyv* eleje){
    bool talalt = false;

    printf("\nIrja be az evszamot: ");
    int ev;
    scanf("%d", &ev);

    int szamlalo = 1;

    Konyv* temp = eleje;

    while(temp){
        Konyv* ideiglenes = temp->kovetkezo;
        if (temp->kiadasiev == ev){
            talalt = true;
            printf("%d. %s: %s, tema: %s.\n", szamlalo, temp->szerzo, temp->cim, temp->tema);
            szamlalo += 1;


            int valasz;
            printf("\n1) modositas\n2) torles\n3) tovabb\n");
            scanf("%d", &valasz);

            if(valasz==1)
                modositas(temp);
            else if(valasz==2)
                torles(&eleje, temp->cim);
        }
        temp = ideiglenes;
    }
    if (!talalt)
        printf("\n***Nincsen az adatbazisban ilyen evjaratu konyv***\n");
}


void kereses_tema(Konyv* eleje){
    bool talalt = false;

    printf("\nIrja be a keresett temat: ");
    char* kerestema = (char*) malloc((20+1)*sizeof(char));

    fflush(stdin);
    scanf("%[^\n]", kerestema);

    Konyv* temp = eleje;

    int szamlalo = 1;

    while(temp){
        Konyv* ideiglenes = temp->kovetkezo;
        if (!(strstr(temp->tema, kerestema)==NULL)){
            talalt = true;
            printf("%d. %s: %s    (%d).\n", szamlalo, temp->szerzo, temp->cim, temp->kiadasiev);
            szamlalo += 1;

            int valasz;
            printf("\n1) modositas\n2) torles\n3) tovabb\n");
            scanf("%d", &valasz);

            if(valasz==1)
                modositas(temp);
            else if(valasz==2)
                torles(&eleje, temp->cim);
        }
        temp = ideiglenes;
    }
    free(kerestema);

    if (!talalt){
        printf("\n***Nincsen az adatbazisban ilyen temaju konyv***\n");
    }
}

void olvaso_konyvei(Konyv* eleje){
    bool talalt = false;

    printf("\nIrja be az olvaso nevet: (szabad = kikolcsonozheto) ");
    char* olvaso = (char*) malloc((30+1)*sizeof(char));

    fflush(stdin);
    scanf("%[^\n]", olvaso);

    Konyv* temp = eleje;

    int szamlalo = 1;

    while(temp){
        if (!(strstr(temp->kinelvan, olvaso)==NULL)){
            talalt = true;
            printf("%d. %s: %s    (%d).\n", szamlalo, temp->szerzo, temp->cim, temp->kiadasiev);
            szamlalo += 1;
        }
        temp = temp->kovetkezo;
    }

    free(olvaso);

    if (!talalt){
        printf("\n***Nincsen ennel az olvasonal konyv***\n");
    }
}
