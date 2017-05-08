#define _USE_MATH_DEFINES
#include<math.h>
#include "funkcjeSzablon.h"
#include "funkcje.h"
#include<stdio.h>
#include<string.h>
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





// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) 
{
	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface *eti;
	Zasoby_str zasoby;
	Plansza_str plansza;
	Klocek_str klocek;
	Gra_str gra;
	gra.zasoby = &zasoby;
	gra.plansza = &plansza;
	gra.klocek = &klocek;
	gra.ON = false; //GRA JEST NA POCZATKU WYLACZONA    
	gra.pauzaON = false;
	gra.czasDoKolejnegoPrzysp = 0;    // Przed wlaczeniem gry czas do kolejnego etapu jest wyzerowany
        


	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe³noekranowy
	//rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,&zasoby.window, &zasoby.renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,  &zasoby.window, &zasoby.renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(zasoby.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(zasoby.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(zasoby.window, "Tetris - Projekt II (PP 2015), Michal Kazanowski");

	zasoby.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	zasoby.scrtex = SDL_CreateTexture(zasoby.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	zasoby.charset = SDL_LoadBMP("./cs8x8.bmp");
	if(zasoby.charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(zasoby.screen);
		SDL_DestroyTexture(zasoby.scrtex);
		SDL_DestroyWindow(zasoby.window);
		SDL_DestroyRenderer(zasoby.renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(zasoby.charset, true, 0x000000);


	eti = SDL_LoadBMP("./eti.bmp");
	if (laduj(&zasoby) == 1) return 1;
	 
	init(&gra);                                                   //WYPELNIENIE PLANSZY PUSTA I USTAWIENIE KLOCKA JAKO NIEWIDZIALNEGO 
	

	char text[128];
	int czarny = SDL_MapRGB(zasoby.screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(zasoby.screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(zasoby.screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(zasoby.screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	distance = 0;
	etiSpeed = 1;
	worldTime = 0;
	
	

	do 
	{
		t2 = SDL_GetTicks();

		
		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		
	delta = (t2 - t1) * gra.przyspieszenieKlocka;

		if (delta > 0.5)   
		{
			t1 = t2;
			worldTime += delta;

			ruch(&gra);                                                        //RUCH KLOCKA
		}

		if (gra.ON && !gra.pauzaON)   
		{
			gra.czasDoKolejnegoPrzysp -= 0.001;      // czasDoKolejnegoPrzyspieszenia okreslany jest w milisekundach, wiec jesli bedziemy odejmowac 0.001 milisekundy to bedzie sie nam czas przesuwal w sekundach
		}

		if (gra.czasDoKolejnegoPrzysp < 0 && gra.czasDoKolejnegoPrzysp >-0.001)           // JESLI czasDoKolejnegoPrzyspieszenia minie, czyli bedzie wynosil 0, to
		{
			gra.czasDoKolejnegoPrzysp = deltaTIME;     // ustaw znow czasDoKolejnegoPrzyspieszenia na dany czas deltaTIME
                    
			                                           
			if (gra.etap < gra.licznikEtapu && gra.ON)                         // JESLI ETAP NIE OSIAGNAL JESZCZE WARTOSCI LICZNIKA ETAPU I GRA JEST WLACZONA, TO 
			{
				gra.etap += 1;                                              // ZWIEKSZAJ ETAP TYLKO DO MAKYMALNEGO MOZLIWEGO ETAPU
				gra.przyspieszenieKlocka += deltaPRZYSPIESZENIA;            // przyspieszenie zwieksz o dana deltePrzyspieszenia
			}
		}
	

		distance += etiSpeed * delta;

		SDL_FillRect(zasoby.screen, NULL, czarny);

		rysujGre(&gra);                                               
		

		

//	DrawScreen(screen, plane, ship, charset, worldTime, delta, vertSpeed);

		// naniesienie wyniku rysowania na rzeczywisty ekran
//		SDL_Flip(screen);

		fpsTimer += delta;
		if(fpsTimer > 0.5) 
		{
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
			};
		

		// WYSWIETLENIE CZASU DO KOLEJNEGO PRZYSPIESZENIA I DANEGO ETAPU GRY
		sprintf(text, "Zwiekszenie przyspieszenia za  %.1lf ", gra.czasDoKolejnegoPrzysp);           
		DrawString(zasoby.screen, 450, 10, text, zasoby.charset);

		sprintf(text, "Aktualne przyspieszenie = %.5lf ", gra.przyspieszenieKlocka);
		DrawString(zasoby.screen, 450, 30, text, zasoby.charset);

		sprintf(text, "Dany etap = %.i ", gra.etap);          
		DrawString(zasoby.screen, 450, 50, text, zasoby.charset);

		sprintf(text, "Aktualna liczba punktow = %.i ", gra.liczbaPunktow);
		DrawString(zasoby.screen, 450, 70, text, zasoby.charset);


		if (gra.pauzaON)        
		{
			sprintf(text, "!PAUZA WLACZONA!");
			DrawString(zasoby.screen, 55, 55, text, zasoby.charset);
		}
		

		SDL_UpdateTexture(zasoby.scrtex, NULL, zasoby.screen->pixels, zasoby.screen->pitch);
//		SDL_RenderClear(renderer);
		SDL_RenderCopy(zasoby.renderer, zasoby.scrtex, NULL, NULL);
		SDL_RenderPresent(zasoby.renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y)
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_n) nowaGra(&gra);       
					else if (event.key.keysym.sym == SDLK_p) pauzuj(&gra, &zasoby);
				/*	else if(event.key.keysym.sym == SDLK_UP) etiSpeed = 2.0; */
				/*	else if(event.key.keysym.sym == SDLK_DOWN) etiSpeed = 0.3;  */
					if (!gra.pauzaON)  // JESTLI GRA JEST WLACZONA, TO TYLKO WTEDY MOZNA UZYWAC NIZEJ DANE PRZYCISKI
					{
					if (event.key.keysym.sym == SDLK_RIGHT) wykonajRuch(&gra, RIGHT);
					else if (event.key.keysym.sym == SDLK_LEFT) wykonajRuch(&gra, LEFT);
					else if (event.key.keysym.sym == SDLK_SPACE) obracaj(&gra);   //obracanie przy wcisnieciu spacji
					else if (event.key.keysym.sym == SDLK_UP) obracaj(&gra);        //obracanie przy wcisnieciu klawisza do gory
					else if (event.key.keysym.sym == SDLK_DOWN) natychmiastOpadaj(&gra);
					else if (event.key.keysym.sym == SDLK_s) automatyczniePrzyspieszaj(&gra);
					}
					
					break;

				case SDL_KEYUP:
					etiSpeed = 1.0;
					break; 
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		frames++;
		}while (!quit);

	// zwolnienie powierzchni
	SDL_FreeSurface(zasoby.charset);
	SDL_FreeSurface(zasoby.screen);
	SDL_DestroyTexture(zasoby.scrtex);
	SDL_DestroyRenderer(zasoby.renderer);
	SDL_DestroyWindow(zasoby.window);

	SDL_Quit();
	return 0;
	};
