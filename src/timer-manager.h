/***
 * Timer Manager
 * 
 * Handles -managing- the active timers in the system
 * the timer logic is handled in the actual timer
 * implementation class(es)
 * 
 * Author: Ben Gavin
 * Date: 2021-01-25
 ***/
#ifndef __timer_manager_h
#define __timer_manager_h

#include <stdlib.h>
#include "timer-instance.h"

#define MAX_TIMERS 10

class TimerManager
{
private:
    TimerInstance *_timers[MAX_TIMERS];
    uint8_t _currentTimerIndex;
    uint64_t _lastMillis = 0;

public:
    TimerManager(uint64_t currentMillis);

    TimerInstance *add_timer();
    TimerInstance *get_current_timer();
    TimerInstance *get_next_timer();

    bool has_next_timer();
    bool can_add_timer();

    void update(uint64_t currentMillis);
    void save_timers();
    void load_timers();
};

#endif
