#ifndef _h_SDLC_Component
#define _h_SDLC_Component
#include<SDL2/SDL.h>
class SDLC_Component;
class SDLC_Context;

#include"SDLC_Event.h"

class SDLC_Component
{
protected:
    int id;
    int x;
    int y;
    int width;
    int height;
    bool isvisible;
    int upLock;
    SDL_Surface *surface;

    SDLC_Context *context;

    SDLC_Component *brother;
    SDLC_Component *prebrother;

    SDLC_Component *child;
    SDLC_Component *parent;

    Handler mouseButtonHandler;
    OutHandler outHandler;
    InHandler inHandler;
    StrickHandler strickHandler;
    Uint32 bgcolor;
    bool _movable;

    int intervalc;
    int interval;
    
    bool canRaise;

public:

    bool defaultmouseButtonHandler(const SDL_Event& event,SDLC_Component *cmp);
    void defaultOutHandler(SDLC_Component *cmp);
    void defaultInHandler(SDLC_Component *cmp);
    void defaultStrickHandler(SDLC_Component *cmp);
 
    int abx();
    int aby();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    SDLC_Context* _context();
    SDLC_Component* rear();
    SDLC_Component* header();

    bool movable();
    void setbgcolor(Uint32 bg);
    Uint32 getBgcolor();
    void setMovable(bool v);
    void setRaise(bool v);
    void setInterval(int i,StrickHandler h);
    void setListener(Handler handler);
    void setOutHandler(OutHandler outHandler);
    void setInHandler(InHandler outHandler);

    void strick();
    int getId();
    /* api */
    bool fliterEvent(const SDL_Event& event) ;
    bool dispatch(const SDL_Event& event);
    bool handleEvent(const SDL_Event& event);


    virtual bool visible();
    virtual void setvisible(bool isvisible);

    virtual void setchild(SDLC_Component *cmp);
    virtual void setbrother(SDLC_Component *cmp);
    virtual void addComponent(SDLC_Component *cmp);

    virtual void setPostion(int x,int y);
    virtual void setSize(int width,int height);

//    virtual void ondraw(SDL_Surface* surface);
    virtual void updateSurface();

    void display();
    virtual SDLC_Component *findById(int id);
    virtual SDLC_Component *removeById(int id);

    virtual void raise();

    SDLC_Component(SDLC_Context *context);
    SDLC_Component(SDLC_Context *context,int w,int d);
    SDLC_Component(SDLC_Context *context,int x,int y,int w,int d);
    SDLC_Component(SDLC_Context *context,int x,int y,int w,int d,Uint32 bg);
    
    ~SDLC_Component();
    friend class SDLC_Context;
};

#endif