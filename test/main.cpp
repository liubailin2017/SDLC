
#include<iostream>
#include<SDL2/SDL.h>
#include "../src/SDLC_log.h"
#include "../src/SDLC_Context.h"
#include "../src/SDLC_Component.h"
#include "../src/Extends/Image.h"
int w = 50;

#include"string"
int main(int argc ,char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win = SDL_CreateWindow(
                                        "SDL_TEST",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        960,640,
                                        SDL_WINDOW_SHOWN);

   // SDL_Surface* win_sur = SDL_GetWindowSurface(win);
    SDL_Event event;
    int isquit = 0;
    
    SDLC_Context context(win);

    SDLC_Component c(&context, 100,  100,50,50);
    
    Image c2(&context,400,0,100,100);
     Image c2_1(&context,400,0,100,100);
    
    SDLC_Component c3(&context,150,150,200,200,0xffff00ff);
    
    SDLC_Component *c4 = new SDLC_Component(&context,0,0,300,300,0x7000ff00);
    
    SDLC_Component c5(&context,50,50,200,20,  0xff0000ff);
    SDLC_Component c6(&context,50,100,200,20,  0xff0000ff);
 
    context.addComponent(&c2);

    c2.addComponent(c4);

    c4->addComponent(&c3);

     c3.addComponent(&c5);
     c3.addComponent(&c6);

    c4->setMovable(true);
     c3.setMovable(true);
     c2.setMovable(true);
     c5.setMovable(true);
     c2.load("test.jpg");
     c2_1.load("test.png");
     c2.addComponent(&c2_1);
     c2_1.setMovable(true);
    int ticket = SDL_GetTicks();

    while(!isquit)
    {
          if(SDL_PollEvent(&event)){
               switch(event.type)
               {
                    case SDL_MOUSEBUTTONUP:
                    case SDL_MOUSEMOTION:
                    case SDL_MOUSEBUTTONDOWN:                          
                    context.dispatch(event);
                    break;

                    case SDL_QUIT :
                    isquit = 1;
                    break;
               }
          }

          if(SDL_GetTicks() - ticket > 15) {
               context.updateWindow();  
               ticket = SDL_GetTicks();
          }
         // SDL_Delay(10);           
    }
    return 0;
}
