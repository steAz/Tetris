#define _CRT_SECURE_NO_WARNINGS
#include "funkcje.h"
#include "funkcjeSzablon.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
#include <time.h>
#include <stdlib.h>


extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}



void wstawPuste(blok tab[4][4]) 
{
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			tab[y][x] = PUSTY;
		}
	}
}


void generujO(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if ((y == 1 && (x == 1 || x == 2)) || (y == 2 && (x == 1 || x == 2)))
			{
				klocek->tab[y][x] = CYAN;
			}
		}
	}
}


void generujI(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if (x = 1)
			{
				klocek->tab[y][x] = RED;
			}
		}
	}
}


void generujT(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (y == 1 || (y == 2 && x == 1))
			{
				klocek->tab[y][x] = ORANGE;
			}
		}
	}
}


void generujL(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (x == 1 || (y == 2 && x == 2))
			{
				klocek->tab[y][x] = YELLOW;
			}
		}
	}
}


void generujJ(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (x == 2 || (y == 2 && x == 1))
			{
				klocek->tab[y][x] = PURPLE;
			}
		}
	}
}


void generujS(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 3; y++)
	{
		for (int x=0; x < 4; x++)
		{
			if ((y == 2 && (x == 1 || x == 2)) || (y == 1 && (x == 2 || x == 3)))
			{
				klocek->tab[y][x] = BLUE;
			}
		}
	}
}


void generujZ(Klocek_str* klocek)
{
	wstawPuste(klocek->tab);

	for (int y = 0; y < 3; y++)
	{
		for (int x=0; x < 3; x++)
		{
			if ((y == 1 && (x == 0 || x == 1)) || (y == 2 & (x == 1 || x == 2)))
			{
				klocek->tab[y][x] = GREEN;
			}
		}
	}
}


int wczytajObrazek(SDL_Surface** obrazek, Zasoby_str* zasoby, char* sciezka)
{
	*obrazek = SDL_LoadBMP(sciezka);

	if (*obrazek == NULL) 
	{
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(zasoby->charset);
		SDL_FreeSurface(zasoby->screen);
		SDL_DestroyTexture(zasoby->scrtex);
		SDL_DestroyWindow(zasoby->window);
		SDL_DestroyRenderer(zasoby->renderer);
		SDL_Quit();
		return 1;
	};

	return 0;
}


void rysujBlok(blok kolor, Zasoby_str* zasoby, int x, int  y)
{
	int xStart = 30;
	int yStart = SCREEN_HEIGHT / 2 - WYSOKOSC*ROZMIAR_BLOKU / 2 + 20;
	SDL_Surface* wybrany = NULL;

	switch (kolor)
	{
	case PUSTY:
		break;

	case RED:
		wybrany = zasoby->red;
		break;

	case GREY:
		wybrany= zasoby->grey;
		break;

	case PURPLE:
		wybrany = zasoby->purple;
		break;

	case GREEN:
		wybrany = zasoby->green;
		break;

	case BLUE:
		wybrany = zasoby->blue;
		break;

	case YELLOW:
		wybrany = zasoby->yellow;
		break;

	case CYAN:
		wybrany = zasoby->cyan;
		break;

	case ORANGE:
		wybrany = zasoby->orange;
		break;

	default:
		break;
	}
	
	
	if (wybrany != NULL)
		DrawSurface(zasoby->screen, wybrany, xStart + ROZMIAR_BLOKU*x, yStart + ROZMIAR_BLOKU*y);
}


void rysujPlansze(Plansza_str* plansza, Zasoby_str* zasoby)
{
	for (int y = 0; y < WYSOKOSC; y++)
	{
		for (int x = 0; x < SZEROKOSC; x++)
			rysujBlok(plansza->tab[y][x], zasoby, x, y);
	}
}


void init(Gra_str* gra)   //WYPELNIENIE PLANSZY PUSTA I USTAWIENIE GRY NA WYLACZONA
{
	gra->klocek->czyWidzialny = false;
	pustaPlansza(gra->plansza);
}


