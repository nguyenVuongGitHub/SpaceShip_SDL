#pragma once
#include "global.h"
#include "game.h"
void drawHelp();
void loadHelp();
void showHelp();
//=======================================================
void drawHelp()
{
    // SDL_RenderCopy(renderer,background_help,NULL,NULL);
    moveBackground();


    // vẽ chữ help 
    text helpText;
    initText(&helpText);
    setText("<- HELP ->",&helpText);
    loadText(72,&helpText,pathFont,getColor(WHITE));
    setPosText(displayMode.w/2 - helpText.w/2,150,&helpText);
    drawText(&helpText);
    // vẽ hướng dẫn di chuyển

    SDL_Rect moveMouseRect = {displayMode.w/2 - 350,250,150,150};
    SDL_RenderCopy(renderer,mouseMove,NULL,&moveMouseRect);
    text mouseMoveText;
    initText(&mouseMoveText);
    setText("MOVE SHIP",&mouseMoveText);
    loadText(42,&mouseMoveText,pathFont,getColor(WHITE));
    setPosText(moveMouseRect.w + moveMouseRect.x + 50,moveMouseRect.h+moveMouseRect.y / 2 + 30,&mouseMoveText);
    drawText(&mouseMoveText);
    // vẽ hướng dẫn bắn

    SDL_Rect clickMouseRect = {displayMode.w/2 - 350,400,150,150};
    SDL_RenderCopy(renderer,clickMouse,NULL,&clickMouseRect);
    text clickMouseText;
    initText(&clickMouseText);
    setText("SHOT",&clickMouseText);
    loadText(42,&clickMouseText,pathFont,getColor(WHITE));
    setPosText(clickMouseRect.w + clickMouseRect.x + 50,clickMouseRect.h+clickMouseRect.y / 2 + 100,&clickMouseText);
    drawText(&clickMouseText);
    // vẽ phụ đề

    SDL_Rect escRect = {displayMode.w/2 - 350,550,150,150};
    SDL_RenderCopy(renderer,esc,NULL,&escRect);

    text escText;
    initText(&escText);
    setText("RETURN",&escText);
    loadText(42,&escText,pathFont,getColor(WHITE));
    setPosText(escRect.w + escRect.x + 50,escRect.h+escRect.y / 2 + 180,&escText);
    drawText(&escText);
    // Vẽ nút bắt đầu
    SDL_Rect startRect = { 1200, 750, 200, 50 };
    SDL_RenderCopy(renderer, startButton, NULL, &startRect);

    // Vẽ nút thoát
    SDL_Rect backRect = { 200, 750, 200, 50 };
    SDL_RenderCopy(renderer, backButton, NULL, &backRect);

    SDL_GetMouseState(&mouseX,&mouseY);
    if ( mouseX >= 1200 && mouseX <= 1400 && mouseY >= 750 && mouseY <= 800)
    {
        // Vẽ nút bắt đầu
        SDL_RenderCopy(renderer, startButton2, NULL, &startRect);
    }
    if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
    {
        SDL_RenderCopy(renderer, backButton2, NULL, &backRect);
    }

}
void loadHelp()
{
    SDL_Surface *surface;
    IMG_Init(IMG_INIT_PNG);
    surface = IMG_Load("image\\help.png");
    if(surface != NULL){
        background_help = SDL_CreateTextureFromSurface(renderer,surface);
        if(background_help == NULL){
            printf("Khong tao duoc texture tu surface: %s", SDL_GetError());
        }else{
            SDL_RenderCopy(renderer,background_help,NULL,NULL);
            SDL_FreeSurface(surface);
        }   
    }else{
        printf("Khong load duoc anh: %s", IMG_GetError());
    }
}
void showHelp()
{
    while(gameOver)
    {
        SDL_RenderClear(renderer);
        SDL_Event event2;
        drawHelp();
        drawMouse();
        while (SDL_PollEvent(&event2))
        {
            if(event2.type == SDL_MOUSEBUTTONDOWN)
            {
                // game
                SDL_GetMouseState(&mouseX,&mouseY);
                if ( mouseX >= 1200 && mouseX <= 1400 && mouseY >= 750 && mouseY <= 800)
                {
                    inputPlayer(&playerer);
                    gameLoop();
                    gameOver = false;
                }
                // back
                if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
                {
                    return;
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}