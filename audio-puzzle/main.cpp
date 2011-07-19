// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <sdl/sdl.h>

// This is a display surface to represent the window.
SDL_Surface *screen;

SDL_Event event;

int main(int argc, char **argv)
{
	
	// Initialize SDL library for video and audio subsystems
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	// Set the video mode
	screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);

	// Set the window title
	SDL_WM_SetCaption("Simple Window", "Simple Window");

	bool done = false;

	while(!done) {
		// Wait until the window is quit
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
		}

		// Fill the screen with black color
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		// Update the screen buffer
		SDL_Flip(screen);
	}

	// Quit SDL library
	SDL_Quit();
	
	return 0;
}