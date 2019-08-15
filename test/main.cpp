
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

bool onin(SDLC_Component *cmp) {
     cmp->setbgcolor(0xff554455);
     cmp->_context()->notifyUpdate();
     return true;
}

bool onout(SDLC_Component *cmp) {
     cmp->setbgcolor(0xff981121);
     cmp->_context()->notifyUpdate();
     return true;
}
bool ondown(const SDL_Event &event, SDLC_Component *cmp) {
     switch (event.type)
     {
     case SDL_MOUSEBUTTONDOWN:
          cmp->setbgcolor(0xff102746);
          std::cout << "down id:" << cmp->getId()<<"bg:"<< cmp->getBgcolor()<<std::endl;
          cmp->raise();
          break;
     case SDL_MOUSEBUTTONUP:
          cmp->setbgcolor(0xff573498);
          
          std::cout << "up id:" << cmp->getId()<<"bg:"<< cmp->getBgcolor()<<std::endl;
          break;
     default:
          break;
     }
     
     cmp->_context()->notifyUpdate();
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
     //c2_1.setListener(ondown);
     context.addComponent(&c2_1);
     context.addComponent(&c2);

     c2.setListener(ondown);

     for(int i = 0; i < 3; i++) {
          SDLC_Component *sdlc_i = new SDLC_Component(&context,0,0,-i*10+350,i*10+350,0xff000000+i*0x110000);
          for(int j = 0; j<3; j++) {
               SDLC_Component *sdlc_j = new SDLC_Component(&context,0,0,-j*10+150,j*10+150,0x9f000000+i*0x110000+j*0x1100);
               for (int k = 0; k < 3; k++)
               {
                    SDLC_Component *sdlc_k = new SDLC_Component(&context,0,0,-k*10+100,k*10+10,0x7f000000+i*0x110000+j*0x1100+k*0x11);
                    sdlc_k->setMovable(true);
                    sdlc_k->setListener(ondown);
                    sdlc_k->setOutHandler(onout);
                    sdlc_k->setInHandler(onin);
                    sdlc_j->addComponent(sdlc_k);
               }
               sdlc_j->setListener(ondown_for_raise);
               sdlc_j->setRaise(false);
               sdlc_j->setMovable(true);
               sdlc_i->addComponent(sdlc_j);
          }
          sdlc_i->setListener(ondown);
          sdlc_i->setOutHandler(onout);
          sdlc_i->setInHandler(onin);
          sdlc_i->setMovable(true);
          context.addComponent(sdlc_i);
          AnimationTest*animaiton = new AnimationTest(&context);
          animaiton->setMovable(true);
          animaiton->setListener(ondown);
          context.addComponent(animaiton);
  
     }
     int ticket = SDL_GetTicks();
     while(!isquit)
     {
          if(SDL_PollEvent(&event)){
               switch(event.type)
               {
                    case SDL_QUIT :
                    isquit = 1;
                    break;
               }
               context.dispatch(event);
          }

     if(SDL_GetTicks() - ticket > 15) {
               context.updateWindow();  
               ticket = SDL_GetTicks();
               context.strick();
     }
     SDL_Delay(1);           
     }
     return 0;
}
