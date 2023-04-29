#include "../includes/music.h"

Mix_Music* init_audio(){
    if(SDL_Init(SDL_INIT_AUDIO)<0){
		printf("Erreur lors de l'initialisaiton de SDL: %s",SDL_GetError());
		return NULL;
	}
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0){
		printf("Erreur lors de l'initialisaiton de SDL_Mixer: %s",Mix_GetError());
		return NULL;
	}
	Mix_Music * music = Mix_LoadMUS("sound/Piano.mp3");
    //Mix_Music * music = Mix_LoadMUS("sound/traveller.mp3");
	if(!music){
		printf("Erreur lors du chargement de la musique: %s",Mix_GetError());
		return NULL;
	}
    Mix_VolumeMusic(MIX_MAX_VOLUME/8);
	return music;
}

void free_audio(Mix_Music * music){
    Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
}