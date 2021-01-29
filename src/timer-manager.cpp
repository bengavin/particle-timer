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
#include <fcntl.h>

#include "timer-manager.h"
#include "timer-instance.h"

TimerManager::TimerManager(uint64_t currentMillis)
{
    // Clear the timer instance pointer memory
    memset(_timers, 0, sizeof(_timers));

    // attempt to load any existing timers
    load_timers();
    update(currentMillis);
}

void TimerManager::load_timers()
{
    int fd = open("/Config/timer.config", O_RDONLY);
    if (fd != -1)
    {
        // file format:
        // [# of timers][timer_data(n)]
        // (uint8_t)(uint64_t)
        uint8_t buffer[8]; // accommodate a 64-bit read
        int bytesRead = read(fd, &buffer[0], 1);
        if (bytesRead > 0)
        {
            uint8_t timerIdx = 0;
            for (uint8_t toRead = buffer[0]; toRead > 0 && timerIdx < MAX_TIMERS; toRead--)
            {
                bytesRead = read(fd, &buffer[0], sizeof(buffer));
                if (bytesRead <= 0)
                {
                    break;
                }
                if (bytesRead == sizeof(buffer))
                {
                    _timers[timerIdx++] = new TimerInstance((uint64_t)buffer[0]);
                }
            }
        }
        close(fd);
    }
}

void TimerManager::save_timers()
{
    int fd = open("/Config/timer.config", O_RDWR | O_TRUNC | O_CREAT);
    if (fd != -1)
    {
        // file format:
        // [# of timers][timer_data(n)]
        // (uint8_t)(uint64_t)...
        uint8_t timerCount = 0;

        // Jump past the timer count first
        lseek(fd, 1, SEEK_SET);
        for (uint8_t idx = 0; idx < MAX_TIMERS; idx++)
        {
            // Don't worry about saving finished timers
            if (_timers[idx] != NULL && !_timers[idx]->is_finished())
            {
                uint64_t timerData = _timers[idx]->serialize();
                int bytesWritten = write(fd, &timerData, sizeof(timerData));
                if (bytesWritten > 0)
                {
                    timerCount++;
                }
            }
        }

        // Now, go back and set the number of timers we've saved
        lseek(fd, 0, SEEK_SET);
        write(fd, &timerCount, sizeof(timerCount));
        close(fd);
    }
}

bool TimerManager::can_add_timer()
{
    // TODO: make this more performant as needed
    for (uint8_t idx = 0; idx < MAX_TIMERS; idx++)
    {
        if (_timers[idx] == NULL)
        {
            return true;
        }
    }

    return false;
}

bool TimerManager::has_next_timer()
{
    for (uint8_t idx = 0; idx < MAX_TIMERS; idx++)
    {
        if (_timers[idx] != NULL && idx != _currentTimerIndex)
        {
            return true;
        }
    }

    return false;
}

TimerInstance *TimerManager::get_current_timer()
{
    return _timers[_currentTimerIndex];
}

TimerInstance *TimerManager::get_next_timer()
{
    // search forward, then wrap around
    uint8_t candidateIndex = (_currentTimerIndex + 1) % MAX_TIMERS;
    while (candidateIndex != _currentTimerIndex)
    {
        if (_timers[candidateIndex] != NULL)
        {
            _currentTimerIndex = candidateIndex;
            return _timers[candidateIndex];
        }

        candidateIndex = (candidateIndex + 1) % MAX_TIMERS;
    }

    return NULL;
}

TimerInstance *TimerManager::add_timer()
{
    for (uint8_t idx = 0; idx < MAX_TIMERS; idx++)
    {
        if (_timers[idx] == NULL)
        {
            _timers[idx] = new TimerInstance(0, 0);
            _currentTimerIndex = idx;
            return _timers[idx];
        }
    }

    return NULL;
}

void TimerManager::update(uint64_t currentMillis)
{
    // We're assuming currentMillis will -always- increase, so we don't
    // need to worry about rollover
    if (currentMillis == _lastMillis)
    {
        // time hasn't changed
        return;
    }

    // Now, update any started timers
    for (uint8_t index = 0; index < MAX_TIMERS; index++)
    {
        TimerInstance *curr = _timers[index];
        if (curr == NULL)
        {
            continue;
        }

        if (curr->is_started())
        {
            curr->tick(currentMillis);
        }
    }
}