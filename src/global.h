#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <unistd.h>

#define MAX_BULLET 1000

int widthScreen;
int heightScreen;

int mouseX = 0, mouseY = 0;
bool gameOver;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Renderer *renderer_bullet;
SDL_mutex *mutex_bullet;
SDL_Texture *background = NULL;
SDL_Texture *background_menu = NULL;
SDL_Texture *background_help = NULL;

SDL_Texture* mouse = NULL;
SDL_Texture* startButton = NULL;
SDL_Texture* helpButton = NULL;
SDL_Texture* quitButton = NULL;
SDL_Texture* backButton = NULL;
SDL_Texture* backButton2 = NULL;
SDL_Texture* startButton2 = NULL;
SDL_Texture* helpButton2 = NULL;
SDL_Texture* quitButton2 = NULL;



