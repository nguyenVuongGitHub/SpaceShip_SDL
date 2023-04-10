#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
enum TEXT_COLOR{
    WHITE,RED,BLACK
};

struct text
{
    const char* value;
    int x;
    int y;
    int w;
    int h;
    TTF_Font *font;
    SDL_Texture* texture;
};
typedef struct text text;

void initText(text *t); // khởi tạo text
void loadText(int size, text *t, const char * path, SDL_Color color); // font và size
void setPosText(int x, int y, text *t); // set vị trí cho text
void setText(const char *value,text *t); // set giá trị cho text
void drawText(text *t); // vẽ text lên màn hình
SDL_Color getColor(TEXT_COLOR color); // lấy màu từ enum 
//=================================================================

void initText(text *t)
{
    t->value = "";
    t->x = 0;
    t->y = 0;
    t->w = 0;
    t->h = 0;
    t->font = NULL;
    t->texture = NULL;
}

void loadText(int size, text *t, const char * path, SDL_Color color)
{ 
    if(t->texture != NULL)
    {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
    }
    if(t->font != NULL)
    {
        TTF_CloseFont(t->font);
        t->font = NULL;
    }
    TTF_Font *font = TTF_OpenFont(path,size);
    t->font = font;
    SDL_Surface *surface = TTF_RenderText_Solid(t->font,t->value,color);
    if(surface != NULL)
    {
        t->w = surface->w;
        t->h = surface->h;
        t->texture = SDL_CreateTextureFromSurface(renderer,surface);
    }
    SDL_FreeSurface(surface);
}

void setPosText(int x, int y, text *t)
{
    t->x = x;
    t->y = y;
}

void setText(const char *value,text *t)
{
    t->value = value;
}

void drawText(text *t)
{
    SDL_Rect dstrect = { t->x, t->y, t->w, t->h };
    SDL_RenderCopy(renderer, t->texture, NULL, &dstrect);
}

SDL_Color getColor(TEXT_COLOR color)
{
    switch (color) {
        case WHITE:
            return { 255, 255, 255, 255 };
        case RED:
            return { 255, 0, 0, 255 };
        case BLACK:
            return { 0, 0, 0, 255 };
        default:
            return { 255, 255, 255, 255 };
    }
}


// int main(int argc, char* argv[])
// {
//     // Khởi tạo SDL
//     SDL_Init(SDL_INIT_EVERYTHING);
    

//     // Tạo cửa sổ
//    window = SDL_CreateWindow("Text Demo",
//                                           SDL_WINDOWPOS_CENTERED,
//                                           SDL_WINDOWPOS_CENTERED,
//                                           640, 480,
//                                           SDL_WINDOW_SHOWN);

//     // Tạo renderer
//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     // Tạo font
    

//     // Tạo đối tượng văn bản
//     text t;
//     initText(&t);
//     setText("Hello, world!", &t);
//     // Tải văn bản lên texture
//     loadText(30, &t,"fonts/Minecraft.ttf");
    
    
//     // Thiết lập vị trí văn bản
//     setPosText(100, 100,&t);

//     // Vẽ văn bản
//     drawText(&t);
    
//     // Vẽ lên màn hình
//     SDL_RenderPresent(renderer);
//     // Delay 3 giây
//     SDL_Delay(3000);
    
//     // Giải phóng bộ nhớ và thoát
//     SDL_DestroyTexture(t.texture);
//     TTF_CloseFont(t.font);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     TTF_Quit();
//     SDL_Quit();

//     return 0;
// }

// // //=================================================================