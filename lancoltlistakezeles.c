#include <stdio.h>
#include <stdlib.h>
#include "strukt.h"
#include "debugmalloc.h"
#include <string.h>


/* Lefoglal egy új Könyv változót, beolvassa
enterig az adatait, majd visszatér vele
!hívó feladata felszabadítani! (ha szükséges)*/
Konyv* konyv_beolvas(){
    Konyv* uj_konyv = (Konyv*) malloc(sizeof(Konyv));

    printf("Szerzo:\n");
    fflush(stdin);
    scanf("%[^\n]", uj_konyv->szerzo);

    printf("Cim:\n");
    fflush(stdin);
    scanf("%[^\n]", uj_konyv->cim);

    printf("Kiadasi ev:\n");
    int ev;
    scanf("%d", &ev);
    uj_konyv->kiadasiev = ev;

    printf("Tema:\n");
    fflush(stdin);
    scanf("%[^\n]", uj_konyv->tema);

    printf("Kinel van jelenleg (szabad = senkinel):\n");
    fflush(stdin);
    scanf("%[^\n]", uj_konyv->kinelvan);

    return uj_konyv;
}

/* sima lista felszabadító függvény, while-lal megy
végig a listán, előadáson bemutatott módon */
void felszabadit(Konyv* eleje){
    Konyv* temp = eleje;
    while(temp){
        Konyv* kov = temp->kovetkezo;
        free(temp);
        temp = kov;
    }
    printf("\nSikeres felszabaditas.\n");
}

/* -||-, while-lal végigmegy a listán (amíg nem talál NULL pointert)
 közben pedig kiírja az érvényes adatokat */
void listat_kiir(Konyv* eleje){
    Konyv* temp = eleje;
    int szamlalo = 1;
    printf("\n**********************\n");
    while(temp){
        Konyv* kov = temp->kovetkezo;
        printf("%d. %s: %s (%d), temaja: %s. (%s)\n", szamlalo, temp->szerzo, temp->cim, temp->kiadasiev, temp->tema, temp->kinelvan);
        temp = kov;
        szamlalo += 1;
    }
    printf("**********************\n");
}

/* először beolvas egy új Konyv típust, amibe majd beolvasom
az adatokat. */
void hozza_ad(Konyv* eleje){
    printf("Irja be az uj konyv adatait:\n");
    Konyv* uj = konyv_beolvas();

    uj->kovetkezo = NULL;

    if (!eleje)
        eleje = uj;
    else{
    Konyv* temp = eleje;
        while(temp->kovetkezo){
            temp = temp->kovetkezo;
        }
    temp->kovetkezo = uj;
    }
    printf("\nSikeres felvetel!\n\n");
}



/*elõadáson bemutatott módszert alkalmazza,
egy lemarado és egy temp pointerrel megy végig a listán, amibe
aztán eltárolom a törlendõ adatot és az azt megelõzöt is
(habár itt beleírtam egy temp == NULL ellenõrzõt is, a valóságban
 ez nem történhet meg, mivel eleve a keresõ fgv hívja meg
 a törlést / módosítást, így mindenképpen érvényes adatot kéne törölni
 paraméterként a törlendő könyv címét kapja meg, az alapján keresi ki
 az elemet és az azt megelőzőt
*/
void torles(Konyv** eleje, char* mit){
    Konyv* lemarado = NULL;
    Konyv* temp = *eleje;

    while(temp!= NULL && strcmp(temp->cim, mit) != 0){ //végigmegy a listán és megáll a törlendõ elemnél
        lemarado = temp;
        temp = temp->kovetkezo;
    }

    if (temp == NULL){
        printf("****Hiba!****\n");
        return;}
    else if (lemarado == NULL){ //avagy hogyha az elsõ elemet töröljük
        Konyv* ujeleje = temp->kovetkezo;
        free(temp);
        *eleje = ujeleje;
    }
    else{ //lista közepébõl törlünk
        lemarado->kovetkezo = temp->kovetkezo;
        free(temp);
    }
    printf("\nSikeres torles!\n\n");
}

/* hasonló módszer, mint az új elem létrehozása,
lefoglalok egy üres Konyv elemet, majd ebbe beleolvasom és átmásolom
a módosítandóba */
void modositas(Konyv* mit){
    printf("Irja be a konyv uj adatait:\n");
    Konyv* uj = konyv_beolvas();

    //másolás...
    strcpy(mit->szerzo, uj->szerzo);
    strcpy(mit->cim, uj->cim);
    strcpy(mit->tema, uj->tema);
    strcpy(mit->kinelvan, uj->kinelvan);
    mit->kiadasiev = uj->kiadasiev;

    free(uj);   //végén felszabadítom amibe csak beolvastam az új adatait a már meglévőnek

    printf("\nSikeres modositas!\n\n");
}
