#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char* player_name(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Event e;
    bool quit = false;
    SDL_Color textColor = { 255, 255, 255 };
    char inputText[100] = "";
    int textLength = 0;

    SDL_StartTextInput();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && textLength > 0) {
                    inputText[--textLength] = '\0';
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    quit = true;
                }
            } else if (e.type == SDL_TEXTINPUT) {
                if ((textLength + strlen(e.text.text)) < 100) {
                    strcat(inputText, e.text.text);
                    textLength += strlen(e.text.text);
                }
            }
        }

        SDL_RenderClear(renderer);

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, inputText, textColor);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        int textWidth = 0;
        int textHeight = 0;
        SDL_QueryTexture(message, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect renderQuad = { (SCREEN_WIDTH - textWidth) / 2, (SCREEN_HEIGHT - textHeight) / 2, textWidth, textHeight };
        SDL_RenderCopy(renderer, message, NULL, &renderQuad);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();

    return strdup(inputText);
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    char* name = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        window = SDL_CreateWindow("Player Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            } else {
                font = TTF_OpenFont("fonts/minecraft.ttf", 28);
                if (font == NULL) {
                    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                } else {
                    name = player_name(renderer, font);
                    printf("Player name is: %s\n", name);
                    free(name);
                TTF_CloseFont(font);
            }
            SDL_DestroyRenderer(renderer);
        }
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
}
SDL_Quit();

return 0;
}