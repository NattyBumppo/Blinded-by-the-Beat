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

void PlayAudio(char* filename, int ear_channel, int num_channel)
{

	
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

	Mix_PlayChannel(num_channel, sample, 0);


}