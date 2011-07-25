#include <sdl/SDL_audio.h>
#include <sdl/SDL_mixer.h>

void AudioInit();
void AudioShutdown();
void PlayAudio(char*, int, int, int);
void PlayBlockSound(int, int, int[3][6]);
bool Sound_combo_exists(int, int[3][6]);
bool Win_Condition(int[3][6]);

enum ear
{
	LEFT,
	RIGHT,
	BOTH
};
