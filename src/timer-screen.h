/***
 * Timer Screen Definition
 * 
 * Author: Ben Gavin
 * Date: 2021-01-25
 ***/
#ifndef _timer_screen_h
#define _timer_screen_h

#include <Adafruit_GFX.h>
#include "timer-manager.h"

typedef enum
{
    BUTTON_1,
    BUTTON_2,
    BUTTON_3
} SCREEN_BUTTON;

class TimerScreen
{
protected:
    TimerManager *_manager;

public:
    TimerScreen(TimerManager *manager) : _manager(manager){};
    virtual void render(Adafruit_GFX *output);
    virtual void *button_pressed(SCREEN_BUTTON which);
};

#endif
