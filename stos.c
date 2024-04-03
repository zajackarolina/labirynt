#include <stdio.h>
#include <stdlib.h>
#include "labirynt.h"
// tworzy nowy stos o podanym rozmiarze, alokuje pamiêæ dla tablicy wspó³rzêdnych stosu i inicjalizuje pozosta³e pola struktury stosu
stos_t* nowy_stos(unsigned rozmiar) {
    stos_t* S = (stos_t*)malloc(sizeof(stos_t));
    if (S == NULL) {
        return NULL; // B³¹d alokacji pamiêci
    }

    S->tablica = (wsp_t*)malloc(rozmiar * sizeof(wsp_t));
    if (S->tablica == NULL) {
        free(S);
        return NULL; // B³¹d alokacji pamiêci
    }

    S->rozmiar = rozmiar;
    S->wierzcholek = -1;

    return S;
}

void zwolnij_stos(stos_t* S) {
    free(S->tablica);
    free(S);
}

int stos_pusty(stos_t* S) {
    return (S->wierzcholek == -1);
}

int stos_pelny(stos_t* S) {
    return (S->wierzcholek == S->rozmiar - 1);
}
// funkcja dodaje element w na wierzcho³ek stosu, jeœli stos nie jest pe³ny
void stos_dodaj(stos_t* S, wsp_t w) {
    if (!stos_pelny(S)) {
        S->wierzcholek++; // zwieksza wierzcholek o 1 zeby dodac wartosc
        S->tablica[S->wierzcholek] = w;
    }
}
//³u¿y do usuniêcia elementu ze stosu i zwrócenia jego wartoœci
wsp_t stos_zdejmij(stos_t* S) {
    wsp_t w;
    w.w = -1; // Wartoœæ domyœlna w przypadku b³êdu

    if (!stos_pusty(S)) {
        w = S->tablica[S->wierzcholek];
        S->wierzcholek--;
    }

    return w; //wartosc zdejmowana ze stosu
}
//³u¿y do odczytania wartoœci elementu znajduj¹cego siê na szczycie stosu, bez usuwania go ze stosu
wsp_t stos_szczytowy(stos_t* S) {
    wsp_t w;
    w.w = -1; // Wartoœæ domyœlna w przypadku b³êdu

    if (!stos_pusty(S)) {
        w = S->tablica[S->wierzcholek];
    }

    return w; //zwraca w ktore jest na szczycie stosu
}

