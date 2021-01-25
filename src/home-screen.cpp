#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeMono9pt7b.h>

#include "home-screen.h"
#include "display-helpers.h"

void* HomeScreen::button_pressed(SCREEN_BUTTON which)
{
    switch (which)
    {
        case BUTTON_1:
            if (timerCount > 1) 
            {
                uint8_t newTimerValue = ++currentTimer;
                if (newTimerValue > timerCount) { newTimerValue = 1; }
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

void HomeScreen::render(Adafruit_GFX* output)
{
    if (timerCount > 1) 
    {
        gfx_draw_next_button(output, GRID_BOX_TOP(1), GRID_BOX_LEFT(1));
    }

    if (timerCount < 10)
    {
        gfx_draw_add_button(output, GRID_BOX_TOP(2), GRID_BOX_LEFT(1));
    }

    if (currentTimer > 0)
    {
        gfx_draw_select_button(output, GRID_BOX_TOP(3), GRID_BOX_LEFT(1));
    }

    // TODO: Draw actual timers
    output->setCursor(GRID_BOX_LEFT(2), GRID_BOX_TOP(2));
    output->setFont(&FreeMono9pt7b);
    output->setTextSize(1);
    output->setTextColor(SH110X_WHITE);
    if (timerCount <= 0)
    {
        output->printf("No Timers");
    }
    else
    {
        output->printf("Timer %i", currentTimer);
    }
}