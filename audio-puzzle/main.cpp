// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <sdl/sdl.h>
#include <sdl/SDL_image.h>
#include <sdl/SDL_audio.h>
#include "audio.h"
#include <math.h>


// This is a display surface to represent the window.
SDL_Surface *screen;

SDL_Event event;

int blocks[3][6] =
{
	{2, 1, 0, 4, 1, 1},
	{5, 0, 5, 4, 2, 5},
	{2, 3, 4, 3, 0, 3},
};

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

// Draw a rectangle of the given color
void DrawRect(SDL_Surface *image, int x0, int y0, int x1, int y1, Uint8 R, Uint8 G, Uint8 B)
{
	/* Lock the screen for direct access to the pixels */
	if ( SDL_MUSTLOCK(image) )
	{
		if ( SDL_LockSurface(image) < 0 )
		{
			OutputDebugString((LPCWSTR)"Can't lock screen:\n");
			OutputDebugString((LPCWSTR)SDL_GetError());

		}
	}
	
	// Write rectangle pixels
	for(int y = y0; y < y1; y++)
	{
		for(int x = x0; x < x1; x++)
		{
			putpixel(image, x, y, SDL_MapRGB(image->format, R, G, B));
		}
	}

	// Unlock screen, now that we've accessed the pixels
	if ( SDL_MUSTLOCK(image) )
	{
		SDL_UnlockSurface(image);
	}

}

float Distance(int x0, int y0, int x1, int y1)
{
	return sqrt((float)((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}

// Draw a circle of the given color
void DrawCircle(SDL_Surface *image, int center_x, int center_y, int radius, Uint8 R, Uint8 G, Uint8 B, bool filled)
{
	for (int y = center_y - radius; y < center_y + radius; y++)
	{
		for (int x = center_x - radius; x < center_x + radius; x++)
		{
			// Make sure the point is in the image
			if(x >= 0 && x < image->w && y >= 0 && y < image->h)
			{
				// If the point falls in the circle, draw it
				if(floor(Distance(center_x, center_y, x, y)) <= radius)
				{
					// But don't draw if we're not filling it, and if it's inside
					if(filled)
					{
						putpixel(image, x, y, SDL_MapRGB(image->format, R, G, B));
					}
					else if(Distance(center_x, center_y, x, y) + 4 > radius)
					{
						putpixel(image, x, y, SDL_MapRGB(image->format, R, G, B));
					}
				}
			}
		}
	}
}

int main(int argc, char **argv)
{
	
	struct cursor_loc
	{
		int x;
		int y;
			
	};

	struct cursor_loc c;
	c.x = 0;
	c.y = 0;


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

		// Set the window title
		SDL_WM_SetCaption("Shhh!", "Shhh!");

		bool done = false;

		while(!done)
		{
			
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
								// End currently playing block noise
								Mix_HaltChannel(0);
								Mix_HaltChannel(1);
							}
							else
							{
								PlayAudio("resources/boop.wav", LEFT, 3, 0);
							}

							break;
						case SDLK_RIGHT:
						case SDLK_d:
							// move cursor right
							if(c.x != 4)
							{
								c.x++;
								// End currently playing block noise
								Mix_HaltChannel(0);
								Mix_HaltChannel(1);
							}
							else
							{
								PlayAudio("resources/boop.wav", RIGHT, 3, 0);
							}
							break;
						case SDLK_UP:
						case SDLK_w:
							// move cursor up
							if(c.y != 0)
							{
								c.y--;
								// End currently playing block noise
								Mix_HaltChannel(0);
								Mix_HaltChannel(1);
							}
							else
							{
								PlayAudio("resources/boop.wav", BOTH, 3, 0);
							}

							break;
						case SDLK_DOWN:
						case SDLK_s:
							// move cursor down
							if(c.y != 2)
							{
								
								c.y++;
								// End currently playing block noise
								Mix_HaltChannel(0);
								Mix_HaltChannel(1);
							}
							else
							{
								PlayAudio("resources/boop.wav", BOTH, 3, 0);
							}
							break;
						case SDLK_SPACE:
							// switch blocks at cursor
							
							// Play switch sound
							//PlayAudio("resources/ding.wav", BOTH, 2, 0);
							
							// End currently playing block noise
							Mix_HaltChannel(0);
							Mix_HaltChannel(1);
							{
								int temp = blocks[c.y][c.x];
								blocks[c.y][c.x] = blocks[c.y][c.x + 1];
								blocks[c.y][c.x + 1] = temp;
							}
							break;
						default:
							break;
					  }
				}
				
					
			}

			// Check cursor location and produce appropriate sounds
			PlayBlockSound(blocks[c.y][c.x], LEFT, blocks);
			PlayBlockSound(blocks[c.y][c.x + 1], RIGHT, blocks);

			if(Win_Condition(blocks))
			{
				done = true;
				bool end_game = false;
				// Win condition reached!
				while(!end_game)
				{
					while(SDL_PollEvent(&event))
					{
						if (event.type == SDL_QUIT)
						{
							end_game = true;
						}
					}
			
					// Draw white screen
					DrawRect(image, 0, 0, image->w, image->h, 0xff, 0xff, 0xff);

					// Draw nucleus in the middle
					DrawCircle(image, 400, 400, 80, 0xff, 0x66, 0x66, true);

					// Draw first orbital
					DrawCircle(image, 400, 400, 180, 0x00, 0x00, 0x00, false);

					// Draw second orbital
					DrawCircle(image, 400, 400, 240, 0x00, 0x00, 0x00, false);

					// Draw third orbital
					DrawCircle(image, 400, 400, 300, 0x00, 0x00, 0x00, false);

					// Draw electron #1
					DrawCircle(image, 276, 271, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #2
					DrawCircle(image, 526, 524, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #3
					DrawCircle(image, 400, 160, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #4
					DrawCircle(image, 400, 640, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #5
					DrawCircle(image, 160, 400, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #6
					DrawCircle(image, 640, 400, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #7
					DrawCircle(image, 230, 230, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #8
					DrawCircle(image, 570, 230, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #9
					DrawCircle(image, 570, 570, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #10
					DrawCircle(image, 230, 570, 20, 0xff, 0xcf, 0x42, true);

					// Draw electron #11
					DrawCircle(image, 540, 135, 20, 0xff, 0xcf, 0x42, true);



					if(	!SDL_BlitSurface(image, NULL, screen, &rcDest))
					{
						char * error = SDL_GetError();
					}

					// Update the screen buffer
					SDL_Flip(screen);
				}
			}

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