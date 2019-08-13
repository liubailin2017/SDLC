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

    Uint32 bgcolor;
    bool _movable;
public:

    int abx();
    int aby();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    
    SDLC_Component* rear();
    SDLC_Component* header();

    bool movable();
    void setMovable(bool v);
    int getId();
    /* api */
    bool fliterEvent(const SDL_Event& event) ;
    bool dispatchMouseButton(const SDL_Event& event);
    bool dispatchMouseMotion(const SDL_Event& event);
    bool handleEvent(const SDL_Event& event);

    void setListener(Handler handler);
    void setListener(OutHandler outHandler);

    virtual bool visible();
    virtual void setvisible(bool isvisible);

    virtual void setchild(SDLC_Component *cmp);
    virtual void setbrother(SDLC_Component *cmp);
    virtual void addComponent(SDLC_Component *cmp);

    virtual void setPostion(int x,int y);
    virtual void setSize(int width,int height);

    virtual void ondraw(SDL_Surface* surface);
    virtual void updateSurface();
    void display();
    virtual SDLC_Component *findById(int id);
    virtual SDLC_Component *removeById(int id);

    SDLC_Component(SDLC_Context *context);
    SDLC_Component(SDLC_Context *context,int w,int d);
    SDLC_Component(SDLC_Context *context,int x,int y,int w,int d);
    SDLC_Component(SDLC_Context *context,int x,int y,int w,int d,Uint32 bg);
    
    ~SDLC_Component();
    friend class SDLC_Context;
};

#endif