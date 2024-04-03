#include"labirynt.h"
#include <stdio.h>
#include <stdlib.h>

//tworzy plik graficzny w formatu pgm ktorybedziereprezentowal labirynt
//Plik graficzny będzie zawierał trzy poziomy szarości odpowiadające wartościom pól labiryntu: wolne pole, zajęte pole i odwiedzone pole

int labirynt2PGM(const Labirynt* labirynt, const char* nazwaPliku) {
    FILE* plik = fopen(labirynt, "wb");
    if (plik == NULL) {
        return 1; 
    }

    fprintf(plik, "P5\n");
    fprintf(plik, "%d %d\n", labirynt->LK, labirynt->LW);
    fprintf(plik, "255\n");

    for (int w = 0; w < labirynt->LW; w++) {
        for (int k = 0; k < labirynt->LK; k++) {
            unsigned char pixel;
            switch (labirynt->Pole[w][k]) {
            case WOLNE:
                pixel = 0;
                break;
            case ZAJETE:
                pixel = 127;
                break;
            case ODWIEDZONE:
                pixel = 255;
                break;
            default:
                pixel = 0;
            }
            fwrite(&pixel, sizeof(unsigned char), 1, plik);
        }
    }

    fclose(plik);
    return 0; 
}

//funkcja ta odczytuje plik w formacie pgm i generuje struktuure labirynt
// Funkcja zwraca wskaźnik na zaalokowaną strukturę Labirynt lub NULL w przypadku problemó
Labirynt* PGM2labirynt(const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "rb");
    if (plik == NULL) {
        return NULL; // Błąd otwarcia pliku
    }

    char magic[3];
    unsigned short LK, LW;
    int maxVal;
    fscanf(plik, "%2s %hu %hu %d", magic, &LK, &LW, &maxVal);
    // nie jest ignorowana bo nastepny warunek sprawdza
    if (magic[0] != 'P' || magic[1] != '5' || maxVal != 255) {
        fclose(plik);
        return NULL; 
    }

    Labirynt* labirynt = (Labirynt*)malloc(sizeof(Labirynt));
    if (labirynt == NULL) {
        fclose(plik);
        return NULL; 
    }

    labirynt->LK = LK;
    labirynt->LW = LW;

    for (int w = 0; w < LW; w++) {
        for (int k = 0; k < LK; k++) {
            unsigned char pixel;
            fread(&pixel, sizeof(unsigned char), 1, plik);
            if (pixel % 2 == 0) {
                labirynt->Pole[w][k] = WOLNE;
            }
            else {
                labirynt->Pole[w][k] = ZAJETE;
            }
        }
    }

    fclose(plik);
    return labirynt;
}
//wejscieW i wejscieK TO wskaźnikami do zmiennych, do których funkcja znajdzWejscie przypisuje znalezione współrzędne wejścia do labiryntu
//Wkolumnie lub wierszu moze byc wejscie
void znajdzWejscie(Labirynt* labirynt, int* wejscieW, int* wejscieK) {
    int w, k;
    for (w = 0; w < labirynt->LW; w++) {
        if (labirynt->Pole[w][0] == WOLNE) {
            *wejscieW = w;
            *wejscieK = 0;
            return;
        }
        if (labirynt->Pole[w][labirynt->LK - 1] == WOLNE) {
            *wejscieW = w;
            *wejscieK = labirynt->LK - 1;
            return;
        }
    }

    for (k = 0; k < labirynt->LK; k++) {
        if (labirynt->Pole[0][k] == WOLNE) {
            *wejscieW = 0;
            *wejscieK = k;
            return;
        }
        if (labirynt->Pole[labirynt->LW - 1][k] == WOLNE) {
            *wejscieW = labirynt->LW - 1;
            *wejscieK = k;
            return;
        }
    }

    //Jeśli nie znaleziono wejścia
    *wejscieW = -1;
    *wejscieK = -1;
}

