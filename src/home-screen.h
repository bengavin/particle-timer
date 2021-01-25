#ifndef _home_screen_h
#define _home_screen_h

#include <Adafruit_GFX.h>
#include "timer-screen.h"

class HomeScreen : public TimerScreen 
{
    private:
        uint8_t timerCount = 0;
        uint8_t currentTimer = 0;

    public:
        void* button_pressed(SCREEN_BUTTON which);
        void render(Adafruit_GFX* output);
};

#endif