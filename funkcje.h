#pragma once

#ifndef funkcje_h
#define _CRT_SECURE_NO_WARNINGS
#define funkcje_h
#define WYSOKOSC 22
#define SZEROKOSC 12
#define ROZMIAR_BLOKU 34
#define deltaTIME 30;
#define deltaPRZYSPIESZENIA 0.00015;
#define LICZNIK_ETAPU 10;


extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}


enum blok
{
	PUSTY,
	RED,
	GREY,
	PURPLE,
	CYAN,
	ORANGE,
	YELLOW,
	BLUE,
	GREEN
};


enum typKlocka
{
	I = 0,
	O = 1,
	T = 2,
	L = 3,
	J = 4,
	S = 5,
	Z = 6,
};


enum Kierunek_en
{
	RIGHT = 0,
	LEFT = 1
};


struct Plansza_str
{
	blok tab[WYSOKOSC][SZEROKOSC];
};


struct Zasoby_str
{
	SDL_Window *window;
	SDL_Surface *grey, *red, *blue, *green, *yellow, *purple, *orange, *cyan, *pauza;
	SDL_Texture *scrtex;
	SDL_Renderer *renderer;
	SDL_Surface *screen, *charset;
};


struct Klocek_str
{
	blok kolor;
	int x, y;
	bool czyWidzialny;
	blok tab[4][4];
	Kierunek_en kierunek;
};


struct Gra_str
{
	Plansza_str* plansza;
	Zasoby_str* zasoby;
	Klocek_str* klocek;
	bool ON;
	bool pauzaON;
	unsigned int czasGry;
	double przyspieszenieKlocka;
	double czasDoKolejnegoPrzysp;
	double deltaPrzyspKlocka;
	int etap;
	int licznikEtapu;
	int liczbaPunktow;
	int usunieteWiersze;
	bool mniejNiz4;
};



void automatyczniePrzyspieszaj(Gra_str* gra);
bool czyZajete(Plansza_str* plansza, int x, int y);
bool CzyKoliduje(blok tab[4][4], Plansza_str* plansza, int dx, int dy);
bool czyKoliduje(Klocek_str* klocek, Plansza_str* plansza, int dx, int dy);
bool dodajDoPlanszy(Klocek_str* klocek, Plansza_str* plansza);
void pustaPlansza(Plansza_str* plansza);
void rysujPlansze(Plansza_str* plansza, Zasoby_str* zasoby);
void rysujBlok(blok kolor, Zasoby_str* zasoby, int x, int  y);
void nowaGra(Gra_str* gra);
void nowyKlocek(Klocek_str* nowy, Plansza_str* plansza);
void rysujKlocek(Klocek_str* klocek, Zasoby_str* zasoby);
void nowyKlocek(Klocek_str* nowy, Plansza_str* plansza);
void przesunWiersz(Plansza_str* plansza_str, int yToDelete);
void sprawdzWiecejWierszy(Plansza_str* plansza);
void usunPelneWiersze(Plansza_str* plansza);
void natychmiastOpadaj(Gra_str* gra);
int laduj(Zasoby_str* zasoby);
SDL_Surface wczytajObrazek(SDL_Surface* obrazek, SDL_Surface* charset, SDL_Surface* screen, SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *scrtex, char* sciezka);
void init(Gra_str* gra);
void  rysujGre(Gra_str* gra);
void wstawPuste(blok tab[4][4]);
void generujI(Klocek_str* klocek);
void generujO(Klocek_str* klocek);
void generujT(Klocek_str* klocek);
void generujL(Klocek_str* klocek);
void generujJ(Klocek_str* klocek);
void generujS(Klocek_str* klocek);
void generujZ(Klocek_str* klocek);
void generujKlocek(Klocek_str* klocek);
void okreslajPrzesuniecie(Kierunek_en kierunek, int *dx);
bool czyRuchMozliwy(Gra_str* gra, Klocek_str* klocek, Plansza_str* plansza);
void wykonajRuch(Gra_str* gra, Kierunek_en kierunek);
void ruch(Gra_str* gra);
void obracaj(Gra_str* gra);
void pauzuj(Gra_str* gra, Zasoby_str* zasoby);
void zliczajPunkty(Gra_str* gra);
#endif