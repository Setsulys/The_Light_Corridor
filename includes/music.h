#ifndef __MUSIC_H
#define __MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music * init_audio();

void free_audio(Mix_Music * music);
#endif