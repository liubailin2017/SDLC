#ifndef _h_SDLC_Context
#define _h_SDLC_Context
#include<SDL2/SDL.h>
#include"SDLC_Event.h"
class SDLC_Component;

class SDLC_Context;
typedef bool (*HandleFun)(SDL_Event event,SDLC_Context *context);
typedef void (*UpdateBg)(SDL_Surface* surface);
class SDLC_Context {
private :
    int status[10];
    /*用于生成id,使id不重复 */
    bool shouldRepatint;
    int cid;
    int width;
    int height;
    SDL_Surface *surface;
    SDL_Window *window;
    SDLC_Component *components;
    SDLC_Component *curCmp;
    SDLC_Component *curMvCmp;
    SDLC_Component *focusCmp;
    UpdateBg updateBg;
    HandleFun onhandle;
    StrickHandler strickHandler;
    int interval;
    int intervalc;
public:
    int generateId();
    bool fliterEvent(const SDL_Event& event);
    bool dispatch(const SDL_Event& event);
    void update();

    SDLC_Component* addComponent(SDLC_Component *component);
    SDLC_Component *findById(int id);
    SDLC_Component *removeById(int id);
    void setListener(HandleFun handler);
    void setListener(UpdateBg handler);
    void setInterval(int i,StrickHandler h);

    SDLC_Context(SDL_Window *w);
    void notifyUpdate();
    void updateWindow();

    void strick();
    friend class SDLC_Component;
};

#endif
