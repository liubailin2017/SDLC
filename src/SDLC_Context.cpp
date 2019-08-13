#include "SDLC_Context.h"
#include"SDLC_Component.h"
#include"SDLC_log.h"

bool isContain(int x ,int y,int rx,int ry, int rw,int rh) { 
    if(x > rx && x < rx + rw && y > ry && y < ry + rh) {
        return true;
    }else {
        return false;
    }
}

bool SDLC_Context::dispatch(const SDL_Event& event) {
    switch (event.type)
    {
        case    SDL_MOUSEBUTTONUP:
                if(curMvCmp) {
                    curMvCmp = NULL;
                    return true;
                }
                if(components && components->dispatchMouseButton(event)) {
                    return true;
                }
                break;
        case    SDL_MOUSEBUTTONDOWN:
                if(components && components->dispatchMouseButton(event)) {
                    return true;
                }
                break;

        case    SDL_MOUSEMOTION:
                if(curMvCmp) {
                    int x,y;
                    x = (status[2] + event.motion.x - status[0]);
                    y = (status[3] + event.motion.y - status[1]);
                    SDLC_Component *prn = curMvCmp->header()->parent;
                    if(prn) {
                        int pabx = prn->abx();
                        int paby = prn->aby();
                        if(event.motion.x < pabx) {
                            x =  (status[2] + pabx - status[0]);
                        }
                        if(event.motion.x > pabx + prn->width) {
                            x =  (status[2] + (pabx + prn->width) - status[0]);
                        }
                        if(event.motion.y < paby) {
                            y =  (status[3] + paby - status[1]);
                        }
                        if(event.motion.y > paby + prn->height) {
                            y =  (status[3] + (paby + prn->height) - status[1]);
                        }
                    }
                    curMvCmp->setPostion(x,y);
                    return true;
                }
                if(components && components->dispatchMouseMotion(event)) {
                    return true;
                }else {
                    if(curCmp) {
                        curCmp->outHandler(curCmp);
                        curCmp = NULL;
                    }
                }
                break;
        default:
                break;
    }

    if(onhandle) {
        return onhandle(event,this);
    }

    return false;
}


int SDLC_Context::generateId() {
    return cid++;
}

SDLC_Component *SDLC_Context::addComponent(SDLC_Component *component) {
        if(!component) return NULL;
        if(component ->id) {
            SDLC_LOG_.log(_2C "The component have consisted in context:");
            SDLC_LOG_.log(component->id);
            SDLC_LOG_.notice("");
            return NULL;
        }
        
        component->id = SDLC_Context::generateId();
        if(components) {
            SDLC_Component *node = components->rear();
            node->setbrother(component);
        }else {
            component->prebrother = NULL;
            component->parent = NULL;
            components = component;
        }
        return component;
}

SDLC_Component *SDLC_Context::findById(int id) {
    SDLC_Component *tmp = components;
    SDLC_Component *result = NULL;
    while(tmp) {
        if( (result = tmp->findById(id) )){
            return result;
        };
        tmp = tmp->brother;
    }
    return result;
}

SDLC_Component* SDLC_Context::removeById(int id) {
    SDLC_Component *tmp = findById(id);
    if(tmp == NULL) return NULL;

    if(tmp->prebrother) {
        tmp->prebrother->setbrother(tmp->brother);
    }else {
        if(tmp->parent) {
            tmp->parent->setchild(tmp->brother);
        }else {
            components = tmp->brother;
            if(tmp->brother) {
                tmp -> brother ->parent = NULL;
                tmp -> brother->prebrother = NULL;
            }
            tmp->brother = NULL;
            tmp->parent = NULL;
            tmp->prebrother = NULL;
        }
    }
    tmp->parent = NULL;
    tmp -> brother = NULL;
    tmp->prebrother = NULL;
    tmp->id = 0;
    return tmp;
}

void SDLC_Context::setListener(HandleFun handler) {
    onhandle = handler;
}

SDLC_Context::SDLC_Context(SDL_Window *w) :
                                        cid(1),window(w),
                                        components(NULL),curCmp(NULL),curMvCmp(NULL),
                                        onhandle(NULL)
                                         {
        if(!(surface = SDL_GetWindowSurface(w))) {
            SDLC_LOG_.notice(_2C "Construct of SDLC_Context have a err");
        };
        
        if(surface) {
           width = surface->w;
           height = surface->h; 
        }else
        {
            width = 0;
            height = 0;
        }
        
}
#include<string.h>
void SDLC_Context::updateWindow() {
    memset(surface->pixels,0,surface->h*surface->pitch);
    SDLC_Component *tmp = this->components;
    while(tmp) {
        tmp->display();
        tmp = tmp->brother;
    }
    SDL_UpdateWindowSurface(window);
}
