/***
 * Timer
 * 
 * Handles a specific instance
 * of a timer.
 * 
 * Author: Ben Gavin
 * Date: 2021-01-25
 ***/

#ifndef _timer_h
#define _timer_h

#include <Wire.h>
#include <stdint.h>

class TimerInstance
{
private:
    uint32_t _totalMilliseconds = 0;
    uint32_t _elapsedMilliseconds = 0;
    uint64_t _lastMillis = 0;
    bool _started = false;
    bool _finished = false;

    void deserialize(uint64_t data)
    {
        _totalMilliseconds = (uint32_t)data & 0xFFFFFFFF;
        _elapsedMilliseconds = (uint32_t)(data >> 32) & 0xFFFFFFFF;
        if (_elapsedMilliseconds > 0) // timer was started
        {
            _lastMillis = System.millis();
        }
    }

public:
    TimerInstance(uint8_t hours, uint8_t minutes) : _totalMilliseconds((hours * 60 + minutes) * 1000){};
    TimerInstance(uint64_t serializedData)
    {
        deserialize(serializedData);
    };

    void start(uint64_t currentMillisecond);
    void tick(uint64_t currentMillisecond);
    inline uint64_t serialize() { return (_elapsedMilliseconds << 16) + _totalMilliseconds; };

    void add_hours(uint8_t hours);
    void add_minutes(uint8_t minutes);

    uint8_t hours_left();
    uint8_t minutes_left();
    uint8_t seconds_left();

    inline bool is_started() { return _started; };
    inline bool is_finished() { return _finished; };
};

#endif
