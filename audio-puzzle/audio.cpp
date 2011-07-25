#include "stdafx.h"
#include "audio.h"

void AudioInit()
{
		Mix_Init(MIX_INIT_MP3);

		if(!Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 1024))
		{
			char * error = Mix_GetError();
		}
}

void AudioShutdown()
{
	Mix_CloseAudio();
	Mix_Quit();
}

void PlayAudio(char* filename, int ear_channel, int num_channel, int loops)
{

	if (!Mix_Playing(num_channel)){
		Mix_Chunk *sample;
		sample = Mix_LoadWAV(filename);
		if(!sample)
		{
			char * error = Mix_GetError();
		}

		if(ear_channel == LEFT)
		{
			if(!Mix_SetPanning(num_channel, 255, 0))
			{
				char * error = Mix_GetError();
			}
		}
		else if(ear_channel == RIGHT)
		{
			Mix_SetPanning(num_channel, 0, 255);
		}
		else
		{
			Mix_SetPanning(num_channel, 127, 127);
		}

		Mix_PlayChannel(num_channel, sample, loops);
	}
}

// Play one sound on each ear, corresponding to the blocks passed in
void PlayBlockSound(int sound, int ear, int blocks[3][6])
{
	int channel;
	if (ear == LEFT)
	{
		channel = 0;
	}
	else
	{
		channel = 1;
	}

	// Play sound, so long as current sound is not comboing
	if(!Sound_combo_exists(sound, blocks))
	{
		switch(sound)
		{
		  case 0:
			  PlayAudio("resources/0.wav", ear, channel, 0);
			  break;
		  case 1:
			  PlayAudio("resources/1.wav", ear, channel, 0);
			  break;
		  case 2:
			  PlayAudio("resources/2.wav", ear, channel, 0);
			  break;
		  case 3:
			  PlayAudio("resources/3.wav", ear, channel, 0);
			  break;
		  case 4:
			  PlayAudio("resources/4.wav", ear, channel, 0);
			  break;
		  case 5:
			  PlayAudio("resources/5.wav", ear, channel, 0);
			  break;
		  default:
			  break;
		}
	}
}

// Checks the blocks to see if the specified sound
// has been comboed into a row or column of three
bool Sound_combo_exists(int sound, int blocks[3][6])
{
	int x_counter, y_counter;
	// Look for horizontal combos first
	for (int y = 0; y < 3; y++)
	{
		x_counter = 0;
		for (int x = 0; x < 6; x++)
		{
			// Increment x_counter for each block of this sound
			// found consecutively; otherwise, drop the counter back
			// down to zero
			if(blocks[y][x] == sound)
			{
				x_counter++;
			}
			else
			{
				x_counter = 0;
			}

			// Combo found if the counter is up to 3
			if(x_counter >= 3)
			{
				return true;
			}
		}
	}

	// Look for vertical combos next
	for (int x = 0; x < 6; x++)
	{
		y_counter = 0;
		for (int y = 0; y < 3; y++)
		{
			// Increment y_counter for each block of this sound
			// found consecutively; otherwise, drop the counter back
			// down to zero
			if(blocks[y][x] == sound)
			{
				y_counter++;
			}
			else
			{
				y_counter = 0;
			}

			// Combo found if the counter is up to 3
			if(y_counter >= 3)
			{
				return true;
			}
		}
	}

	// No combo found
	return false;
}

bool Win_Condition(int blocks[3][6])
{
	for(int sound = 0; sound < 6; sound++)
	{
		if(!Sound_combo_exists(sound, blocks))
		{
			return false;
		}
	}

	return true;
}