void pustaPlansza(Plansza_str* plansza)
{
	for (int y = 0; y < WYSOKOSC; y++)
	{
		for (int x = 0; x < SZEROKOSC; x++)
		{
			if ((y > 0 && y < WYSOKOSC - 1) && (x > 0 && x < SZEROKOSC - 1))
			{
				plansza->tab[y][x] = PUSTY;
			}
			else
			{
				plansza->tab[y][x] = GREY;
			}
		}
	}
}


bool czyZajete(Plansza_str* plansza, int x, int y)
{
	return (y > 0 && plansza->tab[y][x] != PUSTY);
}


int laduj(Zasoby_str* zasoby)  //jesli obrazek nie bedzie mozliwy do wczytania zwroc 1 ( wartosc inna niz 0 w zwracaniu funkcji bedzie bledem )
{
	if (wczytajObrazek(&(zasoby->red), zasoby, "./red.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->grey), zasoby, "./grey.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->green), zasoby, "./green.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->cyan), zasoby, "./cyan.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->purple), zasoby, "./purple.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->yellow), zasoby, "./yellow.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->orange), zasoby, "./orange.bmp") == 1)
		return 1;
	if (wczytajObrazek(&(zasoby->blue), zasoby, "./blue.bmp") == 1)
		return 1;

	return 0;
}


void generujKlocek(Klocek_str* klocek)
{
	int losuj;
	srand(time(NULL));
	losuj = rand() % 7;

	if (losuj == I)
	{
		generujI(klocek);
	}

	else if (losuj == O)
	{
		generujO(klocek);
	}

	else if (losuj == T)
	{
		generujT(klocek);
	}

	else if (losuj == L)
	{
		generujL(klocek);
	}

	else if (losuj == J)
	{
		generujJ(klocek);
	}

	else if (losuj == S)
	{
		generujS(klocek);
	}

	else if (losuj == Z)
	{
		generujZ(klocek);
	}
}


void nowyKlocek(Klocek_str* nowy, Plansza_str* plansza)  //funkcja wyprowadzajaca nowy klocek z gory planszy po kolizji poprzedniego z innymi
{
	generujKlocek(nowy);      
	nowy->x = 5;              //OKRESLENIE STARTOWYCH WSPOLRZEDNYCH NOWEGO KLOCKA
	nowy->y = -1;
	nowy->czyWidzialny = true;
}


void nowaGra(Gra_str* gra)
{
	pustaPlansza(gra->plansza);
	gra->ON = true;
	gra->pauzaON = false;
	nowyKlocek(gra->klocek, gra->plansza);
	gra->przyspieszenieKlocka = 0.0012;         //POCZATKOWE PRZYSPIESZENIE KLOCKA,
	gra->czasDoKolejnegoPrzysp = deltaTIME;  //CZAS DO KOLEJNEGO PRZYSPIESZENIA, 
	gra->licznikEtapu = 10;
	gra->etap = 0;   // , ZACZYNAMY W ETAPIE ZEROWYM
	gra->liczbaPunktow = 0;
	gra->usunieteWiersze = 0;
	gra->mniejNiz4 = true;          //ustawiamy boola na true, zeby na starcie gry zliczal pierwszy wariant zliczania pkt w momencie usuwania 4 wierszy
}


bool czyKoliduje(blok tab[4][4], Plansza_str* plansza, int dx, int dy)
{
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++)
		{
			if (tab[y][x] != PUSTY && czyZajete(plansza, x + dx, y + dy))  //jesli w tablicy klocka dany kwadrat jest zapelniony i na planszy w odleglosci dx i dy jest zajete pole, to wtedy koliduje (true)
				return true;
		}
	}
	return false;
}


bool czyKoliduje(Klocek_str* klocek, Plansza_str* plansza, int dx, int dy)
{
	return czyKoliduje(klocek->tab, plansza, klocek->x + dx, klocek->y + dy);
}


void natychmiastOpadaj(Gra_str* gra)
{
	for (int h = 1; h < WYSOKOSC - 1; h++)
	{
		if (czyKoliduje(gra->klocek, gra->plansza, 0, h))  // jesli kolidujacy kwadrat jest w odleglosci h w dol od danego spadajacego klocka, to :
		{
			gra->klocek->y = gra->klocek->y + h - 1; // przesun klocek o dana wysokosc h pomniejszona o 1, zeby klocek nie wbil sie w kolidujacy kwadrat i przerwij petle, zeby na nowo zliczac kolejna wysokosc 
			break; 
		}
	}
}


