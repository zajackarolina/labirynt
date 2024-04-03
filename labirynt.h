

#ifndef _LABIRYNT_H_
#define _LABIRYNT_H_

#define MAXWIDTH	512

// warto�ci p�l w macierzy
typedef enum //__attribute__((__packed__)) 
{
	WOLNE = 0, ZAJETE, ODWIEDZONE
} pole_t;

// wsp�rz�dne (w,k)
// wsp�rz�dne (w,k)
typedef struct {
	int w;
	int k;   /* uzupe�ni� */
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
	unsigned int wierzcholek;/* uzupe�ni� */
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
// 'Pole' mo�e by� typu pole_t, gdy uda si� ograniczy� go do 1 bajta

#define ROZMIAR_WIERSZA	    sizeof(((Labirynt *)NULL)->Pole[0])


// procedury *obowi�zkowe*

// * przechodzi labirynt, zaczynaj�c od wsp�rz�dnych (w,k), a� dojdzie do
//   wyj�cia (kom�rka na kraw�dzi labiryntu, kt�ra nie jest �cian�)
// * zwraca stos ze wsp�rz�dnymi poszczeg�lnych krok�w
//
// * mo�e zwr�ci� NULL, gdy by� problem z alokacj�,
// * zwr�cony stos b�dzie rozmiaru 0, gdy podano z�e wsp�rz�dne {w,k}, albo
//   labirynt ma z�e w�a�ciwo�ci (np. LW==0)
// * stos bedzie pusty, gdy nie mo�na doj�� do (innego) wyj�cia
stos_t* spacer(Labirynt* L, unsigned w, unsigned k);

Labirynt* nowy_labirynt(short l_wierszy, unsigned l_kolumn);
void zwolnij_labirynt(Labirynt*);
// Funkcja zapisuje labirynt do pliku w formacie PGM
// i zwraca liczb� ca�kowit� informuj�c� o powodzeniu operacji.
int labirynt2PGM(const Labirynt* labirynt, const char* nazwaPliku);

// Funkcja generuje labirynt na podstawie pliku PGM
// i zwraca wska�nik na zaalokowan� struktur� labiryntu.
// Zwraca NULL w przypadku problem�w.
Labirynt* PGM2labirynt(const char* nazwaPliku);





// proponowane funkcje pomocnicze
// mo�na u�ywa� innych
// 
// // weryfikacja wsp�rz�dnych; ogranicze� dostarcza labirynt
// int test_krawedzi( wsp_t, Labirynt * ); // weryfikacja wsp�rz�dnych
// int test_pozycji( wsp_t, Labirynt * ); // weryfikacja wsp�rz�dnych
// int test_pola( wsp_t, Labirynt * );    // weryf. wsp�rz�dnych i warto�ci
// 
// 
// // zwraca wsp�rz�dne pierwszego punktu, spe�niaj�cego wymagania, 
// // albo {-1,-1}, gdy takiego nie ma
// // wymagania: punkt oddalony o 1 od zadanego, w kierunku N,W,S,E,
// // wskazane przez niego pole jest WOLNE
// wsp_t mozliwy_krok( wsp_t, Labirynt * );
// 
// // * modyfikuje stos przed dodanie lub usuni�cie jednego elementu
// //   modyfikuje labirynt zamieniaj�c WOLNE na ODWIEDZONE
// // * operacja odpowiada wykonaniu jednego ruchu w labiryncie
// // * za�o�enie: stos nie jest pusty, L i S wskazuj� na struktury
// void nastepny_krok( Labirynt * L, stos_t * S );


//--**----------------------------------------------------------------------
//  I/O
//  miejsce na deklacj� funkcji do odczytu/zapisu plik�w PGM

// opcja: definicja kod�w i komunikat�w b��d�w
// extern int IOerrCode;
// extern char * IOerr[];



//--**----------------------------------------------------------------------





#endif	//_LABIRYNT_H_