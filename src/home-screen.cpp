#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/Org_01.h>

#include "home-screen.h"
#include "display-helpers.h"

void *HomeScreen::button_pressed(SCREEN_BUTTON which)
{
    switch (which)
    {
    case BUTTON_1:
        if (timerCount > 1)
        {
            uint8_t newTimerValue = ++currentTimer;
            if (newTimerValue > timerCount)
            {
                newTimerValue = 1;
            }
            currentTimer = newTimerValue;
            Serial.printlnf("Cycle to next timer: %i", currentTimer);
        }
        break;

    case BUTTON_2:
        timerCount++;
        currentTimer = timerCount;
        Serial.println("Adding New timer");
        break;

    case BUTTON_3:
        Serial.printlnf("Go to selected timer: %i", currentTimer);
        break;

    default:
        Serial.println("Unsupported command");
        break;
    }

    return NULL;
}

void HomeScreen::render(Adafruit_GFX *output)
{
    TimerInstance *currentTimer = _manager->get_current_timer();

    if (_manager->has_next_timer())
    {
        gfx_draw_next_button(output, GRID_BOX_TOP(1), GRID_BOX_LEFT(1));
    }

    if (_manager->can_add_timer())
    {
        gfx_draw_add_button(output, GRID_BOX_TOP(2), GRID_BOX_LEFT(1));
    }

    if (currentTimer != NULL)
    {
        gfx_draw_select_button(output, GRID_BOX_TOP(3), GRID_BOX_LEFT(1));
        output->setCursor(GRID_BOX_LEFT(2), GRID_BOX_TOP(2));
        output->setFont(&FreeMono9pt7b);
        output->setTextSize(1);
        output->setTextColor(SH110X_WHITE);
        output->printf("%02i:%02i", currentTimer->hours_left(), currentTimer->minutes_left());

        output->setFont(&Org_01);
        output->printlnf(":%02i", currentTimer->seconds_left());

        if (currentTimer->is_finished())
        {
            output->setCursor(GRID_BOX_LEFT(2), GRID_BOX_TOP(3));
            output->setFont(&FreeMono9pt7b);
            output->println("FINISHED!");
        }
    }
    else
    {
        output->printf("No Timers");
    }
}