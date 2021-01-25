/***
 * Display Helper Routines
 * 
 * Author: Ben Gavin
 * Date: 2021-01-18
 ***/
#ifndef _display_helpers_h
#define _display_helpers_h

#include <Adafruit_GFX.h>

#define BOX_GUTTER 4
#define BOX_WIDTH 16
#define BOX_HEIGHT 16
#define GRID_BOX_TOP(row) (row * BOX_GUTTER + (row - 1) * BOX_HEIGHT)
#define GRID_BOX_LEFT(col) (col * BOX_GUTTER + (col - 1) * BOX_WIDTH)

void gfx_draw_play_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_pause_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_stop_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_add_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_up_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_down_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_select_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_back_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_cancel_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_edit_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_reset_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);
void gfx_draw_next_button(Adafruit_GFX* output, uint8_t boxTop, uint8_t boxLeft);

#endif
