// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <sdl/sdl.h>
#include <sdl/SDL_image.h>
#include <sdl/SDL_audio.h>
#include "audio.h"


// This is a display surface to represent the window.
SDL_Surface *screen;

SDL_Event event;

int main(int argc, char **argv)
{
	

	// Initialize SDL library for video and audio subsystems
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	AudioInit();

	// Load image from file
	SDL_Surface *image = IMG_Load("resources/main_screen.jpg");

	// Set the video mode
	screen = SDL_SetVideoMode(image->w, image->h, 16, SDL_SWSURFACE);


	// If the image works, then do cool stuff
	if(image)
	{
		SDL_Rect rcDest = { 0, 0, image->w, image->h };
		
		if(	!SDL_BlitSurface(image, NULL, screen, &rcDest))
		{
			char * error = SDL_GetError();
		}
		SDL_FreeSurface(image);

		// Set the window title
		SDL_WM_SetCaption("Simple Window", "Simple Window");

		bool done = false;

		PlaySound("resources/test_L.wav");
		PlaySound("resources/test_R.wav");

		while(!done) {
			// Wait until the window is quit
			while(SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					done = true;
				}
			}

			// Fill the screen with black color
			//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

			// Update the screen buffer
			SDL_Flip(screen);

		}
	}
	// Otherwise print error info
	else
	{

		// Get and output the filename
		TCHAR s[100];
		DWORD a = GetCurrentDirectory(100, s);

		char * error = IMG_GetError();

		OutputDebugString(LPCWSTR(IMG_GetError()));


	}

	// Quit
	AudioShutdown();
	SDL_Quit();
	
	return 0;
}