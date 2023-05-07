#pragma once
#include <stdio.h>
#include "global.h"

void initMusic();
void volume();
void desMusic();
//===========================
void volume()
{
    Mix_VolumeChunk(hit, MIX_MAX_VOLUME/4);  //chỉnh âm luọng của hit
    Mix_VolumeChunk(shot, MIX_MAX_VOLUME/4);  //chỉnh âm luọng của shot
    Mix_VolumeChunk(Menu, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(BGM, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(Boss, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(Menu, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(eatHp, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(gameOverSong, MIX_MAX_VOLUME/4);
}
void initMusic()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    // Load và phát nhạc nền
    Menu = Mix_LoadWAV("audio/Menu.wav");
    BGM = Mix_LoadWAV("audio/bgm.wav");
    Boss = Mix_LoadWAV("audio/BossMusic2.wav");
    hit = Mix_LoadWAV("audio/SE_enemy_vanish.wav");
    dead = Mix_LoadWAV("audio/SE_dead.wav");
    shot = Mix_LoadWAV("audio/SE_shot.wav");
    eatHp = Mix_LoadWAV("audio/SE_powerup.wav");
    gameOverSong = Mix_LoadWAV("audio/FunnySong.wav");

    if (Menu == NULL || BGM == NULL || Boss == NULL || hit == NULL || dead == NULL || eatHp == NULL){
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}
void desMusic()
{
    Mix_FreeChunk(Menu);
    Mix_FreeChunk(BGM);
    Mix_FreeChunk(Boss);
    Mix_FreeChunk(hit);
    Mix_FreeChunk(dead);
    Mix_FreeChunk(shot);
    Mix_FreeChunk(eatHp);
    Mix_FreeChunk(gameOverSong);
    Mix_CloseAudio();
}