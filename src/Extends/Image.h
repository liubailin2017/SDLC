#include "../SDLC_Component.h"
#include "string"
class Image : public SDLC_Component
{
private:
  SDL_Surface *img;
public:

    virtual void ondraw(SDL_Surface* surface);
    virtual void updateSurface();
    Image(SDLC_Context *context);
    Image(SDLC_Context *context,int w,int d);
    Image(SDLC_Context *context,int x,int y,int w,int d);
    Image(SDLC_Context *context,int x,int y,int w,int d,Uint32 bg);
    
    void load(char name[]);
};
