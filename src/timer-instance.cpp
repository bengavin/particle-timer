/***
 * Timer
 * 
 * Handles a specific instance
 * of a timer.
 * 
 * Author: Ben Gavin
 * Date: 2021-01-25
 ***/
#include "timer-instance.h"
#define MAX_HOURS 99
#define MAX_MINUTES 59

#define MINS_TO_MSEC(mins) ((mins)*60 * 1000)
#define HOURS_TO_MSEC(hrs) ((hrs)*MINS_TO_MSEC(60))
#define MSEC_TO_HOURS(ms) ((ms) / HOURS_TO_MSEC(1))
#define MSEC_TO_MINS(ms) (((ms)-HOURS_TO_MSEC(MSEC_TO_HOURS((ms)))) / MINS_TO_MSEC(1))
#define MSEC_TO_SEC(ms) (((ms)-HOURS_TO_MSEC(MSEC_TO_HOURS((ms))) - MINS_TO_MSEC(MSEC_TO_MINS((ms)))) / 1000)

void TimerInstance::add_hours(uint8_t hours)
{
    if (_started)
    {
        return;
    } // can't change a running timer [for now]

    hours = min(hours, MAX_HOURS);
    uint8_t currentHours = hours_left();
    uint8_t newHours = (currentHours + hours) % MAX_HOURS;
    if (currentHours > newHours)
    {
        // Subtract our current number of hours
        _totalMilliseconds -= HOURS_TO_MSEC(currentHours);

        // Add the new number of hours (rollover)
        _totalMilliseconds += HOURS_TO_MSEC(newHours);
    }
    else
    {
        // Just add the number of hours that was requested
        _totalMilliseconds += HOURS_TO_MSEC(hours);
    }
}

void TimerInstance::add_minutes(uint8_t minutes)
{
    if (_started)
    {
        return;
    } // can't change a running timer [for now]

    minutes = min(minutes, MAX_MINUTES);
    uint8_t currentMinutes = minutes_left();
    uint8_t newMinutes = (currentMinutes + minutes) % MAX_MINUTES;
    if (currentMinutes > newMinutes)
    {
        // we had a roll-over, subtract current minutes and add new minutes
        _totalMilliseconds -= MINS_TO_MSEC(currentMinutes);
        _totalMilliseconds += MINS_TO_MSEC(newMinutes);
    }
    else
    {
        // Add the requested number of minutes
        _totalMilliseconds += MINS_TO_MSEC(minutes);
    }
}

uint8_t TimerInstance::hours_left()
{
    return (uint8_t)MSEC_TO_HOURS(_totalMilliseconds - _elapsedMilliseconds);
}

uint8_t TimerInstance::minutes_left()
{
    return (uint8_t)MSEC_TO_MINS(_totalMilliseconds - _elapsedMilliseconds);
}

uint8_t TimerInstance::seconds_left()
{
    return (uint8_t)MSEC_TO_SEC(_totalMilliseconds - _elapsedMilliseconds);
}

void TimerInstance::start(uint64_t currentMillisecond)
{
    _lastMillis = currentMillisecond;
    _started = true;
}

void TimerInstance::tick(uint64_t currentMillis)
{
    if (!_started || _finished)
    {
        // no ticking of a stopped clock
        return;
    }

    if (currentMillis == _lastMillis)
    {
        // nothing to do
        return;
    }

    uint64_t millisDif = currentMillis - _lastMillis;
    _elapsedMilliseconds += millisDif;
    _lastMillis = currentMillis;

    // TODO: actually do something if the timer has expired!!
    if (_elapsedMilliseconds >= _totalMilliseconds)
    {
        _started = false;
        _finished = true;
        _elapsedMilliseconds = _totalMilliseconds;
    }
}