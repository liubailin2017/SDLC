#include<SDL2/SDL.h>
#include<iostream>
#include"SDLC_Component.h"
#include"SDLC_Context.h"
#include"SDLC_log.h"

extern bool isContain(int x ,int y,int rx,int ry, int rw,int rh);

bool defaulthandler(const SDL_Event& event,SDLC_Component *cmp) {
//    if(event.type == SDL_MOUSEBUTTONDOWN) {
//         std::cout <<"DOWN id:"<<cmp->getId()<<std::endl;
//    }
//    if(event.type == SDL_MOUSEBUTTONUP) { 
//         std::cout <<"UP id:"<<cmp->getId()<<std::endl;
//    }
//    if(event.type == SDL_MOUSEMOTION) {
//        std::cout << "MOTION ID:"<< cmp->getId() <<std::endl;
//    }
   return true;
}

bool defaultOutHandler(SDLC_Component *cmp) {
    //std::cout << "Out of ID:"<< cmp->getId() <<std::endl;
    return true;
}

void SDLC_Component::ondraw(SDL_Surface* surface) {
 
}

bool SDLC_Component::movable() {
    return _movable;
}

void SDLC_Component::setMovable(bool v) {
    _movable = v;
}

int SDLC_Component::abx() {
    SDLC_Component *head = header();
    if(head -> parent) {
        return head->parent->abx() + x; 
    }else {
        return x;
    }
}

int SDLC_Component::aby() {
    SDLC_Component *head = header();
    if(head -> parent) {
        return head->parent->aby() + y; 
    }else {
        return y;
    }
}
bool  SDLC_Component::dispatchMouseMotion(const SDL_Event& event) {
    if(brother) {
        if(brother -> dispatchMouseMotion(event)) {
            return true;
        }
    }

    int bx = event.motion.x,by = event.motion.y;
    int tx = abx(),ty = aby();

    if(child ) {
        if( isContain(bx,by,tx,ty,width,height)) {
            if(child -> dispatchMouseMotion(event)) {
                return true;
            }
        }
    }

    if(handleEvent(event)) {
        return true;
    }
    return false;
}

bool SDLC_Component::dispatchMouseButton(const SDL_Event& event) {

    if(brother) {
        if(brother -> dispatchMouseButton(event)) {
            return true;
        }
    }

    int bx = event.button.x,by = event.button.y;
    int tx = abx(),ty = aby();

    if(child ) {
        if( isContain(bx,by,tx,ty,width,height) || event.type == SDL_MOUSEBUTTONUP) {
            if(child -> dispatchMouseButton(event)) {
                return true;
            }
        }
    }

    if(handleEvent(event)) {
        return true;
    }

    return false;
}


/*this funtion may have bug */
bool SDLC_Component::fliterEvent(const SDL_Event& event) {
    int bx = 0,by = 0;
    int tx = 0,ty = 0;
    Uint32 *bufp = NULL;

    if(event.type == SDL_MOUSEBUTTONDOWN) {
        bx = event.button.x;
        by = event.button.y;
        tx = abx();
        ty = aby();
        if(isContain(bx,by,tx,ty,width,height)) {
            bufp = (Uint32 *)surface->pixels + (bx-tx) + (by-ty) * surface->pitch/4;
            if(*bufp & 0xff000000) {
                upLock = event.button.button;
                return true;
            }
        }
    }

    if(event.type == SDL_MOUSEBUTTONUP && upLock == event.button.button) {
        upLock = 0;
        return true;
    }

    if(event.type == SDL_MOUSEMOTION ) {
        bx = event.motion.x;
        by = event.motion.y;
        tx = abx();
        ty = aby();
        if(isContain(bx,by,tx,ty,width,height)) {
            bufp = (Uint32 *)surface->pixels + (bx-tx) + (by-ty) * surface->pitch/4;
            if(*bufp & 0xff000000) {
                upLock = event.button.button;
                return true;
            }
        }
    }

    return false;
}

bool SDLC_Component::handleEvent(const SDL_Event& event) {
    bool result = false;

    if(fliterEvent(event)) {

        if(event.type == SDL_MOUSEMOTION) {
            if(context->curCmp) {
                if(context->curCmp != this) {
                    OutHandler h =  context->curCmp -> outHandler;
                    if(h) { h(context->curCmp); }
                }
            }
            context ->curCmp = this;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(_movable){
                context->curMvCmp = this;
                context->status[0] = event.button.x;
                context->status[1] = event.button.y;
                context->status[2] = x;
                context->status[3] = y;
            }
        }

        if(mouseButtonHandler && mouseButtonHandler(event,this)) {
            result = true;
        }

    }

    return result;
}

void SDLC_Component::setListener(OutHandler handler) {
    SDLC_Component::outHandler = handler;
}

void SDLC_Component::setListener(Handler handler) {
    SDLC_Component::mouseButtonHandler = handler;
}

void SDLC_Component::display() {
    updateSurface();
    ondraw(surface);
    SDLC_Component *tmp = this->child;
    while(tmp) {
        tmp->display();
        tmp = tmp->brother;
    }

    SDL_Rect ps = {x,y,width,height};
    if(isvisible){

        SDL_Surface* dest; 
        SDLC_Component *parent_ = header()->parent;
        if(parent_){
            dest = parent_->surface;
        }else {
            dest = context->surface;
        }
        SDL_BlitSurface(surface,NULL,dest,&ps);
    }
    else {
        return ;
    }

}

SDLC_Component* SDLC_Component::rear() {
    SDLC_Component *tmp = this;
    while (tmp->brother)
    {
        tmp = tmp -> brother;
    }
    return tmp;
}