stos_t* spacer(Labirynt* labirynt, int w, int k) {
    if (labirynt == NULL || labirynt->LW == 0 || labirynt->LK == 0) {
        return NULL; // Labirynt ma złe właściwości
    }

    if (w < 0 || w >= labirynt->LW || k < 0 || k >= labirynt->LK) {
        return nowy_stos(0); // Złe współrzędne początkowe, zwróć pusty stos
    }

    stos_t* stos = nowy_stos(labirynt->LW * labirynt->LK);
    if (stos == NULL) {
        return NULL; // Błąd alokacji stosu
    }

    wsp_t aktualna = { w, k };
    wsp_t sasiad;
    stos_dodaj(stos, aktualna);

    while (!stos_pusty(stos)) {
        aktualna = stos_zdejmij(stos);
        w = aktualna.w;
        k = aktualna.k;

        if (labirynt->Pole[w][k] == ODWIEDZONE) {
            continue;
        }

       labirynt->Pole[w][k] = ODWIEDZONE;   

        if (w == 0 || w == labirynt->LW - 1 || k == 0 || k == labirynt->LK - 1) {
            return stos;
        }

        if (w - 1 >= 0 && labirynt->Pole[w - 1][k] == WOLNE) {
            sasiad.w = w - 1;
            sasiad.k = k;
            stos_dodaj(stos, sasiad);
        }
        if (w + 1 < labirynt->LW && labirynt->Pole[w + 1][k] == WOLNE) {
            sasiad.w = w + 1;
            sasiad.k = k;
            stos_dodaj(stos, sasiad);
        }
        if (k - 1 >= 0 && labirynt->Pole[w][k - 1] == WOLNE) {
            sasiad.w = w;
            sasiad.k = k - 1;
            stos_dodaj(stos, sasiad);
        }
        if (k + 1 < labirynt->LK && labirynt->Pole[w][k + 1] == WOLNE) {
            sasiad.w = w;
            sasiad.k = k + 1;
            stos_dodaj(stos, sasiad);
        }
    }

    return nowy_stos(0); 
}
Labirynt* nowy_labirynt(short l_wierszy, unsigned l_kolumn) {
    if (l_wierszy <= 0 || l_kolumn == 0) {
        return NULL; 
    }

    Labirynt* labirynt = (Labirynt*)malloc(sizeof(Labirynt));
    if (labirynt == NULL) {
        return NULL; 
    }

    labirynt->LW = l_wierszy;
    labirynt->LK = l_kolumn;

    return labirynt;
}
//funkcja zwalnia labirynt
void zwolnij_labirynt(Labirynt* labirynt) {
    if (labirynt != NULL) {
        free(labirynt);
    }
}

/*int main() {
    const char* plikWejsciowy = "labirynt.pgm";
    const char* plikWyjsciowy = "labirynt_wynik.pgm";

    // Wczytaj labirynt z pliku PGM
    Labirynt* labirynt = PGM2labirynt(plikWejsciowy);
    if (labirynt == NULL) {
        printf("Błąd wczytywania labiryntu z pliku.\n");
        return 1;
    }

    int wejscieW, wejscieK;
    znajdzWejscie(labirynt, &wejscieW, &wejscieK);
    if (wejscieW == -1 || wejscieK == -1) {
        printf("Nie znaleziono wejścia do labiryntu.\n");
        free(labirynt);
        return 1;
    }

    if (!spacer(labirynt, wejscieW, wejscieK)) {
        printf("Nie udało się przejść labiryntu.\n"); 
    }

    // Zapisz labirynt z odwiedzonymi komórkami do pliku PGM
    if (labirynt2PGM(labirynt, plikWyjsciowy) != 0) {
        printf("Błąd zapisu labiryntu do pliku.\n");
    }

    free(labirynt);
    printf("Program zakończony.\n");

    return 0;
}*/
stos_t* przejdzLabirynt(Labirynt* labirynt) {
    int wejscieW, wejscieK;
    znajdzWejscie(labirynt, &wejscieW, &wejscieK);

    if (wejscieW == -1 && wejscieK == -1) {
        return NULL;
    }

    stos_t* stos = nowy_stos(labirynt->LW * labirynt->LK);
    if (stos == NULL) {
        return NULL;
    }

    wsp_t aktualna = { wejscieW, wejscieK };
    wsp_t sasiad;
    stos_dodaj(stos, aktualna);

    while (!stos_pusty(stos)) {
        aktualna = stos_zdejmij(stos);
        int w = aktualna.w;
        int k = aktualna.k;

        if (labirynt->Pole[w][k] == ODWIEDZONE) {
            continue;
        }

        labirynt->Pole[w][k] = ODWIEDZONE;

        if (w == 0 || w == labirynt->LW - 1 || k == 0 || k == labirynt->LK - 1) {
            // Udało się przejść labirynt
            return stos;
        }

        // Sprawdź sąsiadów
        if (w - 1 >= 0 && labirynt->Pole[w - 1][k] == WOLNE) {
            sasiad.w = w - 1;
            sasiad.k = k;
            stos_dodaj(stos, sasiad);
        }
        if (w + 1 < labirynt->LW && labirynt->Pole[w + 1][k] == WOLNE) {
            sasiad.w = w + 1;
            sasiad.k = k;
            stos_dodaj(stos, sasiad);
        }
        if (k - 1 >= 0 && labirynt->Pole[w][k - 1] == WOLNE) {
            sasiad.w = w;
            sasiad.k = k - 1;
            stos_dodaj(stos, sasiad);
        }
        if (k + 1 < labirynt->LK && labirynt->Pole[w][k + 1] == WOLNE) {
            sasiad.w = w;
            sasiad.k = k + 1;
            stos_dodaj(stos, sasiad);
        }
    }

    // Nie można dojść do wyjścia
    return NULL;
}




