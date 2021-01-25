#include <Adafruit_GFX.h>
#include "timer-screen.h"
#include "display-helpers.h"

void* TimerScreen::button_pressed(SCREEN_BUTTON which)
{
    // do nothing by default
    Serial.printlnf("%i button pressed", which);
    return NULL;
}

void TimerScreen::render(Adafruit_GFX* output) 
{
    // by default, render our set of buttons
    gfx_draw_play_button(output, GRID_BOX_TOP(1), GRID_BOX_LEFT(1));
    gfx_draw_pause_button(output, GRID_BOX_TOP(2), GRID_BOX_LEFT(1));
    gfx_draw_stop_button(output, GRID_BOX_TOP(3), GRID_BOX_LEFT(1));

    gfx_draw_add_button(output, GRID_BOX_TOP(1), GRID_BOX_LEFT(2));
    gfx_draw_up_button(output, GRID_BOX_TOP(2), GRID_BOX_LEFT(2));
    gfx_draw_down_button(output, GRID_BOX_TOP(3), GRID_BOX_LEFT(2));

    gfx_draw_select_button(output, GRID_BOX_TOP(1), GRID_BOX_LEFT(3));
    gfx_draw_back_button(output, GRID_BOX_TOP(2), GRID_BOX_LEFT(3));
    gfx_draw_cancel_button(output, GRID_BOX_TOP(3), GRID_BOX_LEFT(3));

    gfx_draw_edit_button(output, GRID_BOX_TOP(1), GRID_BOX_LEFT(4));
    gfx_draw_reset_button(output, GRID_BOX_TOP(2), GRID_BOX_LEFT(4));
    gfx_draw_edit_button(output, GRID_BOX_TOP(3), GRID_BOX_LEFT(4));

}