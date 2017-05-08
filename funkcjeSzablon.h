#pragma once

#ifndef funkcjeSzablon_h
#define funkcjeSzablon_h


#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	750

extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}


void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

#endif
