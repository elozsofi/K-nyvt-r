#include <stdio.h>
#include <stdlib.h>
#include "strukt.h"
#include "debugmalloc.h"
#include "lancoltlistakezeles.h"

//segedfuggveny, a f�jlb�l beolvas�shoz seg�t
int fajlban_sorokat_megszamol(FILE* fp){
    int sorok_szama = 0;
    int c;

    while((c = fgetc(fp)) != EOF){
        if (c == '\n'){     // 1 sor = 1 Konyv
            sorok_szama += 1;
        }
    }
    rewind(fp); //f�jlpointert visszarakjuk a f�jl elej�re
    return sorok_szama;
}

//visszat�r az els� pointerrel. 1 sor = 1 k�nyv
//a ciklus soronk�nt v�gigmegy a f�jlon, k�zben olvassa be a k�nyvek adatait
//egyes�vel adja hozz� az elemeket
Konyv* listaba_beolvas(){

    FILE* fp = fopen("Konyvtar.txt", "r");
    if (fp == NULL){                     //ha esetleg nem siker�lne a K�nyvt�r megnyit�sa
        perror("\n***Fajlhiba!***\n");
        return NULL;
    }

    Konyv* legelso_elem = NULL;
    Konyv* legutobbi_elem = NULL;

    //ciklushoz
    int sorok_szama = fajlban_sorokat_megszamol(fp);


    for(int i = 0; i < sorok_szama; ++i){

        //addig foglal, am�g van �rv�nyes sor
        Konyv* egy_konyv = (Konyv*) malloc(1 * sizeof(Konyv));

        //beolvas�s
        fscanf(fp, "%[^\t]\t%[^\t]\t%d\t%[^\t]\t%[^\n]\n", egy_konyv->szerzo, egy_konyv->cim, &egy_konyv->kiadasiev, egy_konyv->tema, egy_konyv->kinelvan);

        egy_konyv->kovetkezo = NULL;
        if(legutobbi_elem == NULL){
            legelso_elem = egy_konyv;
        }
        else{
            legutobbi_elem->kovetkezo = egy_konyv;
        }
        legutobbi_elem = egy_konyv;
    }


    printf("Sikeres beolvasas.\n");
    fclose(fp);
    return legelso_elem;
}

/* am�g tal�l �rv�nyes elemet a list�ban (for ciklussal megy rajta v�gig)
addig bele�rja a f�jlba, majd megh�vja a felszabad�t� f�ggv�nyt is */
void listat_lement_es_felszabadit(Konyv* eleje){

    if (eleje == NULL){
        printf("\n\n****a lista ures!****\n\n");
        return; //ha a lista �res nem kell lementeni �s felszabad�tani, le�llhat a program
    }
    FILE* fp = fopen("Konyvtar.txt", "w");
    if (fp == NULL){                     //ha esetleg nem siker�lne a K�nyvt�r megnyit�sa
        perror("\n****Fajlhiba: nem lehet lementeni a listat!****\n");
        return;
    }

    for(Konyv* iter = eleje; iter != NULL; iter = iter->kovetkezo){
        fprintf(fp, "%s\t%s\t%d\t%s\t%s\n", iter->szerzo, iter->cim, iter->kiadasiev, iter->tema, iter->kinelvan);

    }
    felszabadit(eleje);
    printf("Sikeres lementes.\n\n");
    fclose(fp);
}
