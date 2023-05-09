#pragma once
// #include "global.h"
#include "stdio.h"
// #include "text.h"
// #include "game.h"

void handlePause()
{
    while(gameOver)
    {
        SDL_Event event;
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&mouseX,&mouseY);

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEMOTION:
                    if(checkText(helpPause)){
                        loadText(50,&helpPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&helpPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(continuePause)){
                        loadText(50,&continuePause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&continuePause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(exitPause)){
                        loadText(50,&exitPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&exitPause,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(soundOn)){
                        loadText(50,&soundOn,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&soundOn,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }

                    if(checkText(soundOff)){
                        loadText(50,&soundOff,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(RED));
                    }
                    else{
                        loadText(50,&soundOff,"fonts/VCR_OSD_MONO_1.001.ttf",getColor(WHITE));
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    if(checkText(helpPause)){
                        bool check = true;
                        while(check)
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
                                        return;
                                    }
                                    // back
                                    if( mouseX >= 200 && mouseX <= 400 && mouseY >= 750 && mouseY <= 800)
                                    {
                                        gameOver = false;
                                        return;
                                    }
                                }
                            }
                            
                            SDL_RenderPresent(renderer);
                            SDL_Delay(10);
                        }
                    }
                    
                    if(checkText(continuePause)){
                        return;
                    }

                    if(checkText(exitPause)){
                        // tạo node mới để thêm vào danh sách người chơi
                        node_pr *nodepr = createNode(playerer);
                        addNode(nodepr,lpr);
                        playerer.hp = 3;
                        wave = 0;
                        playerer.score = 0;
                        strcpy(playerer.name,"");
                        gameOver = false;
                    }

                    if(checkText(soundOn) && hasAudio){
                        hasAudio = false;
                        Mix_Pause(-1);  // dừng phát nhạc tạm thời, -1 tức là tắt tất cả kênh âm thanh
                        // drawText(&soundOff);
                    }

                    else if(checkText(soundOff) && !hasAudio){
                        hasAudio = true;
                        Mix_Resume(-1);  // Bật lại nhạc đã tạm dừng trước đó, -1 tức là bật tất cả các kênh âm thanh
                    }                    
                break;
            }
        }
    
        moveBackground();
        drawMouse();


        drawText(&pauseGame);
        drawText(&helpPause);
        drawText(&continuePause);
        drawText(&exitPause);
        if(hasAudio){
            drawText(&soundOn);
        }
        else drawText(&soundOff);
        
        SDL_Delay(10);
        SDL_RenderPresent(renderer);
    }
}