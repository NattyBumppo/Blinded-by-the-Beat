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

int blocks[6][6] =
{
	{1, 2, 3, 4, 5, 6},
	{1, 2, 3, 4, 5, 6},
	{1, 2, 3, 4, 5, 6},
	{1, 2, 3, 4, 5, 6},
	{1, 2, 3, 4, 5, 6},
	{1, 2, 3, 4, 5, 6}
};

int main(int argc, char **argv)
{
	
	struct cursor_loc
	{
		int x;
		int y;
			
	};

	struct cursor_loc c;
	c.x = 0;
	c.y = 3;


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

		while(!done) {
			
			// Grab keyboard/mouse input
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
 				  case SDL_QUIT:
					  done = true;
					  break;
				  // Handle keyboard input
				  case SDL_KEYDOWN:
					  switch(event.key.keysym.sym)
					  {
					    case SDLK_LEFT:
						case SDLK_a:
							// move cursor left
							if(c.x != 0)
							{
								c.x--;
							}
							else
							{
								PlayAudio("resources/boop.wav", LEFT, 3);
							}

							break;
						case SDLK_RIGHT:
						case SDLK_d:
							// move cursor right
							if(c.x != 4)
							{
								c.x++;
							}
							else
							{
								PlayAudio("resources/boop.wav", RIGHT, 3);
							}
							break;
						case SDLK_UP:
						case SDLK_w:
							// move cursor up
							if(c.y != 0)
							{
								c.y--;
							}
							else
							{
								PlayAudio("resources/boop.wav", BOTH, 3);
							}

							break;
						case SDLK_DOWN:
						case SDLK_s:
							// move cursor down
							if(c.y != 5)
							{
								c.y++;
							}
							else
							{
								PlayAudio("resources/boop.wav", BOTH, 3);
							}
							break;
						case SDLK_SPACE:
							// switch blocks at cursor
							PlayAudio("resources/ding.wav", BOTH, 2);
							int temp = blocks[c.x][c.y];
							blocks[c.x][c.y] = blocks[c.x + 1][c.y];
							blocks[c.x + 1][c.y] = temp;
							break;
					  }
				}
				
					
			}

			// Check cursor location and produce appropriate sounds
			PlayBlockSounds(blocks[c.x][c.y], blocks[c.x + 1][c.y]);

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