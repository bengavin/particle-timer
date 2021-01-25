#include <Wire.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "display-helpers.h"

// 16x16 'play' button outline
uint8_t playBitmap[] PROGMEM = {
  0x18, 0x00,
  0x26, 0x00,
  0x41, 0x00,
  0x40, 0xC0,
  0x40, 0x20,
  0x40, 0x18,
  0x40, 0x04,
  0x40, 0x02,
  0x40, 0x02,
  0x40, 0x04,
  0x40, 0x18,
  0x40, 0x20,
  0x40, 0xC0,
  0x41, 0x00,
  0x26, 0x00,
  0x18, 0x00
};
void gfx_draw_play_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    output->drawBitmap(boxLeft, boxTop, &playBitmap[0], 16, 16, SH110X_WHITE);
}

uint8_t pauseBitmap[] PROGMEM = {
  0x3E, 0x7C,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x22, 0x44,
  0x3E, 0x7C
};
void gfx_draw_pause_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    output->drawBitmap(boxLeft, boxTop, &pauseBitmap[0], 16, 16, SH110X_WHITE);
}

void gfx_draw_stop_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // Stop
    output->drawRect(boxLeft + 1, boxTop + 1, 14, 14, SH110X_WHITE);
}

void gfx_draw_add_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // Plus
    output->drawFastHLine(boxLeft+1, boxTop+7, 14, SH110X_WHITE);
    output->drawFastHLine(boxLeft+1, boxTop+8, 14, SH110X_WHITE);
    output->drawFastVLine(boxLeft+7, boxTop+1, 14, SH110X_WHITE);
    output->drawFastVLine(boxLeft+8, boxTop+1, 14, SH110X_WHITE);
}

void gfx_draw_up_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // Up
    output->drawLine(boxLeft+1, boxTop+9, boxLeft+7, boxTop+3, SH110X_WHITE);
    output->drawLine(boxLeft+2, boxTop+9, boxLeft+8, boxTop+3, SH110X_WHITE);
    output->drawLine(boxLeft+8, boxTop+3, boxLeft+14, boxTop+9, SH110X_WHITE);
    output->drawLine(boxLeft+7, boxTop+3, boxLeft+13, boxTop+9, SH110X_WHITE);
}

void gfx_draw_down_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // Down
    output->drawLine(boxLeft+1, boxTop+7, boxLeft+7, boxTop+13, SH110X_WHITE);
    output->drawLine(boxLeft+2, boxTop+7, boxLeft+8, boxTop+13, SH110X_WHITE);
    output->drawLine(boxLeft+8, boxTop+13, boxLeft+14, boxTop+7, SH110X_WHITE);
    output->drawLine(boxLeft+7, boxTop+13, boxLeft+13, boxTop+7, SH110X_WHITE);
}

void gfx_draw_select_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // right-arrow
    output->drawFastHLine(boxLeft+1, boxTop+7, 14, SH110X_WHITE);
    output->drawFastHLine(boxLeft+1, boxTop+8, 14, SH110X_WHITE);
    output->drawLine(boxLeft+12, boxTop+4, boxLeft+15, boxTop+7, SH110X_WHITE);
    output->drawLine(boxLeft+12, boxTop+11, boxLeft+15, boxTop+8, SH110X_WHITE);
}

void gfx_draw_back_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // left-arrow
    output->drawFastHLine(boxLeft+1, boxTop+7, 14, SH110X_WHITE);
    output->drawFastHLine(boxLeft+1, boxTop+8, 14, SH110X_WHITE);
    output->drawLine(boxLeft+4, boxTop+4, boxLeft+1, boxTop+7, SH110X_WHITE);
    output->drawLine(boxLeft+4, boxTop+11, boxLeft+1, boxTop+8, SH110X_WHITE);
}

void gfx_draw_cancel_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    // circle+slash
    output->drawCircle(boxLeft+8, boxTop+8, 7, SH110X_WHITE);
    output->drawLine(boxLeft+4, boxTop+12, boxLeft+12, boxTop+4, SH110X_WHITE);
}

// 16x16 'edit' button outline
uint8_t editBitmap[] PROGMEM = {
    0x00, 0x00,
    0x00, 0x10,
    0x00, 0x38,
    0x00, 0x7C,
    0x00, 0xDE,
    0x01, 0xAC,
    0x03, 0x18,
    0x06, 0x30,
    0x0C, 0x60,
    0x18, 0xC0,
    0x29, 0x80,
    0x27, 0x00,
    0x32, 0x00,
    0x3C, 0x00,
    0x00, 0x00,
    0x00, 0x00,
};
void gfx_draw_edit_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    output->drawBitmap(boxLeft, boxTop, &editBitmap[0], 16, 16, SH110X_WHITE);
}

// 16x16 'reset' button outline
uint8_t resetBitmap[] PROGMEM = {
    0x00, 0x00,
    0x07, 0xC0,
    0x48, 0x30,
    0x50, 0x08,
    0x60, 0x04,
    0x78, 0x04,
    0x00, 0x02,
    0x00, 0x02,
    0x40, 0x02,
    0x40, 0x02,
    0x20, 0x04,
    0x20, 0x04,
    0x10, 0x08,
    0x0C, 0x30,
    0x03, 0xC0,
    0x00, 0x00,
};
void gfx_draw_reset_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    output->drawBitmap(boxLeft, boxTop, &resetBitmap[0], 16, 16, SH110X_WHITE);
}

// 'Next' or 'Cycle' button (NOTE: only a 8x16 bitmap for mem savings)
uint8_t nextBitmap[] PROGMEM = {
    0x3F, 0xF0,
    0x3F, 0xF8,
    0x00, 0x18,
    0x00, 0x18,
    0x00, 0x5A,
    0x00, 0x5A,
    0x00, 0x3C,
    0x00, 0x18,
};
void gfx_draw_next_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft)
{
    output->drawBitmap(boxLeft, boxTop+4, &nextBitmap[0], 16, 8, SH110X_WHITE);
}
