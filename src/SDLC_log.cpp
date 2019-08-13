#include"SDLC_log.h"
#include<iostream>

SDLC_log SDLC_LOG_ ;
SDLC_log::SDLC_log()
{
}

SDLC_log::~SDLC_log()
{
}

void SDLC_log::log(int str) {
    std::cout <<str;
}
void SDLC_log::log(char *str) {
    std::cout <<str;
}

void SDLC_log::notice(char *str) {
    std::cout << "***" << str << "***" <<std::endl;
}

void SDLC_log::msg(char *str) {
    std::cout <<str <<std::endl;
}

