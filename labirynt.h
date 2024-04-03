

#ifndef _LABIRYNT_H_
#define _LABIRYNT_H_

#define MAXWIDTH	512

// wartoœci pól w macierzy
typedef enum //__attribute__((__packed__)) 
{
	WOLNE = 0, ZAJETE, ODWIEDZONE
} pole_t;

// wspó³rzêdne (w,k)
// wspó³rzêdne (w,k)
typedef struct {
	int w;
	int k;   /* uzupe³niæ */
} wsp_t;


typedef struct _labirynt {
	unsigned short LW, LK;
	char /*pole_t*/ Pole[][MAXWIDTH];
} Labirynt;

int labirynt2PGM(const Labirynt* labirynt, const char* nazwaPliku);
Labirynt* PGM2labirynt(const char* nazwaPliku);

//--**---stos dla struktur wsp_t--------------------------------------------
// 
typedef struct {
	wsp_t* tablica;
	unsigned int rozmiar;
	unsigned int wierzcholek;/* uzupe³niæ */
} stos_t;

stos_t* nowy_stos(unsigned rozmiar);
void zwolnij_stos(stos_t* S);

// testy
int stos_pusty(stos_t* S);
int stos_pelny(stos_t* S);

// modyfikowanie stosu
void stos_dodaj(stos_t* S, wsp_t w);
wsp_t stos_zdejmij(stos_t* S);
// odczytuje szczyt, ale go nie pobiera
wsp_t stos_szczytowy(stos_t* S);
//--**----------------------------------------------------------------------






//--**---reprezentacja labiryntu--------------------------------------------
// 'Pole' mo¿e byæ typu pole_t, gdy uda siê ograniczyæ go do 1 bajta

#define ROZMIAR_WIERSZA	    sizeof(((Labirynt *)NULL)->Pole[0])


// procedury *obowi¹zkowe*

// * przechodzi labirynt, zaczynaj¹c od wspó³rzêdnych (w,k), a¿ dojdzie do
//   wyjœcia (komórka na krawêdzi labiryntu, która nie jest œcian¹)
// * zwraca stos ze wspó³rzêdnymi poszczególnych kroków
//
// * mo¿e zwróciæ NULL, gdy by³ problem z alokacj¹,
// * zwrócony stos bêdzie rozmiaru 0, gdy podano z³e wspó³rzêdne {w,k}, albo
//   labirynt ma z³e w³aœciwoœci (np. LW==0)
// * stos bedzie pusty, gdy nie mo¿na dojœæ do (innego) wyjœcia
stos_t* spacer(Labirynt* L, unsigned w, unsigned k);

Labirynt* nowy_labirynt(short l_wierszy, unsigned l_kolumn);
void zwolnij_labirynt(Labirynt*);
// Funkcja zapisuje labirynt do pliku w formacie PGM
// i zwraca liczbê ca³kowit¹ informuj¹c¹ o powodzeniu operacji.
int labirynt2PGM(const Labirynt* labirynt, const char* nazwaPliku);

// Funkcja generuje labirynt na podstawie pliku PGM
// i zwraca wskaŸnik na zaalokowan¹ strukturê labiryntu.
// Zwraca NULL w przypadku problemów.
Labirynt* PGM2labirynt(const char* nazwaPliku);





// proponowane funkcje pomocnicze
// mo¿na u¿ywaæ innych
// 
// // weryfikacja wspó³rzêdnych; ograniczeñ dostarcza labirynt
// int test_krawedzi( wsp_t, Labirynt * ); // weryfikacja wspó³rzêdnych
// int test_pozycji( wsp_t, Labirynt * ); // weryfikacja wspó³rzêdnych
// int test_pola( wsp_t, Labirynt * );    // weryf. wspó³rzêdnych i wartoœci
// 
// 
// // zwraca wspó³rzêdne pierwszego punktu, spe³niaj¹cego wymagania, 
// // albo {-1,-1}, gdy takiego nie ma
// // wymagania: punkt oddalony o 1 od zadanego, w kierunku N,W,S,E,
// // wskazane przez niego pole jest WOLNE
// wsp_t mozliwy_krok( wsp_t, Labirynt * );
// 
// // * modyfikuje stos przed dodanie lub usuniêcie jednego elementu
// //   modyfikuje labirynt zamieniaj¹c WOLNE na ODWIEDZONE
// // * operacja odpowiada wykonaniu jednego ruchu w labiryncie
// // * za³o¿enie: stos nie jest pusty, L i S wskazuj¹ na struktury
// void nastepny_krok( Labirynt * L, stos_t * S );


//--**----------------------------------------------------------------------
//  I/O
//  miejsce na deklacjê funkcji do odczytu/zapisu plików PGM

// opcja: definicja kodów i komunikatów b³êdów
// extern int IOerrCode;
// extern char * IOerr[];



//--**----------------------------------------------------------------------





#endif	//_LABIRYNT_H_