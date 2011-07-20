#include <sdl/SDL_audio.h>

void AudioInit();
void AudioShutdown();
void MixAudio(void*, Uint8*, int);
void PlaySound(char*);