bool dodajDoPlanszy(Klocek_str* klocek, Plansza_str* plansza)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (klocek->tab[y][x] != PUSTY)
			{
				if (klocek->y + y < 1)  //Jesli klocek osiagnal juz maksymalne górne pole planszy, czyli 1 (wspolrzednia y od 1 mniejsza wykracza poza plansze), to nie wstawiaj juz nowych klockow
				{
					return false;
				}

				plansza->tab[klocek->y + y][klocek->x + x] = klocek->tab[y][x];  // x+x i y+y , bo jak dany klocek juz spadnie, to musi byc narysowany caly taki jaki spadal, czyli sprawdzamy wszystkie mozliwe x i y obok
			}
		}
	}

	klocek->czyWidzialny = false;  // ustawiamy klocek jako niewidzialny, bo wtedy bedziemy mogli dodac nowy klocek funkcj¹ nowyKlocek

	return true;
}


void przesunWiersz(Gra_str* gra, int yToDelete)
{
	for (int y = yToDelete; y > 1; y--)
	{
		for (int x = 1; x < SZEROKOSC; x++)
		{
			gra->plansza->tab[y][x] = gra->plansza->tab[y - 1][x];
		}
	}
}


void sprawdzWiecejWierszy(Gra_str* gra)  // funkcja przechodzaca przez wszystkie pola planszy oprocz gornej i dolnej krawedzi w celu wyszukania wiecej ilosci zapelnionych wierszy
{
	int iterator = 0;
	while (iterator < WYSOKOSC - 1)  // ustawiona WYSOKOSC-1, bo wspolrzedna y nie musi isc dalej niz gorna krawedz
	{
		for (int y = WYSOKOSC - 2; y > 1; y--)
		{
			int x;
			for (x = 1; x < SZEROKOSC; x++)
			{
				if (gra->plansza->tab[y][x] == PUSTY)
				{
					break;
				}
			}

			if (x == SZEROKOSC)
			{
				gra->usunieteWiersze += 1;
				przesunWiersz(gra, y);
			}
		}

		iterator++;
	}
}


void usunPelneWiersze(Gra_str* gra)
{
	for (int y = WYSOKOSC - 2; y > 1; y--)   //Zaczyna przechodzic po calej planszy od pozycji (y=WYSOKOSC-2;x=1) czyli w lewym dolnym rogu w celu sprawdzania wierszy
	{
		int x;
		for (x = 1; x < SZEROKOSC; x++)
		{
			if (gra->plansza->tab[y][x] == PUSTY)  //jesli punkt na planszy najdzie na puste pole  -> to znaczy, ze w tym wierszu nie ma pelnych wierszy i mozna przerwac szukanie (petle)
			{
				break;
			}
		}

		if (x == SZEROKOSC)
		{
			gra->usunieteWiersze += 1;        
			przesunWiersz(gra, y);
			sprawdzWiecejWierszy(gra);
		}
	}
}


void zliczajPunkty(Gra_str* gra)
{
	if (gra->usunieteWiersze == 1)
	{
		gra->liczbaPunktow += 100 * (gra->etap + 1);
		gra->mniejNiz4 = true;
	}

	else if (gra->usunieteWiersze == 2)
	{
		gra->liczbaPunktow += 200 * (gra->etap + 1);
		gra->mniejNiz4 = true;
	}

	else if (gra->usunieteWiersze == 3)
	{
		gra->liczbaPunktow += 400 * (gra->etap + 1);
		gra->mniejNiz4 = true;
	}

	else if (gra->usunieteWiersze == 4 && gra->mniejNiz4)      
	{
		gra->liczbaPunktow += 800 * (gra->etap + 1);
		gra->mniejNiz4 = false;          // teraz bool ustawiony jest na false, zeby kolejne usuniecie 4 wierszy dalo nam punktacje taka jak jest ponizej
	}

	else if (gra->usunieteWiersze == 4 && !gra->mniejNiz4)
	{
		gra->liczbaPunktow += 1200 * (gra->etap + 1);
	}
}


