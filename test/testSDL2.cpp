

#include<SDL2/SDL.h>

int main(int argc ,char *argv[])
{
    int    rmask = 0x000000ff;
    int    gmask = 0x0000ff00;
    int    bmask = 0x00ff0000;
    int    amask = 0xff000000;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win = SDL_CreateWindow(
                                        "SDL_TEST",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640,480,
                                        SDL_WINDOW_SHOWN);

   // SDL_Surface* win_sur = SDL_GetWindowSurface(win);
   SDL_Surface *surface = NULL;
    SDL_Event event;
    int isquit = 0;
    while(!isquit)
    {
           while(SDL_PollEvent(&event)){
                switch(event.type)
                {
                        case SDL_QUIT :
                        isquit = 1;
                        break;
                }
           } 
           SDL_Delay(1);     
        surface = SDL_CreateRGBSurface(0,320,240,32,rmask,gmask,bmask,0);
        SDL_FreeSurface(surface);

    }
    return 0;
}