SDLC_Component* SDLC_Component::header()
{
    SDLC_Component *tmp = this;
    while (tmp->prebrother)
    {
        tmp = tmp ->prebrother;
    }
    return tmp;
}

static int    rmask = 0x000000ff;
static int    gmask = 0x0000ff00;
static int    bmask = 0x00ff0000;
static int    amask = 0xff000000;

void SDLC_Component::updateSurface() {
    if(SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
    }
    for(int i = 0; i< surface->w*surface->h; i++) {
        *((Uint32*)(surface->pixels)+i) = bgcolor;
    }
    if(SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

void SDLC_Component::setPostion(int x,int y) {
    this->x = x;
    this->y = y;
    context->shouldRepatint = true;
}

void SDLC_Component::setSize(int width,int height) {
    SDL_Surface *tmp = surface;
    surface = SDL_CreateRGBSurface(0,width,height,32,rmask,gmask,bmask,amask);
    SDL_SetSurfaceBlendMode(surface,SDL_BLENDMODE_BLEND);
    this->width = width;
    this->height = height;
    context->shouldRepatint = true;
    SDL_FreeSurface(tmp);
}

int SDLC_Component::getId() {
    return id;
}

bool SDLC_Component::visible() {
    return isvisible;
}

void SDLC_Component::setvisible(bool isvisible) {
    this->isvisible = isvisible;
}

void SDLC_Component::addComponent(SDLC_Component *cmp) {
    if(!cmp) return ;
    cmp->id = context->generateId();
    if(child) {
        SDLC_Component *node = child->rear();
        node->setbrother(cmp);
    }else {
        setchild(cmp);
    }
}
    
void SDLC_Component::setchild(SDLC_Component *cmp) {
    if(cmp) {
        cmp->prebrother = NULL;
        cmp->parent = this;
        child = cmp;
    }else {
        child = NULL;
    }
}

void SDLC_Component::setbrother(SDLC_Component *cmp) {
    if(cmp) {
        cmp->parent = NULL;
        cmp->prebrother = this;
        brother = cmp;
    }else {
        brother = NULL;
    }
}

SDLC_Component* SDLC_Component::findById(int id) {
    if(this->id == id) {
        return this;
    }

    SDLC_Component *tmp = this->child;
    SDLC_Component *result = NULL;
    while(tmp) {
        if( ( result = tmp->findById(id) ) ){
            return result;
        };
        tmp = tmp->brother;
    }
    return result;
}

SDLC_Component* SDLC_Component::removeById(int id) {
    SDLC_Component *tmp = findById(id);
    if(tmp == NULL) return NULL;
    if(tmp->prebrother) {
        tmp->prebrother->setchild(tmp->brother);
    }else {
        if(tmp->parent) {
            tmp->parent->setchild(tmp->brother);
        }else {
            tmp = context->removeById(id);
        }
    }
    tmp->id = 0;
    return tmp;
}

SDLC_Component::SDLC_Component(SDLC_Context *context):SDLC_Component(context,0,0) {}
SDLC_Component::SDLC_Component(SDLC_Context *context,int w,int h):SDLC_Component(context,0,0,w,h) {}
SDLC_Component::SDLC_Component(SDLC_Context *context,int x,int y,int w,int h):SDLC_Component(context,x,y,w,h,0xffffffff){}
SDLC_Component::SDLC_Component(SDLC_Context *context,int x,int y,int w,int h,Uint32 bg) :
                                                        id(0),
                                                        x(x),y(y),width(w),height(h),
                                                        isvisible(true),
                                                        upLock(0),
                                                        context(context),
                                                        brother(NULL),prebrother(NULL),
                                                        child(NULL),parent(NULL),
                                                        mouseButtonHandler(defaulthandler),
                                                        outHandler(defaultOutHandler),
                                                        strickHandler(NULL),
                                                        bgcolor(bg),_movable(false),
                                                        intervalc(0),interval(0)
{
    int    rmask = 0x000000ff;
    int    gmask = 0x0000ff00;
    int    bmask = 0x00ff0000;
    int    amask = 0xff000000;
    surface = SDL_CreateRGBSurface(0,width,height,32,rmask,gmask,bmask,amask);
    SDL_SetSurfaceBlendMode(surface,SDL_BLENDMODE_BLEND);

    if(SDL_MUSTLOCK(surface)) {SDL_LockSurface(surface);}
    for(int i = 0; i< surface->w*surface->h; i++) {
        *((Uint32*)(surface->pixels)+i) = bgcolor;
    }
    if(SDL_MUSTLOCK(surface)) {SDL_UnlockSurface(surface);}
}
    
SDLC_Component::~SDLC_Component(){
        if(id) {
            removeById(id);
        }
        if(child) {
            child -> parent = NULL;
        }
        if(brother) {
            brother = prebrother = NULL;
        }
        SDL_FreeSurface(surface);
}


int SDLC_Component::getX() { return x; }
int SDLC_Component::getY() { return y; }
int SDLC_Component::getWidth() { return width; }
int SDLC_Component::getHeight() { return height; }

/**
 * magic  i == i + 1 
 * */
void SDLC_Component::setInterval(int i,StrickHandler h) {
    if(i >= -1) {
        interval = i+1;
        strickHandler = h;
    }
}

void SDLC_Component::strick() {
    SDLC_Component *tmp = this->child;
    while(tmp) {
        tmp->strick();
        tmp = tmp->brother;
    }
    if(interval == 0 || !strickHandler)
        return;
    if(!intervalc) {
        strickHandler(this);
    }
    intervalc += 1;
    intervalc %= interval;
}
