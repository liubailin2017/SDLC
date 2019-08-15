#ifndef _h_SDLC_Event_
#define _h_SDLC_Event_

class SDLC_Component;

typedef bool (*Handler)(const SDL_Event& event,SDLC_Component *cmp);
typedef bool (*OutHandler)(SDLC_Component *cmp);
typedef bool (*InHandler)(SDLC_Component *cmp);
typedef void (*StrickHandler)(SDLC_Component *cmp);
#endif