bool czyRuchMozliwy(Gra_str* gra, Klocek_str* klocek, Plansza_str* plansza)
{
	if (!klocek->czyWidzialny)  // jesli zaznal kolizji, czyli nie jest juz widzialny
	{
		usunPelneWiersze(gra);
		nowyKlocek(klocek, plansza);
		zliczajPunkty(gra);
		gra->usunieteWiersze = 0;          //po kazdym zliczeniu pkt, zerujemy aktualnie usuniete wiersze, zeby pozniej zliczac inne mozliwe warianty
	}

	if (czyKoliduje(klocek, plansza, 0, 1))  //jesli koliduje ( 0, 1 bo przy x nie sprawdza bokow, a przy y sprawdza czy jest o jeden nizej na dole juz jakis klocek )
	{
		
		return dodajDoPlanszy(klocek, plansza);
	}

	else 
	{
		klocek->y += 1;  // ruszaj sie spadajac o jeden klocek w dol
	}

	return true;
}


void okreslajPrzesuniecie(Kierunek_en kierunek, int *dx)
{
	switch (kierunek)
	{
	case RIGHT:
		*dx = 1;
		break;

	case LEFT:
		*dx = -1;
		break;
	}
}


void pauzuj(Gra_str* gra, Zasoby_str* zasoby)
{
	if (!gra->pauzaON)  
	{
		gra->pauzaON = true;
	}

	else if (gra->pauzaON)
	{
		gra->pauzaON = false;
	}
}


void obracaj(Gra_str* gra)
{
	Klocek_str* klocek = gra->klocek;
	blok buffor[4][4];

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			buffor[x][3 - y] = klocek->tab[y][x];  //zmienione buforowe indeksy dostaja klockowe wspolrzedne
		}
	}

	if (!czyKoliduje(buffor, gra->plansza, klocek->x, klocek->y) && (gra->klocek->y > 0))  //jesli nie koliduje i jest na planszy ( plansza zaczyna sie od y=1), to pozwalaj na obrot
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				klocek->tab[y][x] = buffor[y][x]; // jesli klocek nie koliduje, to dostaje wczesniej wypelnione wspolrzedne bufora
			}
		}
	}
}


void wykonajRuch(Gra_str* gra,Kierunek_en kierunek)
{
	int dx = 0;
	okreslajPrzesuniecie(kierunek, &dx);

	if (!czyKoliduje(gra->klocek, gra->plansza, dx, 0) && (gra->klocek->y > 0))  //jesli nie koliduje i jest na planszy ( plansza zaczyna sie od y=1), to pozwalaj na ruch w lewo badz prawo
	{
		gra->klocek->x += dx;
	}
}


void rysujKlocek(Klocek_str* klocek,Zasoby_str* zasoby)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (klocek->y + y > 0 && klocek->tab[y][x] != PUSTY)
				rysujBlok(klocek->tab[y][x], zasoby, klocek->x + x, klocek->y + y); // x+x i y+y , bo podczas spadania dany klocek musi byc rysowany caly czas
		}
	}
}


void automatyczniePrzyspieszaj(Gra_str* gra)
{
	gra->czasDoKolejnegoPrzysp = deltaTIME;

	if (gra->etap < gra->licznikEtapu && gra->ON)
	{
		gra->etap += 1;
		gra->przyspieszenieKlocka += deltaPRZYSPIESZENIA;
	}

	
}


void rysujGre(Gra_str* gra)
{
	Zasoby_str* zasoby = gra->zasoby;
	Klocek_str* klocek = gra->klocek;
	Plansza_str* plansza = gra->plansza;

	if (klocek->czyWidzialny)
	{
		rysujKlocek(klocek, zasoby);
	}
		
	rysujPlansze(gra->plansza, zasoby);
}


void ruch(Gra_str* gra)
{
	if (gra->ON && !gra->pauzaON)  //jesli gra jest wlaczona i pauza jest wylaczona, to pozwalaj na ruch  
	{
		if (!czyRuchMozliwy(gra, gra->klocek, gra->plansza))  //jesli ruch nie jest mozliwy , to wylacz gre 
		{
			gra->ON = false;             
		}
	}
}


