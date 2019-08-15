#include"../SDLC_Component.h"
#include"AnimationTest.h"
#include"iostream"
#include<SDL2/SDL_image.h>
#include"../SDLC_Context.h"
void animation(SDLC_Component *cmp) {
    AnimationTest * p = (AnimationTest *)cmp;
    p->cur ++;
    p->cur %= 9;
    cmp->_context()->notifyUpdate();
}

void AnimationTest::updateSurface() {
    SDLC_Component::updateSurface();
    if(imgs[cur]) {
        SDL_BlitSurface(imgs[cur],NULL,surface,NULL);
    }
}

AnimationTest::AnimationTest(SDLC_Context *context):SDLC_Component(context,0,0,100,100,0x00000000),cur(0) {
    for(int i = 0; i< 9; i++) {
        std::string filename("imgs/Character");
        filename+=((char)('0'+i+1));
        filename+=".png";
        imgs[i] = IMG_Load(filename.c_str());
        if(!imgs[i]) std::cout<<SDL_GetError()<<std::endl;
    }
    SDLC_Component::setInterval(10,animation);
}
