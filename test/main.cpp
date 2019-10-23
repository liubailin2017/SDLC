
#include<iostream>
#include<SDL2/SDL.h>
#include "../src/SDLC_log.h"
#include "../src/SDLC_Context.h"
#include "../src/SDLC_Component.h"
#include "../src/Extends/Image.h"
#include"../src/Extends/AnimationTest.h"
int w = 50;

#include"string"
void onstrick(SDLC_Component *cmp) {
     if(cmp){
          std::cout <<"strick id:"<<cmp->getId() <<std::endl;
     }else {
          std::cout << "strick id:context" <<std::endl;
     }
}

void onin(SDLC_Component *cmp) {
     cmp->setbgcolor(0xff573498);
}

void onout(SDLC_Component *cmp) {
     cmp->setbgcolor(0xff981121);
}

bool ondown(const SDL_Event &event, SDLC_Component *cmp) {
     switch (event.type)
     {
     case SDL_MOUSEBUTTONDOWN:
          cmp->setbgcolor(0xff102746);
          cmp->raise();
          break;
     case SDL_MOUSEBUTTONUP:
          cmp->setbgcolor(0xff573498);
          break;
     default:
          break;
     }

     return true;
}
bool ondown_for_raise(const SDL_Event &event, SDLC_Component *cmp) {
     switch (event.type)
     {
     case SDL_MOUSEBUTTONDOWN:
          cmp->raise();
          break;
     }
     return true;
}

bool ondown_for_handle(const SDL_Event &event, SDLC_Component *cmp) {

     return false;
}

bool onmove(const SDL_Event &event,SDLC_Component *cmp) {
     ondown(event,cmp);
     switch (event.type)
     {
     case SDL_MOUSEMOTION:
          cmp->setbgcolor(0xff00ff00);
          break;
     default:
          break;
     }
     return true;
}
#undef main
extern int SDL_Init(Uint32 flags);

int main(int argc ,char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win = SDL_CreateWindow(
                                        "SDL_TEST",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        960,640,
                                        SDL_WINDOW_RESIZABLE);

     // SDL_Surface* win_sur = SDL_GetWindowSurface(win);
     SDL_Event event;
     int isquit = 0;
    
     SDLC_Context context(win);
 
     Image c2(&context,0,0,100,100);
     c2.load("test.png");
     Image c2_1(&context,0,0,100,100);
     c2_1.load("test.jpg");
     c2.setMovable(true);
     c2_1.setMovable(true);
     //c2_1.setListener(ondown);
     context.addComponent(&c2_1);
     context.addComponent(&c2);
   

     c2.setListener(ondown_for_raise);
     c2_1.setListener(ondown_for_handle);

     for(int i = 0; i < 1; i++) {
          SDLC_Component *sdlc_i = new SDLC_Component(&context,0,0,-i*10+350,i*10+350,0xff000000+i*0x110000);
          for(int j = 0; j<3; j++) {
               SDLC_Component *sdlc_j = new SDLC_Component(&context,0,0,-j*10+150,j*10+150,0x9f000000+i*0x110000+j*0x1100);
               for (int k = 0; k < 1; k++)
               {
                    SDLC_Component *sdlc_k = new SDLC_Component(&context,0,0,-k*10+100,k*10+10,0x7f000000+i*0x110000+j*0x1100+k*0x11);
                    sdlc_k->setMovable(true);
                    sdlc_k->setListener(ondown);
                    sdlc_k->setOutHandler(onout);
                    sdlc_k->setInHandler(onin);
                    sdlc_j->addComponent(sdlc_k);
               }
               sdlc_j->setListener(ondown_for_raise);
               sdlc_j->setMovable(true);
               sdlc_i->addComponent(sdlc_j);
               AnimationTest*animaiton = new AnimationTest(&context);
               animaiton->setMovable(true);
               
               animaiton->setListener(ondown_for_handle);
               if(j == 2) { 
                    animaiton->setListener(ondown_for_raise);
               }
               animaiton->setPostion(j*50,0);
               sdlc_i->addComponent(animaiton);
          }
          sdlc_i->setListener(ondown);
          sdlc_i->setOutHandler(onout);
          sdlc_i->setInHandler(onin);
          sdlc_i->setMovable(true);
          context.addComponent(sdlc_i);

     }

     int ticket = SDL_GetTicks();
     while(!isquit)
     {
          while(SDL_PollEvent(&event)){
               switch(event.type)
               {
                    case SDL_QUIT :
                    isquit = 1;
                    break;
               }
               context.dispatch(event);
          }
          int t = SDL_GetTicks() ;
          if(SDL_GetTicks() - ticket > 30) {
                    context.updateWindow();  
                    ticket = SDL_GetTicks();
                    context.strick();
          }
          if(SDL_GetTicks()-t < 10){
               SDL_Delay(10); 
          }
     }
     return 0;
}
