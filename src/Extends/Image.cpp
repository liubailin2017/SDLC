#include "Image.h"
#include "SDL2/SDL_image.h"

#include"iostream"
void Image::ondraw(SDL_Surface* surface) {
}

void Image::updateSurface() { 
    setSize(200,200);
    SDLC_Component::updateSurface();

    if(img) {
        SDL_BlitScaled(img,NULL,surface,NULL);
    }
}

void Image::load(char name[]) {
    img = IMG_Load(name);
    if(!img) {
       std::cout << IMG_GetError() << std::endl;
       return;
    }
    SDL_SetSurfaceBlendMode(img,SDL_BLENDMODE_BLEND);
    this->setSize(img->w,img->h);
}


Image::Image(SDLC_Context *context):Image(context,0,0) { }
Image::Image(SDLC_Context *context,int w,int d):Image(context,0,0,w,d){}
Image::Image(SDLC_Context *context,int x,int y,int w,int d):Image(context,x,y,w,d,0x00000000){}
Image::Image(SDLC_Context *context,int x,int y,int w,int d,Uint32 bg):SDLC_Component(context,x,y,w,d,bg){};
